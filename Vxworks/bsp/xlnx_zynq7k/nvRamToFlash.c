/* nvRamToFlash.c - non-volatile RAM to flash mapping routine */

/*
 * Copyright (c) 2010, 2014 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
04nov14,c_l  fix INCLUDE_ZYNQ7K_QSPI definition. (VXW6-83719)
01a,18dec10,clx  created from arm_a9_ctx rev 01a
*/

/*
DESCRIPTION
This library contains non-volatile RAM manipulation routines for targets
lacking non-volatile RAM, but that do have FLASH memory.  Read and write
wrappers are provided for the FLASH memory routines sysFlashGet() and
sysFlashSet().
*/

/* includes */

#include <drv/mem/memDev.h>
#include <drv/mem/flashDev.h>

/*******************************************************************************
*
* sysNvRamGet - get the contents of non-volatile RAM
*
* This routine calls sysFlashGet() to copy the contents of flash memory
* into a specified string.  The string is terminated with an EOS.
*
* NOTE: This routine uses NOR flash memory as NVRAM.
*
* RETURNS: The return value of sysFlashGet().
*
* SEE ALSO: sysNvRamSet(), sysFlashGet()
*/

STATUS sysNvRamGet
    (
    char *string,       /* where to copy non-volatile RAM    */
    int strLen,         /* maximum number of bytes to copy   */
    int offset          /* byte offset into non-volatile RAM */
    )
    {
#ifdef INCLUDE_ZYNQ7K_QSPI
    STATUS retVal;

    offset += NV_BOOT_OFFSET;

    if ((offset < 0) || (strLen < 0) || ((offset + strLen) > NV_RAM_SIZE))
        return (ERROR);

    retVal = sysFlashGet(string, strLen, offset + NV_RAM_ADRS);

    string[strLen] = EOS;

    return (retVal);
#else
    return (ERROR);
#endif /* INCLUDE_ZYNQ7K_QSPI */
    }

/*******************************************************************************
*
* sysNvRamSet - write to non-volatile RAM
*
* This routine calls sysFlashSet() to copy a specified string into flash memory.
*
* NOTE: This routine uses NOR flash memory as NVRAM.
*
* RETURNS: The return value of sysFlashSet().
*
* SEE ALSO: sysNvRamGet(), sysFlashSet()
*/

STATUS sysNvRamSet
    (
    char *string,       /* string to be copied into non-volatile RAM */
    int strLen,         /* maximum number of bytes to copy           */
    int offset          /* byte offset into non-volatile RAM         */
    )
    {
#ifdef INCLUDE_ZYNQ7K_QSPI
    offset += NV_BOOT_OFFSET;   /* boot line begins at <offset> = 0 */

    if ((offset < 0) || (strLen < 0) || ((offset + strLen) > NV_RAM_SIZE ))
        return (ERROR);

    return (sysFlashSet(string, strLen, offset + NV_RAM_ADRS));
#else
    return (ERROR);
#endif /* INCLUDE_ZYNQ7K_QSPI */
    }

