# brainstorm: clean ATG mainline rt naming

## Goal

Remove misleading `rt` shorthand and stale RT-style wording from `code/tracking/atg_reference_mainline.cpp` so the file reads as a direct current-frame ATG bridge instead of a runtime-adapter layer, while keeping behavior unchanged.

## What I already know

* User explicitly does not want `rt` / runtime-style abstractions to keep spreading in this project.
* `code/tracking/atg_reference_mainline.cpp` currently has an uncommitted top comment block containing `rt->gray` / `rt->encoder_total`; `git blame` marks it as `Not Committed Yet`.
* The same file and header use `runtime_t *rt` as function parameter names.
* `runtime_t` itself is an existing cross-layer data holder used by `main.cpp`, `runners.cpp`, `report.cpp`, `assistant.cpp`, and tracking headers. Renaming the type would be a broad refactor and is not necessary to fix this complaint.
* Trellis backend quality guidance says the current differential-drive contract must not mechanically port RT1064 steering-servo semantics into `guide_error`.

## Assumptions (temporary)

* This task should be a naming/comment cleanup only: no tracking behavior, thresholds, ATG globals, control math, or data layout changes.
* Existing `runtime_t` type can remain for now because removing it would touch many layers and create unnecessary risk.

## Open Questions

* Decide whether this task should stop at removing the uncommitted misleading comment, or grow into a separate all-code naming cleanup for `rt` parameter names.

## Requirements (evolving)

* Remove the misleading uncommitted flow comment that uses `rt->gray`.
* Avoid introducing any new runtime adapter, fallback, or extra state.
* Preserve the current ATG frame contract: gray frame + ATG encoder distance in, current `rptsn` selected line out, current-frame `guide_error` computed from selected line.
* Keep the patch small and reviewable.

## Acceptance Criteria (evolving)

* [ ] The uncommitted top flow comment in `code/tracking/atg_reference_mainline.cpp` is removed.
* [ ] `git diff -- code/tracking/atg_reference_mainline.cpp code/tracking/atg_reference_mainline.hpp` shows naming/comment-only changes.
* [ ] `git diff --check -- code/tracking/atg_reference_mainline.cpp code/tracking/atg_reference_mainline.hpp` passes.
* [ ] Minimal build or compile check is run if implementation proceeds.

## Definition of Done

* Tests added/updated only if behavior changes; for naming-only cleanup, compile/diff checks are enough.
* No unrelated dirty files are staged or modified.
* Final response states that `runtime_t` type was intentionally not renamed.

## Out of Scope

* Renaming `runtime_t` globally.
* Reworking `runners.cpp`, `report.cpp`, `assistant.cpp`, or the control API.
* Changing ATG algorithm behavior, thresholds, guide-error math, or fallback behavior.
* Cleaning Trellis spec examples unless the user separately asks for spec hygiene.

## Technical Notes

* Relevant files: `code/tracking/atg_reference_mainline.cpp`, `code/tracking/atg_reference_mainline.hpp`.
* Current dirty worktree has many unrelated modified files; this task must avoid touching them.
* `code/types.hpp` documents `runtime_t` as input image + ATG distance state plus current vision/control state.
* `git blame -L 1,35 -- code/tracking/atg_reference_mainline.cpp` shows the top flow comment is uncommitted.
* `rg -n "\\brt\\b|rt->" code -g'*.cpp' -g'*.hpp' -g'*.c' -g'*.h'` shows `rt` is not local to `atg_reference_mainline.cpp`; it also appears in `runners`, `report`, and `assistant`.

## Feasible Approaches

### Approach A: Delete bad comment only

* How: remove the uncommitted top flow comment block.
* Pros: smallest possible diff; fixes the most visible violation.
* Cons: leaves `runtime_t *rt` parameters in the main file, so the shorthand remains in the code path.

### Approach B: Delete bad comment and rename local parameters to `car`

* How: remove the top flow comment; rename `runtime_t *rt` parameter names in `atg_reference_mainline.cpp/.hpp` to `car`.
* Pros: still local and behavior-neutral; removes `rt->` from the file the user named; `car` is concrete and domain-specific without introducing a new abstraction.
* Cons: low value after global search because `rt` remains in `runners`, `report`, and `assistant`; a single-file rename may create a false sense of cleanup.

### Approach C: Rename `rt` parameter names consistently across the app layer

* How: keep the `runtime_t` type, but rename parameter variables in `runners`, `report`, `assistant`, and tracking to a chosen explicit name.
* Pros: real consistency; removes the shorthand from live app code.
* Cons: broader mechanical diff across diagnostic/control entry files; still no behavior value, so it should be a separate cleanup commit if selected.

### Approach D: Rename `runtime_t` type globally

* How: choose a new type name and update all call sites.
* Pros: removes the root type name.
* Cons: broad cross-layer refactor, high churn, no behavior value for this complaint; likely overengineering.

## Recommendation

Use Approach A for the immediate cleanup. Do not do the single-file `rt -> car` rename because global search shows it is not meaningful in isolation. If `rt` naming is worth fixing, make it a separate all-code mechanical cleanup with no behavior changes.
