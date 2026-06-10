# IPM Generator

This directory contains the desktop OpenCV IPM calibration generator used by
this repository.

## Build

```bash
cmake -S . -B build
cmake --build build
```

## Run

Run the tool from the project root, or pass an explicit `--out` path. The
default output directory is `output` relative to the current working directory.

Interactive point picking:

```bash
./build/ipm_generator --input path/to/gray_640x360.png --out output
```

Click four points in this exact order:

```text
left-bottom -> right-bottom -> left-top -> right-top
```

Keyboard controls in the OpenCV window:

```text
u       undo last point
r       reset points
enter   accept after four points
space   accept after four points
esc     abort
```

For non-interactive runs, pass points directly:

```bash
./build/ipm_generator \
  --input path/to/gray_640x360.png \
  --points x1,y1,x2,y2,x3,y3,x4,y4 \
  --no-window \
  --out output
```

Point order is still `left-bottom, right-bottom, left-top, right-top`.
Point coordinates must be inside the 640x360 input image.

## Outputs

The output directory contains:

```text
selected_points.json
ipm_matrix_initial.txt
ipm_matrix_tuned.txt
preview_original_points.png
preview_ipm_initial.png
preview_ipm_tuned.png
camera_param.c
```

The generated file is copied directly into the reference-shaped runtime path:

```text
autop_reference/Project/CODE/camera_param.c
```

The generated C symbol contract matches the RT1064 reference naming:

```text
K[3][3]
D[4]
H[3][3]
H_inv[3][3]
mapx[MT9V03X_CSI_H][MT9V03X_CSI_W]
mapy[MT9V03X_CSI_H][MT9V03X_CSI_W]
invx[MT9V03X_CSI_H][MT9V03X_CSI_W]
invy[MT9V03X_CSI_H][MT9V03X_CSI_W]
map_inv()
```

`mapx/mapy` are raw -> IPM tables. Negative values mean that no valid mapping
exists for that raw point. The current calibration tool does not model lens
distortion, so `K/D` are placeholders and `invx/invy` are identity
undistorted-raw -> raw tables; `H/H_inv` carry the homography.

## Current Defaults

The tool reads a `640x360` grayscale calibration image, scales selected points to
the runtime `160x120` coordinate system, and uses this default target rectangle:

```text
left-bottom:  (63, 70)
right-bottom: (97, 70)
left-top:     (63, 30)
right-top:    (97, 30)
```

The tuned result shifts this target rectangle vertically based on the geometric
valid area from the initial transform. White image pixels (`255`) are treated as
normal image content, not as invalid border pixels.
