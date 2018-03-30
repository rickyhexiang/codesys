/* usbPciStub.c - system specific USB functions */

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
01c,30jan13,ljg  add USB TCD support
01b,15jun12,fao  update for the first release.
01a,14jun12,rab  Written.
*/

#include <vxWorks.h>
#include "config.h"

/* defines */

#define EHCI0_REG_READ_32(addr) \
        *((volatile UINT32 *)(ZYNQ7K_USB0_BASE + addr))

#define EHCI0_REG_WRITE_32(addr, data) \
        *((volatile UINT32 *)(ZYNQ7K_USB0_BASE + addr)) = data

#define ZYNQ7K_EHCI0_PORTSC1        0x184
#define ZYNQ7K_EHCI0_USBMODE        0x1A8
#define ZYNQ7K_EHCI_HOST_MODE       0x03
#define ZYNQ7K_EHCI_PORT_ULPI       0x80000000

/*******************************************************************************
*
* ehci0Init - initialize the on-chip EHCI controller (USB0)
*
* This routine initializes the ZYNQ-7000 on-chip EHCI controller (USB0).
*
* RETURNS: N/A
*
* ERRNO: N/A
*/

void zynq7kEhci0Init (void)
    {
    UINT32  regval;

    /* Set PHY to ULPI mode */

    regval = EHCI0_REG_READ_32 (ZYNQ7K_EHCI0_PORTSC1);
    regval |= ZYNQ7K_EHCI_PORT_ULPI;
    EHCI0_REG_WRITE_32(ZYNQ7K_EHCI0_PORTSC1, regval);

    /* Set USB controller to Host mode */

    regval = EHCI0_REG_READ_32 (ZYNQ7K_EHCI0_USBMODE);
    regval |= ZYNQ7K_EHCI_HOST_MODE;
    EHCI0_REG_WRITE_32 (ZYNQ7K_EHCI0_USBMODE, regval);
    }

/*******************************************************************************
*
* ehci0PostResetHook - post reset hook of the on-chip EHCI controller (USB0)
*
* This routine sets the on-chip EHCI controller (USB0) to host mode after reset.
*
* RETURNS: N/A
*
* ERRNO: N/A
*/

void zynq7kEhci0PostResetHook (void)
    {
    UINT32  regval;

    regval = EHCI0_REG_READ_32 (ZYNQ7K_EHCI0_USBMODE);
    regval |= ZYNQ7K_EHCI_HOST_MODE;
    EHCI0_REG_WRITE_32 (ZYNQ7K_EHCI0_USBMODE, regval);
    }

#if defined (INCLUDE_FSL_TCD)

/*******************************************************************************
*
* usbPciMemioOffset - Return PCI MEMIO to CPU MEMIO offset
*
* For memory-mapped I/O, the CPU's view of a memory address may not be the
* same as that programmed into the base address register of a PCI adapter.
* The CPU should add the value returned by this function to the BAR in order
* to produce the correct CPU-visible memory address.
*
* RETURNS: USB_PCI_MEMIO_OFFSET
*/

UINT32 usbPciMemioOffset (void)
    {
    return 0;
    }

/*******************************************************************************
*
* usbPciIntConnect - Connect to a interrupt vector
*
* Connects the <func> to the interrupt number <intNo>.  <param> is an
* application-specific value which will be passed to <func> each time
* the interrupt handler is invoked.
*
* RETURNS: OK, or ERROR if unable to connect/enable interrupt
*/

STATUS usbPciIntConnect
    (
    VOIDFUNCPTR func, /* new interrupt handler */
    VOID * param,      /* parameter for int handler */
    UINT16 intNo      /* interrupt vector number */
    )

    {
    UINT32 vec = (UINT32)intNo ;
    UINT32 level = (UINT32)intNo;

    if (intConnect((VOIDFUNCPTR *)vec, func, (int)param) != OK)
        return ERROR;
    
    if (intEnable(level) != OK)
        {
        return ERROR;
        }

    return OK;
    }

/*******************************************************************************
*
* usbPciIntDisconnect - Removes an interrupt handler
*
* Removes an interrupt handler installed by usbPciIntConnect().  <func>,
* <param>, and <intNo> must match the corresponding parameters from an earlier
* call to usbPciIntConnect().
*
* RETURNS: N/A
*/

VOID usbPciIntRestore
    (
    VOIDFUNCPTR func,  /* int handler to be removed */
    VOID * param,       /* parameter for int handler */
    UINT16 intNo       /* interrupt vector number */
    )

    {
    UINT32 vec = (UINT32)intNo ;
    UINT32 level = (UINT32)intNo;

    if (intDisconnect((VOIDFUNCPTR *)vec, func, (int)param) != OK)
        return;

    intDisable(level);
    }

#endif /* INCLUDE_FSL_TCD */
