#ifndef AUTOP_REFERENCE_STEP_H
#define AUTOP_REFERENCE_STEP_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

void autop_reference_reset(void);
int autop_reference_process_frame(uint8_t gray[120][160], int64_t encoder_total);
int autop_reference_track_line_found(void);
void autop_reference_fill_ipm_tables(float mapx[120][160], float mapy[120][160]);

#ifdef __cplusplus
}
#endif

#endif
