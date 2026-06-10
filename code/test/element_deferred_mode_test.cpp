#include <cstdio>
#include <cstring>

#include "types.hpp"

// Whitebox test: include mainline.cpp so frame_action_t/frame_mode_t stay private.
#include "tracking/mainline.cpp"

namespace
{
void fail(const char *name, int actual, int expected, int *failed)
{
    std::fprintf(stderr, "FAIL: %s actual=%d expected=%d\n", name, actual, expected);
    *failed = 1;
}

void expect_eq(const char *name, int actual, int expected, int *failed)
{
    if(actual != expected)
    {
        fail(name, actual, expected, failed);
    }
}

void init_runtime(runtime_t *rt, int mid_position, int width_base)
{
    std::memset(rt, 0, sizeof(*rt));
    rt->control_center_x = CONTROL_CENTER_X;
    rt->mid_position = mid_position;
    rt->width_base = width_base;
    rt->track.reject_reason = TRACK_REJECT_NONE;
    rt->track.search_update_kind = TRACK_SEARCH_UPDATE_NONE;
    rt->track.search_mid_before = mid_position;
    rt->track.search_mid_after = -1;
    rt->track.width_base_before = width_base;
    rt->track.width_base_after = -1;
}

int run_cross_deferred_contract()
{
    int failed = 0;
    runtime_t rt = {};
    init_runtime(&rt, 70, 52);

    // Newly entered cross does not take over until the next frame snapshot.
    frame_action_t action = {};
    action.cross_state0 = CROSS_STATE_NONE;
    action.ring_kind0 = RING_KIND_NONE;
    action.base_candidates_ready = 1;
    action.ordinary_track_type = TRACK_TYPE_RIGHT;
    rt.cross.state = CROSS_STATE_BEGIN;
    frame_mode_t mode = classify_frame_mode(&rt, &action);
    expect_eq("new cross far deferred", mode.cross_far, 0, &failed);
    expect_eq("new cross near deferred", mode.cross_near, 0, &failed);
    expect_eq("new cross ring inactive", mode.ring_active, 0, &failed);
    expect_eq("new cross ordinary side", mode.work_track_type, TRACK_TYPE_RIGHT, &failed);
    expect_eq("new cross element action", mode.element_action, 0, &failed);

    init_runtime(&rt, 70, 52);
    action = {};
    action.cross_state0 = CROSS_STATE_BEGIN;
    action.ring_kind0 = RING_KIND_NONE;
    action.base_candidates_ready = 1;
    action.ordinary_track_type = TRACK_TYPE_LEFT;
    rt.cross.state = CROSS_STATE_BEGIN;
    mode = classify_frame_mode(&rt, &action);
    expect_eq("begin cross near", mode.cross_near, 1, &failed);
    expect_eq("begin cross side", mode.work_track_type, TRACK_TYPE_LEFT, &failed);
    expect_eq("begin cross element action", mode.element_action, 1, &failed);

    init_runtime(&rt, 70, 52);
    action = {};
    action.cross_state0 = CROSS_STATE_IN;
    action.ring_kind0 = RING_KIND_NONE;
    action.base_candidates_ready = 0;
    action.ordinary_track_type = TRACK_TYPE_RIGHT;
    rt.cross.state = CROSS_STATE_IN;
    rt.cross.track_type = TRACK_TYPE_LEFT;
    mode = classify_frame_mode(&rt, &action);
    expect_eq("in cross far", mode.cross_far, 1, &failed);
    expect_eq("in cross side", mode.work_track_type, TRACK_TYPE_LEFT, &failed);
    expect_eq("in cross element action", mode.element_action, 1, &failed);
    return failed;
}

int run_ring_deferred_contract()
{
    int failed = 0;
    runtime_t rt = {};
    init_runtime(&rt, 70, 52);

    // Newly entered ring does not take over until the next frame snapshot.
    frame_action_t action = {};
    action.cross_state0 = CROSS_STATE_NONE;
    action.ring_kind0 = RING_KIND_NONE;
    action.base_candidates_ready = 1;
    action.ordinary_track_type = TRACK_TYPE_RIGHT;
    rt.ring.kind = RING_KIND_LEFT;
    rt.ring.state = RING_STATE_BEGIN;
    frame_mode_t mode = classify_frame_mode(&rt, &action);
    expect_eq("new ring inactive", mode.ring_active, 0, &failed);
    expect_eq("new ring ordinary side", mode.work_track_type, TRACK_TYPE_RIGHT, &failed);
    expect_eq("new ring element action", mode.element_action, 0, &failed);

    init_runtime(&rt, 70, 52);
    action = {};
    action.cross_state0 = CROSS_STATE_NONE;
    action.ring_kind0 = RING_KIND_LEFT;
    action.ring_state0 = RING_STATE_BEGIN;
    action.base_candidates_ready = 1;
    action.ordinary_track_type = TRACK_TYPE_LEFT;
    rt.ring.kind = RING_KIND_LEFT;
    rt.ring.state = RING_STATE_BEGIN;
    snapshot_ring_frame_start_crop(&rt, &action);
    mode = classify_frame_mode(&rt, &action);
    expect_eq("left ring begin active", mode.ring_active, 1, &failed);
    expect_eq("left ring begin side", mode.work_track_type, TRACK_TYPE_RIGHT, &failed);
    expect_eq("left ring begin element action", mode.element_action, 1, &failed);
    rt.ring.state = RING_STATE_IN;
    mode = classify_frame_mode(&rt, &action);
    expect_eq("left ring begin ignores current state", mode.work_track_type, TRACK_TYPE_RIGHT, &failed);

    init_runtime(&rt, 70, 52);
    action = {};
    action.cross_state0 = CROSS_STATE_NONE;
    action.ring_kind0 = RING_KIND_LEFT;
    action.ring_state0 = RING_STATE_IN;
    action.base_candidates_ready = 1;
    action.ordinary_track_type = TRACK_TYPE_RIGHT;
    rt.ring.kind = RING_KIND_LEFT;
    rt.ring.state = RING_STATE_IN;
    snapshot_ring_frame_start_crop(&rt, &action);
    mode = classify_frame_mode(&rt, &action);
    expect_eq("left ring in active", mode.ring_active, 1, &failed);
    expect_eq("left ring in side", mode.work_track_type, TRACK_TYPE_LEFT, &failed);
    expect_eq("left ring in element action", mode.element_action, 1, &failed);
    return failed;
}

int run_ring_crop_record_contract()
{
    int failed = 0;
    runtime_t rt = {};
    init_runtime(&rt, 70, 52);

    frame_action_t action = {};
    action.cross_state0 = CROSS_STATE_NONE;
    action.ring_kind0 = RING_KIND_LEFT;
    action.ring_state0 = RING_STATE_RUN;
    action.base_candidates_ready = 1;
    action.ordinary_track_type = TRACK_TYPE_LEFT;
    rt.ring.kind = RING_KIND_LEFT;
    rt.ring.state = RING_STATE_IN;
    rt.track.right.l_found = 1;
    rt.track.right.l_ok = 0;
    rt.track.right.l_now_index = 31;
    snapshot_ring_frame_start_crop(&rt, &action);
    frame_mode_t mode = classify_frame_mode(&rt, &action);
    expect_eq("left ring run side", mode.work_track_type, TRACK_TYPE_RIGHT, &failed);
    expect_eq("left ring run crop side", action.ring_frame_start_crop_side, TRACK_TYPE_RIGHT, &failed);
    expect_eq("left ring run crop index", action.ring_frame_start_crop_index, 31, &failed);

    rptsc0_num = 20;
    rptsc1_num = 20;
    rt.track.candidate_crop_side = TRACK_TYPE_NONE;
    rt.track.candidate_crop_index = -1;
    frame_mode_t no_ring_mode = {};
    no_ring_mode.ring_active = 0;
    action.ring_frame_start_crop_side = TRACK_TYPE_RIGHT;
    action.ring_frame_start_crop_index = 7;
    apply_frame_start_element_crop(&rt, &no_ring_mode, &action);
    expect_eq("inactive ring crop side", rt.track.candidate_crop_side, TRACK_TYPE_NONE, &failed);
    expect_eq("inactive ring crop index", rt.track.candidate_crop_index, -1, &failed);
    expect_eq("inactive ring right kept", rptsc1_num, 20, &failed);

    rt.track.candidate_crop_side = TRACK_TYPE_NONE;
    rt.track.candidate_crop_index = -1;
    mode.ring_active = 1;
    apply_frame_start_element_crop(&rt, &mode, &action);
    expect_eq("active ring crop side", rt.track.candidate_crop_side, TRACK_TYPE_RIGHT, &failed);
    expect_eq("active ring crop index", rt.track.candidate_crop_index, 7, &failed);
    expect_eq("active ring right cropped", rptsc1_num, 7, &failed);
    return failed;
}
}

int main()
{
    int failed = 0;
    failed |= run_cross_deferred_contract();
    failed |= run_ring_deferred_contract();
    failed |= run_ring_crop_record_contract();
    if(failed)
    {
        return 1;
    }

    std::puts("element_deferred_mode_test: ok");
    return 0;
}
