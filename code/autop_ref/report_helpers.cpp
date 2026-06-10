#include "tracking/imgproc.hpp"

#include <cstdlib>

int seed_pair_accepted(const seed_pair_t *seeds, int seed_state)
{
    if(seeds == nullptr)
    {
        return 0;
    }
    if((seed_state & 1) == 0 || (seed_state & 2) == 0)
    {
        return 0;
    }
    if(seeds->left.y != seeds->right.y || seeds->row != seeds->left.y)
    {
        return 0;
    }
    const int span = seeds->right.x - seeds->left.x;
    return span >= RAW_W / 8 && span <= RAW_W - 4;
}

int midline_has_forward_lookahead(const midline_t *midline, int aim_distance, int ref_y)
{
    if(midline == nullptr || midline->step <= 0)
    {
        return 0;
    }

    int best = -1;
    for(int i = 0; i < midline->step; ++i)
    {
        if(midline->dist[i] < aim_distance)
        {
            continue;
        }
        if(best < 0 || midline->dist[i] < midline->dist[best])
        {
            best = i;
        }
    }
    if(best < 0)
    {
        return 0;
    }
    return midline->pts[best].y < ref_y;
}
