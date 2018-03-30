/* config.h - Xilinx Zynq-7000 configuration header */

/*
 * Copyright (c) 2011-2015 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
04jan15,c_l  Add 32MBytes of flash support for ZC706. (VXW6-23897)
04nov14,c_l  fix INCLUDE_ZYNQ7K_QSPI definition. (VXW6-83719)
31jul14,c_l  add DRV_ARM_GLOBAL_TIMER. (VXW6-83146)
06jun14,c_l  Update BSP version. (VXW6-83017)
07may14,c_l  add ROM_WARM_ADRS. (VXW6-82585)
22apr14,g_x  update BSP version (VXW6-81785)
24mar14,xms  Update BSP version
             add two macros for GEM. (VXW6-70152)
11feb14,c_l  Update BSP version. (VXW6-70150)
01n,05aug13,c_l  Correct INCLUDE_USB component definition. (WIND00429232)
01m,06jun13,y_c  update BSP_REV.
01l,22apr13,zgl  minor update for robust.(WIND00413417)
01k,18apr13,zgl  added DRV_I2C_GENERIC_DEV as require of DRV_I2CBUS_ZYNQ7K.
                 (WIND00413408)
01j,15apr13,y_c  add required components for TFFS. (WIND00411921)
01i,08apr13,zgl  fixed smp mode timer issue. (WIND00394997)
01h,07apr13,y_c  add 1G ram support in PS.
01g,07apr13,y_c  remove #undef INCLUDE_USB. (WIND00411028)
01f,30jan13,ljg  add USB TCD support.
01e,09jan13,fao  add INCLUDE_SYS_MEM_MGMT. (WIND00397943)
01d,19oct12,fao  change TFFS settings.(WIND00383467)
01c,15sep12,fao  uprev release.
01b,15jun12,fao  update for the first release.
01a,09may11,rab  created from arm_a9_ctx rev 01a
*/

/*
DESCRIPTION
This file contains the configuration parameters for the
Xilinx Zynq-7000 board.
*/

#ifndef __INCconfigh
#define __INCconfigh

#ifdef __cplusplus
extern "C" {
#endif

/*
 * BSP version/revision identification, should be placed
 * before #include "configAll.h"
 */

#define BSP_VERSION     "6.9"
#define BSP_REV         "/8" /* 0 for first revision */

#include <configAll.h>

#include "xlnx_zynq7k.h"

#undef  CONSOLE_BAUD_RATE
#define CONSOLE_BAUD_RATE 115200

#ifdef _WRS_CONFIG_SMP
#   define SYS_MODEL "Xilinx Zynq-7000 ARMv7 MPCore"
#else
#   define SYS_MODEL "Xilinx Zynq-7000 ARMv7"
#endif /* _WRS_CONFIG_SMP */

#define INCLUDE_VXBUS
#define INCLUDE_HWMEM_ALLOC
#define INCLUDE_PLB_BUS
#define INCLUDE_PARAM_SYS
#define INCLUDE_SIO_UTILS
#define DRV_SIO_ZYNQ7K
#define INCLUDE_INTCTLR_LIB
#define DRV_ARM_GIC
#define INCLUDE_TIMER_SYS
#define DRV_VXBEND_ZYNQMAC
#define INCLUDE_MII_BUS
#define INCLUDE_GENERICPHY
#undef  DRV_I2CBUS_ZYNQ7K
#define INCLUDE_ZYNQ7K_SPI
#define INCLUDE_ZYNQ7K_QSPI
#define DRV_CHAR_ZYNQ7K_DEVC
#undef DRV_RESOURCE_ZYNQ7K_AD
#define INCLUDE_ZYNQ7K_2_ETH
/*
 * 对于SD控制器，系统自带了DRV_STORAGE_SDHC驱动，
 * 但是这个驱动只支持SD卡不支持MMC,
 * 后来我开发了DRV_ZYNQ_SDHC_CTRL，SD/MMC两者皆可支持
 */
#undef  DRV_STORAGE_SDHC
#define DRV_ZYNQ_SDHC_CTRL

#ifdef  DRV_ZYNQ_SDHC_CTRL
#undef  DRV_STORAGE_SDHC
#endif

/* AXI external devices */
#undef INCLUDE_AXI_DMA   /* AXI DMA */
#ifdef INCLUDE_AXI_DMA
#endif /* INCLUDE_AXI_DMA */

#undef INCLUDE_AXI_ETHERNET /* AXI ETH */
#ifdef INCLUDE_AXI_ETHERNET
#define INCLUDE_AXI_DMA
#define DRV_VXBEND_XLNX_TEMAC
#endif /* INCLUDE_AXI_ETHERNET */

#undef INCLUDE_ZYNQ7K_AD
#ifdef  INCLUDE_ZYNQ7K_AD
#   define INCLUDE_ZYNQ7K_BOARD1
#   define INCLUDE_ZYNQ7K_BOARD2
#   define INCLUDE_ZYNQ7K_BOARD3
#   define INCLUDE_ZYNQ7K_BOARD4
#endif

#if 0
//#undef INCLUDE_ZYNQ7K_RADAR
#define INCLUDE_ZYNQ7K_PL_UART0
#define INCLUDE_ZYNQ7K_PL_UART1
#endif

#ifndef _WRS_CONFIG_SMP
#   define DRV_ARM_MPCORE_TIMER
#else /* _WRS_CONFIG_SMP */
#   define DRV_TIMER_ZYNQ7K
#endif /* !_WRS_CONFIG_SMP */

#undef DRV_DMA_PL330

#ifdef _WRS_CONFIG_SMP
#   define INCLUDE_VXIPI
#endif /* _WRS_CONFIG_SMP */

#define HWMEM_POOL_SIZE 50000
#define INCLUDE_VXB_CMDLINE

#if 1
#define DEFAULT_BOOT_LINE \
    "gem(0,0)host:vxWorks h=192.168.1.20 e=192.168.1.10:ffffff00 \
     g=192.168.1.1 u=target pw=target f=0x8 tn=xlnx_zynq7k"
#else
#define DEFAULT_BOOT_LINE \
    "fs(0,0)host:/sd0:1/vxWorks h=192.168.1.20 e=192.168.1.10:ffffff00 \
     g=192.168.1.1 u=target pw=target f=0x0 tn=xlnx_zynq7k"
#endif
#define BOOTROM_DIR  "/sd0:1"

#define FORCE_DEFAULT_BOOT_LINE

/* Memory configuration */

#define USER_RESERVED_MEM     0x00000000

#define LOCAL_MEM_LOCAL_ADRS  0x00100000    //1M

#define LOCAL_MEM_SIZE        (0x10000000 - 0x500000)  //256M - 5M

#define LOCAL_MEM_END_ADRS    (LOCAL_MEM_LOCAL_ADRS + LOCAL_MEM_SIZE) //1M + 251M

/*
 * The constants ROM_TEXT_ADRS and ROM_SIZE are defined
 * in config.h and Makefile.
 * All definitions for these constants must be identical.
 */

#define ROM_BASE_ADRS       0x0fc00000          /* ROM base                    */
#define ROM_TEXT_ADRS       0x0fc00000          /* code start addr in ROM      */
#define ROM_WARM_ADRS       (ROM_TEXT_ADRS + 4) /* ROM warm entry address      */

#define ROM_SIZE            0x00200000       //2M   /* size of ROM holding VxWorks */
#define ROM_SIZE_TOTAL      0x00400000       //4M   /* total size of ROM           */

/* Macro for enlarge RAM to 1G */

#define ZYNQ7K_MEM_EXTRA       (LOCAL_MEM_END_ADRS + ROM_SIZE_TOTAL)  //252M + 4M

#define ZYNQ7K_MEM_EXTRA_SIZE  0x20000000       //512M

/* Close boot clear */

#undef ROMSTART_BOOT_CLEAR

/* Serial port configuration */

#undef  NUM_TTY
#define NUM_TTY             N_SIO_CHANNELS

/*
 * Cache/MMU configuration
 *
 * Note that when MMU is enabled, cache modes are controlled by
 * the MMU table entries in sysPhysMemDesc[], not the cache mode
 * macros defined here.
 */

/*
 * We use the generic architecture libraries, with caches/MMUs present. A
 * call to sysHwInit0() is needed from within usrInit before
 * cacheLibInit() is called.
 */

#ifndef _ASMLANGUAGE
IMPORT void sysHwInit0 (void);
#endif /* _ASMLANGUAGE */

#define INCLUDE_SYS_HW_INIT_0
#define SYS_HW_INIT_0()         sysHwInit0()

#ifdef _WRS_CONFIG_SMP
#   define VX_SMP_NUM_CPUS 2
#endif /* _WRS_CONFIG_SMP */

/*
 * These processors can be either write-through or copyback (defines
 * whether write-buffer is enabled); cache itself is write-through.
 */

#undef  USER_I_CACHE_MODE
#define USER_I_CACHE_MODE       (CACHE_COPYBACK)

#undef  USER_D_CACHE_MODE
#define USER_D_CACHE_MODE       (CACHE_COPYBACK)

#ifdef BOOTAPP
#   undef INCLUDE_MMU_BASIC
#   undef INCLUDE_MMU_FULL
#   undef INCLUDE_MMU_GLOBAL_MAP
#   undef INCLUDE_EDR_SYSDBG_FLAG
#else /*BOOTAPP*/
#   define INCLUDE_MMU_BASIC
#   define INCLUDE_MMU_FULL
#   define INCLUDE_CACHE_SUPPORT
#endif /*BOOTAPP*/

#define INCLUDE_VFP /* vector floating point support */

/*
 * interrupt mode - interrupts can be in either preemptive or non-preemptive
 * mode. For preemptive mode, change INT_MODE to INT_PREEMPT_MODEL
 */

#define INT_MODE                 INT_NON_PREEMPT_MODEL

#define ISR_STACK_SIZE           (0x2000)    /* size of ISR stack, in bytes */

/* timer config */

#ifdef _WRS_CONFIG_SMP
#   define SYSCLK_TIMER_NAME    "zynqTimer"
#   define SYSCLK_TIMER_UNIT    0
#   define SYSCLK_TIMER_NUM     0

#   define AUXCLK_TIMER_NAME    "zynqTimer"
#   define AUXCLK_TIMER_UNIT    1
#   define AUXCLK_TIMER_NUM     0

#   define TIMESTAMP_TIMER_NAME     "armGlobalTimer"
#   define TIMESTAMP_TIMER_UNIT     0
#   define TIMESTAMP_TIMER_NUM      0
#endif /* _WRS_CONFIG_SMP */

/* L2 cache support */

#define INCLUDE_L2_CACHE

/* I2C device support */

#ifdef DRV_I2C_PCFRTC
#   define INCLUDE_TIMER_RTC
#endif /* DRV_I2C_PCFRTC */

#ifdef DRV_I2C_EEPROM
#   define INCLUDE_EEPROMDRV
#endif /* DRV_I2C_EEPROM */

#if defined(DRV_I2C_PCFRTC) || defined(DRV_I2C_EEPROM)
#   define DRV_I2CBUS_ZYNQ7K
#endif /* DRV_I2C_PCFRTC || DRV_I2C_EEPROM */

#ifdef DRV_I2CBUS_ZYNQ7K
#   define INCLUDE_I2C_BUS
#   define DRV_I2C_GENERIC_DEV
#endif /* DRV_I2CBUS_ZYNQ7K */

#ifdef DRV_SPIBUS_ZYNQ7K
#   define INCLUDE_SPI_BUS
#   define DRV_SPI_GENERIC_DEV
#endif /* DRV_I2CBUS_ZYNQ7K */

#ifdef DRV_STORAGE_SDHC
#   define INCLUDE_DOSFS
#endif

#ifdef DRV_ZYNQ_SDHC_CTRL
#   define INCLUDE_DOSFS
#   define DRV_MMCSTORAGE_CARD
#   define DRV_SDSTORAGE_CARD
#endif

#ifdef INCLUDE_ZYNQ7K_QSPI
#   define SPI_FLASH_BASE_ADRS      (0xFC000000) /* flash Base Address            */

/*
 * Example for flash configuration:
 * 2 x 16 MBytes Flash ROM (S25FL128SAG) are available on board ZC706.
 *        #define SPI_FLASH_SIZE           (SZ_32M)
 *        #define SPI_BUS_TYPE             SPI_DUAL_8BIT
 *
 * 1 x 16 MBytes Flash ROM (S25FL128SAG) is available on board ZC706.
 *        #define SPI_FLASH_SIZE           (SZ_16M)
 *        #define SPI_BUS_TYPE             SPI_SINGLE_4BIT
 *
 * 1 x 16 MBytes Flash ROM (N25Q128) is available on board ZC702.
 *        #define SPI_FLASH_SIZE           (SZ_16M)
 *        #define SPI_BUS_TYPE             SPI_SINGLE_4BIT
 *
 *
 * SPI_FLASH_SIZE:
 * Note that this definition may lead to the old bootrom vs new VxWorks
 * image mis-matching the NVRAM location. In order to backward compatibility,
 * it is only 16 MBytes are available by default for both ZC702 and
 * ZC706.
 *
 * SPI_BUS_TYPE:
 * For 8 bit parallel configuration, even bits of the data words are located in
 * lower memory and odd bits of data are located in upper memory, and the
 * Quad-SPI controller sends erase command to both chips, so two sectors will
 * be erased on every erase command.
 */

#   define SPI_SINGLE_4BIT          (0x1)
#   define SPI_DUAL_8BIT            (0x2)
#   define SPI_DUAL_4BIT            (0x3) /* not supported currently */
#   define SPI_SINGLE_LEGACY        (0x4) /* not supported currently */

#   define SPI_BUS_TYPE             SPI_SINGLE_4BIT

#if ((SPI_BUS_TYPE == SPI_DUAL_4BIT) || (SPI_BUS_TYPE == SPI_SINGLE_LEGACY))
#error "SPI_DUAL_4BIT and SPI_SINGLE_LEGACY mode are not supported."
#endif /*((SPI_BUS_TYPE == SPI_DUAL_4BIT)||(SPI_BUS_TYPE == SPI_SINGLE_LEGACY)) */

#if (SPI_BUS_TYPE == SPI_DUAL_8BIT)
#   define SPI_FLASH_SECTOR_SIZE    (SZ_64K * 2)     /* two sector size */
#   define SPI_FLASH_PAGE_SIZE      (0x100  * 2)     /* two page size   */
#else
#   define SPI_FLASH_SECTOR_SIZE    (SZ_64K)         /* sector size     */
#   define SPI_FLASH_PAGE_SIZE      (0x100)          /* page size       */
#endif /* (SPI_BUS_TYPE == SPI_DUAL_8BIT) */

#   define SPI_FLASH_SIZE           (SZ_32M)

#if (SPI_FLASH_SIZE > SZ_32M)
#error "Invalid flash size value, the maximum addressable memory size is 32MB."
#endif /* SPI_FLASH_SIZE > SZ_32M*/

#   define SPI_FLASH_MEM_SIZE       (SPI_FLASH_SIZE)
#   define SPI_FLASH_SECTOR_NUM     ((SPI_FLASH_SIZE) / (SPI_FLASH_SECTOR_SIZE))

/*
 * FLASH_OVERLAY means saving the sector firstly and then write the
 * speficied offset.
 */

#   define FLASH_OVERLAY
#   undef  NV_BOOT_OFFSET
#   define NV_BOOT_LINE_SIZE        (0x200)
#   define NV_BOOT_OFFSET           (0)
#   define NV_RAM_SIZE              (SZ_64K * 2)
#   define NV_RAM_ADRS              (SPI_FLASH_SIZE - NV_RAM_SIZE)
#   define NV_MAC_ADRS_OFFSET       (SPI_FLASH_SECTOR_SIZE)
#else
#   undef  NV_RAM_SIZE
#   define NV_RAM_SIZE NONE
#endif /* INCLUDE_ZYNQ7K_QSPI */

/* uncomment to support TFFS */

/* #define INCLUDE_TFFS */

#ifdef INCLUDE_TFFS

/* FLASH_BASE_ADRS is the base address used by TFFS */

#   define FLASH_BASE_ADRS          (SPI_FLASH_BASE_ADRS)

/*
 * FLASH_SIZE is the flash size used by TFFS.
 * This definition can be modified.
 */

#   define FLASH_SIZE               (SPI_FLASH_SIZE - NV_RAM_SIZE)

#   define FLASH_SECTOR_SIZE        (SPI_FLASH_SECTOR_SIZE)

#   define INCLUDE_TFFS_MOUNT
#   define INCLUDE_TL_FTL

#   define INCLUDE_FS_MONITOR
#   define INCLUDE_FS_EVENT_UTIL
#   define INCLUDE_ERF
#   define INCLUDE_XBD
#   define INCLUDE_DEVICE_MANAGER
#   define INCLUDE_XBD_BLK_DEV
#   define INCLUDE_XBD_PART_LIB
#endif /* INCLUDE_TFFS */

/* uncomment to support USB */

/* #define INCLUDE_USB */

#ifdef INCLUDE_USB
#   define INCLUDE_USB_INIT
#   define INCLUDE_EHCI
#   define INCLUDE_EHCI_INIT
#endif /* INCLUDE_USB */

#ifdef INCLUDE_FSL_TCD
#   define FSL_USB_DR_DEVICE_IO_BASE            ZYNQ7K_USB0_BASE
#   define FSL_USB_DR_DEVICE_INT_NUM            INT_VEC_USB0
#   define FSL_USB_DR_DEVICE_BE_REG             FALSE
#   define FSL_USB_DR_DEVICE_BE_DESC            FALSE
#   define FSL_USB_DR_DEVICE_BE_SETUP           FALSE
#   define FSL_USB_DR_DEVICE_SYS_CONF           FALSE
#   define FSL_USB_DR_DEVICE_BUFFER_ES          TRUE
#   define FSL_USB_DR_DEVICE_PHY_MODE           FSL_USB_DR_PHY_ULPI
#   define INCLUDE_USB_TARG
#   define INCLUDE_MS_EMULATOR
#   define INCLUDE_MS_EMULATOR_INIT
#   define INCLUDE_DOSFS
#   define INCLUDE_XBD_RAMDRV
#endif /* INCLUDE_FSL_TCD */

#if (defined(INCLUDE_USB)) && (defined(INCLUDE_FSL_TCD))
#   error "INCLUDE_USB and INCLUDE_FSL_TCD can not be defined at same \
time for they use same USB OTG port!"
#endif /* INCLUDE_USB && INCLUDE_FSL_TCD */

/* Support network devices */

#define ZYNQ_EMIO_GMII  1  /* Use for the GMII/MII via EMIO interface */
#define ZYNQ_MIO_RGMII  0  /* Use for the RGMII via internal MIO interface */

#ifdef DRV_VXBEND_ZYNQMAC
#   ifndef INCLUDE_NETWORK
#       define INCLUDE_NETWORK
#   endif /* INCLUDE_NETWORK */
#   ifndef INCLUDE_END
#       define INCLUDE_END
#   endif /* INCLUDE_END */

#   define MAC_ADRS_LEN         6
#   define MAX_MAC_ADRS         3
#   define MAX_MAC_DEVS         3

#   define ETHERNET_MAC_HANDLER

#   ifdef ETHERNET_MAC_HANDLER
#       ifdef BOOTAPP
#           define INCLUDE_BOOT_ETH_MAC_HANDLER
#       endif
#   endif /* ETHERNET_MAC_HANDLER */

/* MAC address configuration */

#   define XLNX_ENET0           0x00
#   define XLNX_ENET1           0x0a
#   define XLNX_ENET2           0x35

#   define CUST_ENET3           0x00
#   define CUST_ENET4           0x01
#   define CUST_ENET5           0x22

/* Default MAC address */

#   define ENET_DEFAULT0        XLNX_ENET0
#   define ENET_DEFAULT1        XLNX_ENET1
#   define ENET_DEFAULT2        XLNX_ENET2

/*
 *  INCLUDE_SYS_MEM_MGMT is used to define the specific memory malloc/free
 *  functions so that IP stack can use them instead of the default ones there
 */

#   define INCLUDE_SYS_MEM_MGMT

#endif /* DRV_VXBEND_ZYNQMAC */

#ifdef __cplusplus
}
#endif
#endif  /* __INCconfigh */

#if defined(PRJ_BUILD)
#include "prjParams.h"
#endif
