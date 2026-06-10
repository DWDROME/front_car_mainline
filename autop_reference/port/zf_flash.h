#ifndef AUTOP_REFERENCE_PORT_ZF_FLASH_H
#define AUTOP_REFERENCE_PORT_ZF_FLASH_H

#include "headfile.h"

#define FLASH_SECTOR_NUM 1

static inline void flash_init(void)
{
}

static inline void flash_read_page(int sector, int page, uint32 *buffer, int len)
{
    (void)sector;
    (void)page;
    if(buffer != NULL && len > 0)
    {
        memset(buffer, 0, (size_t)len * sizeof(uint32));
    }
}

static inline void flash_erase_sector(int sector)
{
    (void)sector;
}

static inline void flash_page_program(int sector, int page, const uint32 *buffer, int len)
{
    (void)sector;
    (void)page;
    (void)buffer;
    (void)len;
}

#endif
