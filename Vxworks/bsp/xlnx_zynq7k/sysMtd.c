/* sysMtd.c - MTD driver for numonyx N25Q128 flash */

/*
 * Copyright (c) 2012, 2013 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
01b,12apr13,y_c  delete some blanks at the end of line.
01a,04jul12,clx  created from stm_spear13xx/sysMtd.c rev 01a

*/

/*
DESCRIPTION
This file provides the TFFS MTD driver for numonyx N25Q128 series flash parts.
The driver handles the low level operations like erase and program of the flash.
It also provides an identify routine to check if it is compatible with the
devices.

INCLUDE FILES:

SEE ALSO:
*/

#include <stdio.h>
#include <tffs/flflash.h>
#include <tffs/backgrnd.h>

/* defines */

/* disable debugging */

#undef CFI_DEBUG

#ifdef CFI_DEBUG
#   define DEBUG_PRINT    printf
#else
#   undef DEBUG_PRINT
#endif /* CFI_DEBUG */

IMPORT STATUS qspiFlashSectorErase (int);
IMPORT STATUS qspiFlashPageWrite (UINT32, UINT8*, UINT32);

#define n25Q128Identify sysMtdIdentify

#define PAGE_SIZE  (0x100)  /* N25Q128 page size is 256bytes */

/*******************************************************************************
*
* sysMtdWrite - write routine for flash
*
* This routine writes data to the flash.
*
* RETURNS: flOK or flWriteFault if write failed.
*
* ERRNO: N/A
*/

LOCAL FLStatus sysMtdWrite
    (
    FLFlash         vol,
    CardAddress     address,
    const void FAR1 *buffer,
    int             length,
    int             overwrite
    )
    {
    UINT32  unaligned;
    UINT8  *buf = (UINT8 *)buffer;
    UINT32  left = length;
    int     offset = 0;

    if (flWriteProtected(vol.socket))
        return flWriteProtect;

    /* calculate the program addr, make sure it's aligned */

    unaligned = (UINT32)vol.map (&vol, address, 0);

    unaligned -= SPI_FLASH_BASE_ADRS;

    /* address is not page align */

    if ((UINT32)unaligned % PAGE_SIZE)
        {
        if ((length + ((UINT32)unaligned % PAGE_SIZE)) < PAGE_SIZE)
            {
            if (qspiFlashPageWrite(unaligned, buf, length) != flOK)
                return flWriteFault;
            left = 0;
            }
        else
            {
            left = PAGE_SIZE - (UINT32)unaligned % PAGE_SIZE;
            if (qspiFlashPageWrite(unaligned, buf, left) != flOK)
                return flWriteFault;
            left = length - left;
            offset = length - left;
            }
        }

    /* continue page write */

    while (left / PAGE_SIZE)
        {
        if (qspiFlashPageWrite(unaligned + offset, buf + offset, PAGE_SIZE) != flOK)
            return flWriteFault;
        left -= PAGE_SIZE;
        offset = length - left;
        }

    /* write the last portion */

    if(left)
        {
        if (qspiFlashPageWrite(unaligned + offset, buf + offset, left) != flOK)
            return flWriteFault;
        }

    if (tffscmp((void FAR0 *) vol.map (&vol, address, 0), buffer, length))
        {
#ifdef DEBUG_PRINT
        DEBUG_PRINT("Debug: CFISCS write failed in verification.\n");
#endif /* DEBUG_PRINT */
        return flWriteFault;
        }

    return flOK;
    }

/*******************************************************************************
*
* sysMtdErase - erase routine for flash
*
* This routine erases the specified blocks.
*
* RETURNS: flOK or flWriteFault if erase failed.
*
* ERRNO: N/A
*/

LOCAL FLStatus sysMtdErase
    (
    FLFlash vol,
    int     firstEraseBlock,
    int     numberOfEraseBlocks
    )
    {
    FLStatus status = flOK;
    int      iBlock;
    UINT32   sector;

#ifdef DEBUG_PRINT
    DEBUG_PRINT("Debug: CFISCS erase firstblock %d.\n", firstEraseBlock);
    DEBUG_PRINT("Debug: CFISCS address 0x%x.\n", (unsigned int)flMap(vol.socket,
                 firstEraseBlock * vol.erasableBlockSize));
#endif /* DEBUG_PRINT */

    if (flWriteProtected(vol.socket))
        {
        return flWriteProtect;
        }

    sector = (UINT32)vol.map(&vol, firstEraseBlock * vol.erasableBlockSize, 0);
    sector = (sector - SPI_FLASH_BASE_ADRS) / vol.erasableBlockSize;

   /* sector += 0x40;*/

    for (iBlock = sector;
         iBlock < sector + numberOfEraseBlocks && status == flOK;
         iBlock++)
         {
         status = qspiFlashSectorErase(iBlock * FLASH_SECTOR_SIZE);
         }

    return status;
    }

/******************************************************************************
*
* n25Q128Map - MTD map routine
*
* RETURNS: FLStatus
*
*/

LOCAL void FAR0* n25Q128Map
    (
    FLFlash* pVol,
    CardAddress address,
    int length
    )
    {
    UINT32 flashBaseAddr = (pVol->socket->window.baseAddress << 12);
    void FAR0* pFlash = (void FAR0*) (flashBaseAddr + address);
    return(pFlash);
    }

/*******************************************************************************
*
* sysMtdIdentify - identify routine for flash
*
* This routine probes the information of the flash part
*
* RETURNS: always flOK.
*
* ERRNO: N/A
*/

FLStatus sysMtdIdentify
    (
    FLFlash vol
    )
    {
#ifdef DEBUG_PRINT
    DEBUG_PRINT("Debug: entering CFISCS identification routine.\n");
#endif /* DEBUG_PRINT */

    /* CFI INFO */

    vol.type = 0x1820; /* Vendor and Device ID */

    vol.erasableBlockSize = FLASH_SECTOR_SIZE;

    vol.chipSize = FLASH_SIZE;

    vol.interleaving = 1;
    vol.noOfChips = 1;

    vol.erasableBlockSize *= vol.interleaving;

    vol.write = sysMtdWrite;
    vol.erase = sysMtdErase;
    vol.map = n25Q128Map;

    return flOK;
    }
