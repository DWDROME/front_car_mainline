# Stage 3 Cross IN Review

Updated: 2026-06-06.

Scope: review only. No source edit is required by this review.

## Result

Stage 3 passes.

The current `CROSS_IN` path already follows the intended contract:

```text
rt->cross.left_pts / rt->cross.right_pts farline tail
-> track_leftline() / track_rightline()
-> far_cand
-> build_rptsn(force_begin_id0 = 1)
-> rt->track.mid
```

The old wrappers are gone:

```text
track_leftline_from_start
track_rightline_from_start
```

`git grep` finds no declaration, definition, or call under `code/`.

## Evidence

### CROSS_IN frame classification

`code/tracking/mainline.cpp:204-205`:

```cpp
mode.cross_far =
    (action->cross_state0 == CROSS_STATE_IN && rt->cross.state == CROSS_STATE_IN);
```

`code/tracking/mainline.cpp:263-268`:

```cpp
if(mode->cross_far)
{
    return solve_cross_mid(rt, ref);
}
```

This preserves the intended timing rule: only a frame that started in
`CROSS_STATE_IN` may use farline. Same-frame BEGIN -> IN still remains a near
cross frame.

### No-seed / trace-failed CROSS_IN continuation

`code/tracking/mainline.cpp:753-763`:

```cpp
if(!seed_ok)
{
    if(rt->cross.state != CROSS_STATE_IN)
        reject;
    clear_rpts();
    cross_process(rt);
}
```

`code/tracking/mainline.cpp:767-775`:

```cpp
if(!trace_edges(rt, &use_matrix))
{
    if(rt->cross.state != CROSS_STATE_IN)
        reject;
    clear_rpts();
    cross_process(rt);
}
```

This keeps the reference-aligned special case: `CROSS_IN` may continue via
farline even when ordinary near-line seed/trace is unavailable.

### Farline tail to candidate

`code/tracking/mainline.cpp:412-458` left side:

```cpp
const int cand_num = track_leftline(rt->cross.left_pts + start,
                                    num,
                                    far_cand,
                                    k_track_approx_num,
                                    ROAD_HALF_WIDTH);
return build_rptsn(far_cand, cand_num, ref.x, ref.y, 1, &rt->track.mid);
```

`code/tracking/mainline.cpp:464-498` right side:

```cpp
const int cand_num = track_rightline(rt->cross.right_pts + start,
                                     num,
                                     far_cand,
                                     k_track_approx_num,
                                     ROAD_HALF_WIDTH);
return build_rptsn(far_cand, cand_num, ref.x, ref.y, 1, &rt->track.mid);
```

The `1` argument is the required `force_begin_id0` behavior.

### Candidate and normalization APIs

`code/tracking/imgproc.hpp:125-162` declares only:

```cpp
track_leftline(...)
track_rightline(...)
build_rptsn(..., force_begin_id0, ...)
```

`code/tracking/imgproc.cpp:805-883` implements `track_leftline/rightline` as
1:1 candidate generators.

`code/tracking/imgproc.cpp:890-930` starts `build_rptsn()` and preserves the
`force_begin_id0` branch.

## Checks Run

```bash
git grep -n "track_leftline_from_start\|track_rightline_from_start" -- code || true
```

Result: no output.

Additional source ranges inspected:

```text
code/tracking/mainline.cpp:200-280
code/tracking/mainline.cpp:412-500
code/tracking/mainline.cpp:745-815
code/tracking/imgproc.hpp:125-165
code/tracking/imgproc.cpp:805-930
```

## Decision

No source cleanup before Stage 4.

Step 3 does not need a code commit. It only closes the wrapper-review concern.

The next real decision stage is Stage 4:

```text
ring owner / build_opp() / zebra ownership
```
