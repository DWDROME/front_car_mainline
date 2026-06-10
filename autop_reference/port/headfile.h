#ifndef AUTOP_REFERENCE_PORT_HEADFILE_H
#define AUTOP_REFERENCE_PORT_HEADFILE_H

#include <assert.h>
#include <math.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MT9V03X_CSI_W 160
#define MT9V03X_CSI_H 120

#ifndef PI
#define PI 3.14159265358979323846f
#endif

#define AT_DTCM_SECTION_ALIGN(name, align) name
#define AT_DTCM_SECTION_ALIGN_INIT(name, align) name
#define AT_ITCM_SECTION_INIT(name) name
#define AT_SDRAM_SECTION_ALIGN(name, align) name
#define AT_SDRAM_SECTION_ALIGN_INIT(name, align) name

typedef int16_t int16;
typedef int32_t int32;
typedef uint8_t uint8;
typedef uint16_t uint16;
typedef uint32_t uint32;

typedef void *rt_sem_t;
typedef void *rt_mailbox_t;
typedef void *rt_timer_t;
typedef void *rt_thread_t;

#define RT_NULL NULL
#define RT_WAITING_FOREVER (-1)
#define RT_IPC_FLAG_FIFO 0
#define RT_TIMER_FLAG_PERIODIC 0

static inline uint32_t rt_tick_get_millisecond(void)
{
    return 0;
}

#endif
