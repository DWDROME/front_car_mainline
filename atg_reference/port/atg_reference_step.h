#ifndef ATG_REFERENCE_STEP_H
#define ATG_REFERENCE_STEP_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

void atg_reference_reset(void);
int atg_reference_process_frame(uint8_t gray[120][160], int64_t encoder_total);
int atg_reference_track_line_found(void);

#ifdef __cplusplus
}
#endif

#endif
