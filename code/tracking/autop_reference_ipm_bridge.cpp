#include "tracking/ipm_table_generated.hpp"

extern "C" void autop_reference_fill_ipm_tables(float mapx[120][160], float mapy[120][160])
{
    for(int y = 0; y < RAW_H; ++y)
    {
        for(int x = 0; x < RAW_W; ++x)
        {
            mapx[y][x] = g_raw_to_ipm_x[y][x];
            mapy[y][x] = g_raw_to_ipm_y[y][x];
        }
    }
}
