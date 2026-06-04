#pragma once

static inline int clip_i(int v, int min_v, int max_v)
{
    if(v < min_v)
    {
        return min_v;
    }
    if(v > max_v)
    {
        return max_v;
    }
    return v;
}

static inline int round_i(double v)
{
    return v >= 0.0 ? (int)(v + 0.5) : (int)(v - 0.5);
}
