# Porting Boundary

This branch starts from the current `front_car_mainline` main branch, then
copies the RT1064 reference project source into `autop_reference/Project/`.

The intended shape is:

```text
reference algorithm core:
  Project/CODE/imgproc.c
  Project/CODE/cross.c
  Project/CODE/circle.c
  Project/USER/src/main.c data flow

port boundary:
  UVC gray frame -> reference img_raw
  current static IPM table -> reference mapx/mapy/invx/invy
  current encoder feedback -> reference get_total_encoder()
  reference centerline/error -> current differential control input
  current GPIO/PWM/motor driver -> actuator output
  current report/assistant -> display selected reference state
```

Hard rule:

```text
The reference algorithm chain must continue to use reference globals:
img_raw, mapx/mapy, ipts/rpts/rptsc/rptsn, track_type, cross_type, circle_type.
```

Do not make the algorithm chain depend on:

```text
runtime_t as the primary owner
rt->track as the centerline owner
g_raw_to_ipm_x/y lookups inside algorithm code
guide_error as the internal algorithm product
```

Allowed adaptation:

```text
Fill mapx/mapy from g_raw_to_ipm_x/y once at the port boundary.
Convert the final reference output to the current differential-drive control
input at the final port boundary only.
```

Current status:

```text
The main executable builds through the reference port:
  code/tracking/autop_reference_mainline.cpp
  code/tracking/autop_reference_ipm_bridge.cpp
  autop_reference/port/headfile.h
  autop_reference/port/common.h
  autop_reference/port/encoder_port.h
  autop_reference/port/reference_step.c
  autop_reference/port/reference_globals.c
  autop_reference/port/autop_reference_step.h

Compiled reference algorithm files:
  Project/CODE/imgproc.c
  Project/CODE/cross.c
  Project/CODE/circle.c
  Project/CODE/utils.c
  Project/CODE/flash_param.c

Not compiled from the reference tree:
  Project/USER/src/main.c
  RT1064 peripheral modules
  garage/yroad/apriltag/openart runtime modules
```

`Project/USER/src/main.c` remains the source template for frame order. The port
layer mirrors its line extraction, corner extraction, element check/run,
selected centerline, and normalization flow while keeping the same reference
globals.

The imported `Project/CODE` directory is intentionally trimmed to the algorithm
files above plus headers required by that build. Removed RT1064 peripheral and
optional element modules are represented only where the active cross/circle
chain still needs a contract: encoder constants live in `encoder_port.h`, and
inactive garage/yroad/apriltag/openart enums plus stubs live in
`reference_globals.c`.

## Active Parameters

These values are set at the port boundary in
`autop_reference/port/reference_step.c`. They are deliberately called out here
because they affect thresholding, geometric gates, centerline generation, and
upper-monitor interpretation.

```text
threshold:
  thres = 140
  block_size = 5
  clip_value = 8
  line_blur_kernel = 7

seed / far scan:
  begin_x = 14
  begin_y = 84
  far_x1 = 36
  far_x2 = 119

geometry / control:
  ROAD_HALF_WIDTH = 26
  pixel_per_meter = 52 / ROAD_WIDTH = 115.56
  sample_dist = 3 / pixel_per_meter = 0.02596m
  sample_dist * pixel_per_meter = 3px
  angle_dist = 0.2m
  aim_distance = 0.58m
```

`sample_dist` is tied to the actual 3px point spacing. The reference gates that
use `0.1 / sample_dist`, `0.2 / sample_dist`, `0.4 / sample_dist`, `0.8 /
sample_dist`, and `1.0 / sample_dist` therefore correspond to about 4, 8, 15,
31, and 39 resampled points on this 160x120 IPM scale.

`thres = 140` remains the RT1064 global threshold. The adaptive trace window now
uses `block_size = 5` and `clip_value = 8`; this is a port-side lighting
adaptation and still needs real UVC exposure validation on the car.

## Control Centerline Contract

The RT1064 reference finds the wheel reference point from:

```text
mapx[MT9V03X_CSI_H * 0.78][MT9V03X_CSI_W / 2]
mapy[MT9V03X_CSI_H * 0.78][MT9V03X_CSI_W / 2]
```

The port keeps that contract. On the current generated IPM table the raw wheel
point `(80, 93)` maps to approximately `(88.5, 108.6)`, so reports usually show
the control reference around `(89, 109)`.

`SMARTCAR_CONTROL_CENTER_X` is not the first-choice reference point. It is only
the fallback x used when the IPM lookup is invalid. The default fallback is
`86`, from the current hardware calibration; fallback y is `START_HIGH = 116`.

The final bridge to the current differential-drive controller is still only at
the port boundary:

```text
reference rptsn -> rt->track.mid -> guide_error -> target_yaw -> yaw_cmd
```

The reference algorithm itself does not consume `rt->track` or `guide_error`.

## Upper-Monitor Display Notes

The assistant display has three different coordinate meanings:

```text
yellow / green boundaries:
  raw trace points from the reference line search

red centerline:
  reference control/IPM centerline inverse-mapped back to raw pixels for display

red seed row and seed boxes:
  raw first trace points from the current reference frame;
  fallback row is begin_y = 84, not START_HIGH = 116
```

So a raw-image red centerline that visually leans left at the far end is not by
itself proof that the control centerline is wrong. First compare the numeric
report fields:

```text
control_ref / m0 / ml / guide
```

If `m0` and `ml` are close in IPM/control coordinates and `guide` is small, the
raw overlay bend is more likely caused by inverse-IPM projection, IPM table
calibration, or camera mounting offset. If `ml.x - m0.x` and `guide` are already
large in the report, then the reference-selected line or IPM table should be
debugged before tuning the differential controller.
