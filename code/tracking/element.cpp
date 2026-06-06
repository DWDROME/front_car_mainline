#include "element.hpp"

#include "cross.hpp"
#include "ring.hpp"

namespace
{
// 元素状态互斥：十字优先级最高；十字仍在时清掉环岛，十字退出后继续检查环岛。
int run_state(runtime_t *rt)
{
    // cross_process() 每帧只跑一次；已有十字退出后，不在同一帧立刻重进十字。
    cross_process(rt);
    if(rt->cross.state != CROSS_STATE_NONE)
    {
        rt->ring = {};
        return 1;
    }

    // 已在环岛过程中：继续推进环岛状态机。
    if(rt->ring.kind != RING_KIND_NONE)
    {
        ring_process(rt);
        return 1;
    }

    // 不在任何元素中：跑一次环岛检测，看本帧是否新进入环岛。
    ring_process(rt);
    if(rt->ring.kind != RING_KIND_NONE)
    {
        return 1;
    }

    return 0;
}
}

// 赛道元素总入口；斑马线扫描中线由 mainline 按参考 garage 语义另选。
int element_process(runtime_t *rt)
{
    if(rt == nullptr)
    {
        return 0;
    }

    return run_state(rt);
}
