# Stage 7 All Tracking File Contract Plan

Updated: 2026-06-06 17:37:30 +0800.

Scope: Stage 7 contract implementation and remaining evidence gaps.

## Why Stage 7 Exists

Stages 1-6 fixed the control-midline owner:

```text
rpts0s/rpts1s
-> rptsc0/rptsc1 or CROSS_IN far candidate
-> build_rptsn()
-> rt->track.mid
-> guide_error
```

That does not mean the whole tracking package is now structurally clean.

The remaining problem is cross-file contract drift:

```text
seed / trace / boundary / cross / ring / zebra / report
still carry older assumptions that predate the selected-candidate midline
contract.
```

Stage 7 starts the full-file straightening pass.

## Global Contract

Use this as the rule for every later patch:

```text
imgproc     owns seed, trace, point-list primitives, and low-level geometry helpers.
boundary    owns boundary point interpretation and corner/straight geometry.
cross       owns cross state, farline points, and cross track_type; it does not own final midline.
ring        owns ring state and detection/state-continuity boundary edits; it does not own final midline.
element     owns element priority and state-machine dispatch only.
mainline    owns frame-start element action snapshots, selected candidate -> rt->track.mid, and guide_error.
zebra       consumes a scan midline and raw image; it does not define control midline.
assistant   displays already-published runtime state.
report      diagnoses already-published runtime state; it does not define algorithm gates.
control     consumes guide_error and element stop states; it does not reinterpret vision geometry.
```

## Implemented Contract Snapshot

Implemented on 2026-06-06:

```text
boundary:
  l_found    = front-segment single-side L candidate exists.
  l_ok       = accepted single-side L for ring/zebra/crop consumers.
  l_pair_ok  = strict double-L pair passed; cross entry consumes this, not l_ok.

cross:
  NONE -> BEGIN and BEGIN -> IN remain strict double-L paths.
  No weak cross entry is implemented without replay / real-car evidence.

ring:
  build_ring_opp_for_detection() is internal detection/state-continuity support.
  ring-edited boundary_t is not rebuilt into current-frame rptsc0/rptsc1.
  mainline remains the only current-frame selected-candidate -> rt->track.mid owner.

zebra:
  mainline builds the scan midline from current rptsc0/rptsc1 candidates.
  zebra_process() only consumes the provided scan midline and raw image.

report/runners:
  observability now reports seed_pair_span, seed_ipm_pair_diag,
  single-side L, strict pair_ok/state/width, element state, mid, guide, reject.
  Removed "complete-looking" pair base/open coordinate fields from runtime reports.
```

## Current File Map

| File | Current role | Contract status | Main problem |
| --- | --- | --- | --- |
| `code/tracking/mainline.cpp` | Frame orchestration and final midline owner | Mostly aligned | Cross/ring action coupling remains deliberate frame-action timing, not a midline ownership leak. |
| `code/tracking/imgproc.cpp/.hpp` | Seed, trace, point-list primitives, candidate offset, `build_rptsn()` | Aligned enough | Seed pair span is computed on demand; border seed and trace margin tuning are separate behavior questions. |
| `code/tracking/boundary.cpp/.hpp` | Boundary point interpretation and L/straight geometry | Aligned | Single-side L and strict double-L pair semantics are separated by `l_ok` vs `l_pair_ok`. |
| `code/tracking/cross.cpp/.hpp` | Cross state machine and farline state | Contract clear, behavior still evidence-gated | Strict double-L is the only implemented entry. Weak entry requires replay / real-car proof. |
| `code/tracking/ring.cpp/.hpp` | Ring state machine | Ownership clear | Opposite boundary synthesis is renamed `build_ring_opp_for_detection()` and remains detection/state-continuity only. |
| `code/tracking/element.cpp/.hpp` | Element priority / dispatch | Mostly aligned | Needs clearer action/state-only contract after cross/ring cleanup. |
| `code/tracking/zebra.cpp/.hpp` | Zebra and bottom stop-line detection | Mostly aligned | Verify scan midline source after any cross/ring crop change. |
| `code/app/assistant.cpp/.hpp` | Runtime visualization | Mostly aligned | Red line now uses `rt->track.mid`; keep it display-only. |
| `code/app/report.cpp` | Runtime diagnostics | Aligned enough | Reports explicit validation fields and avoids owning algorithm gates. |
| `code/app/runners.cpp` | Runtime loop / replay diagnostics | Aligned enough | Replay fields are limited to state, strict pair, farline, midline, guide, reject. |
| `code/core/control.cpp/.hpp` | Control consumer | Aligned enough | Do not change during Stage 7 except config tuning after real-car validation. |
| `code/types.hpp` | Runtime state structs | Aligned enough | `seed_pair_t::width` is removed; `boundary_t::l_pair_ok` documents strict double-L separately. |

## Stage 7 Patch Results

### Patch 7A: Seed / Trace / Report Semantics

Purpose:

```text
Make seed explicitly mean "trace start point", not "road width contract".
Make report stop treating seed-pair width as the central geometry truth.
```

Files:

```text
code/types.hpp
code/tracking/imgproc.cpp
code/tracking/imgproc.hpp
code/tracking/mainline.cpp
code/app/report.cpp
```

Implemented source changes:

```text
1. Remove `seed_pair_t::width`.
2. Keep `seed_pair_accepted()` as a diagnostic same-row pair predicate by
   recomputing `right.x - left.x` only when both seeds are present on the same
   row.
3. Stop writing seed width state in `trace_edges()`.
4. Replace report field `seed_width` with `seed_pair_span`, computed only when
   same-row pair acceptance passes.
5. Rename or clarify `inspect_ipm_seed_geometry()` as report-only diagnostic.
   It must not sound like the tracking gate.
```

Do not change in Patch 7A:

```text
seed search algorithm
upward missing-side search
trace border margins
cross/ring state machines
control/PID
assistant protocol
```

Validation:

```bash
rg -n "seed_width|\\.width|seeds.width|seed_pair_t" code
git diff --check -- code/types.hpp code/tracking/imgproc.cpp code/tracking/imgproc.hpp code/tracking/mainline.cpp code/app/report.cpp
bash code/test.sh --host
```

Decision:

```text
Q7A-1 result: replace `seed_width` with `seed_pair_span`.
Reason: this preserves observability while making the semantics explicit.
```

Result:

```text
Implemented.
`seed_pair_t::width` was removed.
`seed_pair_accepted()` recomputes same-row span.
Reports use `seed_pair_span` and `seed_ipm_pair_diag`.
No seed search, trace, cross, ring, zebra, assistant protocol, or control behavior was intentionally changed.
```

### Patch 7B: Cross Entry State Machine

Purpose:

```text
Fix the current turning-into-cross failure mode.
The issue is not that farline trace cannot be produced. It is that cross state
may never reach CROSS_IN because double-L near-corner gates fail first.
```

Files:

```text
code/tracking/cross.cpp
code/tracking/cross.hpp
code/tracking/mainline.cpp only if action/state wiring needs a name cleanup
code/app/report.cpp / code/app/runners.cpp only if extra telemetry is needed
```

Current evidence:

```text
cross_process():
  NONE -> BEGIN only when strict_double_l_ok(left, right).
cross_begin():
  BEGIN -> IN only when both sides still have l_pair_ok and at least one paired L is near.
```

Reference evidence:

```text
RT1064 also uses double L for check_cross() and BEGIN->IN.
However, the current camera angle / 160x120 geometry can make the inner near L
drop during a turning cross entry. That is a current-platform mismatch, not a
farline availability issue.
```

Design direction:

```text
Keep strict double-L as the strongest path.
Add a weaker entry path only when evidence supports it:
  one L near + opposite boundary long/straight + farline stable for N frames
or
  current cross BEGIN with one side missing but farline track_type stable.
```

Do not do:

```text
Do not change solve_cross_mid() so far_l < 0 becomes start=0.
That mixes farline availability with far-L semantic cropping and can make
straight but semantically wrong far lines control the car.
```

Human / hardware action:

```text
Camera angle should be raised first if possible. Seeing farther and slightly
more of the car reduces inner-line and near-L loss at cross entry.
```

Required telemetry before implementation:

```text
cross.state
left.l_found / left.l_ok / left.l_now_index
right.l_found / right.l_ok / right.l_now_index
left.l_pair_ok / right.l_pair_ok
left.l_pair_state / right.l_pair_state
left.now_step / right.now_step
cross.left_far_found / right_far_found
cross.left_l / right_l
cross.track_type
mid.step
reject_reason
```

Evidence-gated decisions:

```text
Q7B-1: Do we require real cross-entry replay frames before coding weak entry?
Recommended: yes.

Q7B-2: If weak entry is added, should it be guarded by farline stability over
multiple frames?
Recommended: yes, at least 2 frames.

Q7B-3: Should camera angle adjustment be tried before weak-entry code?
Recommended: yes, because it fixes seed/L geometry globally.
```

Result:

```text
Strict double-L remains the only implemented cross entry.
The strict gate is named `strict_double_l_ok()` and consumes only `l_pair_ok`.
Single-side `l_ok` is explicitly reserved for ring/zebra/crop consumers.
No weak entry was added because no replay / real-car evidence is available in the repository.
```

### Patch 7C: Ring Ownership And State Contract

Purpose:

```text
Decide whether the ring opposite-boundary helper remains detection-only or is
removed / replaced by RT1064-style side/crop rules.
```

Files:

```text
code/tracking/ring.cpp
code/tracking/ring.hpp
code/tracking/mainline.cpp
code/app/report.cpp / code/app/runners.cpp if telemetry changes are needed
```

Current evidence:

```text
mainline builds rptsc0/rptsc1 before element_process().
ring_process() may edit boundary_t after candidates are already built.
mainline does not rebuild candidates from ring-edited boundary_t.
Therefore build_ring_opp_for_detection() cannot affect current-frame control midline.
```

Decision space before implementation:

```text
C1: keep opposite-boundary synthesis detection-only, document it, and tune ring state gates.
C2: remove opposite-boundary synthesis and align ring with RT1064 side/crop only.
C3: intentionally rebuild candidates after ring edits.
```

Recommendation:

```text
Prefer C1 first. C3 is not reference-aligned and should be avoided unless real
ring telemetry proves the synthesized boundary is needed for control.
```

Evidence-gated decisions:

```text
Q7C-1: Are current ring failures "state stuck / wrong side" or "control line
too short"?
Need telemetry before deciding.

Q7C-2: Should the opposite-boundary helper be kept for detection continuity only?
Recommended: yes for now.

Q7C-3: Should ring transitions move closer to RT1064 names and side table?
Recommended: yes, but as a behavior-specific patch after telemetry.
```

Result:

```text
Implemented C1.
`build_opp()` was renamed to `build_ring_opp_for_detection()`.
It remains an anonymous-namespace helper used only inside ring_process().
No candidate rebuild was added after ring_process().
No ring state thresholds or transition behavior were changed.

Mainline frame-action naming now makes the timing explicit:
`snapshot_ring_frame_start_action()` captures ring side/crop intent before
`element_process()`, and `ring_frame_start_crop_*` clips only the already-built
`rptsc0/rptsc1` candidates.
```

### Patch 7D: Boundary Corner Semantics

Purpose:

```text
Separate "corner found" from "corner accepted as a paired cross gate".
Cross/ring need different corner semantics.
```

Files:

```text
code/tracking/boundary.cpp
code/tracking/boundary.hpp
code/types.hpp
code/tracking/cross.cpp
code/tracking/ring.cpp
```

Current problem:

```text
boundary_t used to expose l_found and l_ok, and downstream treated l_ok as a
single truth. For cross, strict double-L pair validation is required. For ring,
zebra, and crop logic, a single unpaired L can still be meaningful.
```

Implemented design:

```text
l_found: boundary geometry scan saw a single-side L candidate.
l_ok: accepted front-segment single-side L for ring/zebra/crop consumers.
l_pair_ok: strict double-L pair passed; cross entry consumes this.
```

Evidence-gated item:

```text
Q7D-1: Should weak cross entry use `l_found` or `l_ok` for the visible side?
Recommended: start from `l_ok` plus additional straight/farline guards, because
`l_ok` now means accepted single-side L rather than pair success.
Weak cross remains unimplemented until evidence exists.
```

Result:

```text
Implemented.
`refresh_boundary_corners()` now writes single-side L and strict pair results as
separate stages:
  scan corner -> l_found
  front-consumer gate -> l_ok
  strict pair validation -> l_pair_ok
Double-L pair failure no longer clears single-side `l_ok`.
`cross.cpp` uses `l_pair_ok`.
`ring.cpp`, `mainline.cpp` zebra scan selection, and assistant display continue to use single-side `l_ok`.
```

### Patch 7E: Observability Cleanup

Purpose:

```text
Make reports reveal where the frame failed:
seed, trace, boundary corner, element state, selected candidate, normalized
midline, or control.
```

Files:

```text
code/app/report.cpp
code/app/runners.cpp
code/app/assistant.cpp only if visual overlays need an existing state exposed
```

Likely source changes:

```text
1. Add clearer cross entry telemetry if Patch 7B needs it.
2. Add selected work_track_type and mode fields if they are not already visible.
3. Remove or rename misleading seed-width diagnostics.
4. Keep assistant protocol stable unless user explicitly wants a display field.
```

Validation:

```bash
bash code/test.sh --host
Run one replay sequence and confirm line/reject/cross/ring fields are visible.
```

Result:

```text
Implemented partially.
Report/live/replay output now exposes only validation-relevant fields:
single-side L, strict pair_ok/state/width, cross farline, ring/cross/zebra state,
midline step, guide_error, reject_reason.

No extra observation fields were added for "completeness"; report/runners remain
diagnostic consumers of already-published runtime state.

The repository currently contains only documentation screenshots
(`1270x684` and `1085x390`), while device_load_gray() requires exact RAW_W x
RAW_H input. Therefore no valid offline replay evidence was produced from local
files in this pass.
```

## Things Not To Do In Stage 7

```text
Do not change control PID.
Do not change assistant binary protocol unless explicitly requested.
Do not split files physically.
Do not rename public runtime_t fields before behavior is stable.
Do not treat farline trace visibility as proof that CROSS_IN control should be active.
Do not use seed-pair width as a tracking validity gate.
```

## Remaining Evidence-Gated Work

Do not implement weak cross entry or ring behavior changes until there is
replay / real-car evidence with the new telemetry.

Required next evidence:

```text
1. Cross-entry replay or real-car sequence showing:
   l_found/l_ok/l_pair_ok/pair_state, near L index, farline found/num/L,
   mid.step, reject_reason.
2. Ring sequence showing whether failure is state stuck, wrong side/crop,
   too-short selected candidate, or final midline reject.
3. Zebra confirmation after any future cross/ring crop semantic change.
```

## 2026-06-06 Boundary Closure Update

This update removes the remaining naming ambiguity without changing the
evidence-gated behavior:

```text
boundary.cpp:
  strict_pair_inputs_ready()
  scan corner -> l_found
  consumer-front gate -> l_ok
  strict double-L check -> l_pair_ok

cross.cpp:
  strict_double_l_ok() is the only entry gate.
  BEGIN uses left_strict_l/right_strict_l names.
  weak entry remains absent by design.

mainline.cpp:
  base_candidates_ready replaces normal_ok.
  snapshot_ring_frame_start_action() captures ring decisions before ring edits.
  ring_frame_start_crop_* documents that RUN crop clips current frame candidates.
  build_zebra_scan_midline() documents that mainline owns zebra scan-line choice.
```

Validation:

```text
rg -n "normal_ok|ring_run_crop|snapshot_ring_action|apply_element_crop|build_zebra_mid|pair_check_inputs_ready|left->l_ok && right->l_ok|left\\.l_ok && right\\.l_ok|build_opp\\(" code
  -> no matches

rg -n "l_pair_base_pt|l_pair_open_pt|seed_width|seeds\\.width|IPM_GEOMETRY|build_opp\\(" code
  -> no matches

git diff --check -- changed source files
  -> passed

bash code/test.sh --host
  -> [100%] Built target front_car_mainline
```
