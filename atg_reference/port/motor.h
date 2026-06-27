/* =====================================================================
 *  电机/编码器接口（motor）
 * ===================================================================== */
#ifndef ATG_REFERENCE_PORT_MOTOR_H
#define ATG_REFERENCE_PORT_MOTOR_H

#include "common.h"

#ifdef __cplusplus
extern "C" {
#endif

/* 获取编码器累计值 */
int64_t get_total_encoder(void);

#ifdef __cplusplus
}
#endif

#endif /* ATG_REFERENCE_PORT_MOTOR_H */
