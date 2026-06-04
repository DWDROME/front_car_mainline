#!/bin/bash
set -euo pipefail

cat >&2 <<'MSG'
behavior_equivalence.sh 已退休。

原因：当前主线不再保留 front_car_mainline_legacy 旧路线，也不再用新旧双二进制对比作为通过条件。
回归验证只走当前主链：scripts/test.sh、scripts/straight_baseline_audit.sh、scripts/ipm_geometry_audit.sh。
MSG
exit 2
