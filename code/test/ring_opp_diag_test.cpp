#include <cstdio>
#include <cstring>

#include "types.hpp"

// Whitebox test: include the owner file so the ring_opp diagnostic helper is
// tested without exposing a production-only hook.
#include "tracking/ring.cpp"

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

int run_record_success_contract()
{
    int failed = 0;
    runtime_t rt = {};
    boundary_t cur = {};
    boundary_t opp = {};
    cur.now_step = 34;
    opp.now_step = 27;
    opp.l_ok = 1;
    opp.l_now_index = 8;

    record_ring_opp_diag(&rt, &cur, &opp, 1, 1);

    expect_eq("left ring flag", rt.track.ring_opp_left, 1, &failed);
    expect_eq("cur now step", rt.track.ring_cur_step, 34, &failed);
    expect_eq("opp now step", rt.track.ring_opp_step, 27, &failed);
    expect_eq("opp l ok", rt.track.ring_opp_l_ok, 1, &failed);
    expect_eq("opp l index", rt.track.ring_opp_l_index, 8, &failed);
    expect_eq("build result", rt.track.ring_opp_build_result, 1, &failed);
    return failed;
}

int run_record_fail_contract()
{
    int failed = 0;
    runtime_t rt = {};

    record_ring_opp_diag(&rt, nullptr, nullptr, 0, -1);

    expect_eq("right ring flag", rt.track.ring_opp_left, 0, &failed);
    expect_eq("null cur step", rt.track.ring_cur_step, 0, &failed);
    expect_eq("null opp step", rt.track.ring_opp_step, 0, &failed);
    expect_eq("null opp l ok", rt.track.ring_opp_l_ok, 0, &failed);
    expect_eq("null opp l index", rt.track.ring_opp_l_index, -1, &failed);
    expect_eq("fail build result", rt.track.ring_opp_build_result, -1, &failed);
    return failed;
}
}

int main()
{
    int failed = 0;
    failed |= run_record_success_contract();
    failed |= run_record_fail_contract();
    if(failed)
    {
        return 1;
    }

    std::puts("ring_opp_diag_test: ok");
    return 0;
}
