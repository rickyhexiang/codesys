/* xlnx_zynq7k.h - Xilinx Zynq-7000 board header file */

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
04jan15,c_l  Add PSS_IDCODE definition. (VXW6-23897)
01aug14,c_l  add DRV_ARM_GLOBAL_TIMER. (VXW6-83146)
16jul14,c_l  Add protection for system level control registers. (VXW6-83097)
05jun14,c_l  correct ZYNQ7K_SR_ARM_PLL_OFFSET definition. (VXW6-82931)
28may14,c_l  correct ZYNQ7K_I2C_CLK definition. (VXW6-82671)
25apr14,c_l  correct ZYNQ7K_TIMERS_CLK definition. (VXW6-80653)
01f,11jul13,z_l  correct ZYNQ7K_I2C_CLK definition. (WIND00422526)
01e,29may13,y_c  add support for the Programmable Logic.(WIND00417766)
01d,08apr13,zgl  fixed smp mode timer issue. (WIND00394997)
01c,15sep12,fao  add DMA and TTC support.
01b,15jun12,fao  update for the first release.
01a,09may11,rab  created
*/

/*
This file contains I/O address and related constants for the
Xilinx Zynq-7000 board.
*/

#ifndef __INCxlnx_zynq7kh
#define __INCxlnx_zynq7kh

#ifdef __cplusplus
extern "C" {
#endif

/* DRAM */

/* OCM */

#define ZYNQ7K_OCM_MEM_ADRS        (0x00000000)
#define ZYNQ7K_OCM_MEM_SIZE        (0x00100000)

/* FLASH (Boot Monitor) */

#define ZYNQ7K_ROM_BASE_VIRT       (ROM_TEXT_ADRS)
#define ZYNQ7K_ROM_BASE_PHYS       (ROM_TEXT_ADRS)

/* system registers */

#define ZYNQ7K_SR_BASE              (0xF8000000)
#define ZYNQ7K_SR_SCL               (0x00)
#define ZYNQ7K_SR_LOCK_OFFSET       (0x04)
#define ZYNQ7K_SR_UNLOCK_OFFSET     (0x08)
#define ZYNQ7K_SR_LOCK_STAT_OFFSET  (0x0C)
#define ZYNQ7K_SR_ARM_PLL_OFFSET    (0x100)
#define ZYNQ7K_SR_GEM0_CLK_OFFSET   (0x140)
#define ZYNQ7K_SR_GEM1_CLK_OFFSET   (0x144)
#define ZYNQ7K_SR_DMAC_RST_OFFSET   (0x20C)
#define ZYNQ7K_SR_I2C_RST_OFFSET    (0x224)
#define ZYNQ7K_SR_LQSPI_RST_OFFSET  (0x230)
#define ZYNQ7K_SR_FPGA_RST_OFFSET   (0x240) /* FPGA Software Reset Control */
#define ZYNQ7K_SR_PSS_IDCODE_OFFSET (0x530)
#define ZYNQ7K_SR_LVL_SHFTR_OFFSET  (0x900) /* Level Shifters Enable */

#define ZYNQ7K_SR_LOCK             (ZYNQ7K_SR_BASE + ZYNQ7K_SR_LOCK_OFFSET)
#define ZYNQ7K_SR_UNLOCK           (ZYNQ7K_SR_BASE + ZYNQ7K_SR_UNLOCK_OFFSET)
#define ZYNQ7K_SR_LOCK_STAT        (ZYNQ7K_SR_BASE + ZYNQ7K_SR_LOCK_STAT_OFFSET)
#define ZYNQ7K_SR_GEM0_CLK         (ZYNQ7K_SR_BASE + ZYNQ7K_SR_GEM0_CLK_OFFSET)
#define ZYNQ7K_SR_GEM1_CLK         (ZYNQ7K_SR_BASE + ZYNQ7K_SR_GEM1_CLK_OFFSET)
#define ZYNQ7K_SR_I2C_RST          (ZYNQ7K_SR_BASE + ZYNQ7K_SR_I2C_RST_OFFSET)
#define ZYNQ7K_SR_QSPI_RST         (ZYNQ7K_SR_BASE + ZYNQ7K_SR_LQSPI_RST_OFFSET)
#define ZYNQ7K_SR_DMA_CRST         (ZYNQ7K_SR_BASE + ZYNQ7K_SR_DMAC_RST_OFFSET)
#define ZYNQ7K_SR_FPGA_RST         (ZYNQ7K_SR_BASE + ZYNQ7K_SR_FPGA_RST_OFFSET)
#define ZYNQ7K_SR_PSS_IDCODE       (ZYNQ7K_SR_BASE + ZYNQ7K_SR_PSS_IDCODE_OFFSET)
#define ZYNQ7K_SR_LVL_SHFTR_EN     (ZYNQ7K_SR_BASE + ZYNQ7K_SR_LVL_SHFTR_OFFSET)

#define ZYNQ7K_SR_UNLOCK_ALL       (0xDF0D)
#define ZYNQ7K_SR_LOCK_ALL         (0x767B)
#define ZYNQ7K_FPGA_RST_EXIT       (0x0)
#define ZYNQ7K_LVL_SHFTR_EN        (0xf)

/* PL330 dma controller base */

#define ZYNQ7K_PL330_DMA_CTLR_BASE (0xF8003000)
#define ZYNQ7K_PL330_DMA_SIZE      (0x1000)

/* Motherboard Peripherals */

#define ZYNQ7K_PERIPHBASE          (0xF8F00000)
#define ZYNQ7K_PERIPHBASE_SIZE     (SZ_16K)

/* Snoop Control Unit */

#define ZYNQ7K_SCU_BASE            (ZYNQ7K_PERIPHBASE + 0x0)
#define ZYNQ7K_SCU_CTRL            (ZYNQ7K_SCU_BASE + 0x00)
#define ZYNQ7K_SCU_CONFIG          (ZYNQ7K_SCU_BASE + 0x04)
#define ZYNQ7K_SCU_CPU_STATUS      (ZYNQ7K_SCU_BASE + 0x08)
#define ZYNQ7K_SCU_INVALIDATE_ALL  (ZYNQ7K_SCU_BASE + 0x0C)
#define ZYNQ7K_SCU_FILTER_START    (ZYNQ7K_SCU_BASE + 0x40)
#define ZYNQ7K_SCU_FILTER_END      (ZYNQ7K_SCU_BASE + 0x44)
#define ZYNQ7K_SCU_SAC             (ZYNQ7K_SCU_BASE + 0x40)
#define ZYNQ7K_SCU_SNSAC           (ZYNQ7K_SCU_BASE + 0x44)
#define ZYNQ7K_SCU_CTRL_EN         (0x00000001)

/*
 * Generic Interrupt Controller
 * Note: FIQ is not handled within VxWorks so this is just IRQ
 */

#define ZYNQ7K_GIC1_BASE           (0xF8F00000)

#define ZYNQ7K_GIC_CPU_CONTROL     (ZYNQ7K_GIC1_BASE + 0x0100)
#define ZYNQ7K_GIC_CPU_PRIORITY    (ZYNQ7K_GIC1_BASE + 0x0104)
#define ZYNQ7K_GIC_CPU_POINT       (ZYNQ7K_GIC1_BASE + 0x0108)
#define ZYNQ7K_GIC_CPU_ACK         (ZYNQ7K_GIC1_BASE + 0x010C)
#define ZYNQ7K_GIC_CPU_END_INTR    (ZYNQ7K_GIC1_BASE + 0x0110)
#define ZYNQ7K_GIC_CPU_RUNNING     (ZYNQ7K_GIC1_BASE + 0x0114)
#define ZYNQ7K_GIC_CPU_PENDING     (ZYNQ7K_GIC1_BASE + 0x0118)

/* 96 is the maximum interrupt number. It covers SGI, PPI and SPI */

#define SYS_INT_LEVELS_MAX         (96)

/* interrupt distributor */

#define ZYNQ7K_GIC_DIST_CONTROL      (0x1000)
#define ZYNQ7K_GIC_DIST_CTRL_TYPE    (0x1004)
#define ZYNQ7K_GIC_DIST_ENABLE_SET1  (0x1100)
#define ZYNQ7K_GIC_DIST_ENABLE_SET2  (0x1104)
#define ZYNQ7K_GIC_DIST_ENABLE_SET3  (0x1108)
#define ZYNQ7K_GIC_DIST_ENABLE_CLR1  (0x1180)
#define ZYNQ7K_GIC_DIST_ENABLE_CLR2  (0x1184)
#define ZYNQ7K_GIC_DIST_ENABLE_CLR3  (0x1188)
#define ZYNQ7K_GIC_DIST_PEND_SET1    (0x1200)
#define ZYNQ7K_GIC_DIST_PEND_SET2    (0x1204)
#define ZYNQ7K_GIC_DIST_PEND_SET3    (0x1208)
#define ZYNQ7K_GIC_DIST_PEND_CLR1    (0x1280)
#define ZYNQ7K_GIC_DIST_PEND_CLR2    (0x1284)
#define ZYNQ7K_GIC_DIST_PEND_CLR3    (0x1288)
#define ZYNQ7K_GIC_DIST_ACTIVE1      (0x1300)
#define ZYNQ7K_GIC_DIST_ACTIVE2      (0x1304)
#define ZYNQ7K_GIC_DIST_ACTIVE3      (0x1308)
#define ZYNQ7K_GIC_DIST_PRIORITY1    (0x1400) /* Priority reg  0- 3 */
#define ZYNQ7K_GIC_DIST_PRIORITY2    (0x1404) /* Priority reg  4- 7 */
#define ZYNQ7K_GIC_DIST_PRIORITY3    (0x1408) /* Priority reg  8-11 */
#define ZYNQ7K_GIC_DIST_PRIORITY4    (0x140C) /* Priority reg 12-15 */
#define ZYNQ7K_GIC_DIST_PRIORITY5    (0x1410) /* Priority reg 16-19 */
#define ZYNQ7K_GIC_DIST_PRIORITY6    (0x1414) /* Priority reg 20-23 */
#define ZYNQ7K_GIC_DIST_PRIORITY7    (0x1418) /* Priority reg 24-27 */
#define ZYNQ7K_GIC_DIST_PRIORITY8    (0x141C) /* Priority reg 28-31 */
#define ZYNQ7K_GIC_DIST_PRIORITY9    (0x1420) /* Priority reg 32-35 */
#define ZYNQ7K_GIC_DIST_PRIORITY10   (0x1424) /* Priority reg 36-39 */
#define ZYNQ7K_GIC_DIST_PRIORITY11   (0x1428) /* Priority reg 40-43 */
#define ZYNQ7K_GIC_DIST_PRIORITY12   (0x142C) /* Priority reg 44-47 */
#define ZYNQ7K_GIC_DIST_PRIORITY13   (0x1430) /* Priority reg 48-51 */
#define ZYNQ7K_GIC_DIST_PRIORITY14   (0x1434) /* Priority reg 52-55 */
#define ZYNQ7K_GIC_DIST_PRIORITY15   (0x1438) /* Priority reg 56-59 */
#define ZYNQ7K_GIC_DIST_PRIORITY16   (0x143C) /* Priority reg 60-63 */
#define ZYNQ7K_GIC_DIST_TARG         (0x1800)
#define ZYNQ7K_GIC_DIST_CONFIG1      (0x1C00)
#define ZYNQ7K_GIC_DIST_CONFIG2      (0x1C04)
#define ZYNQ7K_GIC_DIST_CONFIG3      (0x1C08)
#define ZYNQ7K_GIC_DIST_CONFIG4      (0x1C0C)
#define ZYNQ7K_GIC_DIST_CONFIG5      (0x1C10)
#define ZYNQ7K_GIC_DIST_CONFIG6      (0x1C14)
#define ZYNQ7K_GIC_DIST_SOFTWARE     (0x1F00)
#define ZYNQ7K_GIC_DIST_PERIPH_ID    (0x1FD0)
#define ZYNQ7K_GIC_DIST_CELL_ID      (0x1FFC)

/* Xilinx Zynq-7000 interrupt level and vectors */

#define INT_LVL_GTMR                (27)
#define INT_LVL_TMR0                (29)
#define INT_LVL_AWDT                (30)
#define INT_LVL_XADC                (39)
#define INT_LVL_DVI                 (40)
#define INT_LVL_WDOG0               (41)
#define INT_LVL_TTC0_0              (42)
#define INT_LVL_TTC0_1              (43)
#define INT_LVL_TTC0_2              (44)
#define INT_LVL_DMAC_ABORT          (45)
#define INT_LVL_DMAC_0              (46)
#define INT_LVL_DMAC_1              (47)
#define INT_LVL_DMAC_2              (48)
#define INT_LVL_DMAC_3              (49)
#define INT_LVL_DMAC_4              (72)
#define INT_LVL_DMAC_5              (73)
#define INT_LVL_DMAC_6              (74)
#define INT_LVL_DMAC_7              (75)
#define INT_LVL_QSPI                (51)
#define INT_LVL_GPIO                (52)
#define INT_LVL_USB0                (53)
#define INT_LVL_ETH0                (54)
#define INT_LVL_SDIO0               (56)
#define INT_LVL_I2C0                (57)
#define INT_LVL_SPI0                (58)
#define INT_LVL_UART0               (59)
#define INT_LVL_CAN0                (60)
#define INT_LVL_TTC1_0              (69)
#define INT_LVL_TTC1_1              (70)
#define INT_LVL_TTC1_2              (71)
#define INT_LVL_USB1                (76)
#define INT_LVL_ETH1                (77)
#define INT_LVL_I2C1                (80)
#define INT_LVL_SPI1                (81)
#define INT_LVL_UART1               (82)
#define INT_LVL_PL0					(61)
#define INT_LVL_PL1					(62)
#define INT_LVL_PL2					(63)
#define INT_LVL_PL_UART0            (68)
#define INT_LVL_PL_UART1            (67)
/*
#define INT_LVL_AXI_ETH             (INT_LVL_PL2)
#define INT_LVL_AXI_DMA_TX          (INT_LVL_PL1)
#define INT_LVL_AXI_DMA_RX          (INT_LVL_PL0)
*/

#define INT_VEC_GTMR                IVEC_TO_INUM(INT_LVL_GTMR)
#define INT_VEC_TMR0                IVEC_TO_INUM(INT_LVL_TMR0)
#define INT_VEC_AWDT                IVEC_TO_INUM(INT_LVL_AWDT)
#define INT_VEC_XADC                IVEC_TO_INUM(INT_LVL_XADC)
#define INT_VEC_DVI                 IVEC_TO_INUM(INT_LVL_DVI)
#define INT_VEC_WDOG0               IVEC_TO_INUM(INT_LVL_WDOG0)
#define INT_VEC_TTC0_0              IVEC_TO_INUM(INT_LVL_TTC0_0)
#define INT_VEC_TTC0_1              IVEC_TO_INUM(INT_LVL_TTC0_1)
#define INT_VEC_TTC0_2              IVEC_TO_INUM(INT_LVL_TTC0_2)
#define INT_VEC_DMAC_ABORT          IVEC_TO_INUM(INT_LVL_DMAC_ABORT)
#define INT_VEC_DMAC_0              IVEC_TO_INUM(INT_LVL_DMAC_0)
#define INT_VEC_DMAC_1              IVEC_TO_INUM(INT_LVL_DMAC_1)
#define INT_VEC_DMAC_2              IVEC_TO_INUM(INT_LVL_DMAC_2)
#define INT_VEC_DMAC_3              IVEC_TO_INUM(INT_LVL_DMAC_3)
#define INT_VEC_DMAC_4              IVEC_TO_INUM(INT_LVL_DMAC_4)
#define INT_VEC_DMAC_5              IVEC_TO_INUM(INT_LVL_DMAC_5)
#define INT_VEC_DMAC_6              IVEC_TO_INUM(INT_LVL_DMAC_6)
#define INT_VEC_DMAC_7              IVEC_TO_INUM(INT_LVL_DMAC_7)
#define INT_VEC_QSPI                IVEC_TO_INUM(INT_LVL_QSPI)
#define INT_VEC_USB0                IVEC_TO_INUM(INT_LVL_USB0)
#define INT_VEC_ETH0                IVEC_TO_INUM(INT_LVL_ETH0)
#define INT_VEC_SDIO0               IVEC_TO_INUM(INT_LVL_SDIO0)
#define INT_VEC_UART0               IVEC_TO_INUM(INT_LVL_UART0)
#define INT_VEC_TTC1_0              IVEC_TO_INUM(INT_LVL_TTC1_0)
#define INT_VEC_TTC1_1              IVEC_TO_INUM(INT_LVL_TTC1_1)
#define INT_VEC_TTC1_2              IVEC_TO_INUM(INT_LVL_TTC1_2)
#define INT_VEC_USB1                IVEC_TO_INUM(INT_LVL_USB1)
#define INT_VEC_ETH1                IVEC_TO_INUM(INT_LVL_ETH1)
#define INT_VEC_I2C0                IVEC_TO_INUM(INT_LVL_I2C0)
#define INT_VEC_I2C1                IVEC_TO_INUM(INT_LVL_I2C1)
#define INT_VEC_SPI0                IVEC_TO_INUM(INT_LVL_SPI0)
#define INT_VEC_SPI1                IVEC_TO_INUM(INT_LVL_SPI1)
#define INT_VEC_UART1               IVEC_TO_INUM(INT_LVL_UART1)
#define INT_VEC_PL_UART0            IVEC_TO_INUM(INT_LVL_PL_UART0)
#define INT_VEC_PL_UART1            IVEC_TO_INUM(INT_LVL_PL_UART1)
/*
#define INT_VEC_AXI_ETH             IVEC_TO_INUM(INT_LVL_AXI_ETH)
#define INT_VEC_AXI_DMA_TX          IVEC_TO_INUM(INT_LVL_AXI_DMA_TX)
#define INT_VEC_AXI_DMA_RX          IVEC_TO_INUM(INT_LVL_AXI_DMA_RX)
*/

/* signals generated from various clock generators */

#define ZYNQ7K_OSCCLK0               (25000000)   /* System bus clock (AHB) */
#define ZYNQ7K_ETHERNET_CLK          (25000000)   /* Fixed 25MHz            */
#define ZYNQ7K_TIMERS_CLK            (333333333)  /* System clock           */
#define ZYNQ7K_UART_CLK              (50000000)   /* UART clock 50Mhz       */
#define ZYNQ7K_SDHC_CLK              (33333000)   /* SDHC clock 100Mhz      */
#define ZYNQ7K_I2C_CLK               (111111111)  /* I2C input clock        */
#define ZYNQ7K_SPI_CLK               (125000000)  /* I2C input clock 125Mhz  */
#define ZYNQ7K_TTC_CLK               (111111111)  /* ttc timer clock        */


/* Ethernet Base Address */

#define ZYNQ7K_GEM0_BASE             0xE000B000
#define ZYNQ7K_GEM1_BASE             0xE000C000

#define ZYNQ7K_GEM_1G_CLK            0x00800101
#define ZYNQ7K_GEM_10M_CLK           0x00803201
#define ZYNQ7K_GEM_100M_CLK          0x00800501

/* definitions for the AMBA UART */

#if defined(INCLUDE_ZYNQ7K_PL_UART0) && defined(INCLUDE_ZYNQ7K_PL_UART1)
#define N_ZYNQ_UART_CHANNELS        (4)
#else
#define N_ZYNQ_UART_CHANNELS        (2)
#endif

#define UART_XTAL_FREQ              (ZYNQ7K_UART_CLK)
#define N_SIO_CHANNELS              (N_ZYNQ_UART_CHANNELS)
#define N_UART_CHANNELS             (N_ZYNQ_UART_CHANNELS)

#define UART_0_BASE_ADR             (0xE0000000)         /* UART 0 base addr */
#define UART_1_BASE_ADR             (0xE0001000)         /* UART 1 base addr */

/* USB */

#define ZYNQ7K_USB0_BASE            (0xE0002000)         /* USB0 base */
#define ZYNQ7K_USB1_BASE            (0xE0003000)         /* USB1 base */
#define EHCI_CAPLENGTH(base)        ((base) + 0x00100)

/* I2C */

#define ZYNQ7K_I2C0_BASE            (0xE0004000)         /* I2C0 base */
#define ZYNQ7K_I2C1_BASE            (0xE0005000)         /* I2C1 base */

/* SPI */

#define ZYNQ7K_SPI0_BASE            (0xE0006000)         /* SPI0 base */
#define ZYNQ7K_SPI1_BASE            (0xE0007000)         /* SPI1 base */

/* GPIO */

#define ZYNQ7K_GPIO_BASE            (0xE000a000)         /* GPIO base */
#define ZYNQ7K_GPIO_DATA0           (0xE000a040)         /* GPIO Data 0 */
#define ZYNQ7K_GPIO_DIR0            (0xE000a204)         /* Direction Mode 0 */
#define ZYNQ7K_GPIO_OEN0            (0xE000a208)         /* Output Enable 0 */
#define ZYNQ7K_GPIO_BIT7            (0x80)

/* SD MMC */

#define ZYNQ7K_SDHC0_BASE           (0xE0100000)         /* SDIO0 base */
#define ZYNQ7K_SDHC1_BASE           (0xE0101000)         /* SDIO1 base */

/* QSPI */

#define ZYNQ7K_QSPI_BASE            (0xE000D000)
#define ZYNQ7K_QSPI_SIZE            (0x01000000)

/* DEVCFG */

#define ZYNQ7K_DEVCFG_BASE          (0xF8007000)
#define ZYNQ7K_DEVCFG_SIZE          (0x00001000)

/* General Purpose Port to the PL */

#define ZYNQ7K_AXI_GP0_BASE          (0x40000000)
#define ZYNQ7K_AXI_GP0_SIZE          (SZ_1G)

#define ZYNQ7K_AXI_GP1_BASE          (0x80000000)
#define ZYNQ7K_AXI_GP1_SIZE          (SZ_1G)

/* AXI DMA */
#define ZYNQ7K_AXI_DMA_BASE          (0x40400000)
#define ZYNQ7K_AXI_DMA_SIZE          (SZ_64K)

/* AXI ETH */
#define ZYNQ7K_AXI_ETH_BASE          (0x43C00000)
#define ZYNQ7K_AXI_ETH_SIZE          (SZ_256K)

/* AD */
#define ZYNQ7K_AD_BASE               (0x40600000)
#define ZYNQ7K_AD_RESOURCE_SIZE      (PAGE_SIZE)
#define ZYNQ7K_AD_BOARD1_START       (0x1C000000)
#define ZYNQ7K_AD_BOARD2_START       (0x1D000000)
#define ZYNQ7K_AD_BOARD3_START       (0x1E000000)
#define ZYNQ7K_AD_BOARD4_START       (0x1F000000)
#define ZYNQ7K_AD_BUFFER_SIZE        (0x1000000)

/* 25所项目相关FPGA资源 */
#define ZYNQ7K_RADAR_BASE            (0x43C00000)
#define ZYNQ7K_RADAR_RESOURCE_SIZE   (PAGE_SIZE)

#define ZYNQ7K_PL_COM0_BASE          (0x82a00000)
#define ZYNQ7K_PL_COM0_RESOURCE_SIZE   (PAGE_SIZE)

#define ZYNQ7K_PL_COM1_BASE          (0x82a02000)
#define ZYNQ7K_PL_COM1_RESOURCE_SIZE   (PAGE_SIZE)

/* definitions for the Cortex A9 Core Private Timer */

#define ZYNQ7K_TTC0_TIMER0_BASE     (0xF8001000)         /* ttc 0 timer 0 */
#define ZYNQ7K_TTC0_TIMER1_BASE     (0xF8001004)         /* ttc 0 timer 1 */
#define ZYNQ7K_TTC0_TIMER2_BASE     (0xF8001008)         /* ttc 0 timer 2 */
#define ZYNQ7K_TTC1_TIMER0_BASE     (0xF8002000)         /* ttc 1 timer 0 */
#define ZYNQ7K_TTC1_TIMER1_BASE     (0xF8002004)         /* ttc 1 timer 1 */
#define ZYNQ7K_TTC1_TIMER2_BASE     (0xF8002008)         /* ttc 1 timer 2 */
#define ZYNQ7K_TIMER_REGS_SIZE      (SZ_4K)              /* timer regs size  */

/* definitions for the Cortex A9 Core Private Timer */

#define CTXA9_TIMER_BASE            (0xF8F00600)         /* start of timer 0 */
#define CTXA9_TIMER_REGS_SIZE       (SZ_4K)              /* timer 0          */

#define CTXA9_TIMER0_BASE           (0xF8F00600)
#define CTXA9_TIMER1_BASE           (0xF8F00620)

#define SYS_TIMER_BASE              (CTXA9_TIMER0_BASE)
#define AUX_TIMER_BASE              (CTXA9_TIMER1_BASE)

#define SYS_TIMER_INT_LVL           (INT_LVL_TIMER_2_3)

#define CTXA9_GLOBAL_TMR_BASE       (0xF8F00200)
#define CTXA9_GLOBAL_TMR_CONFIG     (0xF8F00208)

/* local timer register definitions */

#define CTRL_PRESC(x)               (((x) & 0xff) << 8)
#define CTRL_INT_ENABLE             (0x4)
#define CTRL_INT_AUTO_RELOAD        (0x2)
#define CTRL_TIMER_ENABLE           (0x1)

#define CTRL_DEFAULT_BITS           (CTRL_PRESC(0) | \
                                     CTRL_INT_AUTO_RELOAD | CTRL_TIMER_ENABLE)

#define LOCAL_TIMER_LOAD            (CTXA9_TIMER_BASE + 0x0)
#define LOCAL_TIMER_COUNTER         (CTXA9_TIMER_BASE + 0x4)
#define LOCAL_TIMER_CTRL            (CTXA9_TIMER_BASE + 0x8)

/* add corresponding INT_VEC */

#define SYS_TIMER_INT_VEC           (INT_VEC_TIMER_0_1)

/* frequency of counter/timers */

#define SYS_CLK_FREQ                (ZYNQ7K_TIMERS_CLK)

#define SYS_CLK_RATE_MIN            (1)
#define SYS_CLK_RATE_MAX            (1000)

#define AUX_CLK_RATE_MIN            (1)
#define AUX_CLK_RATE_MAX            (1000)

/* MPCore Tile Interrupt registers */

#define ZYNQ7K_MPCORE_CPU_INTERFACE  (ZYNQ7K_GIC1_BASE)
#define ZYNQ7K_MPCORE_CONTROL_REG    (0x00)
#define ZYNQ7K_MPCORE_PRIO_MASK_REG  (0x04)

#define ZYNQ7K_OCM_BASE             (0xFFFF0000)
#define ZYNQ7K_OCM_BOOT_OFFSET      (0x0000FFF0)
#define ZYNQ7K_OCM_BOOT_ADR         (ZYNQ7K_OCM_BASE + ZYNQ7K_OCM_BOOT_OFFSET)

/* L2 cache controller base */

#define ZYNQ7K_L2_CTLR_BASE         (0xF8F02000)

/* Handy sizes */

#define SZ_1K                       (0x00000400)
#define SZ_4K                       (0x00001000)
#define SZ_8K                       (0x00002000)
#define SZ_16K                      (0x00004000)
#define SZ_64K                      (0x00010000)
#define SZ_128K                     (0x00020000)
#define SZ_256K                     (0x00040000)
#define SZ_512K                     (0x00080000)
#define SZ_1M                       (0x00100000)
#define SZ_2M                       (0x00200000)
#define SZ_4M                       (0x00400000)
#define SZ_8M                       (0x00800000)
#define SZ_16M                      (0x01000000)
#define SZ_32M                      (0x02000000)
#define SZ_64M                      (0x04000000)
#define SZ_128M                     (0x08000000)
#define SZ_256M                     (0x10000000)
#define SZ_512M                     (0x20000000)
#define SZ_1G                       (0x40000000)
#define SZ_2G                       (0x80000000)
#define SCTLR_BE                    (0x02000000)

#define ARM_IMM                     #

/* level of coherency mask of CLIDR */

#define ARM_LOC_MASK                #0x7000000

/* Auxiliary Control Register */

/* cache and tlb maintenance broadcast */

#define AUX_CTL_REG_FW              (0x00000001)
#define AUX_CTL_REG_L1_PRE_EN       (0x00000004)   /* L1 prefetch enable */

#define XLNX_ZYNQ7K_REGISTER_READ(reg) \
    *(volatile UINT32 *)(reg)

#define XLNX_ZYNQ7K_REGISTER_WRITE(reg, data)\
    *(volatile UINT32 *)(reg) = (data)

#define XLNX_ZYNQ7K_SR_REGISTER_READ(reg, val)                          \
    do {                                                                \
    XLNX_ZYNQ7K_REGISTER_WRITE (ZYNQ7K_SR_UNLOCK, ZYNQ7K_SR_UNLOCK_ALL);\
    val = *(volatile UINT32 *)(reg);                                    \
    XLNX_ZYNQ7K_REGISTER_WRITE (ZYNQ7K_SR_LOCK, ZYNQ7K_SR_LOCK_ALL);    \
    } while (0)

#define XLNX_ZYNQ7K_SR_REGISTER_WRITE(reg, data)                        \
    do {                                                                \
    XLNX_ZYNQ7K_REGISTER_WRITE (ZYNQ7K_SR_UNLOCK, ZYNQ7K_SR_UNLOCK_ALL);\
    *(volatile UINT32 *)(reg) = (data);                                 \
    XLNX_ZYNQ7K_REGISTER_WRITE (ZYNQ7K_SR_LOCK, ZYNQ7K_SR_LOCK_ALL);    \
    } while (0)

/*
 * Common code for cache operations on entire data/unified caches,
 * performed by set/way to the point of coherency (PoC).
 * This code is based on 'Example code for cache maintenance operations'
 * provided in "ARM Architecture Reference Manual ARMv7-A and ARMv7-R edition
 * (ARM DDI 0406)" .
 *
 * Registers used: r0-r8. Also note that r0 is 0 when this code completes.
 */

#undef _CORTEX_AR_ENTIRE_DATA_CACHE_OP
#define _CORTEX_AR_ENTIRE_DATA_CACHE_OP(crm) \
                    \
    MRC    p15, 1, r0, c0, c0, 1    /* r0 = Cache Lvl ID register info */;\
    ANDS   r3, r0, ARM_LOC_MASK     /* get level of coherency (LoC) */;\
    MOV    r3, r3, LSR ARM_IMM 23   /* r3 = LoC << 1 */;\
    BEQ    5f            ;\
                    \
    MOV    r7, ARM_IMM 0            /* r7 = cache level << 1; start at 0 */;\
                    \
1:                    ;\
    AND    r1, r0, ARM_IMM 0x7      /* r1 = cache type(s) for this level */;\
    CMP    r1, ARM_IMM 2        ;\
    BLT    4f                       /* no data cache at this level */;\
                    \
    MCR    p15, 2, r7, c0, c0, 0    /* select the Cache Size ID register */;\
    MCR    p15, 0, r7, c7, c5, 4    /* ISB: sync change to Cache Size ID */;\
    MRC    p15, 1, r1, c0, c0, 0    /* r1 = current Cache Size ID info */;\
    AND    r2, r1, ARM_IMM 0x7      /* r2 = line length */;\
    ADD    r2, r2, ARM_IMM 4        /* add line length offset = log2(16 bytes) */;\
    LDR    r4, =0x3FF        ;\
    ANDS   r4, r4, r1, LSR ARM_IMM 3 /* r4 = (# of ways - 1); way index */;\
    CLZ    r5, r4                    /* r5 = bit position of way size increment */;\
    LDR    r6, =0x00007FFF        ;\
    ANDS    r6, r6, r1, LSR ARM_IMM 13/* r6 = (# of sets - 1); set index */;\
                    \
2:                    ;\
    MOV    r1, r4                 /* r1 = working copy of way number */;\
3:                    ;\
    ORR    r8, r7, r1, LSL r5     /* r8 = set/way operation data word: */;\
    ORR    r8, r8, r6, LSL r2     /* cache level, way and set info */;\
                    \
    MCR    p15, 0, r8, c7, crm, 2 /* dcache operation by set/way */;\
                    \
    SUBS   r1, r1, ARM_IMM 1      /* decrement the way index */;\
    BGE    3b            ;\
    SUBS   r6, r6, ARM_IMM 1      /* decrement the set index */;\
    BGE    2b            ;\
                    \
4:                    ;\
    ADD    r7, r7, ARM_IMM 2      /* increment cache index = level << 1 */;\
    CMP    r3, r7                 /* done when LoC is reached */;\
    MOVGT  r0, r0, LSR ARM_IMM 3  /* rt-align type of next cache level */;\
    BGT    1b            ;\
                    \
5:                    ;\

#ifdef __cplusplus
}
#endif

#endif    /* __INCxlnx_zynq7kh */
