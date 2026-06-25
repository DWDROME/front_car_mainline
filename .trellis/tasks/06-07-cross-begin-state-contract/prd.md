# Tracking Reference Alignment Audit

## Problem

Recent field screenshots/logs show frames with `cross=1` while strict double-L
evidence has already disappeared (`pair=0/0`), sometimes with no usable line or
midline. That means `CROSS_STATE_BEGIN` can stay active after the evidence that
created it is gone, and the current frame may still be classified as a cross
frame.

Later field screenshots and repo history comparison expanded the same debug
thread: after commits around `bdc7b274b8993bccdb78e42456c5728796e4ae47`, straight
tracking can crawl to the opposite side, the car can twist heavily on straights,
and ring can be triggered by weak single-side evidence. The user explicitly
rejects fallback-style fixes and wants reference-version alignment checked
proactively, not only after new screenshots are supplied.

## Scope

In scope:

- Verify and minimally fix the cross BEGIN/IN state contract.
- Keep current-frame control classification based on frame-start element state,
  so a state newly triggered inside `element_process()` does not unexpectedly
  affect the same frame.
- Preserve the existing `CROSS_STATE_IN` farline continuation contract.
- Audit straight-line tracking behavior introduced after the reference baseline,
  especially trace identity crossing to the opposite side and excessive steering
  oscillation.
- Audit ring entrance against the active RT1064 `circle.c::check_circle()`
  flow. Unity CD.cpp `check_ring()` / `Element_Check()` is retained only as an
  old archived comparison source after this correction.
- Compare relevant current code against the reference implementation and record
  evidence for each remaining known issue.
- Add project-local workflow norms for this debugging thread: Trellis must
  coordinate scope/spec/check context, `smart-search-cli` must be used for
  external/current facts, `fast_context_search` must be preferred for unclear
  local semantic discovery when available, and four fixed read-only audit roles
  must be used for critical tracking edits when the runtime allows it.
- Preserve the highest coding rule for this project: tracking C/C++ stays simple
  and direct, with small evidence-backed edits instead of broad abstraction or
  fallback behavior.
- Run the existing host/device checks after any source edit.

Out of scope:

- General seed/trace identity redesign.
- Generic assistant protocol changes outside this repository's local workflow
  and Trellis/spec/check norms.
- Control/PID tuning.
- Any fallback that reuses last-frame midline as a substitute for missing
  current-frame geometry.

## Evidence Anchors

- Current symptom: screenshots/logs show `cross=1` with `pair=0/0`, matching
  stale `CROSS_STATE_BEGIN`.
- Good-ish baseline: `103daa68006145c76383151104207696edf31155`.
- Regression region: `bdc7b274b8993bccdb78e42456c5728796e4ae47` and later
  commits.
- Active ring reference implementation:
  `/mnt/e/longxin/RT1064_Code_ref/SJTU-AuTop-RT1064-Code/Project/CODE/circle.c`.
- Archived old Unity ring comparison:
  `../unity_Simulation/Assets/Plugins/CD.cpp` copied to
  `docs/reference/unity_CD_old.cpp`.
- Existing research: archived task
  `.trellis/tasks/archive/2026-06/06-06-align-midline-pipeline-to-autop/`.

## Acceptance Criteria

- `CROSS_STATE_BEGIN` exits when strict double-L evidence is absent.
- `CROSS_STATE_BEGIN` may remain BEGIN only while strict pair evidence is still
  present but not near enough for `CROSS_STATE_IN`.
- `CROSS_STATE_BEGIN` can still transition to `CROSS_STATE_IN` when near-L
  criteria are satisfied.
- A frame that only entered cross/ring during `element_process()` does not use
  the newly entered element mode for current-frame midline selection.
- Ring entrance follows RT1064 direct single-side L + opposite-straight entry:
  left ring from `left.l_ok && !right.l_ok && right straight`, right ring from
  `!left.l_ok && right.l_ok && left straight`.
- Unity-only `check_ring/AIB/BW/pending/ring_times` is not present in the active
  mainline chain; the retained copy is under `docs/reference/` and excluded from
  `code/CMakeLists.txt`.
- Straight tracking regression candidates are audited against the baseline and
  reference; any confirmed root-cause code issue is fixed, not hidden by
  fallback midline reuse.
- Workflow/spec norms for critical tracking edits are present in `AGENTS.md`,
  `.trellis/spec/quality/embedded-tracking-guidelines.md`, `.trellis/spec/guides/`, and
  the active task check context.
- Every tracking behavior change records a fixed rationale table in the active
  task research note or final handoff before commit: `参考版怎么样`,
  `当前代码差异`, `我修改什么`, `原因`, and `不是兜底的证据`.
- Existing valid diagnostic frames do not newly trigger ring on straight or
  non-ring frames.
- `git diff --check` passes.
- `bash code/test.sh --host` passes.
- `bash code/test.sh` passes.

## Current Open Analysis Addendum

As of the latest no-runtime-change audit, the active unresolved straight-line
question is not same-trace dual hypothesis and not a single-side hard reject.
Those routes are rejected unless real-frame evidence proves a narrower
predicate.

The current strongest implemented behavior changes are:

- ordinary frames must pass a complete forward lookahead publication gate before
  `guide_error` is published;
- frame-start ordinary frames now delay `mid_position/width_base` learning until
  `publish_track_result()` succeeds, so short or backward-lookahead geometry
  cannot teach the next seed-search center;
- frame-start cross/ring frames on the accepted nearline path now delay the
  existing `mid_position` learning until `publish_track_result()` succeeds,
  while `width_base` remains frozen outside ordinary frames and farline-only /
  IPM-rejected paths do not gain new learning;
- `TRACE_IDENTITY_REJECT_IPM_SIDE_CROSS` still returns before any learning;
- diagnostics now preserve frame-start ring state, post-`find_seeds()` seed
  evidence, pre-filter trace steps, candidate crop counts, and selected
  midline output length.

These guards still do not prove single-side identity when no opposite
seed/trace/work-point relation exists. Any stricter single-side identity
predicate requires diagnostic or real-frame evidence first.
