#ifndef AUTOP_REF_HEADFILE_H
#define AUTOP_REF_HEADFILE_H

#include <assert.h>
#include <math.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "tuning.hpp"

typedef int8_t int8;
typedef int16_t int16;
typedef int32_t int32;
typedef int64_t int64;
typedef uint8_t uint8;
typedef uint16_t uint16;
typedef uint32_t uint32;
typedef uint64_t uint64;

#ifndef PI
#define PI 3.14159265358979323846f
#endif

#ifndef MIN
#define MIN(a, b) ((a) < (b) ? (a) : (b))
#endif

#ifndef MAX
#define MAX(a, b) ((a) > (b) ? (a) : (b))
#endif

#ifndef MINMAX
#define MINMAX(x, low, up) ((x) > (up) ? (up) : ((x) < (low) ? (low) : (x)))
#endif

#define AT_ITCM_SECTION_INIT(x) x
#define AT_DTCM_SECTION_ALIGN(x, align) x
#define AT_DTCM_SECTION_ALIGN_INIT(x, align) x
#define AT_SDRAM_SECTION_ALIGN(x, align) x

#define MT9V03X_CSI_W RAW_W
#define MT9V03X_CSI_H RAW_H

#endif
