/* sysBspCommon.c - common BSP routines */

/*
 * Copyright (c) 2011 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

 /*
modification history
--------------------
01a,18feb11,z_l created.
*/

/*DESCRIPTION

This file includes the common variable and function which are usually required
in BSP.
*/


/* imports */

IMPORT char end [];                         /* end of system, created by ld */

#ifndef _ARCH_SUPPORTS_PROTECT_INTERRUPT_STACK
IMPORT VOIDFUNCPTR _func_armIntStackSplit;  /* ptr to fn to split stack */
#endif /* !_ARCH_SUPPORTS_PROTECT_INTERRUPT_STACK */

/* globals */

int    sysBus      = 0;               /* system bus type (VME_BUS, etc) */
int    sysCpu      = CPU;             /* system CPU type (e.g. ARMARCH7)*/
char * sysBootLine = BOOT_LINE_ADRS;  /* address of boot line */
char * sysExcMsg   = EXC_MSG_ADRS;    /* catastrophic message area */
int    sysProcNum  = 0;               /* processor number of this CPU */

/*******************************************************************************
*
* sysModel - return the model name of the CPU board
*
* This routine returns the model name of the CPU board.
*
* RETURNS: A pointer to a string identifying the board and CPU.
*/

char *sysModel (void)
    {
    return SYS_MODEL;
    }

/*******************************************************************************
*
* sysBspRev - return the BSP version with the revision eg 1.2/<x>
*
* This function returns a pointer to a BSP version with the revision.
* e.g. 1.2/<x>. BSP_REV is concatenated to BSP_VERSION to form the
* BSP identification string.
*
* RETURNS: A pointer to the BSP version/revision string.
*/

char * sysBspRev (void)
    {
    return (BSP_VERSION BSP_REV);
    }

/*******************************************************************************
*
* sysPhysMemTop - get the address of the top of physical memory
*
* This routine returns the address of the first missing byte of memory,
* which indicates the top of memory.
*
* The user specifies the amount of physical memory with the
* macro LOCAL_MEM_SIZE in config.h.
*
* NOTE: Do not adjust LOCAL_MEM_SIZE to reserve memory for application
* use.  See sysMemTop() for more information on reserving memory.
*
* RETURNS: The address of the top of physical memory.
*
* SEE ALSO: sysMemTop()
*/

char * sysPhysMemTop (void)
    {
    static char * physTop = NULL;

    if (physTop == NULL)
        {
        physTop = (char *)(LOCAL_MEM_LOCAL_ADRS + LOCAL_MEM_SIZE);
        }

    return physTop;
    }

/*******************************************************************************
*
* sysMemTop - get the address of the top of VxWorks memory
*
* This routine returns a pointer to the first byte of memory not
* controlled or used by VxWorks.
*
* The user can reserve memory space by defining the macro USER_RESERVED_MEM
* in config.h.  This routine returns the address of the reserved memory
* area.  The value of USER_RESERVED_MEM is in bytes.
*
* RETURNS: The address of the top of VxWorks memory.
*/

char * sysMemTop (void)
    {
    static char * memTop = NULL;

    if (memTop == NULL)
        {
#ifdef  INCLUDE_EDR_PM
        memTop = (char *)sysPhysMemTop () - USER_RESERVED_MEM - PM_RESERVED_MEM;
#else
        memTop = (char *)sysPhysMemTop () - USER_RESERVED_MEM;
#endif /* INCLUDE_EDR_PM */
        }

    return (memTop);
    }

/*******************************************************************************
*
* sysProcNumGet - get the processor number
*
* This routine returns the processor number for the CPU board, which is
* set with sysProcNumSet().
*
* RETURNS: The processor number for the CPU board.
*
* SEE ALSO: sysProcNumSet()
*/

int sysProcNumGet (void)
    {
    return sysProcNum;
    }

/*******************************************************************************
*
* sysProcNumSet - set the processor number
*
* This routine sets the processor number for the CPU board.  Processor numbers 
* should be unique on a single backplane.
*
* NOTE
* By convention, only processor 0 should dual-port its memory.
*
* RETURNS: N/A
*
* SEE ALSO: sysProcNumGet()
*/

void sysProcNumSet
    (
    int procNum     /* processor number */
    )
    {
    sysProcNum = procNum;
    }

/*******************************************************************************
*
* sysClkFreqGet - get the system clock frequency
*
* This routine gets the system clock frequency.
*
* RETURNS: system clock frequency
*/

UINT32 sysClkFreqGet (void)
    {
    return SYS_CLK_FREQ;
    }

/*******************************************************************************
*
* bspSerialChanGet - get a serial channel
*
* RETURNS: ERROR
*
* \NOMANUAL
*/

SIO_CHAN * bspSerialChanGet
    (
    int channel /* serial channel */
    )
    {
    return ((SIO_CHAN *) ERROR);
    }
