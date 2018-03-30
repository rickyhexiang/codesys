/* usrAppInit.c - stub application initialization routine */

/* Copyright (c) 1998,2006,2011 Wind River Systems, Inc. 
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
01c,26may11,pcs  Add stubs corresponding to the boot sequence hook callout
                 mechanism.
01b,16mar06,jmt  Add header file to find USER_APPL_INIT define
01a,02jun98,ms   written
*/

/*
DESCRIPTION
Initialize user application code.
*/ 

#include <vxWorks.h>
#if defined(PRJ_BUILD)
#include "prjParams.h"
#endif /* defined PRJ_BUILD */

#include <stdio.h>
#include <symLib.h>
#include <loadLib.h>
#include <ioLib.h>
#include <taskLib.h>  

/******************************************************************************
*
* usrAppInit - initialize the users application
*/ 

extern SYMTAB_ID sysSymTbl; 
void usrAppInit (void)
{
#ifdef	USER_APPL_INIT
	USER_APPL_INIT;		/* for backwards compatibility */
#endif

    /* add application specific code here */	
	//ipcom_drv_eth_init("temac", 0, 0);
#if 1
	ipcom_drv_eth_init("gem", 1, 0);
	ifconfig("gem1 lladdr 00:0a:35:00:01:23");
	ifconfig("gem1 192.168.0.10 netmask 255.255.255.0 up");
#endif
	
#if 1
	ifconfig("gem0 dhcp up");

	FUNCPTR taskEntry = NULL;  
	SYM_TYPE *pType;
	int fd = 0;
	fd = open("vxWorks:codesyscontrol.out", O_RDONLY, 0);
	if(fd == NULL)  
	{  
		printf("\nopen project fail..\n");  
		return;  
	}
	if(loadModule(fd, LOAD_ALL_SYMBOLS) == ERROR)  
	{  
		printf("\nload module fail...\n"); 
		close(fd);
		return;  
	}	
	
	if(symFindByName(sysSymTbl, "PlcStart", (char**)&taskEntry, pType) == ERROR)  
	{  
		printf("\nfind symbol fail...\n"); 
		close(fd); 
		return;
	}  
	taskSpawn("PlcStart", 60, 0, 64 * 1024 * 1024, taskEntry, "vxWorks:CODESYSControl_VxWorks.cfg", 0, 0, 0, 0, 0, 0, 0, 0, 0);
	
	close(fd);
#endif	
}

#ifdef INCLUDE_USER_PRE_KERNEL_APPL_INIT
/******************************************************************************
*
* usrPreKernelAppInit - initialize the users pre-kernel application code
*/ 

void usrPreKernelAppInit (void)
    {

    /*
     * Add application specific code here.
     * No kernel feature is available at this point.
     */

    }
#endif

#ifdef INCLUDE_USER_POST_KERNEL_APPL_INIT
/******************************************************************************
*
* usrPostKernelAppInit - initialize the users post-kernel application code
*/ 

void usrPostKernelAppInit (void)
    {

    /*
     * Add application specific code here.
     * Core kernel feature is available at this point.
     * IO system and Network is not available.
     * kernel features dependent on system clock or timer not available.
     */

    }
#endif


#ifdef INCLUDE_USER_PRE_NETWORK_APPL_INIT
/******************************************************************************
*
* usrPreNetworkAppInit - initialize the users pre-network application code
*/ 

void usrPreNetworkAppInit (void)
    {

    /*
     * Add application specific code here.
     * Core kernel feature and IO system is available at this point.
     * Network is not available.
     */

    }
#endif


