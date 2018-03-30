/* qspiFlashMem.h - Xilinx ZYNQ-7000 QSPI flash memory device Header File */

/*
 * Copyright (c) 2012-2015 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
04jan15,c_l  Add 32MBytes of flash support for ZC706. (VXW6-23897)
10feb14,g_x  add Tx FIFO length definition (VXW6-70122)
01b,12apr13,y_c  move include header file out of extern "C" section.
01a,01jul12,clx  created from mspd_comcerto100 rev 01b
*/

#ifndef __INCqspiFlashMemh
#define __INCqspiFlashMemh

#include <vxWorks.h>
#include "config.h"

#ifdef __cplusplus
extern "C" {
#endif

/* spi protocol instruction */

#define QSPI_FLASH_SR_WIP          0x01  /* write in progress */
#define QSPI_FLASH_SR_WEL          0x02  /* Flash Commands */
#define QSPI_FLASH_CMD_WRSR        0x01  /* Write status register */
#define QSPI_FLASH_CMD_PP          0x02  /* Page program */
#define QSPI_FLASH_CMD_READ        0x03  /* Normal read data bytes */
#define QSPI_FLASH_CMD_WRDS        0x04  /* Write disable */
#define QSPI_FLASH_CMD_RDSR        0x05  /* Read status register */
#define QSPI_FLASH_CMD_WE          0x06  /* Write enable */
#define QSPI_FLASH_CMD_FAST_READ   0x0B  /* Fast read data bytes */
#define QSPI_FLASH_CMD_BE_4K       0x20  /* Erase 4KiB block */
#define QSPI_FLASH_CMD_DUAL_READ   0x3B  /* Dual read data bytes */
#define QSPI_FLASH_CMD_BE_32K      0x52  /* Erase 32KiB block */
#define QSPI_FLASH_CMD_QUAD_READ   0x6B  /* Quad read data bytes */
#define QSPI_FLASH_CMD_ERASE_SUS   0x75  /* Erase suspend */
#define QSPI_FLASH_CMD_ERASE_RES   0x7A  /* Erase resume */
#define QSPI_FLASH_CMD_RDID        0x9F  /* Read JEDEC ID */
#define QSPI_FLASH_CMD_BE          0xC7  /* Erase whole flash block */
#define QSPI_FLASH_CMD_SE          0xD8  /* Sector erase (64KB)*/

/* QSPI Controller register offsets */

#define ZYNQ_QSPI_CR            0x00   /* Configuration  Register, RW */
#define ZYNQ_QSPI_ISR           0x04   /* Interrupt Status Register, RO */
#define ZYNQ_QSPI_IER           0x08   /* Interrupt Enable Register, WO */
#define ZYNQ_QSPI_IDR           0x0C   /* Interrupt Disable Register, WO */
#define ZYNQ_QSPI_IMR           0x10   /* Interrupt Enabled Mask Register, RO */
#define ZYNQ_QSPI_ER            0x14   /* Enable/Disable Register, RW */
#define ZYNQ_QSPI_DR            0x18   /* Delay Register, RW */
#define ZYNQ_QSPI_TXD           0x1C   /* Data Transmit Register, WO */
#define ZYNQ_QSPI_RXD           0x20   /* Data Receive Register, RO */
#define ZYNQ_QSPI_SICR          0x24   /* Slave Idle Count Register, RW */
#define ZYNQ_QSPI_THLD          0x28   /* Transmit FIFO Watermark Register,RW */
#define ZYNQ_QSPI_RHLD          0x2C   /* Rx FIFO Watermark Register,RW */
#define ZYNQ_QSPI_TXD1          0x80   /* Data Transmit Register 1,WO */
#define ZYNQ_QSPI_TXD2          0x84   /* Data Transmit Register 2,WO */
#define ZYNQ_QSPI_TXD3          0x88   /* Data Transmit Register 3,WO */
#define ZYNQ_QSPI_LINEAR_CFG    0xA0   /* Linear Adapter Config Ref, RW */
#define ZYNQ_QSPI_LINEAR_STAT   0xA4   /* Linear Adapter Status, RW */
#define ZYNQ_QSPI_MOD_ID        0xFC   /* Module ID Register, RO  */

/* QSPI Interrupt Registers bit Masks */

#define ZYNQ_QSPI_IXR_RXOF      0x00000001 /* RX Overflow */
#define ZYNQ_QSPI_IXR_MODF      0x00000002 /* QSPI Mode Fault */
#define ZYNQ_QSPI_IXR_TXNF      0x00000004 /* QSPI TX FIFO not Full */
#define ZYNQ_QSPI_IXR_TXFULL    0x00000008 /* QSPI TX FIFO Full */
#define ZYNQ_QSPI_IXR_RXNEMTY   0x00000010 /* QSPI RX FIFO Not Empty */
#define ZYNQ_QSPI_IXR_RXFULL    0x00000020 /* QSPI RX FIFO Full */
#define ZYNQ_QSPI_IXR_TXUF      0x00000040 /* QSPI TX FIFO Underflow */
#define ZYNQ_QSPI_IXR_RW        (ZYNQ_QSPI_IXR_TXNF | ZYNQ_QSPI_IXR_MODF)
#define ZYNQ_QSPI_IXR_ALL       0x0000007F /* QSPI Enable Register bit Masks */
#define ZYNQ_QSPI_ER_ENABLE     0x00000001 /* QSPI Controller Enable Bit */

/* QSPI configuration Registers bit definition */

#define ZYNQ_QSPI_CR_MSTR       (1 << 0)  /* Master/Slave Mode Select*/
#define ZYNQ_QSPI_CR_CPOL       (1 << 1)  /* Clock Polarity Control */
#define ZYNQ_QSPI_CR_CPHA       (1 << 2)  /* Clock Phase Control */
#define ZYNQ_QSPI_CR_BDIV(x)    (x << 3)  /* Baud rate divisor (0:2, 1:4, 2:8 */
#define ZYNQ_QSPI_CR_FIFO(x)    (x << 6)  /* FIFO Width, 0:8b, 1:16b, 3:32bi */
#define ZYNQ_QSPI_CR_RCLK       (1 << 8)  /* Reference Clock(1:ext, 0:spi ref)*/
#define ZYNQ_QSPI_CR_SEL_CS     (1 << 10) /* Manual drive Chip Select */
#define ZYNQ_QSPI_CR_MAN_CS     (1 << 14) /* Manual Chip Select mode */
#define ZYNQ_QSPI_CR_MFEN       (1 << 15) /* Manual Start mode */
#define ZYNQ_QSPI_CR_MANSTRT    (1 << 16) /* Manual Start TX data */
#define ZYNQ_QSPI_CR_HOLD       (1 << 19) /* Holdb and WPn pin are driven */
#define ZYNQ_QSPI_CR_BE         (1 << 26) /* Endian (1 for BE) */
#define ZYNQ_QSPI_CR_IFMODE     (1 << 31) /* Flash Mode */
#define ZYNQ_QSPI_CR_RESERVED   ((1 << 17) | (7 << 11))
#define ZYNQ_QSPI_CR_BAUD       0x00000038 /* Baud Rate Mask */

#define CR_MASK (~(ZYNQ_QSPI_CR_MSTR | ZYNQ_QSPI_CR_CPOL | ZYNQ_QSPI_CR_CPHA |\
                ZYNQ_QSPI_CR_BDIV(7) | ZYNQ_QSPI_CR_FIFO(3) | \
                ZYNQ_QSPI_CR_RCLK | ZYNQ_QSPI_CR_SEL_CS | ZYNQ_QSPI_CR_MAN_CS |\
                ZYNQ_QSPI_CR_MFEN | ZYNQ_QSPI_CR_MANSTRT | ZYNQ_QSPI_CR_HOLD |\
                ZYNQ_QSPI_CR_BE | ZYNQ_QSPI_CR_IFMODE))

#define CR_IO_MODE  (ZYNQ_QSPI_CR_MSTR |\
                     ZYNQ_QSPI_CR_BDIV(0) | ZYNQ_QSPI_CR_FIFO(3) |\
                     ZYNQ_QSPI_CR_MFEN | ZYNQ_QSPI_CR_MAN_CS |\
                     ZYNQ_QSPI_CR_HOLD | ZYNQ_QSPI_CR_IFMODE)

/*
 * QSPI controller in linear address mode should set the baud rate divider a
 * larger vaule, ohterwise the controller might hang in a highly loaded system.
 */

#define CR_LIN_MODE (ZYNQ_QSPI_CR_MSTR |\
                    ZYNQ_QSPI_CR_BDIV(2) | ZYNQ_QSPI_CR_FIFO(3) |\
                    ZYNQ_QSPI_CR_HOLD | ZYNQ_QSPI_CR_IFMODE)

/* macro for seting chip select line */

#define QSPI_SET_CS QSPI_REG_WRITE_32 (ZYNQ_QSPI_CR, ZYNQ_QSPI_CR_SEL_CS |\
                                                QSPI_REG_READ_32 (ZYNQ_QSPI_CR))

/* macro for clearing chip select line */

#define QSPI_CLR_CS QSPI_REG_WRITE_32 (ZYNQ_QSPI_CR, (~ZYNQ_QSPI_CR_SEL_CS) &\
                                                QSPI_REG_READ_32 (ZYNQ_QSPI_CR))

/* macro for starting  manual start data transfer */

#define QSPI_MAN_STRT QSPI_REG_WRITE_32 (ZYNQ_QSPI_CR, ZYNQ_QSPI_CR_MANSTRT |\
                                                QSPI_REG_READ_32 (ZYNQ_QSPI_CR))

/* Linear Adapter Config Register bit Masks */

#define ZYNQ_QSPI_LINEAR_EN        (1 << 31)  /* Linear quad SPI mode  */
#define ZYNQ_QSPI_LINEAR_INST_READ (3 << 0)   /* Read as Read Ins code */
#define ZYNQ_QSPI_LINEAR_TWO_MEM   (1 << 30)  /* Both upper and lower  */
#define ZYNQ_QSPI_LINEAR_SEP_BUS   (1 << 29)  /* Separate memory bus   */
#define ZYNQ_QSPI_LINEAR_U_PAGE    (1 << 28)  /* Upper memory page     */

/* TX FIFO length */

#define ZYNQ_QSPI_TXFIFO_LEN        (4 * 63)

/* N25Q128 status register bit defined  */

#define SR_SRWD          (0x1 << 7)         /* SR write protect */
#define SR_BP3           (0x1 << 6)         /* Top/Bottom(TB) bit */
#define SR_TB            (0x1 << 5)         /* Block protect 0 */
#define SR_BP2           (0x1 << 4)         /* Block protect 2 */
#define SR_BP1           (0x1 << 3)         /* Block protect 1 */
#define SR_BP0           (0x1 << 2)         /* Block protect 0 */
#define SR_WEL           (0x1 << 1)         /* Write enable latch */
#define SR_WIP           (0x1 << 0)         /* Write in progress */

#define LINEAR_MODE      0
#define IO_MODE          1
#define WIP_TOUT         300000             /* max 300s */

#define QSPI_FLASH_LINR_BASE       SPI_FLASH_BASE_ADRS
#define QSPI_FLASH_SECTOR_SIZE     (SZ_64K)
#define QSPI_FLASH_ADDR_SHIFT      1
#define QSPI_REG_READ_32(addr)        \
    *((volatile UINT32 *)(ZYNQ7K_QSPI_BASE + addr))
#define QSPI_REG_WRITE_32(addr, data) \
    *((volatile UINT32 *)(ZYNQ7K_QSPI_BASE + addr)) = data

/* disable debugging by default */

#undef ZYNQ7K_QSPI_FLASH_DEBUG
#ifdef ZYNQ7K_QSPI_FLASH_DEBUG

#   define ZYNQ7K_QSPI_DBG_LOG(X0, X1, X2, X3, X4, X5, X6)    \
    do {                                                    \
        if (_func_logMsg != NULL)                           \
            _func_logMsg(X0, X1, X2, X3, X4, X5, X6);       \
    } while ((0))

#else

#   define ZYNQ7K_QSPI_DBG_LOG(X0, X1, X2, X3, X4, X5, X6)

#endif /* SPEAR_SPI_FLASH_DEBUG */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __INCqspiFlashMemh */
