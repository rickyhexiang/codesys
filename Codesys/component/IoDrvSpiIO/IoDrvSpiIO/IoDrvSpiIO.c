/*****************************************************************************
*
*	Copyright:	3S - Smart Software Solutions GmbH, Kempten
*	Program:		Runtime System for the CoDeSys Soft-Plc
*	Module: 		Test component
*	Version:
*	Description:
******************************************************************************/
#ifndef STATICITF_DEF
#define STATICITF_DEF	static
#endif

#include "CmpStd.h"
#include "IoDrvSpiIODep.h"
#include <vxWorks.h>
#include <stdio.h>
#include <ioLib.h>
#include <fcntl.h>
#include <sysLib.h>
#include <sioLib.h>
#include <hwif/vxbus/vxBus.h>
#include <vxBusLib.h>
#include <hwif/vxbus/vxbSpiLib.h>

USE_STMT

#define TEST_BIT(x,offset)  (1&((x)>>(offset)))
#define SET_BIT(x,offset)   ((x)|=(1<<(offset)))
#define CLR_BIT(x,offset)   ((x)&=(~(1<<(offset))))

typedef struct
{
#ifndef CPLUSPLUS
    IBase_C Base;
    ICmpIoDrv_C IoDrv;
    ICmpIoDrvParameter_C IoDrvParameter;
#endif
    IBase *pIBase;
    ICmpIoDrv *pIoDrv;
    ICmpIoDrvParameter *pIoDrvParameter;
    IoDrvInfo Info;
} IoDrvSpiIO;

#ifndef CPLUSPLUS

DECLARE_ADDREF
DECLARE_RELEASE
DECLARE_QUERYINTERFACE

#endif

static IBase *s_pIBase;

VXB_DEVICE_ID pDI_Inst;     /* max31910 */
VXB_DEVICE_ID pDO_Inst;     /* max14912 */

#ifndef RTS_COMPACT_MICRO

DLL_DECL int CDECL ComponentEntry(INIT_STRUCT *pInitStruct)
/*	Used to exchange function pointers between component manager and components.
	Called at startup for each component.
	pInitStruct:			IN	Pointer to structure with:
		pfExportFunctions	OUT Pointer to function that exports component functions
		pfImportFunctions	OUT Pointer to function that imports functions from other components
		pfGetVersion		OUT Pointer to function to get component version
		pfRegisterAPI		IN	Pointer to component mangager function to register a api function
		pfGetAPI			IN	Pointer to component mangager function to get a api function
		pfCallHook			IN	Pointer to component mangager function to call a hook function
	Return					ERR_OK if library could be initialized, else error code
*/
{
    pInitStruct->CmpId = COMPONENT_ID;
    pInitStruct->pfExportFunctions = ExportFunctions;
    pInitStruct->pfImportFunctions = ImportFunctions;
    pInitStruct->pfGetVersion = CmpGetVersion;
    pInitStruct->pfHookFunction = HookFunction;
    pInitStruct->pfCreateInstance = CreateInstance;
    pInitStruct->pfDeleteInstance = DeleteInstance;

    s_pfCMRegisterAPI = pInitStruct->pfCMRegisterAPI;
    s_pfCMRegisterAPI2 = pInitStruct->pfCMRegisterAPI2;
    s_pfCMGetAPI = pInitStruct->pfCMGetAPI;
    s_pfCMGetAPI2 = pInitStruct->pfCMGetAPI2;
    s_pfCMCallHook = pInitStruct->pfCMCallHook;
    s_pfCMRegisterClass = pInitStruct->pfCMRegisterClass;
    s_pfCMCreateInstance = pInitStruct->pfCMCreateInstance;

    if (pInitStruct->pfCMRegisterClass != NULL)
        pInitStruct->pfCMRegisterClass(COMPONENT_ID, CLASSID_CIoDrvSpiIO);

    return ERR_OK;
}

#endif

static IBase *CDECL CreateInstance(CLASSID cid, RTS_RESULT *pResult)
{
#ifdef CPLUSPLUS
    if (cid == CLASSID_CIoDrvSpiIO)
    {
        CIoDrvSpiIO *pCIoDrvSpiIO = static_cast<CIoDrvSpiIO *>(new CIoDrvSpiIO());
        IBase *pIBase = (IBase *)pCIoDrvSpiIO->QueryInterface(pCIoDrvSpiIO, ITFID_IBase, pResult);
        RTS_SETRESULT(pResult, ERR_OK);
        return pIBase;
    }
#else
    if (cid == CLASSID_CIoDrvSpiIO)
    {
        IoDrvSpiIO *pIoDrvSpiIO = (IoDrvSpiIO *)CAL_SysMemAllocData(COMPONENT_NAME, sizeof(IoDrvSpiIO), NULL);
        if (pIoDrvSpiIO != NULL)
        {
            IBase *pI = &pIoDrvSpiIO->Base;
            pIoDrvSpiIO->pIBase = &pIoDrvSpiIO->Base;
            pI->bIEC = 0;
            pI->AddRef = AddRef;
            pI->Release = Release;
            pI->QueryInterface = QueryInterface;
            pI->iRefCount++;
            RTS_SETRESULT(pResult, ERR_OK);
            return pI;
        }
        else
        {
            RTS_SETRESULT(pResult, ERR_NOMEMORY);
            return NULL;
        }
    }
#endif
    RTS_SETRESULT(pResult, ERR_FAILED);
    return NULL;
}

static RTS_RESULT CDECL DeleteInstance(IBase *pIBase)
{
#ifdef CPLUSPLUS
    pIBase->Release();
    return ERR_OK;
#else
    pIBase->iRefCount--;
    CAL_SysMemFreeData(COMPONENT_NAME, pIBase);
    return ERR_OK;
#endif
}

#if !defined(CPLUSPLUS)
IMPLEMENT_ADDREF
IMPLEMENT_RELEASE

static void *CDECL QueryInterface(IBase *pBase, ITFID iid, RTS_RESULT *pResult)
{
    if (iid == ITFID_IBase)
    {
        /* Every interface has as first element a pointer to the IBase interface. So it doesn't matter, which interface
           is used to get the IBase pointer */
        ICmpIoDrv *pI = (ICmpIoDrv *)pBase;
        pI->pBase->iRefCount++;
        RTS_SETRESULT(pResult, ERR_OK);
        return pI->pBase;
    }
    if (iid == ITFID_ICmpIoDrv)
    {
        IoDrvSpiIO *pC = (IoDrvSpiIO *)pBase;
        pC->IoDrv.pBase = pBase;
        pC->IoDrv.IIoDrvCreate = IoDrvCreate;
        pC->IoDrv.IIoDrvDelete = IoDrvDelete;
        pC->IoDrv.IIoDrvGetInfo = IoDrvGetInfo;
        pC->IoDrv.IIoDrvUpdateConfiguration = IoDrvUpdateConfiguration;
        pC->IoDrv.IIoDrvUpdateMapping = IoDrvUpdateMapping;
        pC->IoDrv.IIoDrvReadInputs = IoDrvReadInputs;
        pC->IoDrv.IIoDrvWriteOutputs = IoDrvWriteOutputs;
        pC->IoDrv.IIoDrvStartBusCycle = IoDrvStartBusCycle;
        pC->IoDrv.IIoDrvScanModules = IoDrvScanModules;
        pC->IoDrv.IIoDrvGetModuleDiagnosis = IoDrvGetModuleDiagnosis;
        pC->pIoDrv = &pC->IoDrv;
        pC->Base.iRefCount++;
        RTS_SETRESULT(pResult, ERR_OK);
        return &pC->IoDrv;
    }
    if (iid == ITFID_ICmpIoDrvParameter)
    {
        IoDrvSpiIO *pC = (IoDrvSpiIO *)pBase;
        pC->IoDrvParameter.pBase = pBase;
        pC->IoDrvParameter.IIoDrvReadParameter = IoDrvReadParameter;
        pC->IoDrvParameter.IIoDrvWriteParameter = IoDrvWriteParameter;
        pC->pIoDrvParameter = &pC->IoDrvParameter;
        pC->Base.iRefCount++;
        RTS_SETRESULT(pResult, ERR_OK);
        return &pC->IoDrvParameter;
    }
    RTS_SETRESULT(pResult, ERR_FAILED);
    return NULL;
}
#endif

#ifndef RTS_COMPACT_MICRO

static int CDECL ExportFunctions(void)
/*	Export function pointers as api */
{
    /* Macro to export functions */
    EXPORT_STMT;
    return ERR_OK;
}

static int CDECL ImportFunctions(void)
/*	Get function pointers of other components */
{
    /* Macro to import functions */
    IMPORT_STMT;
    return ERR_OK;
}

static RTS_UI32 CDECL CmpGetVersion(void)
{
    return CMP_VERSION;
}

#endif

#define bool BOOL

#define TEST_BIT(x,offset)  (1&((x)>>offset))
#define SET_BIT(x,offset)   ((x)|=(1<<offset))
#define CLR_BIT(x,offset)   ((x)&=(~(1<<(offset))))

#define GPIO_DIR_OUTPUT			0
#define GPIO_DIR_INPUT			1

#define GPIO_REG_BASE			0xE000A000

#define GPIO_REG_DATA_OUTPUT_BANK2		0x48
#define GPIO_REG_DATA_OUTPUT_BANK3		0x4C
#define GPIO_REG_DIR_BANK2		0x284
#define GPIO_REG_OEN_BANK2		0x288
#define GPIO_REG_DIR_BANK3		0x2C4
#define GPIO_REG_OEN_BANK3		0x2C8

int InitGpio(int index, bool dir, bool value)
{
    unsigned long ulData = 0;

    if((index < 32) && (index >= 0))
    {

    }
    else if((index >= 32) && (index < 53))
    {

    }
    else if((index >= 54) && (index < 86))
    {
        if(dir == GPIO_DIR_OUTPUT)
        {
            ulData = sysInLong(GPIO_REG_BASE + GPIO_REG_DIR_BANK2);
            SET_BIT(ulData, index - 54);
            sysOutLong(GPIO_REG_BASE + GPIO_REG_DIR_BANK2, ulData);

            ulData = sysInLong(GPIO_REG_BASE + GPIO_REG_OEN_BANK2);
            SET_BIT(ulData, index - 54);
            sysOutLong(GPIO_REG_BASE + GPIO_REG_OEN_BANK2, ulData);

            ulData = sysInLong(GPIO_REG_BASE + GPIO_REG_DATA_OUTPUT_BANK2);
            if(value)
                SET_BIT(ulData, index - 54);
            else
                CLR_BIT(ulData, index - 54);
            sysOutLong(GPIO_REG_BASE + GPIO_REG_DATA_OUTPUT_BANK2, ulData);
        }
    }
    else if((index >= 86) && (index <= 117))
    {
        if(dir == GPIO_DIR_OUTPUT)
        {
            ulData = sysInLong(GPIO_REG_BASE + GPIO_REG_DIR_BANK3);
            SET_BIT(ulData, index - 86);
            sysOutLong(GPIO_REG_BASE + GPIO_REG_DIR_BANK3, ulData);

            ulData = sysInLong(GPIO_REG_BASE + GPIO_REG_OEN_BANK3);
            SET_BIT(ulData, index - 86);
            sysOutLong(GPIO_REG_BASE + GPIO_REG_OEN_BANK3, ulData);

            ulData = sysInLong(GPIO_REG_BASE + GPIO_REG_DATA_OUTPUT_BANK3);
            if(value)
                SET_BIT(ulData, index - 86);
            else
                CLR_BIT(ulData, index - 86);
            sysOutLong(GPIO_REG_BASE + GPIO_REG_DATA_OUTPUT_BANK3, ulData);
        }
    }
    else
    {
        return -1;
    }

    return 0;
}

static int InitBoard(void)
{
    int i = 0;
    
    InitGpio(54+54, GPIO_DIR_OUTPUT, 1);    /* DO1_EN */
    InitGpio(57+54, GPIO_DIR_OUTPUT, 1);    /* DO2_EN */
    
    pDI_Inst = vxbInstByNameFind("max31910", 1);
    pDO_Inst = vxbInstByNameFind("max14912", 0);
    if((pDI_Inst == NULL) || (pDO_Inst == NULL))
        return RTS_INVALID_HANDLE;
    
    return ERR_OK;
}

/* Example for a Hook function */
static RTS_RESULT CDECL HookFunction(RTS_UI32 ulHook, RTS_UINTPTR ulParam1, RTS_UINTPTR ulParam2)
{
    switch (ulHook)
    {
    case CH_INIT_SYSTEM:
        break;
    case CH_INIT:
        break;
    case CH_INIT2:
    {
        RTS_HANDLE hIoDrv = 0;
        void *pTmp;

        InitBoard();

        /* first instance */
        pTmp = CAL_IoDrvCreate(hIoDrv, CLASSID_CIoDrvSpiIO, 0, NULL);
        s_pIBase = (IBase *)pTmp;
        CAL_IoMgrRegisterInstance(s_pIBase, NULL);
        break;
    }
    case CH_INIT3:
    	printf("===============================IoDrvSpiIO Init3===============================\n");
        break;
    case CH_INIT_TASKS:
        break;
    case CH_INIT_COMM:
        break;

    /* Cyclic */
    case CH_COMM_CYCLE:
        break;

#ifndef RTS_COMPACT_MICRO
    case CH_EXIT_COMM:
        break;
    case CH_EXIT_TASKS:
        break;
    case CH_EXIT3:
        break;
    case CH_EXIT2:
        break;
    case CH_EXIT:
    {
        /* Delete instance */
        ICmpIoDrv *pI;

        CAL_IoMgrUnregisterInstance(s_pIBase);
        pI = (ICmpIoDrv *)s_pIBase->QueryInterface(s_pIBase, ITFID_ICmpIoDrv, NULL);
        s_pIBase->Release(s_pIBase);
        CAL_IoDrvDelete((RTS_HANDLE)pI, (RTS_HANDLE)pI);
        DeleteInstance(s_pIBase);

        EXIT_STMT;
        break;
    }
    case CH_EXIT_SYSTEM:
        break;
#endif

    default:
        break;
    }
    return ERR_OK;
}

/**
 * My External Function
 */
void CDECL CDECL_EXT myexternalfunction(myexternalfunction_struct *p)
{

}

/**
 * Implementation of the IoDrv Interface
 */
/* Our Fake I/O Area */
#define MAX_CHANNELS 128
#define MAX_DRIVERS 1

static unsigned long s_ulyIO[MAX_DRIVERS][MAX_CHANNELS];

STATICITF RTS_HANDLE CDECL IoDrvCreate(RTS_HANDLE hIIoDrv, CLASSID ClassId, int iId, RTS_RESULT *pResult)
{

    IoDrvInfo *pInfo;
    IoDrvSpiIO *pIoDrvSpiIO;

    RTS_SETRESULT(pResult, ERR_OK);

    /* Only one instance allowed */
    if (iId > 0)
    {
        RTS_SETRESULT(pResult, ERR_NOMEMORY);
        return RTS_INVALID_HANDLE;
    }

#ifdef CPLUSPLUS
    pIoDrvSpiIO = (IoDrvSpiIO *)CAL_SysMemAllocData(COMPONENT_NAME, sizeof(IoDrvSpiIO), NULL);
    pIoDrvSpiIO->pIBase = (IBase *)hIIoDrv;
    pIoDrvSpiIO->pIoDrv = (ICmpIoDrv *)pIoDrvSpiIO->pIBase->QueryInterface(pIoDrvSpiIO->pIBase, ITFID_ICmpIoDrv, NULL);
    pIoDrvSpiIO->pIoDrvParameter = (ICmpIoDrvParameter *)pIoDrvSpiIO->pIBase->QueryInterface(pIoDrvSpiIO->pIBase, ITFID_ICmpIoDrvParameter, NULL);
    pIoDrvSpiIO->pIBase->Release(pIoDrvSpiIO->pIBase);
    pIoDrvSpiIO->pIBase->Release(pIoDrvSpiIO->pIBase);
    pInfo = &pIoDrvSpiIO->Info;
#else
    pIoDrvSpiIO = (IoDrvSpiIO *)hIIoDrv;
    pIoDrvSpiIO->IoDrv.pBase = &pIoDrvSpiIO->Base;
    pIoDrvSpiIO->IoDrvParameter.pBase = &pIoDrvSpiIO->Base;
    pInfo = &pIoDrvSpiIO->Info;
#endif

    pInfo->wId = (RTS_IEC_WORD)iId;
    pInfo->wModuleType = 40100;
    pInfo->hSpecific = (RTS_IEC_HANDLE)s_ulyIO[iId];
    pInfo->dwVersion = CMP_VERSION;

    strcpy(pInfo->szDriverName, "IoDrvSpiIO");
    strcpy(pInfo->szDeviceName, "SPI IO Device");
    strcpy(pInfo->szVendorName, "Hitech");
    strcpy(pInfo->szFirmwareVersion, "Rev. 1.0.0.0");
    return (RTS_HANDLE)pInfo;
}

STATICITF RTS_RESULT CDECL IoDrvDelete(RTS_HANDLE hIoDrv, RTS_HANDLE hIIoDrv)
{
#ifdef CPLUSPLUS
    IoDrvSpiIO *pIoDrvSpiIO = (IoDrvSpiIO *)((unsigned char *)hIoDrv - sizeof(IoDrvSpiIO) + sizeof(IoDrvInfo));
    CAL_SysMemFreeData(COMPONENT_NAME, pIoDrvSpiIO);
#endif
    return ERR_OK;
}

STATICITF RTS_RESULT CDECL IoDrvGetInfo(RTS_HANDLE hIoDrv, IoDrvInfo **ppInfo)
{
    if (ppInfo == NULL || hIoDrv == RTS_INVALID_HANDLE)
        return ERR_PARAMETER;

    *ppInfo = (IoDrvInfo *)hIoDrv;
    return ERR_OK;
}

STATICITF RTS_RESULT CDECL IoDrvUpdateConfiguration(RTS_HANDLE hIoDrv, IoConfigConnector *pConnectorList, int nCount)
{
    IoConfigConnector *pConnector = CAL_IoMgrConfigGetFirstConnector(pConnectorList, &nCount, 40100);
    IoDrvSpiIO *pIoDrvSpiIO = (IoDrvSpiIO *)((unsigned char *)hIoDrv - sizeof(IoDrvSpiIO) + sizeof(IoDrvInfo));
    IBase *pIBase = pIoDrvSpiIO->pIBase;
    /*ICmpIoDrv *pIIoDrv = pIoDrvSpiIO->pIoDrv;*/

    printf("===============================IoDrvSpiIo IoDrvUpdateConfiguration===============================\n");
    
    while (pConnector != NULL)
    {
        IoDrvInfo *pInfo;
        IoConfigParameter *pParameter;
        IoConfigConnector *pChild;
        char *pszVendorName = NULL;
        char *pszDeviceName = NULL;
        unsigned char *pTestParameter;

        IoDrvGetInfo(hIoDrv, &pInfo);

        /* The connector type 40100 is not unique, so additional info must be investigated to detect our own device.
           Here for example, two parameters with the vendorname and the devicename are used. */
        pParameter = CAL_IoMgrConfigGetParameter(pConnector, 393218);
        if (pParameter != NULL && pParameter->dwFlags & PVF_POINTER)
            pszVendorName = (char *)pParameter->dwValue;
        pParameter = CAL_IoMgrConfigGetParameter(pConnector, 393219);
        if (pParameter != NULL && pParameter->dwFlags & PVF_POINTER)
            pszDeviceName = (char *)pParameter->dwValue;

        /* If the connector is still occupied by another driver instance, skip this connector */
        if (pConnector->hIoDrv == 0 &&
                pszVendorName != NULL && strcmp(pszVendorName, pInfo->szVendorName) == 0 &&
                pszDeviceName != NULL && strcmp(pszDeviceName, pInfo->szDeviceName) == 0)
        {
            int i;
			int j;
			
			printf("name ok!\n");
            /* Our driver instance must be registered at this connector to:
            - occupy this connector (that no other driver instance will use this connector)
            - to mark, that the conector is supported by a driver
            - for the IoMgr to be able to direct access the driver of this connector
            Always the pointer to the IBase interface must be written in the IO-driver handle of the connector! */
            pConnector->hIoDrv = (RTS_IEC_HANDLE)pIBase;

            /* If the father is our input connector, you have to register the driver in this connector too
            to mark, that this connector is ours */
            if (pConnector->pFather != NULL && pConnector->pFather->wType == CT_PCI_MASTER)
                pConnector->pFather->hIoDrv = (RTS_IEC_HANDLE)pIBase;

            /* Set the property, that bit consistency is provided by the driver! */
            CAL_IoMgrSetDriverProperties(pIBase, DRVPROP_CONSISTENCY);

            /* If the connector has childs, they can be handled here */
            pChild = CAL_IoMgrConfigGetFirstChild(pConnector, &nCount, pConnector);
            while (pChild != NULL)
            {
                /* With this code you can go through all child connectors of the father pConnector */

                /* Example: This is the access to a parameter of the child connector */
                pParameter = CAL_IoMgrConfigGetParameter(pChild, 4711);

                pChild = CAL_IoMgrConfigGetNextChild(pChild, &nCount, pConnector);
            }

            /* configure the physical device with the connector parameters... */
            pParameter = CAL_IoMgrConfigGetParameter(pConnector, 393220);	/* test parameter */
            if (pParameter != NULL)
            {
                if (pParameter->dwFlags & PVF_POINTER)
                    pTestParameter = (unsigned char *)pParameter->dwValue;
            }
            
            /* inputs */
            for(i = 0; i < MAX_CHANNELS; i++)
            {
                pParameter = CAL_IoMgrConfigGetParameter(pConnector, 1000 + i);
                if (pParameter != NULL)
                {
                    pParameter->dwDriverSpecific = (RTS_IEC_BYTE *)&s_ulyIO[0][i];
                    s_ulyIO[0][i] = i + 1;
                }
                else
                    break;
            }
            printf("===========input %d===========\n", i);
            /* outputs */
			for(/* continue */j = 0; i < MAX_CHANNELS; i++, j++) {
				pParameter = CAL_IoMgrConfigGetParameter(pConnector, 2000 + j);
                if (pParameter != NULL)
                    pParameter->dwDriverSpecific = (RTS_IEC_BYTE *)&s_ulyIO[0][i];
                else
                    break;
            }
            printf("===========output %d===========\n", j);
            /* The diagnosis bits are set here to mark, that everything is OK
               or an error occurred on this connector (in this case set the corresponding error flags
               or remove some valid flags).
               */
            CAL_IoMgrConfigSetDiagnosis(pConnector, CF_DRIVER_AVAILABLE | CF_CONNECTOR_FOUND | CF_CONNECTOR_CONFIGURED | CF_CONNECTOR_ACTIVE);
            if (pConnector->pFather != NULL)
                CAL_IoMgrConfigSetDiagnosis(pConnector->pFather, CF_DRIVER_AVAILABLE | CF_CONNECTOR_FOUND | CF_CONNECTOR_CONFIGURED | CF_CONNECTOR_ACTIVE);

            /* If a very serious error occurred during IoDrvUpdateConfiguration, the driver can return ERR_EXCEPTION
               to generate an exception on the corresponding IO-application:
               return ERR_EXCEPTION; */

            /* If an error occurred during IoDrvUpdateConfiguration, the driver can return ERR_FAILED
               to generate a logger entry on the corresponding IO-application with the error code.
               But this has no further consequence:
               return ERR_FAILED; */
            break;
        }
        pConnector = CAL_IoMgrConfigGetNextConnector(pConnector, &nCount, 40100);
    }
    return ERR_OK;
}

STATICITF RTS_RESULT CDECL IoDrvUpdateMapping(RTS_HANDLE hIoDrv, IoConfigTaskMap *pTaskMapList, int nCount)
{
    return ERR_OK;
}

STATICITF RTS_RESULT CDECL IoDrvReadInputs(RTS_HANDLE hIoDrv, IoConfigConnectorMap *pConnectorMapList, int nCount)
{
    int i;
    unsigned long j;
	SPI_TRANSFER transInfo;
	unsigned char txBuf[8] = {0};
	unsigned char rxBuf[8] = {0};
		
    if (pConnectorMapList == NULL)
        return ERR_PARAMETER;

    for (i = 0; i < nCount; i++)
    {
        for (j = 0; j < pConnectorMapList[i].dwNumOfChannels; j++)
        {
            CAL_IoMgrCopyInputLE(&(pConnectorMapList[i].pChannelMapList[j]), (char *)pConnectorMapList[i].pChannelMapList[j].pParameter->dwDriverSpecific);
        }
    }
    /* BOARD1 */
	memset(&transInfo, 0, sizeof(SPI_TRANSFER));    
	memset(txBuf, 0, sizeof(txBuf));
	memset(rxBuf, 0, sizeof(rxBuf));
    transInfo.txBuf = txBuf;
    transInfo.txLen = 2;
    transInfo.rxBuf = rxBuf;
    transInfo.rxLen = 2;
    
    InitGpio(61+54, GPIO_DIR_OUTPUT, 1);	/* BOARD 2 DI CS */ 
    InitGpio(58+54, GPIO_DIR_OUTPUT, 0);	/* BOARD 2 DI EN(U9 PIN7) */
	               
    InitGpio(59+54, GPIO_DIR_OUTPUT, 1);	/* BOARD 1 DI EN */ 
    InitGpio(63+54, GPIO_DIR_OUTPUT, 0);	/* BOARD 1 DI CS */               
	//taskDelay(1);
	
	vxbSpiTransfer (pDI_Inst, &transInfo);
	//taskDelay(1);    	
	
	InitGpio(63+54, GPIO_DIR_OUTPUT, 1);	/* BOARD 1 DI CS */
	InitGpio(59+54, GPIO_DIR_OUTPUT, 0);	/* BOARD 1 DI EN */

	//logMsg("BOARD 1 DI=%02X %02X\n", rxBuf[0], rxBuf[1], 0, 0, 0, 0);	
    for(i = 0; i < 8; i++)
    {
        s_ulyIO[0][i] = !TEST_BIT(rxBuf[1], i);   //逻辑上低电平有效  所以需要取反
    }
    for(i = 8; i < 16; i++)
    {
        s_ulyIO[0][i] = !TEST_BIT(rxBuf[0], i - 8);
    }
    
    /* BOARD2 */	
   	memset(&transInfo, 0, sizeof(SPI_TRANSFER)); 
	memset(txBuf, 0, sizeof(txBuf));
	memset(rxBuf, 0, sizeof(rxBuf));    	
	transInfo.txBuf = txBuf;
	transInfo.txLen = 2;
	transInfo.rxBuf = rxBuf;
	transInfo.rxLen = 2;
		
	InitGpio(58+54, GPIO_DIR_OUTPUT, 1);	/* BOARD 2 DI EN */
	InitGpio(61+54, GPIO_DIR_OUTPUT, 0);	/* BOARD 2 DI CS */
	//taskDelay(1);
	
	vxbSpiTransfer (pDI_Inst, &transInfo);
	//taskDelay(1);
	
	InitGpio(61+54, GPIO_DIR_OUTPUT, 1);	/* BOARD 2 DI CS */
	InitGpio(58+54, GPIO_DIR_OUTPUT, 0);	/* BOARD 2 DI EN */
    
	//logMsg("BOARD 2 DI=%02X %02X\n", rxBuf[0], rxBuf[1], 0, 0, 0, 0);
	
    for(i = 0; i < 8; i++)
    {
        s_ulyIO[0][i + 16] = !TEST_BIT(rxBuf[1], i);
    }
    for(i = 8; i < 12; i++)    		
    {
        s_ulyIO[0][i + 16] = !TEST_BIT(rxBuf[0], i - 8);
    }
    /*
    printf("DI:\n");
    for(i = 0; i < 28; i++)
    {
    	printf("%02X ", s_ulyIO[0][i]);
    	if(i % 8 == 0)
    		printf("\n");
    }
    printf("\n");
    */
    return ERR_OK;
}

STATICITF RTS_RESULT CDECL IoDrvWriteOutputs(RTS_HANDLE hIoDrv, IoConfigConnectorMap *pConnectorMapList, int nCount)
{
    int i;
    unsigned long j;
    unsigned long ulData = 0;
	SPI_TRANSFER transInfo;
	unsigned char txBuf[8] = {0};
	unsigned char rxBuf[8] = {0};
	
    if (pConnectorMapList == NULL)
        return ERR_PARAMETER;
    
    //printf("nCount=%d,dwNumOfChannels=%d\n", nCount, pConnectorMapList[0].dwNumOfChannels);
    for (i = 0; i < nCount; i++)
    {
        for (j = 0; j < pConnectorMapList[i].dwNumOfChannels; j++)
        {
        	//printf("%d=%d\n", j, *pConnectorMapList[i].pChannelMapList[j].pParameter->dwDriverSpecific);
        	CAL_IoMgrCopyOutputLE(&(pConnectorMapList[i].pChannelMapList[j]), (char *)pConnectorMapList[i].pChannelMapList[j].pParameter->dwDriverSpecific);            
            //if(*pConnectorMapList[i].pChannelMapList[j].pParameter->dwDriverSpecific)
            //    SET_BIT(ulData, 13 + j);
        }
    }

    //sysOutLong(0xe000a048, ulData);
#if 0    //下面代码是只接一块SPI板卡时相关的驱动代码
    memset(&transInfo, 0, sizeof(SPI_TRANSFER));
    for(i = 0; i < 8; i++)
    {
        if(s_ulyIO[0][i + 16])
            SET_BIT(txBuf[0], i);
        else
            CLR_BIT(txBuf[0], i);
    }
    for(i = 8; i < 16; i++)
    {
        if(s_ulyIO[0][i + 16])
            SET_BIT(txBuf[1], i - 8);
        else
            CLR_BIT(txBuf[1], i - 8);
    }
    transInfo.txBuf = txBuf;
    transInfo.txLen = 2;
    transInfo.usDelay = 0;

    InitGpio(62, GPIO_DIR_OUTPUT, 0);	/* CS */ 
    
    InitGpio(55, GPIO_DIR_OUTPUT, s_ulyIO[0][32]);
    InitGpio(56, GPIO_DIR_OUTPUT, s_ulyIO[0][33]);
    InitGpio(58, GPIO_DIR_OUTPUT, s_ulyIO[0][34]);
    InitGpio(59, GPIO_DIR_OUTPUT, s_ulyIO[0][35]);
    InitGpio(60, GPIO_DIR_OUTPUT, s_ulyIO[0][36]);
    InitGpio(61, GPIO_DIR_OUTPUT, s_ulyIO[0][37]);
    
    vxbSpiTransfer (pDO_Inst, &transInfo);
    taskDelay(sysClkRateGet() / 10);
    
    InitGpio(62, GPIO_DIR_OUTPUT, 1);	/* CS */ 
    
    printf("\nDO:\n");
    printf("txBuf=%02X %02X\n", txBuf[0], txBuf[1]);
    for(i = 0; i < 22; i++)
    {
    	printf("%02X ", s_ulyIO[0][i+16]);
    	if((i % 8) == 0);
    		printf("\n");
    }
    printf("\n");
#else
#if 1
    /* BOARD1 */    
    memset(&transInfo, 0, sizeof(SPI_TRANSFER));
	memset(txBuf, 0, sizeof(txBuf));
	memset(rxBuf, 0, sizeof(rxBuf));
	
    for(i = 0; i < 8; i++)
    {
    	/* 推挽模式  PLC输出TRUE为低电平 */
    	if(s_ulyIO[0][i + 28])
    	    CLR_BIT(txBuf[1], i);
    	else
    	    SET_BIT(txBuf[1], i);  	
    }
    for(i = 8; i < 16; i++)
    {
    	if(s_ulyIO[0][i + 28])
    	    CLR_BIT(txBuf[0], i - 8);
    	else
    	    SET_BIT(txBuf[0], i - 8); 	
    }
    transInfo.txBuf = txBuf;
    transInfo.rxBuf = rxBuf;
    transInfo.txLen = 2;
    transInfo.usDelay = 0;

    InitGpio(62+54, GPIO_DIR_OUTPUT, 0);	/* CS */
    vxbSpiTransfer (pDO_Inst, &transInfo);
    taskDelay(1);    
    InitGpio(62+54, GPIO_DIR_OUTPUT, 1);	/* CS */
    
    printf("\nBOARD1 DO:\n");
    printf("txBuf=%02X %02X, rxBuf=%02X %02X\n", txBuf[0], txBuf[1], rxBuf[0], rxBuf[1]);
    for(i = 0; i < 16; i++)
    {
    	printf("%02X ", s_ulyIO[0][i+28]);
    	if((i % 8) == 0)
    		printf("\n");
    }
    printf("\n");
    
#endif    
#if 1
    /* BOARD2 */    
    memset(&transInfo, 0, sizeof(SPI_TRANSFER));
	memset(txBuf, 0, sizeof(txBuf));
	memset(rxBuf, 0, sizeof(rxBuf));
	
    for(i = 0; i < 8; i++)
    {
    	if(s_ulyIO[0][i + 28 + 16])   //BOARD2 + 16个BOARD1的DI
    	    CLR_BIT(txBuf[0], i);
    	else
    	    SET_BIT(txBuf[0], i); 	
    }
/*
    for(i = 8; i < 16; i++)
    {
    	if(s_ulyIO[0][i + 28 + 16])
    	    CLR_BIT(txBuf[0], i - 8);
    	else
    	    SET_BIT(txBuf[0], i - 8);  	
    }
  */  
    transInfo.txBuf = txBuf;
    transInfo.txLen = 1;
    transInfo.usDelay = 0;

    InitGpio(55+54, GPIO_DIR_OUTPUT, 0);	/* CS */
    vxbSpiTransfer (pDO_Inst, &transInfo);  
    taskDelay(1);
    InitGpio(55+54, GPIO_DIR_OUTPUT, 1);	/* CS */  
    
    printf("\nBOARD2 DO:\n");
    printf("txBuf=%02X %02X\n", txBuf[0], txBuf[1]);
    for(i = 0; i < 16; i++)
    {
    	printf("%02X ", s_ulyIO[0][i + 28 + 16]);
    	if((i % 8) == 0)
    		printf("\n");
    }
    printf("\n"); 
#endif       
#endif
    
    return ERR_OK;
}

/* 这里直接操作输入输出 */
STATICITF RTS_RESULT CDECL IoDrvStartBusCycle(RTS_HANDLE hIoDrv, IoConfigConnector *pConnector)
{
    int i = 0;

    if (pConnector->wType != 40100)
        return ERR_OK;
    /*
    s_ulyIO[0][2] = s_ulyIO[0][4];
    s_ulyIO[0][3] = s_ulyIO[0][5];
    */
		/*
    for (i = 0; i < MAX_CHANNELS; i++)
    {
        printf("%x ", s_ulyIO[0][i]);
        if((i + 1) % 16 == 0)
            printf("\n");
    }
    printf("\n");
		*/
		
		
    return IoDrvGetModuleDiagnosis(hIoDrv, pConnector);
}

STATICITF RTS_RESULT CDECL IoDrvScanModules(RTS_HANDLE hIoDrv, IoConfigConnector *pConnector, IoConfigConnector **ppConnectorList, int *pnCount)
{
    return ERR_OK;
}

STATICITF RTS_RESULT CDECL IoDrvGetModuleDiagnosis(RTS_HANDLE hIoDrv, IoConfigConnector *pConnector)
{
    /* Example for IO-error:
    IoDrvInfo *pInfo = (IoDrvInfo *)hIoDrv;
    if (IoError)
    	IoMgrConfigSetDiagnosis(pConnector, CF_CONNECTOR_ERROR);
    else
    	IoMgrConfigResetDiagnosis(pConnector, CF_CONNECTOR_ERROR);
    */
    return ERR_OK;
}

STATICITF RTS_RESULT CDECL IoDrvIdentify(RTS_HANDLE hIoDrv, IoConfigConnector *pConnector)
{
    return ERR_OK;
}

STATICITF RTS_RESULT CDECL IoDrvWatchdogTrigger(RTS_HANDLE hIoDrv, IoConfigConnector *pConnector)
{
    return ERR_OK;
}

STATICITF RTS_RESULT CDECL IoDrvReadParameter(RTS_HANDLE hIoDrv, IoConfigConnector *pConnector, IoConfigParameter *pParameter, void *pData, RTS_SIZE ulBitSize, RTS_SIZE ulBitOffset)
{
    if (pParameter == NULL)
        return ERR_PARAMETER;

    memcpy(pData, (unsigned char *)pParameter->dwValue, ulBitSize / 8);
    return ERR_OK;
}

STATICITF RTS_RESULT CDECL IoDrvWriteParameter(RTS_HANDLE hIoDrv, IoConfigConnector *pConnector, IoConfigParameter *pParameter, void *pData, RTS_SIZE ulBitSize, RTS_SIZE ulBitOffset)
{
    if (pParameter == NULL)
        return ERR_PARAMETER;

    memcpy((unsigned char *)pParameter->dwValue, pData, ulBitSize / 8);
    return ERR_OK;
}

