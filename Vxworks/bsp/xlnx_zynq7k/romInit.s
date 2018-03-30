/* romInit.s -  Xilinx Zynq-7000 board ROM initialization module */

/*
 * Copyright (c) 2011-2014 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */
 
/*
modification history
--------------------
11feb14,c_l  Initialize GIC Priority Mask register for SMP mode. (VXW6-70150)
01c,12apr13,y_c  move #include <config.h> to the end to avoid build warning.
01b,15jun12,fao  update for the first release.
01a,10may11,rab  created from arm_a9_ctx rev 01a
*/

/*
DESCRIPTION
This module contains the entry code for vxWorks images that start
running from ROM, such as 'bootrom' and 'vxWorks_rom'.  The entry
point, romInit(), is the first code executed on power-up.  It performs
the minimal setup needed to call the generic C routine romStart() with
parameter BOOT_COLD.

romInit() masks interrupts in the processor and the interrupt
controller and sets the initial stack pointer (to STACK_ADRS which is
defined in configAll.h).  Other hardware and device initialisation is
performed later in the sysHwInit routine in sysLib.c.

The routine sysToMonitor() jumps to a location after the beginning of
romInit, (defined by ROM_WARM_ADRS) to perform a "warm boot".  This
entry point allows a parameter to be passed to romStart().

The routines in this module don't use the "C" frame pointer %r11@ ! or
establish a stack frame.
*/

#define _ASMLANGUAGE
#include <vxWorks.h>
#include <sysLib.h>
#include <asm.h>
#include <regs.h>
#include <arch/arm/mmuArmLib.h>
#include <arch/arm/cacheArmLib.h>
#include <config.h>

    /* internals */

    .globl  FUNC(romInit)     /* start of system code */
    .globl  VAR(sdata)        /* start of data */
    .globl  _sdata

    /* externals */

    .extern FUNC(romStart)    /* system initialization routine */

    .data
_sdata:
VAR_LABEL(sdata)
    .asciz    "start of data"
    .balign    4

    .text
    .balign 4

/*******************************************************************************
*
* romInit - entry point for VxWorks in ROM
*

* romInit
*     (
*     int startType    /@ only used by 2nd entry point @/
*     )

* INTERNAL
* sysToMonitor examines the ROM for the first instruction and the string
* "Copy" in the third word so if this changes, sysToMonitor must be updated.
*/

_ARM_FUNCTION(romInit)
_romInit:
   
cold:
    MOV  r0, #BOOT_COLD

warm:
    B    start

    /* copyright notice appears at beginning of ROM (in TEXT segment) */

    .ascii   "\nCopyright 2013 Wind River Systems, Inc."
    .balign 4

start:

    MOV   r12, r0 /* save startType */

    MOV r1, #0                       /* data SBZ */
    MCR CP_MMU, 0, r1, c7, c10, 4    /* drain write-buffer */

    MRC CP_MMU, 0, r1, c1, c0, 0     /* Read control register into r1 */
    LDR r2, =CACHE_DC_ENABLE
    AND r1, r1, r2
    TEQ r1, r2
    BNE dcacheDisabledBefore

    /* flush and invalidate cache lines */

    _CORTEX_AR_ENTIRE_DATA_CACHE_OP (c14)

    MCR    p15, 0, r0, c7, c10, 4         /* Data Synch Barrier */

    B invalidateICache

dcacheDisabledBefore:

    /* invalidate all D-cache lines */

    _CORTEX_AR_ENTIRE_DATA_CACHE_OP (c6)

invalidateICache:

    MOV     r0, #0                      /* data SBZ */
    MCR     p15 , 0, r0, c7, c5, 0      /* Invalidate all I-cache */

    ISB
    DSB

    /* disable L1 D-caches */

    MRC     p15, 0, r1, c1, c0, 0       /* Read control register into r1 */
    BIC     r1, r1, # CACHE_DC_ENABLE   /* Clear L1 D-cache enable */
    MCR     p15, 0, r1, c1, c0, 0       /* Write control register */

    /* disable and clear I-cache */

    MRC     p15 , 0, r2, c1, c0, 0      /* Read control register */
    BIC     r2, r2, # CACHE_IC_ENABLE   /* Disable I-cache */
    MCR     p15 , 0, r2, c1, c0, 0      /* Write control register */

    /* TTBCR must be 0 for vxWorks */

    MOV    r1, #0
    MCR    CP_MMU, 0, r1, c2, c0, 2

    /* Flush the entire BTAC before enabling the Z bit */

    MOV     r1, #0
    MCR     CP_MMU, 0, r1, c7, c5, 6

    LDR     r1, =MMU_INIT_VALUE         /* Defined in mmuCortexA8Lib.h */
    MCR     CP_MMU, 0, r1, c1, c0, 0    /* Write to MMU CR */

    /* perform a Data Synchronization Barrier */

    DSB

    /* detach SMP system */

    MRC     p15, 0, r1, c1, c0, 1       /* Read aux control register */
    BIC     r1,  r1, #(0x1 << 6)        /* Clear SMP bit in aux control register */
    MCR     p15, 0, r1, c1, c0, 1       /* Write aux control register */

    MOV     r1, #0                      /* data SBZ */
    MRC     p15, 0, r1, c0, c0, 5       /* read multiprocessor ID register */
    ANDS    r1, r1, #0x0f
    BNE     cpuWaitForEvent

    /* no bootrom copy operation if we are running on upper half RAM */

    MOV r0, pc

    /*
     * the PC address of romInit() will be at 0x0fc00000.
     * 4 is the essential difference of 0x00200000.
     */

    LDR r1, =0x04000000
    TST r0, r1

    /* no bootrom copy operation if already running at 0x0fc00000 */

    BNE instrLabel
    
    LDR r0, =FUNC(romInit)
    LDR r1, =ROM_TEXT_ADRS
    LDR r2, =0

bootromCopy:
    LDR r3, [r0, r2]
    STR r3, [r1, r2]
    ADD r2, r2, #4
    CMP r2, #ROM_SIZE
    BNE bootromCopy

    /* 
     * If this is a native bootrom cold boot, the PC is still in 
     * romInit region, and it must have to be adjusted to 
     * ROM_TEXT_ADRS(=0x0fc00000) segment.
     */

    LDR r3, L$_pcCorrect
    MOV pc, r3

    ISB

instrLabel:

    MOV r0, r12 /* restore startType */

    /* disable interrupts in CPU and switch to SVC32 mode */

    MRS     r1, cpsr
    BIC     r1, r1, #MASK_MODE
    ORR     r1, r1, #MODE_SVC32 | I_BIT | F_BIT
    MSR     cpsr, r1

    /*
     * Set Process ID Register to zero, this effectively disables
     * the process ID remapping feature.
     */

    MOV     r1, #0
    MCR     CP_MMU, 0, r1, c13, c0, 0

    /* Set Context ID Register to zero, including Address Space ID */

    MCR     CP_MMU, 0, r1, c13, c0, 1

    MOV     r1, #0xFFFFFFFF         /* Set All 16 domains to mgr access*/
    MCR     p15, 0, r1, c3, c0, 0   /* Set Domain Permissions */

    /* disable individual interrupts in the interrupt controller */    

    /* disable ints to CPU */

    LDR     r2, =ZYNQ7K_GIC_CPU_CONTROL
    MOV     r1, #0
    STR     r1, [r2, #0]       

    /* disable ints for distributor */

    LDR     r2, =(ZYNQ7K_GIC1_BASE + ZYNQ7K_GIC_DIST_CONTROL)
    STR     r1, [r2, #0]

    /* disable Timers */

    LDR     r2, =CTXA9_TIMER0_BASE            /* Timer 1 */
    STR     r1, [r2, #8]

    LDR     sp, L$_STACK_ADDR
    MOV     fp, #0                  /* zero frame pointer */

    LDR     pc, L$_rStrtInRom       /* CPU0 will run this bootloader */

    /* The Xilinx First Stage Boot Loader (FSBL) should halt the 2nd */
    /* CPU with a WFE instruction. This code is here as a fail safe. */

cpuWaitForEvent:
    LDR     r1, =ZYNQ7K_GIC_CPU_PRIORITY
    MOV     r2, #0xff
    STR     r2, [r1, #0]
    LDR     r1, =ZYNQ7K_GIC_CPU_CONTROL
    MOV     r2, #1
    STR     r2, [r1, #0]

    LDR     r1, =ZYNQ7K_OCM_BOOT_ADR
    LDR     r2, =0xffffffff
    STR     r2, [r1, #0]

    DSB  /* Data Synch Barrier */        

    WFE  /* wait for event */

    /* Read OCM to check for an address to jump too */
        
jumpaddrget:
    LDR     r5, =ZYNQ7K_OCM_BOOT_ADR
    LDR     r6, [r5]
    ANDS    r5, r6, #0x3
    BNE     jumpaddrget
    BX      r6

/******************************************************************************/
/*
 * PC-relative-addressable pointers - LDR Rn,=sym is broken
 * note "_" after "$" to stop preprocessor performing substitution
 */

    .balign    4

L$_rStrtInRom:
    .long   ROM_TEXT_ADRS + FUNC(romStart) - FUNC(romInit)

L$_STACK_ADDR:
    .long    STACK_ADRS

L$_pcCorrect:
    .long   ROM_TEXT_ADRS + instrLabel - FUNC(romInit)
