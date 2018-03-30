/* 20bsp.cdf - BSP-specific component descriptor file */

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
31jul14,c_l  add DRV_ARM_GLOBAL_TIMER component. (VXW6-83146)
01h,05aug13,c_l  Correct INCLUDE_USB component definition. (WIND00429232)
01g,18apr13,zgl  added DRV_I2C_GENERIC_DEV as require of DRV_I2CBUS_ZYNQ7K.
                 (WIND00413408)
01f,08apr13,zgl  fixed smp mode timer issue. (WIND00394997)
01e,07apr13,y_c  add INCLUDE_TFFS component. (WIND00411484)
01d,18jan13,fao  change SYS_MALLOC/SYS_FREE. (WIND00399682)
01c,09jan13,fao  add INCLUDE_SYS_MEM_MGMT component.(WIND00397943)
01b,15jun12,fao  update for the first release.
01a,09may11,rab  created from arm_a9_ctx rev 01a
*/

/*
DESCRIPTION
This file contains descriptions for this BSP components.
*/

Bsp xlnx_zynq7k {
    NAME        board support package
    CPU         ARMARCH7
    ENDIAN      little
    FP          vector
    MP_OPTIONS  SMP
#ifndef _WRS_CONFIG_SMP
    REQUIRES    INCLUDE_KERNEL \
                INCLUDE_VXBUS  \
                DRV_ARM_GIC    \
                DRV_SIO_ZYNQ7K \
                DRV_ARM_MPCORE_TIMER
#else /* _WRS_CONFIG_SMP */
    REQUIRES    INCLUDE_KERNEL \
                INCLUDE_VXBUS  \
                DRV_ARM_GIC    \
                DRV_SIO_ZYNQ7K \
                DRV_TIMER_ZYNQ7K
#endif /* ! _WRS_CONFIG_SMP */
}

Component INCLUDE_BOOT_NET_DEVICES {
    REQUIRES    DRV_VXBEND_ZYNQMAC \
                INCLUDE_GENERICPHY \
                INCLUDE_MII_BUS
}

Parameter RAM_HIGH_ADRS {
    NAME        Bootrom Copy region
    DEFAULT     (INCLUDE_BOOT_RAM_IMAGE)::(0x1d00000) \
                (INCLUDE_BOOT_APP)::(0x1800000) \
                0x1000000
}

Parameter RAM_LOW_ADRS {
    NAME        Runtime kernel load address
    DEFAULT     (INCLUDE_BOOT_RAM_IMAGE)::(0x01a00000) \
                (INCLUDE_BOOT_APP)::(0x00800000) \
                0x200000
}

/*
 * VX_SMP_NUM_CPUS is a SMP parameter only and only available for SMP
 * builds. Due to a limitation of the project tool at the time this
 * parameter is created where the tool can not recognize the ifdef SMP
 * selection, this parameter is set up such that _CFG_PARAMS is not
 * specified here. In the 00vxWorks.cdf file, where the parameter
 * VX_SMP_NUM_CPUS is defined, the _CFG_PARAMS is specified only for
 * VxWorks SMP. Hence the redefining of VX_SMP_NUM_CPUS here should only
 * override the value and not the rest of the properties. And for UP, the
 * parameter is ignored since the parameter is not tied to any component
 * (_CFG_PARAMS is not specified).
 */

Parameter VX_SMP_NUM_CPUS {
        NAME            Number of CPUs available to be enabled for VxWorks SMP
        TYPE            UINT
        DEFAULT         2
}

Profile PROFILE_BOOTAPP {
    COMPONENTS += DRV_ARM_GIC DRV_SIO_ZYNQ7K DRV_ARM_MPCORE_TIMER
}

Component INCLUDE_END {
    INCLUDE_WHEN    INCLUDE_NET_INIT
}

Parameter IP_MAX_UNITS {
    DEFAULT         8
}

Component INCLUDE_SYS_MEM_MGMT {
    NAME        IPNET memory management component
    SYNOPSIS    IPNET memory management component
    _CHILDREN   FOLDER_MEMORY
    CFG_PARAMS  SYS_MALLOC \
                SYS_FREE
}

Parameter SYS_MALLOC {
    NAME        system malloc function
    SYNOPSIS    system malloc function
    TYPE        FUNCPTR
    DEFAULT     sysMalloc
}

Parameter SYS_FREE {
    NAME        system free function
    SYNOPSIS    system free function
    TYPE        FUNCPTR
    DEFAULT     sysFree
}

Component INCLUDE_TFFS {
    REQUIRES    INCLUDE_TFFS_MOUNT \
                INCLUDE_TL_FTL
}

Component INCLUDE_USB {
    REQUIRES    INCLUDE_USB_INIT        \
                INCLUDE_EHCI            \
                INCLUDE_EHCI_INIT
}

Component INCLUDE_TIMESTAMP {
#ifndef _WRS_CONFIG_SMP
    REQUIRES += INCLUDE_VXB_TIMESTAMP
#else
    REQUIRES += INCLUDE_VXB_TIMESTAMP \
                DRV_ARM_GLOBAL_TIMER
#endif /* _WRS_CONFIG_SMP */
}

Component INCLUDE_AUX_CLK {
    REQUIRES += INCLUDE_VXB_AUX_CLK
}

Component DRV_I2C_PCFRTC {
    REQUIRES += DRV_I2CBUS_ZYNQ7K \
                INCLUDE_TIMER_RTC
}

Component DRV_I2C_EEPROM {
    REQUIRES += DRV_I2CBUS_ZYNQ7K \
                INCLUDE_EEPROMDRV
}

Component DRV_I2CBUS_ZYNQ7K {
    REQUIRES += DRV_I2C_GENERIC_DEV
}
