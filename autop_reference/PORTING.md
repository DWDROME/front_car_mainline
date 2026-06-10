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
  autop_reference/port/reference_step.c
  autop_reference/port/reference_globals.c

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
