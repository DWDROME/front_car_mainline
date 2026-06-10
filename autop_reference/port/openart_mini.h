#ifndef AUTOP_REFERENCE_PORT_OPENART_MINI_H
#define AUTOP_REFERENCE_PORT_OPENART_MINI_H

#include "headfile.h"

typedef struct openart_param_t {
    uint8_t rx_buffer[10];
    int fa_type;
    int openart_result;
    int64_t aprilencoder;
    int64_t aprilwaitencoder;
} openart_param_t;

extern openart_param_t openart;

void openart_send(void);
void openart_mini(void);
void check_openart(void);

#endif
