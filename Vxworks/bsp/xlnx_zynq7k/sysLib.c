/* sysLib.c - Xilinx Zynq-7000 board system-dependent library */

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
04nov14,c_l  Fix INCLUDE_ZYNQ7K_QSPI definition. (VXW6-83719)
31jul14,c_l  Add DRV_ARM_GLOBAL_TIMER. (VXW6-83146)
01aug14,zly  SD Card clock frequency is unexpectedly limited on Xilinx Zynq-7000.
             (VXW6-80641)
22jul14,c_l  Add L1 prefetch support. (VXW6-83079)
16jul14,c_l  Add protection for system level control registers. (VXW6-83097)
26jun14,c_l  Remove localTimerInit. (VXW6-83017)
07may14,c_l  Update to use ROM_WARM_ADRS for warm boot. (VXW6-82585)
25apr14,c_l  Fixed sysUsDelay. (VXW6-80653)
24mar14,xms  fix packet missing issue for external PHY. (VXW6-70152)
27jan14,c_l  Add INCLUDE_MMU_GLOBAL_MAP check for global address map. (VXW6-70082)
21jan14,c_l  Fixed RAM address map for adrSpaceShow. (VXW6-23821)
01p,08aug13,c_l  Added MMU_ATTR_CACHE_COHERENCY option for ZYNQ7K_MEM_EXTRA.
                 (WIND00429878)
01o,20jul13,y_c  added sysDevcFpgaResetSet. (WIND00426873)
01n,27jun13,c_l  Fixed a build warning. (WIND00423748)
01m,20jun13,y_c  add sysDevcLvlShftrSet. (WIND00422940)
01l,05jun13,y_c  add a warning when using of I2C switch pca9548. (WIND00417766)
01k,29may13,y_c  add support for the Programmable Logic. (WIND00417766)
01j,07apr13,y_c  add 1G ram support. (WIND00400701)
01i,02apr13,c_l  Fixed a crash issue for SMP in sysCpuEnable. (WIND00409411)
01h,08apr13,zgl  fixed smp mode cache issue. (WIND00411916)
01g,07apr13,y_c  add 1G ram support.
01f,30jan13,ljg  add USB TCD support.
01e,18jan13,fao  add sysMalloc/sysFree. (WIND00399682)
01d,09jan13,fao  add ifMemCached. (WIND00397943)
01c,16sep12,fao  add dma address map.
01b,15jun12,fao  update for the first release.
01a,10may11,rab  created from arm_a9_ctx rev 01a
*/

/*
DESCRIPTION
This library provides board-specific routines for the
Xilinx Zynq-7000 board BSP
*/

/* includes */

#include <vxWorks.h>
#include "config.h"

#if !defined (INCLUDE_MMU) && \
    (defined (INCLUDE_CACHE_SUPPORT) || defined (INCLUDE_MMU_BASIC) || \
     defined (INCLUDE_MMU_FULL) || defined (INCLUDE_MMU_MPU) || \
     defined (INCLUDE_MMU_GLOBAL_MAP))
#   define INCLUDE_MMU
#endif

#include <sysLib.h>
#include <string.h>
#include <intLib.h>
#include <taskLib.h>
#include <vxLib.h>
#include <muxLib.h>
#include <cacheLib.h>

#ifdef INCLUDE_MMU
#   include <arch/arm/mmuArmLib.h>
#   include <private/vmLibP.h>
#endif /* INCLUDE_MMU */
#include <dllLib.h>

#include <private/windLibP.h>

#ifdef INCLUDE_VXIPI
#   include <vxIpiLib.h>
#endif /* INCLUDE_VXIPI */

#ifdef _WRS_CONFIG_SMP
#   include <arch/arm/vxAtomicArchLib.h>
#endif /* _WRS_CONFIG_SMP */

#include <hwif/intCtlr/vxbArmGenIntCtlr.h>

#include <hwif/vxbus/vxBus.h>

#ifdef DRV_VXBEND_ZYNQMAC
#   include <h/end/vxbZynq7kGemEnd.h>
#endif /* DRV_VXBEND_ZYNQMAC */

/* imports */

IMPORT void hardWareInterFaceInit (void);

#ifdef INCLUDE_SIO_UTILS
IMPORT void sysSerialConnectAll (void);
#endif /* INCLUDE_SIO_UTILS */

#ifdef INCLUDE_CACHE_SUPPORT
IMPORT void cacheCortexA9LibInstall (VIRT_ADDR (physToVirt)(PHYS_ADDR),
                                    PHYS_ADDR (virtToPhys)(VIRT_ADDR));
#endif /* INCLUDE_CACHE_SUPPORT */

#ifdef INCLUDE_MMU
IMPORT void mmuCortexA8LibInstall (VIRT_ADDR (physToVirt)(PHYS_ADDR),
                                  PHYS_ADDR (virtToPhys)(VIRT_ADDR));
#endif /* INCLUDE_MMU */

/* globals */

#ifdef INCLUDE_MMU

/*
 * The following structure describes the various different parts of the
 * memory map to be used only during initialization by
 * vm(Base)GlobalMapInit () when INCLUDE_MMU_BASIC/FULL/GLOBAL_MAP are
 * defined.
 *
 * Clearly, this structure is only needed if the CPU has an MMU!
 *
 * The following are not the smallest areas that could be allocated for a
 * working system. If the amount of memory used by the page tables is
 * critical, they could be reduced.
 */

PHYS_MEM_DESC sysPhysMemDesc [] =
    {

    /* OCM */

    {
    ZYNQ7K_OCM_MEM_ADRS,    /* virtual address */
    ZYNQ7K_OCM_MEM_ADRS,    /* physical address */
    ZYNQ7K_OCM_MEM_SIZE,
    MMU_ATTR_VALID_MSK | MMU_ATTR_PROT_MSK | MMU_ATTR_CACHE_MSK,
#ifdef _WRS_CONFIG_SMP       /* needs to be shared */
    MMU_ATTR_VALID     | MMU_ATTR_SUP_RWX  | MMU_ATTR_CACHE_DEFAULT
    | MMU_ATTR_CACHE_COHERENCY
#else
    MMU_ATTR_VALID     | MMU_ATTR_SUP_RWX  | MMU_ATTR_CACHE_DEFAULT
#endif /* _WRS_CONFIG_SMP */
    },

    /* DRAM */

    {
    LOCAL_MEM_LOCAL_ADRS,    /* virtual address */
    LOCAL_MEM_LOCAL_ADRS,    /* physical address */
    LOCAL_MEM_SIZE,
    MMU_ATTR_VALID_MSK | MMU_ATTR_PROT_MSK | MMU_ATTR_CACHE_MSK,
#ifdef _WRS_CONFIG_SMP       /* needs to be shared */
    MMU_ATTR_VALID     | MMU_ATTR_SUP_RWX  | MMU_ATTR_CACHE_DEFAULT
    | MMU_ATTR_CACHE_COHERENCY
#else
    MMU_ATTR_VALID     | MMU_ATTR_SUP_RWX  | MMU_ATTR_CACHE_DEFAULT
#endif /* _WRS_CONFIG_SMP */
    },

    /* Map ROM for sysToMonitor */

    {
    ROM_TEXT_ADRS,     /* virtual address */
    ROM_TEXT_ADRS,     /* physical address */
    ROUND_UP (ROM_SIZE, PAGE_SIZE), /* length, then initial state: */
    MMU_ATTR_VALID_MSK | MMU_ATTR_PROT_MSK | MMU_ATTR_CACHE_MSK,
    MMU_ATTR_VALID     | MMU_ATTR_SUP_RWX  | MMU_ATTR_WRITEALLOCATE
    },

#ifdef INCLUDE_RTP

    /* map the first 2/3 extened 768M DRAM memory*/

    {
    ZYNQ7K_MEM_EXTRA,       /* virtual address */
    ZYNQ7K_MEM_EXTRA,       /* physical address */
    ROUND_UP (ZYNQ7K_MEM_EXTRA_SIZE / 3 * 2, PAGE_SIZE),  //debug
    //ZYNQ7K_MEM_EXTRA_SIZE,
    MMU_ATTR_VALID_MSK | MMU_ATTR_PROT_MSK | MMU_ATTR_CACHE_MSK,
#ifdef _WRS_CONFIG_SMP      /* needs to be shared */
    MMU_ATTR_VALID     | MMU_ATTR_SUP_RWX  | MMU_ATTR_CACHE_OFF
    | MMU_ATTR_CACHE_COHERENCY
#else
    MMU_ATTR_VALID     | MMU_ATTR_SUP_RWX  | MMU_ATTR_CACHE_OFF
#endif /* _WRS_CONFIG_SMP */
    },

#else

    /* map the extened 768M DRAM memory */

    {
    ZYNQ7K_MEM_EXTRA,       /* virtual address */
    ZYNQ7K_MEM_EXTRA,       /* physical address */
    ZYNQ7K_MEM_EXTRA_SIZE,  /* length, then initial state: */
    MMU_ATTR_VALID_MSK | MMU_ATTR_PROT_MSK | MMU_ATTR_CACHE_MSK,
#ifdef _WRS_CONFIG_SMP      /* needs to be shared */
    MMU_ATTR_VALID     | MMU_ATTR_SUP_RWX  | MMU_ATTR_CACHE_OFF
    | MMU_ATTR_CACHE_COHERENCY
#else
    MMU_ATTR_VALID     | MMU_ATTR_SUP_RWX  | MMU_ATTR_CACHE_OFF
#endif /* _WRS_CONFIG_SMP */
    },
#endif /* INCLUDE_RTP */
#if 0
    {
    0x1C000000,    /* system registers */
    0x1C000000,
    SZ_16M,
    /*MMU_ATTR_VALID_MSK | MMU_ATTR_PROT_MSK | MMU_ATTR_CACHE_MSK | MMU_ATTR_DEVICE_SHARED_MSK,
    MMU_ATTR_VALID     | MMU_ATTR_PROT_SUP_READ  | MMU_ATTR_CACHE_OFF | MMU_ATTR_DEVICE_SHARED*/
    MMU_ATTR_VALID_MSK | MMU_ATTR_PROT_MSK | MMU_ATTR_CACHE_MSK,
    MMU_ATTR_VALID     | MMU_ATTR_PROT_SUP_READ  | MMU_ATTR_CACHE_OFF
    },
#endif
    /*
     * I/O space:
     * Do not map in all I/O space, only that which has something there.
     * Otherwise we will use all of RAM allocating page tables!
     */

    {
    ZYNQ7K_SR_BASE,    /* system registers */
    ZYNQ7K_SR_BASE,
    SZ_8K,
    MMU_ATTR_VALID_MSK | MMU_ATTR_PROT_MSK | MMU_ATTR_DEVICE_SHARED_MSK,
    MMU_ATTR_VALID     | MMU_ATTR_SUP_RWX  | MMU_ATTR_DEVICE_SHARED
    },

    {
    UART_0_BASE_ADR,  /* Zynq-7000 UART */
    UART_0_BASE_ADR,
    PAGE_SIZE,
    MMU_ATTR_VALID_MSK | MMU_ATTR_PROT_MSK | MMU_ATTR_DEVICE_SHARED_MSK,
    MMU_ATTR_VALID     | MMU_ATTR_SUP_RWX  | MMU_ATTR_DEVICE_SHARED
    },

    {
    UART_1_BASE_ADR,  /* Zynq-7000 UART */
    UART_1_BASE_ADR,
    PAGE_SIZE,
    MMU_ATTR_VALID_MSK | MMU_ATTR_PROT_MSK | MMU_ATTR_DEVICE_SHARED_MSK,
    MMU_ATTR_VALID     | MMU_ATTR_SUP_RWX  | MMU_ATTR_DEVICE_SHARED
    },

#ifdef DRV_I2CBUS_ZYNQ7K
    {
    ZYNQ7K_I2C0_BASE,  /* Zynq-7000 I2c */
    ZYNQ7K_I2C0_BASE,
    PAGE_SIZE,
    MMU_ATTR_VALID_MSK | MMU_ATTR_PROT_MSK | MMU_ATTR_DEVICE_SHARED_MSK,
    MMU_ATTR_VALID     | MMU_ATTR_SUP_RWX  | MMU_ATTR_DEVICE_SHARED
    },

    {
    ZYNQ7K_I2C1_BASE,  /* Zynq-7000 I2c */
    ZYNQ7K_I2C1_BASE,
    PAGE_SIZE,
    MMU_ATTR_VALID_MSK | MMU_ATTR_PROT_MSK | MMU_ATTR_DEVICE_SHARED_MSK,
    MMU_ATTR_VALID     | MMU_ATTR_SUP_RWX  | MMU_ATTR_DEVICE_SHARED
    },
#endif /* DRV_I2CBUS_ZYNQ7K */

#ifdef INCLUDE_ZYNQ7K_SPI
    {
    ZYNQ7K_SPI0_BASE,  /* Zynq-7000 SPI */
    ZYNQ7K_SPI0_BASE,
    PAGE_SIZE,
    MMU_ATTR_VALID_MSK | MMU_ATTR_PROT_MSK | MMU_ATTR_DEVICE_SHARED_MSK,
    MMU_ATTR_VALID     | MMU_ATTR_SUP_RWX  | MMU_ATTR_DEVICE_SHARED
    },

    {
    ZYNQ7K_SPI1_BASE,  /* Zynq-7000 SPI */
    ZYNQ7K_SPI1_BASE,
    PAGE_SIZE,
    MMU_ATTR_VALID_MSK | MMU_ATTR_PROT_MSK | MMU_ATTR_DEVICE_SHARED_MSK,
    MMU_ATTR_VALID     | MMU_ATTR_SUP_RWX  | MMU_ATTR_DEVICE_SHARED
    },
#endif
    {
    ZYNQ7K_GPIO_BASE,  /* Zynq-7000 gpio */
    ZYNQ7K_GPIO_BASE,
    PAGE_SIZE,
    MMU_ATTR_VALID_MSK | MMU_ATTR_PROT_MSK | MMU_ATTR_DEVICE_SHARED_MSK,
    MMU_ATTR_VALID     | MMU_ATTR_SUP_RWX  | MMU_ATTR_DEVICE_SHARED
    },

#ifdef DRV_VXBEND_ZYNQMAC
    {
    ZYNQ7K_GEM0_BASE,  /* Zynq-7000 Ethernet */
    ZYNQ7K_GEM0_BASE,
    PAGE_SIZE,
    MMU_ATTR_VALID_MSK | MMU_ATTR_PROT_MSK | MMU_ATTR_DEVICE_SHARED_MSK,
    MMU_ATTR_VALID     | MMU_ATTR_SUP_RWX  | MMU_ATTR_DEVICE_SHARED
    },
#endif  /* DRV_VXBEND_ZYNQMAC */

#ifdef INCLUDE_ZYNQ7K_2_ETH
    {
    ZYNQ7K_GEM1_BASE,  /* Zynq-7000 Ethernet */
    ZYNQ7K_GEM1_BASE,
    PAGE_SIZE,
    MMU_ATTR_VALID_MSK | MMU_ATTR_PROT_MSK | MMU_ATTR_DEVICE_SHARED_MSK,
    MMU_ATTR_VALID     | MMU_ATTR_SUP_RWX  | MMU_ATTR_DEVICE_SHARED
    },
#endif  /* DRV_VXBEND_ZYNQMAC */
    
#ifdef DRV_RESOURCE_ZYNQ7K_DEVC
    {
    ZYNQ7K_DEVCFG_BASE,  /* Zynq-7000 DevCfg */
    ZYNQ7K_DEVCFG_BASE,
    PAGE_SIZE,
    MMU_ATTR_VALID_MSK | MMU_ATTR_PROT_MSK | MMU_ATTR_DEVICE_SHARED_MSK,
    MMU_ATTR_VALID     | MMU_ATTR_SUP_RWX  | MMU_ATTR_DEVICE_SHARED
    },

    {
    ZYNQ7K_AXI_GP0_BASE,  /* AXI Memory block of GP0 to the PL*/
    ZYNQ7K_AXI_GP0_BASE,
    ZYNQ7K_AXI_GP0_SIZE,
    MMU_ATTR_VALID_MSK | MMU_ATTR_PROT_MSK | MMU_ATTR_DEVICE_SHARED_MSK,
    MMU_ATTR_VALID | MMU_ATTR_SUP_RWX | MMU_ATTR_DEVICE_SHARED
    },

    {
    ZYNQ7K_AXI_GP1_BASE,  /* AXI Memory block of GP1 to the PL*/
    ZYNQ7K_AXI_GP1_BASE,
    ZYNQ7K_AXI_GP1_SIZE,
    MMU_ATTR_VALID_MSK | MMU_ATTR_PROT_MSK | MMU_ATTR_DEVICE_SHARED_MSK,
    MMU_ATTR_VALID | MMU_ATTR_SUP_RWX | MMU_ATTR_DEVICE_SHARED
    },
#endif  /* DRV_RESOURCE_ZYNQ7K_DEVC */

    {
    ZYNQ7K_PERIPHBASE, /* MPCore functions including SCU and Timers */
    ZYNQ7K_PERIPHBASE,
    SZ_16K,
    MMU_ATTR_VALID_MSK | MMU_ATTR_PROT_MSK | MMU_ATTR_DEVICE_SHARED_MSK,
    MMU_ATTR_VALID     | MMU_ATTR_SUP_RWX  | MMU_ATTR_DEVICE_SHARED
    },

    {
    ZYNQ7K_OCM_BASE,   /* OCM */
    ZYNQ7K_OCM_BASE,
    SZ_64K,
    MMU_ATTR_VALID_MSK | MMU_ATTR_PROT_MSK | MMU_ATTR_DEVICE_SHARED_MSK,
    MMU_ATTR_VALID     | MMU_ATTR_SUP_RWX  | MMU_ATTR_DEVICE_SHARED
    },

#if defined(DRV_STORAGE_SDHC) || defined(DRV_ZYNQ_SDHC_CTRL)
    {
    ZYNQ7K_SDHC0_BASE,   /* SDIO */
    ZYNQ7K_SDHC0_BASE,
    SZ_8K,
    MMU_ATTR_VALID_MSK | MMU_ATTR_PROT_MSK | MMU_ATTR_DEVICE_SHARED_MSK,
    MMU_ATTR_VALID     | MMU_ATTR_SUP_RWX  | MMU_ATTR_DEVICE_SHARED
    },
#endif /* DRV_STORAGE_SDHC || DRV_ZYNQ_SDHC_CTRL */

#if defined(INCLUDE_USB) || defined(INCLUDE_FSL_TCD)
    {
    ZYNQ7K_USB0_BASE,   /* USB0 */
    ZYNQ7K_USB0_BASE,
    PAGE_SIZE,
    MMU_ATTR_VALID_MSK | MMU_ATTR_PROT_MSK | MMU_ATTR_DEVICE_SHARED_MSK,
    MMU_ATTR_VALID     | MMU_ATTR_SUP_RWX  | MMU_ATTR_DEVICE_SHARED
    },
#endif /* INCLUDE_USB || INCLUDE_FSL_TCD */

#ifdef INCLUDE_ZYNQ7K_QSPI
    {
    ZYNQ7K_QSPI_BASE,   /* QSPI */
    ZYNQ7K_QSPI_BASE,
    PAGE_SIZE,
    MMU_ATTR_VALID_MSK | MMU_ATTR_PROT_MSK | MMU_ATTR_DEVICE_SHARED_MSK,
    MMU_ATTR_VALID     | MMU_ATTR_SUP_RWX  | MMU_ATTR_DEVICE_SHARED
    },

    {
    SPI_FLASH_BASE_ADRS,
    SPI_FLASH_BASE_ADRS,
    SPI_FLASH_MEM_SIZE,
    MMU_ATTR_VALID_MSK | MMU_ATTR_PROT_MSK | MMU_ATTR_DEVICE_SHARED_MSK,
    MMU_ATTR_VALID     | MMU_ATTR_SUP_RWX  | MMU_ATTR_DEVICE_SHARED
    },
#endif /* INCLUDE_ZYNQ7K_QSPI */

#ifdef DRV_DMA_PL330
    {
    ZYNQ7K_PL330_DMA_CTLR_BASE,   /* DMA */
    ZYNQ7K_PL330_DMA_CTLR_BASE,
    ZYNQ7K_PL330_DMA_SIZE,
    MMU_ATTR_VALID_MSK | MMU_ATTR_PROT_MSK | MMU_ATTR_DEVICE_SHARED_MSK,
    MMU_ATTR_VALID     | MMU_ATTR_SUP_RWX  | MMU_ATTR_DEVICE_SHARED
    },
#endif /* DRV_DMA_PL330 */

#ifdef INCLUDE_AXI_ETHERNET
    {
    ZYNQ7K_AXI_ETH_BASE,  /* AXI ETH */
    ZYNQ7K_AXI_ETH_BASE,
    ZYNQ7K_AXI_ETH_SIZE,/* PAGE_SIZE or ZYNQ7K_AXI_ETH_SIZE ?*/
    MMU_ATTR_VALID_MSK | MMU_ATTR_PROT_MSK | MMU_ATTR_DEVICE_SHARED_MSK,
    MMU_ATTR_VALID     | MMU_ATTR_SUP_RWX  | MMU_ATTR_DEVICE_SHARED
    },
#endif  /* INCLUDE_AXI_ETHERNET */

#ifdef INCLUDE_AXI_DMA
    {
    ZYNQ7K_AXI_DMA_BASE,   /* AXI DMA */
    ZYNQ7K_AXI_DMA_BASE,
    ZYNQ7K_AXI_DMA_SIZE,
    MMU_ATTR_VALID_MSK | MMU_ATTR_PROT_MSK | MMU_ATTR_DEVICE_SHARED_MSK,
    MMU_ATTR_VALID     | MMU_ATTR_SUP_RWX  | MMU_ATTR_DEVICE_SHARED
    },
#endif /* INCLUDE_AXI_DMA */

#ifdef INCLUDE_ZYNQ7K_AD

    {
    ZYNQ7K_AD_BASE,
    ZYNQ7K_AD_BASE,
    ZYNQ7K_AD_RESOURCE_SIZE,
    MMU_ATTR_VALID_MSK | MMU_ATTR_PROT_MSK | MMU_ATTR_DEVICE_SHARED_MSK,
    MMU_ATTR_VALID     | MMU_ATTR_SUP_RWX  | MMU_ATTR_DEVICE_SHARED
    },
#endif

#ifdef INCLUDE_ZYNQ7K_RADAR

    {
    ZYNQ7K_RADAR_BASE,
    ZYNQ7K_RADAR_BASE,
    ZYNQ7K_RADAR_RESOURCE_SIZE,
    MMU_ATTR_VALID_MSK | MMU_ATTR_PROT_MSK | MMU_ATTR_DEVICE_SHARED_MSK,
    MMU_ATTR_VALID     | MMU_ATTR_SUP_RWX  | MMU_ATTR_DEVICE_SHARED
    },
#endif

#ifdef INCLUDE_ZYNQ7K_PL_UART0
    {
    ZYNQ7K_PL_COM0_BASE,
    ZYNQ7K_PL_COM0_BASE,
    ZYNQ7K_PL_COM0_RESOURCE_SIZE,
    MMU_ATTR_VALID_MSK | MMU_ATTR_PROT_MSK | MMU_ATTR_DEVICE_SHARED_MSK,
    MMU_ATTR_VALID     | MMU_ATTR_SUP_RWX  | MMU_ATTR_DEVICE_SHARED
    },
    
    {
    ZYNQ7K_PL_COM0_BASE + 0x1000,
    ZYNQ7K_PL_COM0_BASE + 0x1000,
    ZYNQ7K_PL_COM0_RESOURCE_SIZE,
    MMU_ATTR_VALID_MSK | MMU_ATTR_PROT_MSK | MMU_ATTR_DEVICE_SHARED_MSK,
    MMU_ATTR_VALID     | MMU_ATTR_SUP_RWX  | MMU_ATTR_DEVICE_SHARED
    },
    
#endif
#ifdef INCLUDE_ZYNQ7K_PL_UART1
    {
    ZYNQ7K_PL_COM1_BASE,
    ZYNQ7K_PL_COM1_BASE,
    ZYNQ7K_PL_COM1_RESOURCE_SIZE,
    MMU_ATTR_VALID_MSK | MMU_ATTR_PROT_MSK | MMU_ATTR_DEVICE_SHARED_MSK,
    MMU_ATTR_VALID     | MMU_ATTR_SUP_RWX  | MMU_ATTR_DEVICE_SHARED
    },
    
    {
    ZYNQ7K_PL_COM1_BASE + 0x1000,
    ZYNQ7K_PL_COM1_BASE + 0x1000,
    ZYNQ7K_PL_COM1_RESOURCE_SIZE,
    MMU_ATTR_VALID_MSK | MMU_ATTR_PROT_MSK | MMU_ATTR_DEVICE_SHARED_MSK,
    MMU_ATTR_VALID     | MMU_ATTR_SUP_RWX  | MMU_ATTR_DEVICE_SHARED
    },
    
#endif
    };

int sysPhysMemDescNumEnt = NELEMENTS (sysPhysMemDesc);

#endif /* INCLUDE_MMU */

/* locals */
#if defined(DRV_STORAGE_SDHC) || defined(DRV_ZYNQ_SDHC_CTRL)
LOCAL UINT32 sysSdhcClkFreqGet (void);
LOCAL BOOL zynqSdCardWpCheck (void);
#endif /* DRV_STORAGE_SDHC || DRV_ZYNQ_SDHC_CTRL */

#ifdef DRV_VXBEND_ZYNQMAC
IMPORT MMU_TRANS_TBL * *mmuContextTbl;
LOCAL BOOL ifMemCached (UINT32 virtAddr);
LOCAL void sysZynq7kGemClkSet (UINT32  unit, UINT32 clkVal, BOOL exFlag);
#endif  /* DRV_VXBEND_ZYNQMAC */

#ifdef DRV_RESOURCE_ZYNQ7K_DEVC
LOCAL void sysDevcLvlShftrSet (UINT32 setVal);
LOCAL void sysDevcFpgaResetSet (UINT32 setVal);
#endif /* DRV_RESOURCE_ZYNQ7K_DEVC */


#ifdef _WRS_CONFIG_SMP

/* constant used with IPI to request reboot of application processors */

#define APPCORE_REBOOT  0xFEFEFEF0

/* constant used with IPI to request core0 reboot */

#define BOOTCORE_REBOOT 0x45600000

LOCAL UINT32 rebootVar = 0;     /* it passes the CPU index */

/* it protect from multiple reboots */

LOCAL SPIN_LOCK_ISR_DECL (rebootLock, 0);

/* Non-Boot CPU Start info. Managed by sysCpuEnable */

struct sysMPCoreStartup
    {
    UINT32      newPC;          /* Address of 'C' based startup code */
    UINT32      newSP;          /* Stack pointer for startup */
    UINT32      newArg;         /* vxWorks kernel entry point */
    UINT32      newSync;        /* Translation Table Base and sync */
    };

extern struct sysMPCoreStartup sysMPCoreStartup[VX_SMP_NUM_CPUS];

#endif /* _WRS_CONFIG_SMP */

/* externals */

#ifndef _ARCH_SUPPORTS_PROTECT_INTERRUPT_STACK
IMPORT void sysIntStackSplit (char *, long);
#endif /* !_ARCH_SUPPORTS_PROTECT_INTERRUPT_STACK */

/* forward declarations */

void    sysUsDelay (int);
void    sysMsDelay (int);
void    sysDelay ();

IMPORT void (*_vxb_usDelayRtn) (int delayTime);
IMPORT void (*_vxb_msDelayRtn) (int delayTime);
IMPORT void (*_vxb_delayRtn) (void);

IMPORT void mmuCortexA8TtbrSetAll (UINT32, UINT32);
IMPORT void   mmuCortexA8AcrSet (UINT32 acrVal);

#ifdef _WRS_CONFIG_SMP
IMPORT void   mmuCortexA8DacrSet (UINT32 dacrVal);
IMPORT STATUS sysArmGicDevInit (void);
IMPORT void   mmuCortexA8AEnable (UINT32 cacheState);
IMPORT void   mmuCortexA8ADisable (void);
IMPORT void   armInitExceptionModes (void);
IMPORT void   sysCpuInit (void);
IMPORT void   cacheCortexA9MPCoreSMPInit (void);
IMPORT void   mmuCortexA8TLBIDFlushAll (void);
IMPORT MMU_LEVEL_1_DESC * mmuCortexA8TtbrGet (void);

UINT32        sysCpuAvailableGet (void);
STATUS        sysCpuEnable (unsigned int, void (* startFunc) (void), char *);
#endif /* _WRS_CONFIG_SMP */

/* included source files */

/* network */

#ifdef ETHERNET_MAC_HANDLER
#   include "sysNet.c"
#endif /* ETHERNET_MAC_HANDLER */

#ifdef INCLUDE_L2_CACHE
#   include "sysL2Cache.c"
#endif /* INCLUDE_L2_CACHE */

#ifdef INCLUDE_ZYNQ7K_QSPI
#   include "qspiFlashMem.c"
#endif /* INCLUDE_ZYNQ7K_QSPI */

#include "nvRamToFlash.c"
#include "hwconf.c"
#include "sysBspCommon.c"

#ifdef INCLUDE_VFP
IMPORT STATUS vfpEnable (void);
IMPORT STATUS vfpDisable (void);
#endif

/*******************************************************************************
*
* sysHwInit0 - perform early BSP-specific initialization
*
* This routine performs such BSP-specific initialization as is necessary before
* the architecture-independent cacheLibInit can be called. It is called
* from usrInit () before cacheLibInit (), before sysHwInit () and before BSS
* has been cleared.
*
* RETURNS: N/A
*
* ERRNO: N/A
*/

void sysHwInit0 (void)
    {
#ifdef _WRS_CONFIG_SMP
    volatile UINT32 scuVal;

    /* setup AUX register and announce we are part of SMP */

    mmuCortexA8AcrSet (AUX_CTL_REG_FW | AUX_CTL_REG_L1_PRE_EN);

    /* enable SCU */

    scuVal = XLNX_ZYNQ7K_REGISTER_READ (ZYNQ7K_SCU_CTRL);
    scuVal |= ZYNQ7K_SCU_CTRL_EN;
    XLNX_ZYNQ7K_REGISTER_WRITE (ZYNQ7K_SCU_CTRL, scuVal);

#else

    /* setup AUX register and enable L1 prefetch */

    mmuCortexA8AcrSet (AUX_CTL_REG_L1_PRE_EN);

#endif /* _WRS_CONFIG_SMP */

#ifdef INCLUDE_CACHE_SUPPORT

    /*
     * Install the appropriate cache library, no address translation
     * routines are required for this BSP, as the default memory map has
     * virtual and physical addresses the same.
     */

    cacheCortexA9LibInstall (mmuPhysToVirt, mmuVirtToPhys);

#ifdef INCLUDE_L2_CACHE
   sysL2CacheInit (ZYNQ7K_L2_CTLR_BASE);
#endif /* INCLUDE_L2_CACHE */

#endif /* INCLUDE_CACHE_SUPPORT */

#ifdef INCLUDE_MMU

    /* Install the appropriate MMU library and translation routines */

    mmuCortexA8LibInstall (mmuPhysToVirt, mmuVirtToPhys);

#endif /* defined (INCLUDE_MMU) */

    return;
    }

/*******************************************************************************
*
* sysHwInit - initialize the CPU board hardware
*
* This routine initializes various features of the hardware.
* Normally, it is called from usrInit () in usrConfig.c.
*
* NOTE: This routine should not be called directly by the user.
*
* RETURNS: N/A
*
* ERRNO: N/A
*/

void sysHwInit (void)
    {
    /* install the IRQ/SVC interrupt stack splitting routine */

#ifndef _ARCH_SUPPORTS_PROTECT_INTERRUPT_STACK
    _func_armIntStackSplit = sysIntStackSplit;
#endif    /* !_ARCH_SUPPORTS_PROTECT_INTERRUPT_STACK */

    XLNX_ZYNQ7K_REGISTER_WRITE (ZYNQ7K_SR_LOCK, ZYNQ7K_SR_LOCK_ALL);

    /* enable global timer counter free running */

    XLNX_ZYNQ7K_REGISTER_WRITE (CTXA9_GLOBAL_TMR_CONFIG, 1);

    hardWareInterFaceInit ();

    _vxb_usDelayRtn = &sysUsDelay;
    _vxb_msDelayRtn = &sysMsDelay;
    _vxb_delayRtn = &sysDelay;

#if defined(INCLUDE_USB) || defined(INCLUDE_FSL_TCD)
    /* Take USB out of Reset */

    XLNX_ZYNQ7K_REGISTER_WRITE (ZYNQ7K_GPIO_DIR0, ZYNQ7K_GPIO_BIT7);
    XLNX_ZYNQ7K_REGISTER_WRITE (ZYNQ7K_GPIO_OEN0, ZYNQ7K_GPIO_BIT7);
    VX_MEM_BARRIER_W ();

    XLNX_ZYNQ7K_REGISTER_WRITE (ZYNQ7K_GPIO_DATA0, ZYNQ7K_GPIO_BIT7);
    XLNX_ZYNQ7K_REGISTER_WRITE (ZYNQ7K_GPIO_DATA0, 0);
    XLNX_ZYNQ7K_REGISTER_WRITE (ZYNQ7K_GPIO_DATA0, ZYNQ7K_GPIO_BIT7);
#endif /* INCLUDE_USB || INCLUDE_FSL_TCD */

#ifdef INCLUDE_ZYNQ7K_QSPI
        qspiFlashInit1 ();
#endif /*  INCLUDE_ZYNQ7K_QSPI */

#ifdef  FORCE_DEFAULT_BOOT_LINE
/*
#undef DEFAULT_BOOT_LINE
#define DEFAULT_BOOT_LINE \
    "gem(0,0)host:vxWorks h=192.168.1.20 e=192.168.1.10:ffffff00 \
     g=192.168.1.1 u=target pw=target f=0x8 tn=xlnx_zynq7k"
     strncpy (sysBootLine, DEFAULT_BOOT_LINE, strlen (DEFAULT_BOOT_LINE)+1);
*/
    sysNvRamGet (sysBootLine, BOOT_LINE_SIZE, 0); /* óéóúvxworks?ú???ˉ??è?2?êyê±óDBUG￡??aà??±?ó?????ˉ2?êy′óFLASH?D?áè?2￠?3?μ??sysBootLine±?á? */
#endif /* FORCE_DEFAULT_BOOT_LINE */
    }

/*******************************************************************************
*
* sysHwInit2 - additional system configuration and initialization
*
* This routine connects system interrupts and does any additional
* configuration necessary. Note that this is called from
* sysClkConnect () in the timer driver.
*
* RETURNS: N/A
*
* ERRNO: N/A
*/

void sysHwInit2 (void)
    {
    static BOOL initialized = FALSE;

    /* ifdef INCLUDE_RTP, add 2/3 of the EXTRA RAM to kernel, the rest to RTP */

#ifdef INCLUDE_RTP
    size_t memAddedToPool = ROUND_UP (ZYNQ7K_MEM_EXTRA_SIZE / 3 * 2, PAGE_SIZE);
#endif /* INCLUDE_RTP */

    if (initialized)
        {
        return;
        }

    vxbDevInit ();

#ifdef DRV_I2CBUS_ZYNQ7K
    /*
     * Set pca9548 I2C switch channel, open I2C channel.
     * Note that, currently, the I2C driver of zynq does not support
     * read access to pca9548.
     */

    //vxbI2cByNameWrite ("pca9548", 0, 0x1f, 0, 0);
#endif /* DRV_I2CBUS_ZYNQ7K */

#ifdef INCLUDE_SIO_UTILS
    sysSerialConnectAll ();
#endif

#ifdef INCLUDE_ZYNQ7K_QSPI
    qspiFlashInit2 ();
#endif /* INCLUDE_ZYNQ7K_QSPI */

#ifdef DRV_RESOURCE_ZYNQ7K_DEVC
    /* Enable FPGA */

    XLNX_ZYNQ7K_SR_REGISTER_WRITE (ZYNQ7K_SR_LVL_SHFTR_EN, ZYNQ7K_LVL_SHFTR_EN);
    XLNX_ZYNQ7K_SR_REGISTER_WRITE (ZYNQ7K_SR_FPGA_RST, ZYNQ7K_FPGA_RST_EXIT);
#endif /* DRV_RESOURCE_ZYNQ7K_DEVC */

    taskSpawn ("tDevConn", 11, 0, 10000, vxbDevConnect,
               0, 1, 2, 3, 4, 5, 6, 7, 8, 9);

    initialized = TRUE;

#ifdef INCLUDE_RTP
#   ifdef INCLUDE_MMU_GLOBAL_MAP
    (void) adrSpaceRAMAddToPool ((PHYS_ADDR) ZYNQ7K_MEM_EXTRA, ZYNQ7K_MEM_EXTRA_SIZE);
    (void) adrSpaceRAMReserve ((PHYS_ADDR) ZYNQ7K_MEM_EXTRA, memAddedToPool);
#   endif
    (void) memAddToPool (ZYNQ7K_MEM_EXTRA, memAddedToPool);
#else
#   ifdef INCLUDE_MMU_GLOBAL_MAP
    (void) adrSpaceRAMAddToPool ((PHYS_ADDR) ZYNQ7K_MEM_EXTRA, ZYNQ7K_MEM_EXTRA_SIZE);
    (void) adrSpaceRAMReserve ((PHYS_ADDR) ZYNQ7K_MEM_EXTRA, ZYNQ7K_MEM_EXTRA_SIZE);
#   endif
    (void) memAddToPool (ZYNQ7K_MEM_EXTRA, ZYNQ7K_MEM_EXTRA_SIZE);
#endif /* INCLUDE_RTP */
    }

/*******************************************************************************
*
* sysToMonitor - transfer control to the ROM monitor
*
* This routine transfers control to the ROM monitor. It is usually called
* only by reboot () -- which services ^X -- and bus errors at interrupt
* level.  However, in some circumstances, the user may wish to introduce a
* new <startType> to enable special boot ROM facilities.
*
* RETURNS: Does not return.
*
* ERRNO: N/A
*/

STATUS sysToMonitor
    (
    int startType    /* passed to ROM to tell it how to boot */
    )
    {
    FUNCPTR  pRom;
    int      i;
    int      intID;
    int      j;
    volatile UINT32 intrAck;
    UINT32   intActiveBits;

#ifdef _WRS_CONFIG_SMP
    cpuset_t cpuList;
    volatile int idx;
    int srcCpuId;

    /* firstAPCore makes sure that IPI is sent once */

    static int firstAPCore = TRUE;

    /* if the current core is not core0, we won't run sysToMonitor directly */

    if (vxCpuIndexGet () != 0)
        {

        /*
         * APPCORE_REBOOT means that all other cores are indicated to shutdown
         * by core0
         */

        if ((startType & 0xFFFFFFF0) == APPCORE_REBOOT)
            {

            /* disable Core ints */

            XLNX_ZYNQ7K_REGISTER_WRITE (ZYNQ7K_GIC_CPU_CONTROL, 0x0);

            /*
             * core0 sent the IPI to Application Processor (AP) to reboot.
             * end the interrupt, because ISR in interrupt controller driver
             * has read (and cleared) this register.
             */

            XLNX_ZYNQ7K_REGISTER_WRITE (ZYNQ7K_GIC_CPU_END_INTR,
                                                          INT_LVL_MPCORE_IPI08);

            /* empty interrupt ack fifo */

            intrAck = XLNX_ZYNQ7K_REGISTER_READ (ZYNQ7K_GIC_CPU_ACK) &
                                                               GIC_INT_SPURIOUS;

            while ((intrAck != GIC_INT_SPURIOUS))
               {
               XLNX_ZYNQ7K_REGISTER_WRITE (ZYNQ7K_GIC_CPU_END_INTR, intrAck);

               intrAck = XLNX_ZYNQ7K_REGISTER_READ (ZYNQ7K_GIC_CPU_ACK) &
                                                               GIC_INT_SPURIOUS;
               }

            /* flush data cache */

            CACHE_PIPE_FLUSH ();

            /* disable the MMU, cache (s) and write-buffer */

            mmuCortexA8ADisable ();

            /* Make sure we go back to the bootMonitor loop */

            pRom = (FUNCPTR)(ROM_WARM_ADRS);

            /* jump to boot ROM */

            (* pRom)(0);
            }
        else
            {

            /*
             * If code reached here, it means that reboot is requested and
             * code is executing on one of AP cores.
             * Notify core0 to run sysToMonitor and wait until
             * core0 sends an IPI to APs to shut down.
             * firstAPCore value check makes sure that only one AP core
             * sends notification to core0.
             * Spin lock makes sure that two APs don't modify firstAPCore
             * simultaneously
             */

            SPIN_LOCK_ISR_TAKE (&rebootLock);

            if (firstAPCore)
                {
                rebootVar = (BOOTCORE_REBOOT | startType |
                             (vxCpuIndexGet () << 10));

                vxIpiEmit (INT_LVL_MPCORE_RESET, 1);

                firstAPCore = FALSE;
                }

            SPIN_LOCK_ISR_GIVE (&rebootLock);

            /* wait for a reset from core0 */

            for (;;);
            }
        }

#endif /* _WRS_CONFIG_SMP */

    sysClkDisable ();

    intIFLock ();

#ifdef _WRS_CONFIG_SMP

    /* here is the core 0 */

    if ((rebootVar & 0xFFF00000) == BOOTCORE_REBOOT)
        {

        /*
         * core0 is informed by other core through IPI to reboot, so we must
         * acknowledge the IPI (SGI) interrupt.
         */

        srcCpuId = (rebootVar & 0x00001C00);

        XLNX_ZYNQ7K_REGISTER_WRITE (ZYNQ7K_GIC_CPU_END_INTR,
                                    INT_LVL_MPCORE_RESET | srcCpuId);

        startType = rebootVar & 0x0000000F;
        }

    /* clear entry address flags */

    XLNX_ZYNQ7K_REGISTER_WRITE (ZYNQ7K_OCM_BOOT_ADR, 0xffffffff);

    /* reset all other cores */

    if ((cpuList = vxCpuEnabledGet ()) && (cpuList > 1))
        {
        for (idx = 1; idx < VX_SMP_NUM_CPUS; idx++)
            {
            if (cpuList & (1 << idx))
                {
                vxIpiEmit (INT_LVL_MPCORE_IPI08, 1 << idx);
                }
            }
        }

    /* delay for non-boot core to shutdown */

    for (idx = 0; idx < 0x1ffff; idx++);

#endif /* _WRS_CONFIG_SMP */

    /* disable GIC cpu interface */

    XLNX_ZYNQ7K_REGISTER_WRITE (ZYNQ7K_GIC_CPU_CONTROL, 0x0);

    /* disable GIC distributor */

    XLNX_ZYNQ7K_REGISTER_WRITE (ZYNQ7K_GIC1_BASE + ZYNQ7K_GIC_DIST_CONTROL,
                                0x0);

    /* empty interrupt ack fifo */

    intrAck = XLNX_ZYNQ7K_REGISTER_READ (ZYNQ7K_GIC_CPU_ACK) & \
                                         GIC_INT_SPURIOUS;

    while ((intrAck != GIC_INT_SPURIOUS) && (intrAck >= SGI_INT_MAX) )
        {
        XLNX_ZYNQ7K_REGISTER_WRITE (ZYNQ7K_GIC_CPU_END_INTR, intrAck);

        intrAck = XLNX_ZYNQ7K_REGISTER_READ (ZYNQ7K_GIC_CPU_ACK) & \
                                             GIC_INT_SPURIOUS;
        }

    /* disable all SPI interrupts */

    for (i = SPI_START_INT_NUM; i < SYS_INT_LEVELS_MAX; i += BITS_PER_WORD)
        {
        XLNX_ZYNQ7K_REGISTER_WRITE (ZYNQ7K_GIC1_BASE + \
            ZYNQ7K_GIC_DIST_ENABLE_CLR1 + (0x4 * NWORD (i)), 0xffffffff);
        }

#ifdef INCLUDE_MMU
    VM_ENABLE (FALSE);     /* Disable the MMU, cache (s) and write-buffer */
#   ifdef _WRS_CONFIG_SMP
        mmuCortexA8AcrSet (0);
#   endif /* _WRS_CONFIG_SMP */
#endif /* INCLUDE_MMU */

#ifdef INCLUDE_VFP
    vfpDisable ();
#endif /* INCLUDE_VFP */

    pRom = (FUNCPTR)(ROM_WARM_ADRS);

    /* jump to boot ROM */

    (* pRom)(startType);

    return OK;
    }

#if defined (_WRS_CONFIG_SMP)

/*******************************************************************************
*
* sysCpuStart - vxWorks startup
*
* This routine establishes a CPUs vxWorks envirnonment.  Note that the MMU
* and caches have been enabled before this routine is called.
*
* This is NOT callable from C.
*
* RETURNS: N/A
*
* ERRNO: N/A
*
* \NOMANUAL
*/

LOCAL void sysCpuStart
    (
    void (*startFunc) (void),
    UINT32 cpuNum
    )
    {
    volatile UINT32 intrAck;

    /* flush all pending local interrupts */

    intrAck = XLNX_ZYNQ7K_REGISTER_READ (ZYNQ7K_GIC_CPU_ACK) & GIC_INT_SPURIOUS;

    while (intrAck != GIC_INT_SPURIOUS)
        {
        XLNX_ZYNQ7K_REGISTER_WRITE (ZYNQ7K_GIC_CPU_END_INTR, intrAck);

        intrAck = XLNX_ZYNQ7K_REGISTER_READ (ZYNQ7K_GIC_CPU_ACK) & \
                                            GIC_INT_SPURIOUS;
        }

    XLNX_ZYNQ7K_REGISTER_WRITE (ZYNQ7K_GIC1_BASE + ZYNQ7K_GIC_DIST_PEND_CLR1,
                               0xffff);

#ifdef INCLUDE_VFP
    vfpEnable ();
#endif

    /* Initialise ARM exception mode registers */

    armInitExceptionModes ();

    /* Enable Local S/W interrupts */

    sysArmGicDevInit ();

    /* Tell the boot CPU we are here */

    sysMPCoreStartup[cpuNum].newSync = 0;

    intIFUnlock (0);

    /* Enter the Kernel */

    (*startFunc)();

    }

/*******************************************************************************
*
* sysCpuEnable - enable a multi core CPU
*
* This routine brings a CPU out of reset
*
* RETURNS: OK or ERROR
*
* ERRNO: N/A
*
* \NOMANUAL
*/

STATUS sysCpuEnable
    (
    unsigned int cpuNum,
    void (*startFunc) (void),
    char *stackPtr
    )
    {
    /*
     * sysCpuEnable is called sequentially for each Application Processor.
     * The IPIs have to be enabled once.
     * sysCpuEnableFirst variable is used to make sure that IPIs
     * are not enabled multiple times.
     */

    static INT32 sysCpuEnableFirst = 1;

    /* Validate cpuNum */

    if (cpuNum < 1 || cpuNum >= VX_SMP_NUM_CPUS)
        return (ERROR);

    if (sysCpuEnableFirst == 1)
        {

        /*
         * IPIs cannot be connected in sysToMonitor, because interrupt handlers
         * cannot be installed in interrupt context.
         * sysToMonitor can be called from interrupt context as well
         * (WIND00321261).
         */

        /*
         * Connect and enable IPI for Application Processor cores.
         * The INT_LVL_MPCORE_IPI08 is sent by core 0 to all the AP cores.
         */

        vxIpiConnect (INT_LVL_MPCORE_IPI08, (IPI_HANDLER_FUNC)(sysToMonitor),
                     (void *)(APPCORE_REBOOT));

        vxIpiEnable (INT_LVL_MPCORE_IPI08);

        /*
         * Connect and enable IPI for core0.
         * The INT_LVL_MPCORE_RESET is sent by an Application processor core
         * to core0.
         */

        vxIpiConnect (INT_LVL_MPCORE_RESET, (IPI_HANDLER_FUNC)(sysToMonitor),
                     (void *) &rebootVar);

        vxIpiEnable (INT_LVL_MPCORE_RESET);

        sysCpuEnableFirst = 0;
        }

    /* Setup init values */

    sysMPCoreStartup[cpuNum].newPC   = (UINT32)sysCpuStart;
    sysMPCoreStartup[cpuNum].newSP   = (UINT32)stackPtr;
    sysMPCoreStartup[cpuNum].newArg  = (UINT32)startFunc;
    sysMPCoreStartup[cpuNum].newSync = (UINT32)mmuCortexA8TtbrGetAll ();

    /* Make sure data hits memory */

    cacheFlush ((CACHE_TYPE)DATA_CACHE, (void *)sysMPCoreStartup,
               (size_t)(sizeof (sysMPCoreStartup)));

    cachePipeFlush ();

    /* Setup CPU for init */

    XLNX_ZYNQ7K_REGISTER_WRITE (ZYNQ7K_OCM_BOOT_ADR, (UINT32)sysCpuInit);

    VX_SYNC_BARRIER ();

    /* wake up core1 from wfe using sev. */

    WRS_ASM ("sev");

    return OK;
    }

#endif /* if defined (_WRS_CONFIG_SMP) */

/*******************************************************************************
*
* sysCpuAvailableGet - return the number of CPUs available
*
* This routine gets the number of CPUs available.
*
* RETURNS:  number of CPU cores available
*
* ERRNO: N/A
*/

UINT32 sysCpuAvailableGet (void)
    {
    return (XLNX_ZYNQ7K_REGISTER_READ (ZYNQ7K_SCU_CONFIG) & 0x3) + 1;
    }

/*******************************************************************************
*
* sysUsDelay - delay at least the specified amount of time (in microseconds)
*
* This routine delays for approximately one us. When system timer
* count register add 1 tick,
* 1 tick = 1/system timer clk = 1/ZYNQ7K_TIMERS_CLK = 1/333333333(s)
* timer grows up.
*
* NOTE:  This routine will not relinquish the CPU; it is meant to perform a
* busy loop delay.  The minimum delay that this routine will provide is
* approximately 10 microseconds.  The maximum delay is approximately the
* size of UINT32; however, there is no roll-over compensation for the total
* delay time, so it is necessary to back off two times the system tick rate
* from the maximum.
*
* RETURNS: N/A
*
* ERRNO: N/A
*/

void sysUsDelay
    (
    int        delay          /* length of time in US to delay */
    )
    {
    UINT64      oldVal;
    UINT64      newVal;
    UINT64      decElapsed = 0;
    UINT64      totalDelta;
    UINT32      countLo;
    UINT32      countHi;
    UINT32      tmp;
    INT32       loop = 10;

    if(delay == 0)
        return;

    /* add to round up before div to provide "at least" */

    totalDelta = (UINT64)(ZYNQ7K_TIMERS_CLK + 1000000) / 1000000;
    totalDelta = totalDelta * (UINT64)delay;

    tmp = XLNX_ZYNQ7K_REGISTER_READ (CTXA9_GLOBAL_TMR_BASE + 0x4);

    do
        {
        countHi = tmp;
        countLo = XLNX_ZYNQ7K_REGISTER_READ (CTXA9_GLOBAL_TMR_BASE);
        tmp     = XLNX_ZYNQ7K_REGISTER_READ (CTXA9_GLOBAL_TMR_BASE + 0x4);
        } while (tmp != countHi);

    oldVal = (((UINT64) countHi) << 32) | ((UINT64) countLo);

    while (decElapsed < totalDelta)
        {
        tmp = XLNX_ZYNQ7K_REGISTER_READ (CTXA9_GLOBAL_TMR_BASE + 0x4);
        do
            {
            countHi = tmp;
            countLo = XLNX_ZYNQ7K_REGISTER_READ (CTXA9_GLOBAL_TMR_BASE);
            tmp     = XLNX_ZYNQ7K_REGISTER_READ (CTXA9_GLOBAL_TMR_BASE + 0x4);
            } while (tmp != countHi);

        newVal = (((UINT64) countHi) << 32) | ((UINT64) countLo);

        if(newVal == oldVal)
            {
            if (loop-- > 0)
                continue;
            }

        /* no rollover */

        if (newVal > oldVal)
            decElapsed += (newVal - oldVal);

        /* rollover */

        else
            {

            /* not a real rollover, timer reset */

            if (((oldVal>>32) & 0xFFFFFFFF) != 0xFFFFFFFF)
                decElapsed += 10;
            else
                decElapsed +=
                       ((0xFFFFFFFF - ((oldVal<<32)>>32)) + ((newVal<<32)>>32));
            }

        oldVal = newVal;
        }
    }

/*******************************************************************************
*
* sysMsDelay - 1ms delay increments
*
* This routine consumes 1ms of time * delay.
*
* RETURNS: N/A
*
* ERRNO: N/A
*/

void sysMsDelay
    (
    int      delay                   /* length of time in MS to delay */
    )
    {
    sysUsDelay ( (int) delay * 1000 );
    }

/*******************************************************************************
*
* sysDelay - delay for approximately one millisecond
*
* This routine delays for approximately one milli-second.
*
* RETURNS: N/A
*/

void sysDelay (void)
    {
    sysMsDelay (1);
    }

#ifdef DRV_VXBEND_ZYNQMAC
/*******************************************************************************
*
* sysZynq7kGemClkSet - set the clock control register for the Gem END
*
* Set the correct clock register value for the Gem ethernet device.
*
* RETURNS: OK
*/

LOCAL void sysZynq7kGemClkSet
    (
    UINT32  unit,
    UINT32  clkVal,
    BOOL    exFlag
    )
    {

    /*
     * if use external PHY, because EMIO clk is set by PL,
     * it is difficult for gem driver to caculate divisor value,
     * so here don't need to reset, just return directly.
     */

    if (exFlag == TRUE)
        {
        return;
        }

    if (unit == 0)
        {
        if (clkVal == GEM_1G_CLK)
            XLNX_ZYNQ7K_SR_REGISTER_WRITE (ZYNQ7K_SR_GEM0_CLK, ZYNQ7K_GEM_1G_CLK);
        else if (clkVal == GEM_100M_CLK)
            XLNX_ZYNQ7K_SR_REGISTER_WRITE (ZYNQ7K_SR_GEM0_CLK,
                                           ZYNQ7K_GEM_100M_CLK);
        else if (clkVal == GEM_10M_CLK)
            XLNX_ZYNQ7K_SR_REGISTER_WRITE (ZYNQ7K_SR_GEM0_CLK, ZYNQ7K_GEM_10M_CLK);
       }
    else if (unit == 1)
        {
        if (clkVal == GEM_1G_CLK)
            XLNX_ZYNQ7K_SR_REGISTER_WRITE (ZYNQ7K_SR_GEM1_CLK, ZYNQ7K_GEM_1G_CLK);
        else if (clkVal == GEM_100M_CLK)
            XLNX_ZYNQ7K_SR_REGISTER_WRITE (ZYNQ7K_SR_GEM1_CLK,
                                           ZYNQ7K_GEM_100M_CLK);
        else if (clkVal == GEM_10M_CLK)
            XLNX_ZYNQ7K_SR_REGISTER_WRITE (ZYNQ7K_SR_GEM1_CLK, ZYNQ7K_GEM_10M_CLK);
        }
    else
       return;
    }

/*******************************************************************************
*
* ifMemCached - check if memory is cacheble
*
* This routine checks if memory is cacheble
*
* RETURNS: TRUE/FALSE
*/

LOCAL BOOL ifMemCached
    (
    UINT32 virtAddr
    )
    {
    UINT32 desc;

    /*  get L1 page table descriptor */

    desc = *(UINT32 *)((UINT32)(mmuContextTbl[0]->pLevel1Table) +
                       (((virtAddr & 0xfff00000) >> 20) * 4));

    /*
     *  check if this is a section descriptor, if not a section descriptor then
     *  get the L2 page table descriptor.
     */

    if ((desc & 0x3) != 0x2)
        desc = *(UINT32 *)((desc & 0xfffffc00) + (((virtAddr & 0xff000) >> 12) * 4));

    if (desc & 0x8) /*  memory cacheable ? */
        return TRUE;
    else
        return FALSE;
    }
#endif  /* DRV_VXBEND_ZYNQMAC */

/*******************************************************************************
*
* sysMalloc - mem malloc
*
* This routine malloc memory.
*
* RETURNS: N/A
*/

void *sysMalloc
    (
    size_t size
    )
    {
    return cacheDmaMalloc (size);
    }

/*******************************************************************************
*
* sysFree - mem free
*
* This routine free memory.
*
* RETURNS: N/A
*/

void sysFree
    (
    void *addr
    )
    {
    cacheDmaFree (addr);
    }

#if defined(DRV_STORAGE_SDHC) || defined(DRV_ZYNQ_SDHC_CTRL)
#define ZYNQ7K_IO_PLL_FREQ            1000000000
#define ZYNQ7K_SDIO_CLK_DIVISOR_SHIFT 8
#define ZYNQ7K_SDIO_CLK_DIVISOR_MASK  0x3F
#define ZYNQ7K_SDIO_CLK_CTRL          (ZYNQ7K_SR_BASE+0x150)
/*******************************************************************************
*
* sysSdhcClkFreqGet - get sdhc freq
*
* This routine get sdhc freq.
*
* RETURNS: freq
*/

LOCAL UINT32 sysSdhcClkFreqGet (void)
    {
    UINT32 sdioClkCtrl;

    sdioClkCtrl = XLNX_ZYNQ7K_REGISTER_READ (ZYNQ7K_SDIO_CLK_CTRL);

    return (ZYNQ7K_IO_PLL_FREQ /
            ((sdioClkCtrl >> ZYNQ7K_SDIO_CLK_DIVISOR_SHIFT) &
             ZYNQ7K_SDIO_CLK_DIVISOR_MASK));
    }

LOCAL BOOL zynqSdCardWpCheck (void)
    {
    return FALSE;
    }
#endif /* DRV_STORAGE_SDHC || DRV_ZYNQ_SDHC_CTRL */

#ifdef DRV_RESOURCE_ZYNQ7K_DEVC
/*******************************************************************************
*
* sysDevcLvlShftrSet - set slcr LVL_SHFTR_EN register
*
* This routine set slcr LVL_SHFTR_EN register to enable or
* disable Level Shifters between PS and PL.
*
* RETURNS: N/A
*/

LOCAL void sysDevcLvlShftrSet
    (
    UINT32 setVal
    )
    {
    XLNX_ZYNQ7K_SR_REGISTER_WRITE (ZYNQ7K_SR_LVL_SHFTR_EN, setVal);
    }

/*******************************************************************************
*
* sysDevcFpgaResetSet - set slcr FPGA_RST register
*
* This routine set slcr FPGA_RST register to enable or
* disable the reset of FPGA.
*
* RETURNS: N/A
*/

LOCAL void sysDevcFpgaResetSet
    (
    UINT32 setVal
    )
    {
    XLNX_ZYNQ7K_SR_REGISTER_WRITE (ZYNQ7K_SR_FPGA_RST, setVal);
    }
#endif /* DRV_RESOURCE_ZYNQ7K_DEVC */
