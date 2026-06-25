# Non-Reference Retention Plan

Updated: 2026-06-06 11:59:42 +0800.

Scope: brainstorm only. No source implementation in this task.

This file records current pushed changes that are not direct RT1064 reference behavior, but must be preserved or consciously delayed while aligning the midline pipeline.

## Rule

Do not treat "align with RT1064 names" as "delete every local improvement".

The current project is 160x120, has a different assistant display path, has `mid_position` / `width_base`, and has recent fixes for seed loss, element short-line gate, and ring same-frame action. These must be explicit constraints in the refactor.

## Current Non-Reference Changes

| Change | Current evidence | Purpose | RT1064 difference | Refactor handling | First-cut risk |
|---|---|---|---|---|---|
| Missing-side upward seed search | `code/tracking/imgproc.cpp:214-327`, especially `274-300` | If fixed `START_HIGH` finds one side only, search upward for the missing side. This addresses frames where a clear boundary enters higher in the image. | RT1064 `process_image()` uses fixed `begin_y` seed scan at `Project/USER/src/main.c:532-545`; it does not do this multi-row missing-side search. | Preserve as seed acquisition behavior. Do not let mixed-row seeds become an accepted same-row pair. | If rewritten as pair logic, invalid width/row assumptions return. If deleted, known side-entry failures return. |
| `seed_pair_t::width` and pair acceptance | `code/types.hpp:14-21`, `code/tracking/imgproc.cpp:257-263`, `330-345`, `mainline.cpp:131-135` | Same-row raw seed span for conservative pair reporting and `width_base` update. | RT1064 has no ordinary seed-pair width state. | Do not expand this contract. Long term can delete stored `width` and recompute same-row span locally, but not in first midline cut. | Mixing this with `rptsc/rptsn` refactor will create too much unrelated churn. |
| Search center follow and `width_base` | `code/types.hpp:202-206`, `code/tracking/mainline.cpp:424-459`, called at `535-536` | After trace filtering, update next-frame `mid_position`; single-side frames use `width_base / 2` to estimate center. | RT1064 fixed seed start does not keep this runtime search center. | Preserve. It must stay after `trace_edges()` clears failed sides. Later rename can be `update_search_center_after_trace()`. | Moving it before trace reintroduces seed noise poisoning. Resetting it each frame reintroduces curved/side-entry loss. |
| Geometry center vs search center split | `code/tuning.hpp:20-30`, `code/tracking/ring.cpp:172-179`, `code/tracking/zebra.cpp:117-118` | `MID_X` is stable image geometry center; `mid_position` follows seed search. | RT1064 does not have this split because it does not use dynamic `mid_position`. | Preserve. Do not replace `MID_X` with `mid_position` in ring/zebra. | Dynamic center can pollute ring synthetic geometry and zebra threshold split. |
| Element short-midline gate | `code/tracking/mainline.cpp:39-45`, `701-716` | Cross/ring element frames allow `mid_ok >= 3` and skip hard lookahead; ordinary frames stay strict. | RT1064 final stage only requires selected tail `>=3` and clips aim index. | Preserve as reference-aligned behavior. It belongs in the unified final midline stage. | If applied to ordinary road, real no-line frames may not stop. If removed, cross/ring can deadlock on short but valid element lines. |
| Ring current-frame action snapshot | `code/tracking/mainline.cpp:495-587`, `610-670` | Compute ring side/crop from frame-start state before `element_process()` mutates state. | RT1064 `run_circle()` directly sets `track_type` and point counts in one global order, so it does not need this adapter. | Preserve until ring dataflow is rewritten. Name it clearly as frame action. | Reading post-state directly can switch side one frame too early. |
| `ring.cpp::build_opp()` synthetic opposite boundary | `code/tracking/ring.cpp:73-237`, used in `345-360` | During ring IN, synthesize and trace the opposite boundary, then refresh corners. | RT1064 `circle.c` has no `build_opp()`. It only sets `track_type` and sometimes crops `rpts*s_num/rptsc*_num`. | Do not touch in first midline cut. Later stage must decide: keep as project-specific aid, or remove while aligning ring to reference. | Combining this with midline split will mix two hard problems: centerline ownership and ring boundary ownership. |
| Cross farline local improvements | `code/tracking/cross.cpp:13-30`, `158-303`, `377-468` | Scaled farline start, far L validation, old-L reuse, and near-line exit logic. | RT1064 has `cross_farline()` global arrays and simpler L/track_type logic. | Preserve in first cut. Cross IN should only change how farline points become normalized `rt->track.mid`. | Rewriting farline detection while changing midline normalization makes failures impossible to isolate. |
| Assistant red line equals control midline | `code/app/assistant.cpp:204-247`, `310-351` | Red line displays `rt->track.mid` projected back to raw. | RT1064 does not have this assistant protocol. | Preserve display contract. No first-cut algorithm edits needed as long as `rt->track.mid` remains final normalized control line. | If `rt->track.mid` semantics change, assistant display becomes misleading again. |

## Decision

The first source-design task must keep all project-specific behavior above. The only first-cut behavior change should be structural:

```text
track_leftline/rightline:
  side boundary -> candidate centerline only

mainline final stage:
  selected candidate centerline -> fixed start normalization -> rt->track.mid
```

Everything else is either a preserved input condition, a preserved element action, or a later refactor.
