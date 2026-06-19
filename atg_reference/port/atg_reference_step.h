#ifndef ATG_REFERENCE_STEP_H
#define ATG_REFERENCE_STEP_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

void atg_reference_reset(void);
int atg_reference_process_frame(uint8_t gray[120][160], int64_t encoder_total);
int atg_reference_track_line_found(void);
void atg_reference_set_vehicle_raw_ref_x(float raw_x);
float atg_reference_vehicle_raw_ref_x(void);
void atg_reference_raw_ref_to_ipm(float raw_x, float raw_y, float *ipm_x, float *ipm_y);

#ifdef __cplusplus
}
#endif

#endif
