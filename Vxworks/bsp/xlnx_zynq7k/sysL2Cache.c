/* sysL2Cache.c - ARM Prime Cell PL310 L2 Cache Controller Routines */

/*
 * Copyright (c) 2010-2012, 2014 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
08oct14,c_l  remove compiler warnings. (VXW6-83566)
23jul14,c_l  Add L2 prefetch support. (VXW6-83079)
06jan14,c_l  Improve cache operation. (VXW6-27040)
01h,17sep12,hcl  Dynamically read number of way.
01g,10sep12,m_h  L2 cachePipeFlush (WIND00240234)
01f,15jun12,ggm  Fixed the failure of atomic operation in non-cachable memory
                 region (WIND00337850)
01e,26sep11,clx  initialize l2CacheBase with non-zero value to put it
                 in data segment.
01d,10nov10,my_  various modification (WIND00240234):
                 1.update description;
                 2.change variable name;
                 3.get controller base address from BSP;
                 4.use explicit cache sync operation;
                 5.remove L2_CACHE_SIZE because it is not used.
01c,11oct10,my_  make the driver SMP-safe (WIND00233175).
01b,29jun10,my_  update for first release.
01a,28jun10,z_l  created.
*/

/*
DESCRIPTION
This file contains support routines for the Prime Cell L2 cache controller
(PL310). Some APIs for cache operation, such as flush/clear/invalidate,
are implemented in this file. These APIs are used in VxWorks arch library to
support L2 cache.

The following are atomic operations:

    Clean Line by PA or by Index/Way
    Invalidate Line by PA
    Clean and Invalidate Line by PA or by Index/Way
    Cache Sync

These operations stall the slave ports until they are complete. When these
registers are read, bit [0], the C flag, indicates that a background  operation
is in progress. So at the end of each operation, we wait for the background
operation is complete.

All cache maintenance operations automatically perform a Cache Sync
operation before starting. Before writing to any other register you must
perform an explicit Cache Sync operation. So at the end of operation, we perform
an explicit Cache Sync operation by writing 0 to Cache Sync register.
*/

#include <vxWorks.h>
#include "config.h"

/* locals */

LOCAL SPIN_LOCK_ISR_DECL(L2CacheLock, 0);

/*
 * L2 Cache Controller Base Address.
 * initialize l2CacheBase with non-zero value to put it in data segment.
 */

LOCAL UINT32 l2CacheBase = 0x12345678;

/* L2 Cache Controller associativity */

LOCAL UINT32 l2CacheAss = 0xff;
LOCAL UINT32 l2CacheSize = 0;

/* register definitions */

#define L2_CACHE_ID              (l2CacheBase + 0x0)
#define L2_CACHE_TYPE            (l2CacheBase + 0x4)
#define L2_CONTROL               (l2CacheBase + 0x100)
#define L2_AUX_CONTROL           (l2CacheBase + 0x104)
#define L2_TAG_RAM_CONTROL       (l2CacheBase + 0x108)
#define L2_DATA_RAM_CONTROL      (l2CacheBase + 0x10C)
#define L2_INT_MASK              (l2CacheBase + 0x214)
#define L2_INT_CLEAR             (l2CacheBase + 0x220)

#define L2_CACHE_SYNC            (l2CacheBase + 0x730)
#define L2_INVALIDATE_PA         (l2CacheBase + 0x770)
#define L2_INVALIDATE_WAY        (l2CacheBase + 0x77c)
#define L2_CLEAN_PA              (l2CacheBase + 0x7b0)
#define L2_CLEAN_WAY             (l2CacheBase + 0x7bc)
#define L2_CLEAN_INVALIDATE_PA   (l2CacheBase + 0x7f0)
#define L2_CLEAN_INVALIDATE_WAY  (l2CacheBase + 0x7fc)

#define L2_CONTROL_ENABLE        (0x1)
#define L2_OPERATION_IN_PROGRESS (0x1)
#define L2_INT_MASK_ALL          (0x0)
#define L2_INT_CLEAR_ALL         (0x1ff)

#define L2_CACHE_LINE_SIZE       (0x20)
#define L2_CACHE_LINE_MASK       (L2_CACHE_LINE_SIZE - 1)

#define L2_AUX_CTRL_DATA_PREFETCH  (1 << 28)
#define L2_AUX_CTRL_INST_PREFETCH  (1 << 29)
#define L2_AUX_CTL_SHARED_BIT      (1 << 22)      /* Shared attribute */
#define L2_AUX_CONTROL_ASS_MSK     (0x1 << 16)    /* Associativity    */
#define L2_AUX_CONTROL_WAYSIZE_MSK (0x7 << 17)    /* Way-size         */
#define L2_AUX_CTL_WAYSIZE_SHIFT   (17)

#define L2_RAM_CTRL_1LATENCY 0
#define L2_RAM_CTRL_2LATENCY 1
#define L2_RAM_CTRL_3LATENCY 2
#define L2_RAM_CTRL_4LATENCY 3
#define L2_RAM_CTRL_5LATENCY 4
#define L2_RAM_CTRL_6LATENCY 5
#define L2_RAM_CTRL_7LATENCY 6
#define L2_RAM_CTRL_8LATENCY 7

#define L2_RAM_CTRL_WRITE_ACCESS_OFST 8
#define L2_RAM_CTRL_READ_ACCESS_OFST  4
#define L2_RAM_CTRL_SETUP_ACCESS_OFST 0

#define DEFAULT_TAG_RAM_CONTROL_MASK \
        ( (7 << L2_RAM_CTRL_WRITE_ACCESS_OFST) | \
          (7 << L2_RAM_CTRL_READ_ACCESS_OFST)  | \
          (7 << L2_RAM_CTRL_SETUP_ACCESS_OFST)   \
        )

#define DEFAULT_DATA_RAM_CONTROL_MASK \
        ( (7 << L2_RAM_CTRL_WRITE_ACCESS_OFST) | \
          (7 << L2_RAM_CTRL_READ_ACCESS_OFST)  | \
          (7 << L2_RAM_CTRL_SETUP_ACCESS_OFST)   \
        )

#ifndef DEFAULT_TAG_RAM_CONTROL_VALUE 
#define DEFAULT_TAG_RAM_CONTROL_VALUE \
        ( (L2_RAM_CTRL_8LATENCY << L2_RAM_CTRL_WRITE_ACCESS_OFST) | \
          (L2_RAM_CTRL_8LATENCY << L2_RAM_CTRL_READ_ACCESS_OFST)  | \
          (L2_RAM_CTRL_8LATENCY << L2_RAM_CTRL_SETUP_ACCESS_OFST)   \
        )
#endif /* DEFAULT_TAG_RAM_CONTROL_VALUE */

#ifndef DEFAULT_DATA_RAM_CONTROL_VALUE 
#define DEFAULT_DATA_RAM_CONTROL_VALUE \
        ( (L2_RAM_CTRL_8LATENCY << L2_RAM_CTRL_WRITE_ACCESS_OFST) | \
          (L2_RAM_CTRL_8LATENCY << L2_RAM_CTRL_READ_ACCESS_OFST)  | \
          (L2_RAM_CTRL_8LATENCY << L2_RAM_CTRL_SETUP_ACCESS_OFST)   \
        )
#endif /*DEFAULT_DATA_RAM_CONTROL_VALUE */

#ifdef ARMBE8
#   define PL310_REGISTER_READ(reg) \
    vxbSwap32(*(volatile UINT32 *)(reg))
#else /* LE */
#   define PL310_REGISTER_READ(reg) \
    *(volatile UINT32 *)(reg)
#endif /* ARMBE8 */

#ifdef ARMBE8
#   define PL310_REGISTER_WRITE(reg, data)\
    *(volatile UINT32 *)(reg) = vxbSwap32(data)
#else /* LE */
#   define PL310_REGISTER_WRITE(reg, data)\
    *(volatile UINT32 *)(reg) = (data)
#endif /* ARMBE8 */

/*
 * The following five function pointers are defined and used in VxWorks ARM
 * arch library. To support L2 cache, customer BSP should initialize them with
 * concrete implementation.
 */

IMPORT void (*_pSysL2CacheEnable)(CACHE_TYPE cacheType);
IMPORT void (*_pSysL2CacheDisable)(CACHE_TYPE cacheType);
IMPORT void (*_pSysL2CacheInvFunc)(CACHE_TYPE cacheType,
                                   void * start, void * end);
IMPORT void (*_pSysL2CacheFlush)(CACHE_TYPE cacheType, 
                                 void * start, void * end);
IMPORT void (*_pSysL2CacheClear)(CACHE_TYPE cacheType, 
                                 void * start, void * end);
IMPORT void (*_pSysL2CachePipeFlush)(void);

/*******************************************************************************
*
* sysL2Invalidate - invalidate L2 Cache
*
* This routine invalidates L2 cache ranging from 'pMemStart' to 'pMemEnd'
*
* RETURNS: N/A
*
* ERRNO: N/A
*/

LOCAL void sysL2Invalidate
    (
    CACHE_TYPE cacheType,
    void * pMemStart,
    void * pMemEnd
    )
    {
    UINT32 phyAddr;
    UINT32 tempSize;
    UINT32 invalidateSize;

    if ((UINT32)pMemEnd == ENTIRE_CACHE) /* invalidate the whole L2 cache */
        {
        SPIN_LOCK_ISR_TAKE(&L2CacheLock);

        PL310_REGISTER_WRITE(L2_INVALIDATE_WAY, l2CacheAss);

        /* poll state until the background invalidate operation is complete */

        while (PL310_REGISTER_READ(L2_INVALIDATE_WAY) & l2CacheAss);

        SPIN_LOCK_ISR_GIVE(&L2CacheLock);

        return;
        }
    else
        {
        if ((UINT32)pMemEnd > (UINT32)pMemStart) /* check the parameters */
            invalidateSize = (UINT32)pMemEnd - (UINT32)pMemStart;
        else
            return;
        }

    /* use the physical address for L2 cache operation */

    phyAddr = (UINT32)mmuVirtToPhys((VIRT_ADDR)pMemStart);
    phyAddr &= ~L2_CACHE_LINE_MASK;

    SPIN_LOCK_ISR_TAKE(&L2CacheLock);

    for (tempSize = 0; tempSize < invalidateSize;
         tempSize += L2_CACHE_LINE_SIZE)
        {
        /* invalidate operation */

        PL310_REGISTER_WRITE(L2_INVALIDATE_PA, (phyAddr + tempSize));

        /* wait for completion */

        while (PL310_REGISTER_READ(L2_INVALIDATE_PA) &
               L2_OPERATION_IN_PROGRESS);
        }

    /* check the boundary cache line */

    if (((L2_CACHE_LINE_SIZE - ((UINT32)pMemStart % L2_CACHE_LINE_SIZE)) +
        invalidateSize % L2_CACHE_LINE_SIZE) > L2_CACHE_LINE_SIZE)
        {
        /* invalidate operation */

        PL310_REGISTER_WRITE(L2_INVALIDATE_PA, (phyAddr + tempSize));

        /* wait for completion */

        while (PL310_REGISTER_READ(L2_INVALIDATE_PA) &
               L2_OPERATION_IN_PROGRESS);
        }

    /* cache sync */

    PL310_REGISTER_WRITE(L2_CACHE_SYNC, 0);

    /* wait for completion */

    while (PL310_REGISTER_READ(L2_CACHE_SYNC) & L2_OPERATION_IN_PROGRESS);

    SPIN_LOCK_ISR_GIVE(&L2CacheLock);
    }

/*******************************************************************************
*
* sysL2Flush - flush L2 Cache
*
* This routine flushes L2 cache ranging from 'pMemStart' to 'pMemEnd'
*
* RETURNS: N/A
*
* ERRNO: N/A
*/

LOCAL void sysL2Flush
    (
    CACHE_TYPE cacheType,
    void * pMemStart,
    void * pMemEnd
    )
    {
    UINT32 phyAddr = 0;
    UINT32 tempSize = 0;
    UINT32 flushSize = 0;

    if ((UINT32)pMemEnd != ENTIRE_CACHE) /* flush the whole L2 cache */
        {
        if ((UINT32)pMemEnd > (UINT32)pMemStart) /* check the parameters */
            flushSize = (UINT32)pMemEnd - (UINT32)pMemStart;
        else
            return;
        }

    if (((UINT32)pMemEnd == ENTIRE_CACHE) /* flush the whole L2 cache */
        || (flushSize >= l2CacheSize))
        {
        SPIN_LOCK_ISR_TAKE(&L2CacheLock);

        PL310_REGISTER_WRITE(L2_CLEAN_WAY, l2CacheAss);

        /* poll state until the background flush operation  is complete */

        while (PL310_REGISTER_READ(L2_CLEAN_WAY) & l2CacheAss);

        SPIN_LOCK_ISR_GIVE(&L2CacheLock);

        return;
        }

    /* use the physical address for L2 cache operation */

    phyAddr = (UINT32)mmuVirtToPhys((VIRT_ADDR)pMemStart);
    phyAddr &= ~L2_CACHE_LINE_MASK;

    SPIN_LOCK_ISR_TAKE(&L2CacheLock);

    for (tempSize = 0; tempSize < flushSize; tempSize += L2_CACHE_LINE_SIZE)
        {
        /* flush operation */

        PL310_REGISTER_WRITE(L2_CLEAN_PA, (phyAddr + tempSize));

        /* wait for completion */

        while (PL310_REGISTER_READ(L2_CLEAN_PA) & L2_OPERATION_IN_PROGRESS);
        }

    /* check the boundary cache line */

    if (((L2_CACHE_LINE_SIZE - ((UINT32)pMemStart % L2_CACHE_LINE_SIZE)) +
        flushSize % L2_CACHE_LINE_SIZE) > L2_CACHE_LINE_SIZE)
        {
        /* flush operation */

        PL310_REGISTER_WRITE(L2_CLEAN_PA, (phyAddr + tempSize));

        /* wait for completion */

        while (PL310_REGISTER_READ(L2_CLEAN_PA) & L2_OPERATION_IN_PROGRESS);
        }

    /* cache sync */

    PL310_REGISTER_WRITE(L2_CACHE_SYNC, 0);

    /* wait for completion */

    while (PL310_REGISTER_READ(L2_CACHE_SYNC) & L2_OPERATION_IN_PROGRESS);

    SPIN_LOCK_ISR_GIVE(&L2CacheLock);
    }

/*******************************************************************************
*
* sysL2Clear - clear L2 Cache
*
* This routine clears L2 cache ranging from 'pMemStart' to 'pMemEnd'
*
* NOTE Clear operation is flush + invalidate
*
* RETURNS: N/A
*
* ERRNO: N/A
*/

LOCAL void sysL2Clear
    (
    CACHE_TYPE cacheType,
    void * pMemStart,
    void * pMemEnd
    )
    {
    UINT32 phyAddr = 0;
    UINT32 tempSize = 0;
    UINT32 clearSize = 0;

    if ((UINT32)pMemEnd != ENTIRE_CACHE) /* if clear the whole L2 cache */
        {
        if ((UINT32)pMemEnd > (UINT32)pMemStart) /* check the parameters */
            clearSize = (UINT32)pMemEnd - (UINT32)pMemStart;
        else
            return;
        }
 
    if (((UINT32)pMemEnd == ENTIRE_CACHE) /* clear the whole L2 cache */
        || (clearSize >= l2CacheSize))
        {
        SPIN_LOCK_ISR_TAKE(&L2CacheLock);

        PL310_REGISTER_WRITE(L2_CLEAN_INVALIDATE_WAY, l2CacheAss);

        /* poll state until the background clear operation  is complete */

        while (PL310_REGISTER_READ(L2_CLEAN_INVALIDATE_WAY) & l2CacheAss);

        SPIN_LOCK_ISR_GIVE(&L2CacheLock);

        return;
        }

    /* use the physical address for L2 cache operation */

    phyAddr = (UINT32)mmuVirtToPhys((VIRT_ADDR)pMemStart);
    phyAddr &= ~L2_CACHE_LINE_MASK;

    SPIN_LOCK_ISR_TAKE(&L2CacheLock);

    for (tempSize = 0; tempSize < clearSize; tempSize += L2_CACHE_LINE_SIZE)
        {
        /* clear operation */

        PL310_REGISTER_WRITE(L2_CLEAN_INVALIDATE_PA, (phyAddr + tempSize));

        /* wait for completion */

        while (PL310_REGISTER_READ(L2_CLEAN_INVALIDATE_PA) &
               L2_OPERATION_IN_PROGRESS);
        }

    /* check the boundary cache line */

    if (((L2_CACHE_LINE_SIZE - ((UINT32)pMemStart % L2_CACHE_LINE_SIZE)) +
        clearSize % L2_CACHE_LINE_SIZE) > L2_CACHE_LINE_SIZE)
        {
        /* clear operation */

        PL310_REGISTER_WRITE(L2_CLEAN_INVALIDATE_PA, (phyAddr + tempSize));

        /* wait for completion */

        while (PL310_REGISTER_READ(L2_CLEAN_INVALIDATE_PA) &
               L2_OPERATION_IN_PROGRESS);
        }

    /* cache sync */

    PL310_REGISTER_WRITE(L2_CACHE_SYNC, 0);

    /* wait for completion */

    while (PL310_REGISTER_READ(L2_CACHE_SYNC) & L2_OPERATION_IN_PROGRESS);

    SPIN_LOCK_ISR_GIVE(&L2CacheLock);

    }

/*******************************************************************************
*
* sysL2PipeFlush - Drain the Write Buffer
*
* This routine drains the L2 write buffer
*
* RETURNS: N/A
*
* ERRNO: N/A
*/

LOCAL void sysL2PipeFlush
    (
    void
    )
    {

    SPIN_LOCK_ISR_TAKE(&L2CacheLock);

    /* cache sync */

    PL310_REGISTER_WRITE(L2_CACHE_SYNC, 0);

    /* wait for completion */

    while (PL310_REGISTER_READ(L2_CACHE_SYNC) & L2_OPERATION_IN_PROGRESS);

    SPIN_LOCK_ISR_GIVE(&L2CacheLock);

    }

/*******************************************************************************
*
* sysL2Enable - enable L2 Cache
*
* This routine enables the external L2 cache connected to Cortex A9 processor
*
* RETURNS: N/A
*
* ERRNO: N/A
*/

LOCAL void sysL2Enable
    (
    CACHE_TYPE cacheType
    )
    {
 
    SPIN_LOCK_ISR_TAKE(&L2CacheLock);

    PL310_REGISTER_WRITE(L2_CONTROL, L2_CONTROL_ENABLE); /* enable L2 cache */

    SPIN_LOCK_ISR_GIVE(&L2CacheLock);
    }

/*******************************************************************************
*
* sysL2Disable - disable L2 Cache
*
* This routine disables the external L2 cache connected to Cortex A9 processor
*
* RETURNS: N/A
*
* ERRNO: N/A
*/

LOCAL void sysL2Disable
    (
    CACHE_TYPE cacheType
    )
    {
    SPIN_LOCK_ISR_TAKE(&L2CacheLock);

    PL310_REGISTER_WRITE(L2_CONTROL, 0x0); /* disable L2 cache */

    SPIN_LOCK_ISR_GIVE(&L2CacheLock);
    }

/*******************************************************************************
*
* sysL2CacheInit - init L2 cache support
*
* This routine initializes L2 cache support. The 'base' parameter is the base
* address of the Prime Cell L2 cache controller and is provided
* by the caller (uauslly in sysHwInit* ).
*
* RETURNS: N/A
*
* ERRNO: N/A
*/

LOCAL void sysL2CacheInit
    (
    UINT32 base
    )
    {

    UINT32 auxRegValue;
    UINT32 l2CacheWaySize;
    UINT32 l2CacheWay;
    volatile UINT32 temp;

    /* set L2 cache controller base provided by BSP */

    l2CacheBase = base;

    /* L2 cache controller associativity */

    auxRegValue = PL310_REGISTER_READ(L2_AUX_CONTROL);
    l2CacheAss = (auxRegValue & L2_AUX_CONTROL_ASS_MSK) ? (0xffff) : (0xff);
    l2CacheWay = (auxRegValue & L2_AUX_CONTROL_ASS_MSK) ? (16) : (8); 
    l2CacheWaySize = (auxRegValue & L2_AUX_CONTROL_WAYSIZE_MSK) 
                  >> L2_AUX_CTL_WAYSIZE_SHIFT;

    /* 
     * If Way-size is 0b000,internally mapped to 16KB.
     *
     * If Way-size is 0b111,internally mapped to 512KB.
     */

    if (l2CacheWaySize == 0)
        l2CacheWaySize = 1;
    if (l2CacheWaySize == 7)
        l2CacheWaySize = 6;

    l2CacheWaySize = (1 << (l2CacheWaySize + 3)) * SZ_1K;

    /*
     * 512KB L2 cache RAM. 8-way associativity. way-size is 64KB
     */

    l2CacheSize = l2CacheWay * l2CacheWaySize;

    PL310_REGISTER_WRITE(L2_CONTROL, 0x0); /* disable L2 cache */

    /*
     * We use the default configuration, so here we do not need to use the
     * auxiliary control register to configure associativity, way size and
     * latency of RAM access.
     * The "shared attribute override enable" bit in AUX_CTL register should 
     * be set to enable atomic operation on non-cacheable shared memory region.
     * This bit only applies to outer non-cacheable transactions for Normal, 
     * shareable memory and transforms them into:
     *    cacheable no allocate for reads
     *    write through no write allocate for writes.
     */

    auxRegValue = PL310_REGISTER_READ(L2_AUX_CONTROL) | L2_AUX_CTL_SHARED_BIT |
                  L2_AUX_CTRL_DATA_PREFETCH | L2_AUX_CTRL_INST_PREFETCH;

    PL310_REGISTER_WRITE(L2_AUX_CONTROL, auxRegValue);     

    /* Set up the Tag RAM Latency */

    temp = PL310_REGISTER_READ(L2_TAG_RAM_CONTROL);
    temp &= ~DEFAULT_TAG_RAM_CONTROL_MASK;
    temp |= DEFAULT_TAG_RAM_CONTROL_VALUE;
    PL310_REGISTER_WRITE(L2_TAG_RAM_CONTROL, temp);

    /* Set up the Data RAM Latency */

    temp = PL310_REGISTER_READ(L2_DATA_RAM_CONTROL);
    temp &= ~DEFAULT_DATA_RAM_CONTROL_MASK;
    temp |= DEFAULT_DATA_RAM_CONTROL_VALUE;
    PL310_REGISTER_WRITE(L2_DATA_RAM_CONTROL, temp);

    /* invalidate the whole L2 cache through way operation */

    PL310_REGISTER_WRITE(L2_INVALIDATE_WAY, l2CacheAss);

    /* poll state until the background invalidate operation is complete */

    while (PL310_REGISTER_READ(L2_INVALIDATE_WAY) & l2CacheAss);

    /* clear all pending interrupts */

    PL310_REGISTER_WRITE(L2_INT_CLEAR, L2_INT_CLEAR_ALL);

    /* mask all interrupts */

    PL310_REGISTER_WRITE(L2_INT_MASK, L2_INT_MASK_ALL);

    _pSysL2CacheInvFunc   = sysL2Invalidate;
    _pSysL2CacheEnable    = sysL2Enable;
    _pSysL2CacheDisable   = sysL2Disable;
    _pSysL2CacheFlush     = sysL2Flush;
    _pSysL2CacheClear     = sysL2Clear;
    _pSysL2CachePipeFlush = sysL2PipeFlush;

    }

