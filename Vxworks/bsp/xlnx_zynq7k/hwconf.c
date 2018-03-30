/* hwconf.c - Hardware configuration support module */

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
31jul14,c_l add DRV_ARM_GLOBAL_TIMER. (VXW6-83146)
24mar14,xms add isExPhy parameter to zynqGemDevResources. (VXW6-70152)
01l,22jul13,c_l  Added interrupt priority/sensitivity support. (WIND00420705)
01k,20jul13,y_c  add fpgaResetSet parameter to devCfgResources. (WIND00426873)
01j,11jul13,z_l  redefine busSpeed in I2C bus. (WIND00422526)
01i,20jun13,y_c  add lvlShftrSet parameter to devCfgResources. (WIND00422940)
01h,31may13,y_c  added support 4 banks of I2C eeprom. (WIND00418742)
01g,29may13,y_c  added support for the Programmable Logic. (WIND00417766)
01f,08apr13,zgl  fixed smp mode timer issue. (WIND00394997)
01e,21feb13,mgc  WIND00364425: Added WindML support
01d,09jan13,fao  add ifMemCached parameter to zynqGemDevResources.(WIND00397943)
01c,15sep12,fao  add DMA and TTC support.
01b,15jun12,fao  update for the first release.
01a,09may11,rab  created from arm_ctx_a9 rev 01a
*/

#include <vxWorks.h>
#include <vxBusLib.h>
#include <hwif/vxbus/vxBus.h>
#include <hwif/vxbus/vxbIntrCtlr.h>
#include <hwif/util/vxbParamSys.h>
#include <hwif/vxbus/hwConf.h>
#include "config.h"

#ifdef DRV_STORAGE_SDHC
#   include <h/storage/vxbSdMmcLib.h>
#   include <h/storage/vxbSdhcStorage.h>
#endif /* DRV_STORAGE_SDHC */

#ifdef DRV_ZYNQ_SDHC_CTRL
#   include <hwif/vxbus/vxbSdLib.h>
#endif /* DRV_STORAGE_SDHC */

#ifdef DRV_I2CBUS_ZYNQ7K
#   include <hwif/vxbus/vxbI2cLib.h>
#endif /* DRV_I2CBUS_ZYNQ7K */

#ifdef INCLUDE_ZYNQ7K_SPI
#   include <hwif/vxbus/vxbSpiLib.h>
#endif

#ifdef INCLUDE_EHCI
IMPORT void   zynq7kEhci0Init (void);
IMPORT void   zynq7kEhci0PostResetHook (void);
#endif  /* INCLUDE_EHCI */

/*
 * Configuring GIC PL390 priority
 * This board is based on the GIC pl390 interrupt controller.
 * The pl390 implements 32 priority levels, this means the priority values in
 * the range of 0 to 248, and in steps of 8.
 * Example:
 *     values 0 - 7  level  0,
 *            8 - 15 level  1,
 *            ...
 */

LOCAL const struct intrCtlrPriority gicPriority[] = {
    /* pin,                priority */
    { INT_VEC_UART0,       120 },
    { INT_VEC_UART1,       120 },
#ifdef DRV_ARM_MPCORE_TIMER
    { INT_VEC_TMR0,        120 },
#ifdef INCLUDE_AUX_CLK
    { INT_VEC_AWDT,        120 },
#endif /* INCLUDE_AUX_CLK */
#endif /* DRV_ARM_MPCORE_TIMER */
#if defined(DRV_STORAGE_SDHC) || defined(DRV_ZYNQ_SDHC_CTRL)
    { INT_VEC_SDIO0,       128 },
#endif /* DRV_STORAGE_SDHC || DRV_ZYNQ_SDHC_CTRL */
#ifdef DRV_I2CBUS_ZYNQ7K
    { INT_VEC_I2C1,        128 },
#endif /* DRV_I2CBUS_ZYNQ7K */
#ifdef INCLUDE_ZYNQ7K_SPI
    { INT_VEC_SPI0,        128 },
#endif
#ifdef INCLUDE_ZYNQ7K_QSPI
    { INT_VEC_QSPI,        128 },
#endif /* INCLUDE_ZYNQ7K_QSPI */
#ifdef INCLUDE_EHCI
    { INT_VEC_USB0,        128 },
#endif  /* INCLUDE_EHCI */
#ifdef DRV_VXBEND_ZYNQMAC
    { INT_VEC_ETH0,        120 },
#endif  /* DRV_VXBEND_ZYNQMAC */
#ifdef DRV_TIMER_ZYNQ7K
    { INT_VEC_TTC0_0,      128 },
#ifdef INCLUDE_AUX_CLK
    { INT_VEC_TTC0_1,      128 },
#endif /* INCLUDE_AUX_CLK */
#endif  /* DRV_TIMER_ZYNQ7K */
#ifdef DRV_ARM_GLOBAL_TIMER
    { INT_VEC_GTMR,        128 },
#endif /* DRV_ARM_GLOBAL_TIMER */
#ifdef DRV_DMA_PL330
    { INT_VEC_DMAC_ABORT,  120 },
    { INT_VEC_DMAC_0,      120 },
    { INT_VEC_DMAC_1,      120 },
    { INT_VEC_DMAC_2,      120 },
    { INT_VEC_DMAC_3,      120 },
    { INT_VEC_DMAC_4,      120 },
    { INT_VEC_DMAC_5,      120 },
    { INT_VEC_DMAC_6,      120 },
    { INT_VEC_DMAC_7,      120 },
#endif  /* DRV_DMA_PL330 */
#ifdef DRV_RESOURCE_ZYNQ7K_DEVC
    { INT_VEC_XADC,        128 },
    { INT_VEC_DVI,         128 },
#endif  /* DRV_RESOURCE_ZYNQ7K_DEVC */
#ifdef INCLUDE_AXI_ETHERNET
    { INT_VEC_AXI_ETH,         120},
#endif
#ifdef INCLUDE_AXI_DMA
    { INT_VEC_AXI_DMA_TX,      120},
    { INT_VEC_AXI_DMA_RX,      120},
#endif
#ifdef INCLUDE_ZYNQ7K_PL_UART0
    { INT_VEC_PL_UART0,      120},
#endif    
#ifdef INCLUDE_ZYNQ7K_PL_UART1
    { INT_VEC_PL_UART1,      120},
#endif    

};

/*
 * Configuring sensitivity
 * Setting each peripheral interrupt to be:
 * VXB_INTR_TRIG_LEVEL or VXB_INTR_TRIG_EDGE.
 *
 * SGIs sensitivity
 * The sensitivity types for SGIs are fixed and cannot be configure.
 *
 * PPIs and SPIs sensitivity
 * ALL PPIs and SPIs interrupt sensitivity types are fixed by the requesting
 * sources and cannot be changed. The GIC must be programmed to accommodate
 * this.
 * SEE ALSO:
 * "Zynq-7000 All Programmable SoC Technical Reference Manual"
 */

LOCAL const struct intrCtlrTrigger gicTrigger[] = {
    /* pin,                     sensitivity */
    { INT_VEC_UART0,            VXB_INTR_TRIG_LEVEL },
    { INT_VEC_UART1,            VXB_INTR_TRIG_LEVEL },
#ifdef DRV_ARM_MPCORE_TIMER
    { INT_VEC_TMR0,             VXB_INTR_TRIG_EDGE },
#ifdef INCLUDE_AUX_CLK
    { INT_VEC_AWDT,             VXB_INTR_TRIG_EDGE },
#endif /* INCLUDE_AUX_CLK */
#endif /* DRV_ARM_MPCORE_TIMER */
#if defined(DRV_STORAGE_SDHC) || defined(DRV_ZYNQ_SDHC_CTRL)
    { INT_VEC_SDIO0,            VXB_INTR_TRIG_LEVEL },
#endif /* DRV_STORAGE_SDHC || DRV_ZYNQ_SDHC_CTRL*/
#ifdef DRV_I2CBUS_ZYNQ7K
    { INT_VEC_I2C1,             VXB_INTR_TRIG_LEVEL },
#endif /* DRV_I2CBUS_ZYNQ7K */
#ifdef INCLUDE_ZYNQ7K_SPI
    { INT_VEC_SPI0,             VXB_INTR_TRIG_LEVEL},
#endif
#ifdef INCLUDE_ZYNQ7K_QSPI
    { INT_VEC_QSPI,             VXB_INTR_TRIG_LEVEL },
#endif /* INCLUDE_ZYNQ7K_QSPI */
#ifdef INCLUDE_EHCI
    { INT_VEC_USB0,             VXB_INTR_TRIG_LEVEL },
#endif  /* INCLUDE_EHCI */
#ifdef DRV_VXBEND_ZYNQMAC
    { INT_VEC_ETH0,             VXB_INTR_TRIG_LEVEL },
#endif  /* DRV_VXBEND_ZYNQMAC */
#ifdef DRV_TIMER_ZYNQ7K
    { INT_VEC_TTC0_0,           VXB_INTR_TRIG_LEVEL },
#ifdef INCLUDE_AUX_CLK
    { INT_VEC_TTC0_1,           VXB_INTR_TRIG_LEVEL },
#endif /* INCLUDE_AUX_CLK */
#endif  /* DRV_TIMER_ZYNQ7K */
#ifdef DRV_ARM_GLOBAL_TIMER
    { INT_VEC_GTMR,               VXB_INTR_TRIG_EDGE},
#endif /* DRV_ARM_GLOBAL_TIMER */
#ifdef DRV_DMA_PL330
    { INT_VEC_DMAC_ABORT,       VXB_INTR_TRIG_LEVEL },
    { INT_VEC_DMAC_0,           VXB_INTR_TRIG_LEVEL },
    { INT_VEC_DMAC_1,           VXB_INTR_TRIG_LEVEL },
    { INT_VEC_DMAC_2,           VXB_INTR_TRIG_LEVEL },
    { INT_VEC_DMAC_3,           VXB_INTR_TRIG_LEVEL },
    { INT_VEC_DMAC_4,           VXB_INTR_TRIG_LEVEL },
    { INT_VEC_DMAC_5,           VXB_INTR_TRIG_LEVEL },
    { INT_VEC_DMAC_6,           VXB_INTR_TRIG_LEVEL },
    { INT_VEC_DMAC_7,           VXB_INTR_TRIG_LEVEL },
#endif  /* DRV_DMA_PL330 */
#ifdef DRV_RESOURCE_ZYNQ7K_DEVC
    { INT_VEC_XADC,             VXB_INTR_TRIG_LEVEL },
    { INT_VEC_DVI,              VXB_INTR_TRIG_LEVEL },
#endif  /* DRV_RESOURCE_ZYNQ7K_DEVC */
#ifdef INCLUDE_AXI_ETHERNET
    { INT_VEC_AXI_ETH,         VXB_INTR_TRIG_LEVEL},
#endif
#ifdef INCLUDE_AXI_DMA
    { INT_VEC_AXI_DMA_TX,      VXB_INTR_TRIG_LEVEL},
    { INT_VEC_AXI_DMA_RX,      VXB_INTR_TRIG_LEVEL},
#endif
#ifdef INCLUDE_ZYNQ7K_PL_UART0
    { INT_VEC_PL_UART0,      VXB_INTR_TRIG_LEVEL},
#endif    
#ifdef INCLUDE_ZYNQ7K_PL_UART1
    { INT_VEC_PL_UART1,      VXB_INTR_TRIG_LEVEL},
#endif    
};

LOCAL struct intrCtlrInputs gicInputs[] = {
    /* pin,                driver,            unit,   index */
    { INT_VEC_UART0,       "zynqSioDev",       0,       0 },
    { INT_VEC_UART1,       "zynqSioDev",       1,       0 },
#ifdef DRV_ARM_MPCORE_TIMER
    { INT_VEC_TMR0,        "armMpCoreTimer",   0,       0 },
#ifdef INCLUDE_AUX_CLK
    { INT_VEC_AWDT,        "armMpCoreTimer",   1,       0 },
#endif /* INCLUDE_AUX_CLK */
#endif /* DRV_ARM_MPCORE_TIMER */
#ifdef DRV_STORAGE_SDHC
    { INT_VEC_SDIO0,       "sdhci",            0,       0 },
#endif /* DRV_STORAGE_SDHC */
#ifdef DRV_ZYNQ_SDHC_CTRL
    { INT_VEC_SDIO0,       "zynqSdhci",         0,       0 },
#endif /* DRV_ZYNQ_SDHC_CTRL */
#ifdef DRV_I2CBUS_ZYNQ7K
    { INT_VEC_I2C1,        "zynq7kI2c",        0,       0 },
#endif /* DRV_I2CBUS_ZYNQ7K */
#ifdef INCLUDE_ZYNQ7K_SPI
    { INT_VEC_SPI0,        "zynq7kSpi",        0,       0 },
#endif
#ifdef INCLUDE_ZYNQ7K_QSPI
    { INT_VEC_QSPI,        "qspi",             0,       0 },
#endif /* INCLUDE_ZYNQ7K_QSPI */
#ifdef INCLUDE_EHCI
    { INT_VEC_USB0,        "vxbPlbUsbEhci",    0,       0 },
#endif  /* INCLUDE_EHCI */
#ifdef DRV_VXBEND_ZYNQMAC
    { INT_VEC_ETH0,        "gem",              0,       0 },
#endif  /* DRV_VXBEND_ZYNQMAC */
#ifdef INCLUDE_ZYNQ7K_2_ETH
    { INT_VEC_ETH1,        "gem",              1,       0 },
#endif  /* DRV_VXBEND_ZYNQMAC */

#ifdef DRV_TIMER_ZYNQ7K
    { INT_VEC_TTC0_0,      "zynqTimer",        0,       0 },
#ifdef INCLUDE_AUX_CLK
    { INT_VEC_TTC0_1,      "zynqTimer",        1,       0 },
#endif /* INCLUDE_AUX_CLK */
#endif  /* DRV_TIMER_ZYNQ7K */
#ifdef DRV_ARM_GLOBAL_TIMER
    { INT_VEC_GTMR,        "armGlobalTimer",   0,       0 },
#endif /* DRV_ARM_GLOBAL_TIMER */
#ifdef DRV_DMA_PL330
    { INT_VEC_DMAC_ABORT,  "pl330dma",         0,       0 },
    { INT_VEC_DMAC_0,      "pl330dma",         0,       1 },
    { INT_VEC_DMAC_1,      "pl330dma",         0,       2 },
    { INT_VEC_DMAC_2,      "pl330dma",         0,       3 },
    { INT_VEC_DMAC_3,      "pl330dma",         0,       4 },
    { INT_VEC_DMAC_4,      "pl330dma",         0,       5 },
    { INT_VEC_DMAC_5,      "pl330dma",         0,       6 },
    { INT_VEC_DMAC_6,      "pl330dma",         0,       7 },
    { INT_VEC_DMAC_7,      "pl330dma",         0,       8 },
#endif  /* DRV_DMA_PL330 */
#ifdef DRV_RESOURCE_ZYNQ7K_DEVC
    { INT_VEC_XADC,        "xadc",             0,       0 },
    { INT_VEC_DVI,         "zynq7kDevCfg",     0,       0 },
#endif  /* DRV_RESOURCE_ZYNQ7K_DEVC */
#ifdef INCLUDE_AXI_ETHERNET
    { INT_VEC_AXI_ETH,         "temac",        0,       0 },
#endif
#ifdef INCLUDE_AXI_DMA
    { INT_VEC_AXI_DMA_TX,      "xlnxDma",      0,       0 },
    { INT_VEC_AXI_DMA_RX,      "xlnxDma",      0,       1 },
#endif
#ifdef INCLUDE_ZYNQ7K_PL_UART0
    { INT_VEC_PL_UART0,       "ns16550",       0,       0 },
#endif   
#ifdef INCLUDE_ZYNQ7K_PL_UART1
    { INT_VEC_PL_UART1,       "ns16550",       1,       0 },
#endif
};

/*
 * if this file is used in SMP environment, the ethernet interface can be
 * re-routed to CPU 1 by changing "0" to "1", "2" in the gicCpu[] structure.
 */

LOCAL struct intrCtlrCpu gicCpu[] = {
    { INT_VEC_ETH0, 0 },
};

LOCAL const struct hcfResource armGIC0Resources[] = {
    { VXB_REG_BASE,        HCF_RES_INT,  {(void *)ZYNQ7K_GIC1_BASE} },
    { "input",             HCF_RES_ADDR, {(void *)&gicInputs[0]} },
    { "intMode",           HCF_RES_INT,  {(void *)INT_MODE} },
    { "maxIntLvl",         HCF_RES_INT,  {(void *)SYS_INT_LEVELS_MAX} },
    { "inputTableSize",    HCF_RES_INT,  {(void *)NELEMENTS(gicInputs) } },
    { "cpuRoute",          HCF_RES_ADDR, {(void *)&gicCpu[0]} },
    { "cpuRouteTableSize", HCF_RES_INT,  {(void *)NELEMENTS(gicCpu)} },
    { "priority",          HCF_RES_ADDR, {(void *)&gicPriority[0]} },
    { "priorityTableSize", HCF_RES_INT,  {(void *)NELEMENTS(gicPriority) } },
    { "trigger",           HCF_RES_ADDR, {(void *)&gicTrigger[0]} },
    { "triggerTableSize",  HCF_RES_INT,  {(void *)NELEMENTS(gicTrigger) } }
#ifdef _WRS_CONFIG_SMP
   ,{ "maxCpuNum",         HCF_RES_INT,  {(void *)VX_SMP_NUM_CPUS} }
#endif /* _WRS_CONFIG_SMP */
};
#define armGIC0Num NELEMENTS(armGIC0Resources)

LOCAL struct hcfResource zynqSioDev0Resources[] = {
    { "regBase",  HCF_RES_INT, {(void *)UART_0_BASE_ADR} },
    { "clkFreq",  HCF_RES_INT, {(void *)UART_XTAL_FREQ} },
};
#define zynqSioDev0Num NELEMENTS(zynqSioDev0Resources)

LOCAL struct hcfResource zynqSioDev1Resources[] = {
    { "regBase",  HCF_RES_INT, {(void *)UART_1_BASE_ADR} },
    { "clkFreq",  HCF_RES_INT, {(void *)UART_XTAL_FREQ} },
};
#define zynqSioDev1Num NELEMENTS(zynqSioDev1Resources)

#ifdef DRV_ARM_MPCORE_TIMER
LOCAL struct hcfResource zynqCPTimerDev0Resources[] = {
    { "regBase",    HCF_RES_INT, {(void *)SYS_TIMER_BASE} },
    { "clkFreq",    HCF_RES_INT, {(void *)ZYNQ7K_TIMERS_CLK} },
    { "minClkRate", HCF_RES_INT, {(void *)SYS_CLK_RATE_MIN} },
    { "maxClkRate", HCF_RES_INT, {(void *)SYS_CLK_RATE_MAX} },
};
#define zynqCPTimerDev0Num NELEMENTS(zynqCPTimerDev0Resources)

#ifdef INCLUDE_AUX_CLK
LOCAL struct hcfResource zynqCPTimerDev1Resources[] = {
    { "regBase",    HCF_RES_INT, {(void *)AUX_TIMER_BASE} },
    { "clkFreq",    HCF_RES_INT, {(void *)ZYNQ7K_TIMERS_CLK} },
    { "minClkRate", HCF_RES_INT, {(void *)AUX_CLK_RATE_MIN} },
    { "maxClkRate", HCF_RES_INT, {(void *)AUX_CLK_RATE_MAX} },
};
#define zynqCPTimerDev1Num NELEMENTS(zynqCPTimerDev1Resources)
#endif /* INCLUDE_AUX_CLK */
#endif /* DRV_ARM_MPCORE_TIMER */

#ifdef DRV_TIMER_ZYNQ7K
LOCAL struct hcfResource zynqTimerDev0Resources[] = {
    { "regBase",    HCF_RES_INT, {(void *)ZYNQ7K_TTC0_TIMER0_BASE} },
    { "clkFreq",    HCF_RES_INT, {(void *)ZYNQ7K_TTC_CLK} },
    { "minClkRate", HCF_RES_INT, {(void *)SYS_CLK_RATE_MIN} },
    { "maxClkRate", HCF_RES_INT, {(void *)SYS_CLK_RATE_MAX} },
};
#define zynqTimerDev0Num NELEMENTS(zynqTimerDev0Resources)

#ifdef INCLUDE_AUX_CLK
LOCAL struct hcfResource zynqTimerDev1Resources[] = {
    { "regBase",    HCF_RES_INT, {(void *)ZYNQ7K_TTC0_TIMER1_BASE} },
    { "clkFreq",    HCF_RES_INT, {(void *)ZYNQ7K_TTC_CLK} },
    { "minClkRate", HCF_RES_INT, {(void *)AUX_CLK_RATE_MIN} },
    { "maxClkRate", HCF_RES_INT, {(void *)AUX_CLK_RATE_MAX} },
};
#define zynqTimerDev1Num NELEMENTS(zynqTimerDev1Resources)
#endif /* INCLUDE_AUX_CLK */
#endif  /* DRV_TIMER_ZYNQ7K */

#ifdef DRV_ARM_GLOBAL_TIMER
LOCAL struct hcfResource zynqGlobalTimerDevResources[] = {
    { "regBase",    HCF_RES_INT, {(void *)CTXA9_GLOBAL_TMR_BASE} },
    { "clkFreq",    HCF_RES_INT, {(void *)ZYNQ7K_TIMERS_CLK} },
    { "minClkRate", HCF_RES_INT, {(void *)SYS_CLK_RATE_MIN} },
    { "maxClkRate", HCF_RES_INT, {(void *)SYS_CLK_RATE_MAX} },
};
#define zynqGlobalTimerDevNum NELEMENTS(zynqGlobalTimerDevResources)
#endif /* DRV_ARM_GLOBAL_TIMER */

#ifdef DRV_VXBEND_ZYNQMAC
LOCAL struct hcfResource zynqGemDevResources[] = {
    { "regBase",    HCF_RES_INT,    {(void *)ZYNQ7K_GEM0_BASE} },
    { "phyAddr",    HCF_RES_INT,    {(void *)0} },
	{ "isExPhy",	HCF_RES_INT,	{(void *)ZYNQ_EMIO_GMII} },
    { "clkSet",     HCF_RES_ADDR,   {(void *)sysZynq7kGemClkSet} },
#   ifdef INCLUDE_SYS_MEM_MGMT
    { "ifCached",   HCF_RES_ADDR,   {(void *)ifMemCached} },
#endif /* INCLUDE_SYS_MEM_MGMT */
    { "miiIfName",  HCF_RES_STRING, {(void *)"gem"} },
    { "miiIfUnit",  HCF_RES_INT,    {(void *)0} }
};
#define zynqGemDevNum NELEMENTS(zynqGemDevResources)
#endif /* DRV_VXBEND_ZYNQMAC */

#ifdef INCLUDE_ZYNQ7K_2_ETH
LOCAL struct hcfResource zynqGemDev2Resources[] = {
    { "regBase",    HCF_RES_INT,    {(void *)ZYNQ7K_GEM1_BASE} },
    { "phyAddr",    HCF_RES_INT,    {(void *)1} },
	{ "isExPhy",	HCF_RES_INT,	{(void *)ZYNQ_EMIO_GMII} },  //ZYNQ_EMIO_GMII
    { "clkSet",     HCF_RES_ADDR,   {(void *)sysZynq7kGemClkSet} },
#   ifdef INCLUDE_SYS_MEM_MGMT
    { "ifCached",   HCF_RES_ADDR,   {(void *)ifMemCached} },
#endif /* INCLUDE_SYS_MEM_MGMT */
    { "miiIfName",  HCF_RES_STRING, {(void *)"gem"} },
    { "miiIfUnit",  HCF_RES_INT,    {(void *)1}}
};
#define zynqGemDev2Num NELEMENTS(zynqGemDev2Resources)
#endif /* DRV_VXBEND_ZYNQMAC */

#ifdef INCLUDE_AXI_ETHERNET
static unsigned char ethAddr[6] = {0x00, 0x0a, 0x35, 0x00, 0x00, 0x01};
LOCAL struct hcfResource zynqAxiEthDevResources[] = {
    { "regBase",    HCF_RES_INT,    {(void *)ZYNQ7K_AXI_ETH_BASE} },
    { "phyAddr",    HCF_RES_INT,    {(void *)0} },  /* //0 //wanghx debug */
    { "miiIfName",  HCF_RES_STRING, {(void *)"temac"} },
    { "miiIfUnit",  HCF_RES_INT,    {(void *)0} },
    { "ethAddr",     HCF_RES_ADDR,   {(void *)ethAddr} },
};
#define zynqAxiEthDevNum NELEMENTS(zynqAxiEthDevResources)
#endif /* INCLUDE_AXI_ETHERNET */

#ifdef INCLUDE_AXI_DMA
const struct hcfResource xlnxDmaResources[] = {
    { "regBase",    HCF_RES_INT,      { (void *)ZYNQ7K_AXI_DMA_BASE} }
    };

#define xlnxDmaNum NELEMENTS(xlnxDmaResources)
#endif /* INCLUDE_AXI_DMA */

#ifdef DRV_STORAGE_SDHC
LOCAL struct hcfResource zynqSdhcResources[] = {
    { "regBase",    HCF_RES_INT,  {(void *)ZYNQ7K_SDHC0_BASE} },
    { "clkFreq",    HCF_RES_ADDR, {(void *)sysSdhcClkFreqGet} },
    { "polling",    HCF_RES_INT,  {(void *)FALSE} },
    { "flags",      HCF_RES_INT,  {(void *)SDHC_HOST_CTRL_CAVIUM} },
};
#define zynqSdhcNum NELEMENTS(zynqSdhcResources)
#endif /* DRV_STORAGE_SDHC */

#ifdef DRV_ZYNQ_SDHC_CTRL
LOCAL struct hcfResource zynqSdhcResources[] = {
    { "regBase",    HCF_RES_INT,  {(void *)ZYNQ7K_SDHC0_BASE} },
    { "clkFreq",    HCF_RES_ADDR, {(void *)sysSdhcClkFreqGet} },
    { "polling",    HCF_RES_INT,  {(void *)FALSE} },
    { "flags",      HCF_RES_INT,  {(void *)SDHC_HOST_CTRL_CAVIUM} },
    { "cardWpCheck", HCF_RES_ADDR, {(void *)zynqSdCardWpCheck} },
};
#define zynqSdhcNum NELEMENTS(zynqSdhcResources)
#endif /* DRV_ZYNQ_SDHC_CTRL */

#ifdef INCLUDE_EHCI
LOCAL const struct hcfResource usbEhci0Resources[] = {
    { VXB_REG_BASE, HCF_RES_INT,  { (void *)EHCI_CAPLENGTH(ZYNQ7K_USB0_BASE)} },
    { "ehciInit",   HCF_RES_ADDR, { (void *)zynq7kEhci0Init } },
};
#define usbEhci0Num NELEMENTS(usbEhci0Resources)
#endif /* INCLUDE_EHCI */

#ifdef DRV_I2CBUS_ZYNQ7K

LOCAL struct i2cDevInputs i2c0DevTbl[] = {

/*
 * Address  Part Number  Size         Description
 * -------- ------------------------------------------------------------------
 * 0x51       pcf8564     16 byte     rtc
 * 0x5d       si570       16 byte     PLL
 * 0x74       pca9548     1 byte      I2C switch
 * 0x54       at24c08     256 bytes   eeprom(1nd bank)
 * 0x55       at24c08     256 bytes   eeprom(2nd bank)
 * 0x56       at24c08     256 bytes   eeprom(3nd bank)
 * 0x57       at24c08     256 bytes   eeprom(4nd bank)
 */
#if 0
    { "pca9548",         0x74,    0},
    { "si570",           0x5d,    0},
    { "eeprom_at24c08",  0x54,    0},   /* 1nd 256 bytes */
    { "eeprom_at24c08",  0x55,    0},   /* 2nd 256 bytes */
    { "eeprom_at24c08",  0x56,    0},   /* 3rd 256 bytes */
    { "eeprom_at24c08",  0x57,    0},   /* 4th 256 bytes*/

    { "rtc_pcf8564",     0x51,    0},
#endif
    { "pca9505",         0x21,    0},
};

LOCAL const struct hcfResource i2c0Resources[] = {
    { "regBase",    HCF_RES_INT,    { (void *)(ZYNQ7K_I2C1_BASE) } },
    { "clkFreq",    HCF_RES_INT,    { (void *)ZYNQ7K_I2C_CLK} },
    { "busSpeed",   HCF_RES_INT,    { (void *)100000} },
    { "polling",    HCF_RES_INT,    { (void *)FALSE} },
    { "i2cDev",     HCF_RES_ADDR,   { (void *)&i2c0DevTbl} },
    { "i2cDevNum",  HCF_RES_INT,    { (void *)NELEMENTS(i2c0DevTbl)} },
};
#   define i2c0Num NELEMENTS(i2c0Resources)

#endif /* DRV_I2CBUS_ZYNQ7K */

#ifdef INCLUDE_ZYNQ7K_SPI

LOCAL struct vxbSpiDevInfo spiDevTbl[] = {
    /* deviceName   chipSelect  bitWidth    devFreq     mode */
    { "mcp23s0",     0,          8,          10000000,   SPI_MODE_3 | SPI_FULL_DUPLEX},
};

#define MODE_INT        0
#define MODE_POLL       1

LOCAL const struct hcfResource spiResources[] = {
    { "regBase",    HCF_RES_INT,    { (void *)(ZYNQ7K_SPI0_BASE) } },
    { "clkFreq",    HCF_RES_INT,    { (void *)ZYNQ7K_UART_CLK} },
    /* { "clkDivisor", HCF_RES_INT,    { (void *)4} },*/
    { "rwMode",     HCF_RES_INT,    { (void *)MODE_INT} },
    { "spiDev",     HCF_RES_ADDR,   { (void *)&spiDevTbl} },
    { "spiDevNum",  HCF_RES_INT,    { (void *)NELEMENTS(spiDevTbl)} },
};
#   define spiNum NELEMENTS(spiResources)

#endif  /* INCLUDE_ZYNQ7K_SPI */

#ifdef DRV_DMA_PL330
const struct hcfResource pl330DmaResources[] = {
    { "regBase",    HCF_RES_INT,      { (void *)ZYNQ7K_PL330_DMA_CTLR_BASE} }
    };

#define pl330DmaNum NELEMENTS(pl330DmaResources)
#endif /* DRV_DMA_PL330 */

#ifdef DRV_RESOURCE_ZYNQ7K_DEVC
const struct hcfResource devCfgResources[] = {
    { "regBase",      HCF_RES_INT,      { (void *)ZYNQ7K_DEVCFG_BASE} },
    { "lvlShftrSet",  HCF_RES_ADDR,     { (void *)sysDevcLvlShftrSet} },
    { "fpgaResetSet", HCF_RES_ADDR,     { (void *)sysDevcFpgaResetSet} },
    };

#define devCfgNum NELEMENTS(devCfgResources)
#endif /* DRV_RESOURCE_ZYNQ7K_DEVC */

#ifdef DRV_CHAR_ZYNQ7K_DEVC
const struct hcfResource charDev0Resources[] = {
    { "regBase",      HCF_RES_INT,      { (void *)ZYNQ7K_DEVCFG_BASE} },
    { "charDevFunc",  HCF_RES_ADDR,     { (void *)NULL} },
    { "channel",      HCF_RES_INT,      { (void *)0} },
    };
#define charDev0Num NELEMENTS(charDev0Resources)

const struct hcfResource charDev1Resources[] = {
    { "regBase",      HCF_RES_INT,      { (void *)ZYNQ7K_DEVCFG_BASE} },
    { "charDevFunc",  HCF_RES_ADDR,     { (void *)NULL} },
    { "channel",      HCF_RES_INT,      { (void *)1} },
    };
#define charDev1Num NELEMENTS(charDev1Resources)

#endif

#ifdef DRV_RESOURCE_ZYNQ7K_AD
const struct hcfResource AdDev0Resources[] = {
    { "regBase",      HCF_RES_INT,      { (void *)ZYNQ7K_AD_BASE} },
    { "adDevFunc",    HCF_RES_ADDR,     { (void *)NULL} },
    { "channel",      HCF_RES_INT,      { (void *)0} },
    };
#define AdDev0Num NELEMENTS(AdDev0Resources)
#endif

#ifdef INCLUDE_ZYNQ7K_PL_UART0
LOCAL struct hcfResource zynqPLSioDev0Resources[] = {

    { "regBase",    HCF_RES_INT,    { (void *)ZYNQ7K_PL_COM0_BASE + 0x1000} },
    { "irqLevel",   HCF_RES_INT,    { (void *)INT_LVL_PL_UART0 } },
    { "irq",        HCF_RES_INT,    { (void *)INT_VEC_PL_UART0} },
    { "clkFreq",    HCF_RES_INT,    { (void *)ZYNQ7K_UART_CLK } },
    { "regInterval",HCF_RES_INT,    { (void *)4 } },
    { "fifoLen",    HCF_RES_INT,    { (void *)16 } }     
};
#define zynqPLSioDev0Num NELEMENTS(zynqPLSioDev0Resources)
#endif

#ifdef INCLUDE_ZYNQ7K_PL_UART1
LOCAL struct hcfResource zynqPLSioDev1Resources[] = {

    { "regBase",    HCF_RES_INT,    { (void *)ZYNQ7K_PL_COM1_BASE  + 0x1000} },
    { "irqLevel",   HCF_RES_INT,    { (void *)INT_LVL_PL_UART1 } },
    { "irq",        HCF_RES_INT,    { (void *)INT_VEC_PL_UART1} },
    { "clkFreq",    HCF_RES_INT,    { (void *)ZYNQ7K_UART_CLK } },
    { "regInterval",HCF_RES_INT,    { (void *)4 } },
    { "fifoLen",    HCF_RES_INT,    { (void *)32 } }      
};
#define zynqPLSioDev1Num NELEMENTS(zynqPLSioDev1Resources)
#endif

const struct hcfDevice hcfDeviceList[] = {
    { "armGicDev",        0, VXB_BUSID_PLB, 0, armGIC0Num,         armGIC0Resources },
    { "zynqSioDev",       0, VXB_BUSID_PLB, 0, zynqSioDev1Num,     zynqSioDev0Resources },
    { "zynqSioDev",       1, VXB_BUSID_PLB, 0, zynqSioDev1Num,     zynqSioDev1Resources },
#ifdef DRV_ARM_MPCORE_TIMER
    { "armMpCoreTimer",   0, VXB_BUSID_PLB, 0, zynqCPTimerDev0Num, zynqCPTimerDev0Resources },
#ifdef INCLUDE_AUX_CLK
    { "armMpCoreTimer",   1, VXB_BUSID_PLB, 0, zynqCPTimerDev1Num, zynqCPTimerDev1Resources },
#endif /* INCLUDE_AUX_CLK */
#endif /* DRV_ARM_MPCORE_TIMER */
#ifdef DRV_TIMER_ZYNQ7K
    { "zynqTimer",        0, VXB_BUSID_PLB, 0, zynqTimerDev0Num,   zynqTimerDev0Resources },
#ifdef INCLUDE_AUX_CLK
    { "zynqTimer",        1, VXB_BUSID_PLB, 0, zynqTimerDev1Num,   zynqTimerDev1Resources },
#endif  /* INCLUDE_AUX_CLK */
#endif  /* DRV_TIMER_ZYNQ7K */
#ifdef DRV_ARM_GLOBAL_TIMER
    { "armGlobalTimer",   0, VXB_BUSID_PLB, 0, zynqGlobalTimerDevNum, zynqGlobalTimerDevResources },
#endif  /* DRV_ARM_GLOBAL_TIMER */
#ifdef DRV_VXBEND_ZYNQMAC
    { "gem",              0, VXB_BUSID_PLB, 0, zynqGemDevNum,      zynqGemDevResources },
#endif /* DRV_VXBEND_ZYNQMAC */ 
#ifdef INCLUDE_ZYNQ7K_2_ETH
    { "gem",              1, VXB_BUSID_PLB, 0, zynqGemDev2Num,      zynqGemDev2Resources },
#endif /* DRV_VXBEND_ZYNQMAC */    
#ifdef INCLUDE_AXI_ETHERNET
    { "temac",              0, VXB_BUSID_PLB, 0, zynqAxiEthDevNum,   zynqAxiEthDevResources },
#endif
#ifdef INCLUDE_AXI_DMA
    { "xlnxDma",          0, VXB_BUSID_PLB, 0, xlnxDmaNum,   xlnxDmaResources },
#endif
#ifdef DRV_DMA_PL330
    { "pl330dma",        0, VXB_BUSID_PLB, 0,  pl330DmaNum,        pl330DmaResources},
#endif /* DRV_DMA_PL330 */
#ifdef DRV_STORAGE_SDHC
    { "sdhci",            0, VXB_BUSID_PLB, 0, zynqSdhcNum,        zynqSdhcResources },
#endif /* DRV_STORAGE_SDHC */
#ifdef DRV_ZYNQ_SDHC_CTRL
   { "zynqSdhci",            0, VXB_BUSID_PLB, 0, zynqSdhcNum,        zynqSdhcResources },
#endif /* DRV_ZYNQ_SDHC_CTRL */
#ifdef DRV_I2CBUS_ZYNQ7K
    { "zynq7kI2c",        0, VXB_BUSID_PLB, 0, i2c0Num,            i2c0Resources },
#endif /* DRV_I2CBUS_ZYNQ7K */
#ifdef INCLUDE_ZYNQ7K_SPI
    { "zynq7kSpi",        0, VXB_BUSID_PLB, 0, spiNum,            spiResources },
#endif /* INCLUDE_ZYNQ7K_SPI */
#ifdef INCLUDE_EHCI
    { "vxbPlbUsbEhci",    0, VXB_BUSID_PLB, 0, usbEhci0Num,        usbEhci0Resources },
#endif  /* INCLUDE_EHCI */
#ifdef DRV_RESOURCE_ZYNQ7K_DEVC
    { "zynq7kDevCfg",     0, VXB_BUSID_PLB, 0, devCfgNum,          devCfgResources },
#endif  /* DRV_RESOURCE_ZYNQ7K_DEVC */
#ifdef DRV_CHAR_ZYNQ7K_DEVC
    { "zynq7kCharDev",     0, VXB_BUSID_PLB, 0, charDev0Num,          charDev0Resources },
    { "zynq7kCharDev",     1, VXB_BUSID_PLB, 0, charDev1Num,          charDev1Resources },
#endif
#ifdef DRV_RESOURCE_ZYNQ7K_AD
    {"zynq7kAdDev",        0, VXB_BUSID_PLB, 0, AdDev0Num,          AdDev0Resources },
#endif
#ifdef INCLUDE_ZYNQ7K_PL_UART0
    { "ns16550",       2, VXB_BUSID_PLB, 0, zynqPLSioDev0Num,     zynqPLSioDev0Resources },
#endif
#ifdef INCLUDE_ZYNQ7K_PL_UART1
    { "ns16550",       3, VXB_BUSID_PLB, 0, zynqPLSioDev1Num,     zynqPLSioDev1Resources },
#endif
    { NULL, 0, 0, 0, 0, NULL }
};

const int hcfDeviceNum = NELEMENTS(hcfDeviceList);

VXB_INST_PARAM_OVERRIDE sysInstParamTable[] = {
#ifdef INCLUDE_EHCI
    { "vxbPlbUsbEhci", 0, "hasEmbeddedTT", VXB_PARAM_INT32,   { (void *)TRUE } },
    { "vxbPlbUsbEhci", 0, "postResetHook", VXB_PARAM_FUNCPTR, { (void *)zynq7kEhci0PostResetHook } },
#endif  /* INCLUDE_EHCI */
    { NULL,  0, NULL, VXB_PARAM_END_OF_LIST, {(void *)0} }
};
