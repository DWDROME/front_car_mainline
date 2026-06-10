#include <cstdio>
#include <cstring>

#include "types.hpp"
#include "tracking/ipm_table_generated.hpp"

// Whitebox test: include the owner file so the anonymous search-center learning
// helpers and publish gate are tested without adding production test hooks.
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

void expect_point_eq(const char *name, point_t actual, point_t expected, int *failed)
{
    if(actual.x != expected.x || actual.y != expected.y)
    {
        std::fprintf(stderr,
                     "FAIL: %s actual=(%d,%d) expected=(%d,%d)\n",
                     name,
                     actual.x,
                     actual.y,
                     expected.x,
                     expected.y);
        *failed = 1;
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

void set_seed_pair(runtime_t *rt, int left_x, int right_x)
{
    rt->seed_state = 3;
    rt->seeds.left = {left_x, START_HIGH};
    rt->seeds.right = {right_x, START_HIGH};
    rt->seeds.row = START_HIGH;
}

void set_left_seed(runtime_t *rt, int left_x)
{
    rt->seed_state = 1;
    rt->seeds.left = {left_x, START_HIGH};
    rt->seeds.right = {-1, -1};
    rt->seeds.row = -1;
}

void push_mid_point(midline_t *mid, int idx, int x, int y, int dist)
{
    mid->pts[idx] = {x, y};
    mid->dist[idx] = dist;
    if(mid->step <= idx)
    {
        mid->step = idx + 1;
    }
}

void push_trace_point(trace_t *trace, int x, int y)
{
    if(trace->step >= POINT_MAX)
    {
        return;
    }
    trace->pts[trace->step] = {x, y};
    trace->stop_point = trace->pts[trace->step];
    ++trace->step;
}

void fill_forward_midline(runtime_t *rt)
{
    rt->track.mid = {};
    for(int i = 0; i < 6; ++i)
    {
        push_mid_point(&rt->track.mid,
                       i,
                       CONTROL_CENTER_X,
                       START_HIGH - i * 8,
                       i == 5 ? 36 : i * 7);
    }
}

void fill_short_forward_midline(runtime_t *rt, int step)
{
    rt->track.mid = {};
    for(int i = 0; i < step; ++i)
    {
        push_mid_point(&rt->track.mid,
                       i,
                       CONTROL_CENTER_X,
                       START_HIGH - i * 8,
                       i * 6);
    }
}

void fill_backward_midline(runtime_t *rt)
{
    rt->track.mid = {};
    for(int i = 0; i < 6; ++i)
    {
        push_mid_point(&rt->track.mid,
                       i,
                       CONTROL_CENTER_X,
                       START_HIGH + i * 2,
                       i == 5 ? 36 : i * 7);
    }
}

frame_mode_t make_mode(int element_action)
{
    frame_mode_t mode = {};
    mode.element_action = element_action;
    mode.work_track_type = TRACK_TYPE_RIGHT;
    return mode;
}

int publish_current_midline(runtime_t *rt, int element_action)
{
    const frame_mode_t mode = make_mode(element_action);
    const point_t ref = {CONTROL_CENTER_X, START_HIGH};
    return publish_track_result(rt, &mode, rt->track.mid.step, ref);
}

void init_identity_runtime(runtime_t *rt)
{
    std::memset(rt, 0, sizeof(*rt));
    rt->seed_state = 3;
    rt->seeds.left = {20, START_HIGH};
    rt->seeds.right = {120, START_HIGH};
    rt->seeds.row = START_HIGH;
    rt->left_trace.seed = rt->seeds.left;
    rt->left_trace.left_side = 1;
    rt->right_trace.seed = rt->seeds.right;
    rt->right_trace.left_side = 0;
}

int run_identity_seed_pass_gain_contract()
{
    int failed = 0;
    runtime_t rt = {};
    init_identity_runtime(&rt);
    push_trace_point(&rt.left_trace, 20, START_HIGH);
    push_trace_point(&rt.left_trace, 122, START_HIGH - 1);
    expect_eq("early left pass rejected",
              trace_identity_reject_bits(&rt, 1, 0) & TRACE_IDENTITY_REJECT_LEFT_PASSED_RIGHT_SEED,
              TRACE_IDENTITY_REJECT_LEFT_PASSED_RIGHT_SEED,
              &failed);

    init_identity_runtime(&rt);
    push_trace_point(&rt.left_trace, 20, START_HIGH);
    push_trace_point(&rt.left_trace, 60, START_HIGH - 10);
    push_trace_point(&rt.left_trace, 122, START_HIGH - 20);
    expect_eq("far left pass gain recorded",
              trace_pass_seed_gain(&rt.left_trace, rt.seeds.right.x, 1),
              20,
              &failed);
    expect_eq("far left pass still rejected",
              trace_identity_reject_bits(&rt, 1, 0) & TRACE_IDENTITY_REJECT_LEFT_PASSED_RIGHT_SEED,
              TRACE_IDENTITY_REJECT_LEFT_PASSED_RIGHT_SEED,
              &failed);

    init_identity_runtime(&rt);
    push_trace_point(&rt.right_trace, 120, START_HIGH);
    push_trace_point(&rt.right_trace, 18, START_HIGH - 1);
    expect_eq("early right pass rejected",
              trace_identity_reject_bits(&rt, 0, 1) & TRACE_IDENTITY_REJECT_RIGHT_PASSED_LEFT_SEED,
              TRACE_IDENTITY_REJECT_RIGHT_PASSED_LEFT_SEED,
              &failed);

    init_identity_runtime(&rt);
    push_trace_point(&rt.right_trace, 120, START_HIGH);
    push_trace_point(&rt.right_trace, 80, START_HIGH - 10);
    push_trace_point(&rt.right_trace, 18, START_HIGH - 20);
    expect_eq("far right pass gain recorded",
              trace_pass_seed_gain(&rt.right_trace, rt.seeds.left.x, 0),
              20,
              &failed);
    expect_eq("far right pass still rejected",
              trace_identity_reject_bits(&rt, 0, 1) & TRACE_IDENTITY_REJECT_RIGHT_PASSED_LEFT_SEED,
              TRACE_IDENTITY_REJECT_RIGHT_PASSED_LEFT_SEED,
              &failed);
    return failed;
}

int run_ordinary_pair_learning()
{
    int failed = 0;
    runtime_t rt = {};
    init_runtime(&rt, 70, 52);
    set_seed_pair(&rt, 20, 100);
    fill_forward_midline(&rt);

    expect_eq("ordinary publish", publish_current_midline(&rt, 0), 1, &failed);
    commit_search_center_update(&rt, TRACK_SEARCH_UPDATE_ORDINARY, 1);
    expect_eq("ordinary kind", rt.track.search_update_kind, TRACK_SEARCH_UPDATE_ORDINARY, &failed);
    expect_eq("ordinary mid", rt.mid_position, 60, &failed);
    expect_eq("ordinary width", rt.width_base, 59, &failed);
    expect_eq("ordinary mid diag", rt.track.search_mid_after, 60, &failed);
    expect_eq("ordinary width diag", rt.track.width_base_after, 59, &failed);
    return failed;
}

int run_ordinary_short_reject_no_learning()
{
    int failed = 0;
    runtime_t rt = {};
    init_runtime(&rt, 70, 52);
    set_seed_pair(&rt, 20, 100);
    fill_short_forward_midline(&rt, 6);

    expect_eq("ordinary short reject", publish_current_midline(&rt, 0), 0, &failed);
    expect_eq("ordinary short reason", rt.track.reject_reason, TRACK_REJECT_NO_MIDLINE, &failed);
    expect_eq("ordinary short kind", rt.track.search_update_kind, TRACK_SEARCH_UPDATE_NONE, &failed);
    expect_eq("ordinary short mid unchanged", rt.mid_position, 70, &failed);
    expect_eq("ordinary short width unchanged", rt.width_base, 52, &failed);
    expect_eq("ordinary short mid diag", rt.track.search_mid_after, -1, &failed);
    expect_eq("ordinary short width diag", rt.track.width_base_after, -1, &failed);
    return failed;
}

int run_ordinary_backward_reject_no_learning()
{
    int failed = 0;
    runtime_t rt = {};
    init_runtime(&rt, 70, 52);
    set_seed_pair(&rt, 20, 100);
    fill_backward_midline(&rt);

    expect_eq("ordinary backward reject", publish_current_midline(&rt, 0), 0, &failed);
    expect_eq("ordinary backward reason", rt.track.reject_reason, TRACK_REJECT_NO_MIDLINE, &failed);
    expect_eq("ordinary backward kind", rt.track.search_update_kind, TRACK_SEARCH_UPDATE_NONE, &failed);
    expect_eq("ordinary backward mid unchanged", rt.mid_position, 70, &failed);
    expect_eq("ordinary backward width unchanged", rt.width_base, 52, &failed);
    return failed;
}

int run_ordinary_single_seed_learning_guard()
{
    int failed = 0;
    runtime_t rt = {};
    init_runtime(&rt, 70, 52);
    set_left_seed(&rt, 55);
    fill_forward_midline(&rt);

    expect_eq("ordinary single publish", publish_current_midline(&rt, 0), 1, &failed);
    commit_search_center_update(&rt, TRACK_SEARCH_UPDATE_ORDINARY, 1);
    expect_eq("ordinary single mid", rt.mid_position, 81, &failed);
    expect_eq("ordinary single width kept", rt.width_base, 52, &failed);

    init_runtime(&rt, 70, 52);
    set_left_seed(&rt, 15);
    fill_forward_midline(&rt);

    expect_eq("ordinary edge single publish", publish_current_midline(&rt, 0), 1, &failed);
    commit_search_center_update(&rt, TRACK_SEARCH_UPDATE_ORDINARY, 1);
    expect_eq("ordinary edge single kind", rt.track.search_update_kind, TRACK_SEARCH_UPDATE_ORDINARY, &failed);
    expect_eq("ordinary edge single mid unchanged", rt.mid_position, 70, &failed);
    expect_eq("ordinary edge single width kept", rt.width_base, 52, &failed);
    expect_eq("ordinary edge single mid diag", rt.track.search_mid_after, 70, &failed);
    return failed;
}

int run_element_pair_learning_keeps_width()
{
    int failed = 0;
    runtime_t rt = {};
    init_runtime(&rt, 70, 52);
    set_seed_pair(&rt, 20, 100);
    fill_short_forward_midline(&rt, 3);

    expect_eq("element publish", publish_current_midline(&rt, 1), 1, &failed);
    commit_search_center_update(&rt, TRACK_SEARCH_UPDATE_ELEMENT, 0);
    expect_eq("element kind", rt.track.search_update_kind, TRACK_SEARCH_UPDATE_ELEMENT, &failed);
    expect_eq("element mid", rt.mid_position, 60, &failed);
    expect_eq("element width kept", rt.width_base, 52, &failed);
    expect_eq("element mid diag", rt.track.search_mid_after, 60, &failed);
    expect_eq("element width diag", rt.track.width_base_after, 52, &failed);
    return failed;
}

int run_element_single_seed_learning()
{
    int failed = 0;
    runtime_t rt = {};
    init_runtime(&rt, 70, 52);
    set_left_seed(&rt, 30);
    fill_short_forward_midline(&rt, 3);

    expect_eq("element single publish", publish_current_midline(&rt, 1), 1, &failed);
    commit_search_center_update(&rt, TRACK_SEARCH_UPDATE_ELEMENT, 0);
    expect_eq("element single kind", rt.track.search_update_kind, TRACK_SEARCH_UPDATE_ELEMENT, &failed);
    expect_eq("element single mid", rt.mid_position, 56, &failed);
    expect_eq("element single width kept", rt.width_base, 52, &failed);
    return failed;
}

int run_control_ref_ipm_index_contract()
{
    int failed = 0;
    runtime_t rt = {};
    init_runtime(&rt, 70, 52);

    // ==== 控制参考点 fallback ====
    rt.has_matrix = 0;
    rt.control_center_x = 23;
    expect_point_eq("control ref fallback",
                    control_ref_point(&rt),
                    {23, START_HIGH},
                    &failed);

    // ==== 控制参考点查表索引 ====
    const int raw_x = RAW_W / 2;
    const int raw_y = static_cast<int>(RAW_H * 0.78F);
    const float table_x = g_raw_to_ipm_x[raw_y][raw_x];
    const float table_y = g_raw_to_ipm_y[raw_y][raw_x];
    expect_eq("control ref table valid", table_x >= 0.0F && table_y >= 0.0F, 1, &failed);

    double ix = -1.0;
    double iy = -1.0;
    expect_eq("control ref lookup valid",
              perspective_lookup_raw_to_ipm(raw_x, raw_y, &ix, &iy),
              1,
              &failed);
    expect_eq("control ref lookup x index",
              static_cast<int>(std::lround(ix)),
              static_cast<int>(std::lround(table_x)),
              &failed);
    expect_eq("control ref lookup y index",
              static_cast<int>(std::lround(iy)),
              static_cast<int>(std::lround(table_y)),
              &failed);

    rt.has_matrix = 1;
    rt.control_center_x = 23;
    point_t expected = {
        clip_i(static_cast<int>(std::lround(table_x)), 0, IPM_W - 1),
        clip_i(static_cast<int>(std::lround(table_y)), 0, IPM_H - 1),
    };
    expect_point_eq("control ref ipm", control_ref_point(&rt), expected, &failed);
    return failed;
}

int run_new_element_state_deferred_mode_contract()
{
    int failed = 0;
    runtime_t rt = {};
    init_runtime(&rt, 70, 52);

    // ==== 新进十字同帧不抢模式 ====
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

    // ==== 帧首十字 BEGIN 才按近线元素帧 ====
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

    // ==== 帧首十字 IN 可走远线 ====
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

int run_new_ring_state_deferred_mode_contract()
{
    int failed = 0;
    runtime_t rt = {};
    init_runtime(&rt, 70, 52);

    // ==== 新进环岛同帧不抢模式 ====
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

    // ==== 帧首左环 BEGIN 按外侧右线 ====
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

    // ==== 帧首左环 IN 按内侧左线 ====
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

    // ==== 环岛 RUN 先裁远处 L ====
    init_runtime(&rt, 70, 52);
    action = {};
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
    mode = classify_frame_mode(&rt, &action);
    expect_eq("left ring run side", mode.work_track_type, TRACK_TYPE_RIGHT, &failed);
    expect_eq("left ring run crop side", action.ring_frame_start_crop_side, TRACK_TYPE_RIGHT, &failed);
    expect_eq("left ring run crop index", action.ring_frame_start_crop_index, 31, &failed);

    // ==== 未激活 ring 不记录裁剪 ====
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

    // ==== 激活 ring 才记录裁剪 ====
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
    failed |= run_identity_seed_pass_gain_contract();
    failed |= run_ordinary_pair_learning();
    failed |= run_ordinary_short_reject_no_learning();
    failed |= run_ordinary_backward_reject_no_learning();
    failed |= run_ordinary_single_seed_learning_guard();
    failed |= run_element_pair_learning_keeps_width();
    failed |= run_element_single_seed_learning();
    failed |= run_control_ref_ipm_index_contract();
    failed |= run_new_element_state_deferred_mode_contract();
    failed |= run_new_ring_state_deferred_mode_contract();
    if(failed)
    {
        return 1;
    }

    std::puts("search_center_learning_test: ok");
    return 0;
}
