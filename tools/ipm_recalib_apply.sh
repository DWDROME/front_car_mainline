#!/bin/bash
set -euo pipefail

ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
SHY_IMAGE_DST="${ROOT}/atg_reference/Project/CODE/shy_Image.c"

MATRIX_SRC="${1:-${ROOT}/.diag/ipm_recalib/ipm_matrix_tuned.txt}"
if [[ "${MATRIX_SRC}" == *.c ]]; then
  MATRIX_DIR="$(cd "$(dirname "${MATRIX_SRC}")" && pwd)"
  MATRIX_SRC="${MATRIX_DIR}/ipm_matrix_tuned.txt"
fi

if [[ ! -f "${MATRIX_SRC}" ]]; then
  echo "ERROR: ipm_matrix_tuned.txt not found: ${MATRIX_SRC}" >&2
  exit 1
fi
if [[ ! -f "${SHY_IMAGE_DST}" ]]; then
  echo "ERROR: ATG shy_Image.c not found: ${SHY_IMAGE_DST}" >&2
  exit 1
fi

python3 - "${MATRIX_SRC}" "${SHY_IMAGE_DST}" <<'PY'
import math
import pathlib
import re
import sys

matrix_path = pathlib.Path(sys.argv[1])
shy_path = pathlib.Path(sys.argv[2])

def read_matrix(path):
    rows = []
    for line in path.read_text(encoding="utf-8").splitlines():
        line = line.strip()
        if not line:
            continue
        vals = [float(x) for x in line.split()]
        if len(vals) != 3:
            raise SystemExit(f"ERROR: expected 3 columns in {path}: {line}")
        rows.append(vals)
    if len(rows) != 3:
        raise SystemExit(f"ERROR: expected 3 rows in {path}, got {len(rows)}")
    return rows

def det3(m):
    return (
        m[0][0] * (m[1][1] * m[2][2] - m[1][2] * m[2][1])
        - m[0][1] * (m[1][0] * m[2][2] - m[1][2] * m[2][0])
        + m[0][2] * (m[1][0] * m[2][1] - m[1][1] * m[2][0])
    )

def inv3(m):
    d = det3(m)
    if abs(d) < 1.0e-12:
        raise SystemExit("ERROR: IPM matrix is singular")
    cof = [
        [
            m[1][1] * m[2][2] - m[1][2] * m[2][1],
            -(m[1][0] * m[2][2] - m[1][2] * m[2][0]),
            m[1][0] * m[2][1] - m[1][1] * m[2][0],
        ],
        [
            -(m[0][1] * m[2][2] - m[0][2] * m[2][1]),
            m[0][0] * m[2][2] - m[0][2] * m[2][0],
            -(m[0][0] * m[2][1] - m[0][1] * m[2][0]),
        ],
        [
            m[0][1] * m[1][2] - m[0][2] * m[1][1],
            -(m[0][0] * m[1][2] - m[0][2] * m[1][0]),
            m[0][0] * m[1][1] - m[0][1] * m[1][0],
        ],
    ]
    return [[cof[c][r] / d for c in range(3)] for r in range(3)]

def normalize(m):
    den = m[2][2]
    if abs(den) < 1.0e-12:
        raise SystemExit("ERROR: IPM matrix bottom-right term is zero")
    return [[v / den for v in row] for row in m]

def to_atg_layout(m):
    # OpenCV matrix maps [x, y, 1] -> [x', y', w].
    # ATG Cal_* functions store coefficients as [y, x, 1] and put x' in row 1, y' in row 0.
    return [
        [m[1][1], m[1][0], m[1][2]],
        [m[0][1], m[0][0], m[0][2]],
        [m[2][1], m[2][0], m[2][2]],
    ]

def fmt(v):
    if abs(v) < 5.0e-10:
        v = 0.0
    return f"{v:.8e}f"

def block(name, comment, matrix):
    lines = [f"float {name}[3][3]={{", f"        //{comment}"]
    for i, row in enumerate(matrix):
        suffix = "," if i < 2 else ""
        lines.append("        {" + ", ".join(fmt(v) for v in row) + "}" + suffix)
    lines.append("};")
    return "\n".join(lines)

raw_to_ipm = normalize(read_matrix(matrix_path))
ipm_to_raw = normalize(inv3(raw_to_ipm))
rot = to_atg_layout(raw_to_ipm)
inv_rot = to_atg_layout(ipm_to_raw)

text = shy_path.read_text(encoding="utf-8")
text, n_rot = re.subn(
    r"float\s+rot\s*\[3\]\s*\[3\]\s*=\s*\{.*?\};",
    block("rot", "透视变换矩阵，由 tools/ipm_generator 生成", rot),
    text,
    count=1,
    flags=re.S,
)
text, n_inv = re.subn(
    r"float\s+inv_rot\s*\[3\]\s*\[3\]\s*=\s*\{.*?\};",
    block("inv_rot", "逆透视变换矩阵，由 tools/ipm_generator 生成", inv_rot),
    text,
    count=1,
    flags=re.S,
)
if n_rot != 1 or n_inv != 1:
    raise SystemExit("ERROR: failed to replace rot/inv_rot in shy_Image.c")
shy_path.write_text(text, encoding="utf-8")
PY

echo "Applied ATG rot/inv_rot from ${MATRIX_SRC} -> ${SHY_IMAGE_DST}"
