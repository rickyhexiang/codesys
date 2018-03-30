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
#include "IoDrvSOCDep.h"

USE_STMT

#define TEST_BIT(x,offset)  (1&((x)>>offset))
#define SET_BIT(x,offset)   ((x)|=(1<<offset))
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
} IoDrvSOC;

#ifndef CPLUSPLUS

DECLARE_ADDREF
DECLARE_RELEASE
DECLARE_QUERYINTERFACE

#endif

static IBase *s_pIBase;

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
		pInitStruct->pfCMRegisterClass(COMPONENT_ID, CLASSID_CIoDrvSOC);

	return ERR_OK;
}

#endif

static IBase* CDECL CreateInstance(CLASSID cid, RTS_RESULT *pResult)
{
#ifdef CPLUSPLUS
	if (cid == CLASSID_CIoDrvSOC)
	{
		CIoDrvSOC *pCIoDrvSOC = static_cast<CIoDrvSOC *>(new CIoDrvSOC());
		IBase *pIBase = (IBase *)pCIoDrvSOC->QueryInterface(pCIoDrvSOC, ITFID_IBase, pResult);
		RTS_SETRESULT(pResult, ERR_OK);
		return pIBase;
	}
#else
	if (cid == CLASSID_CIoDrvSOC)
	{
		IoDrvSOC *pIoDrvSOC = (IoDrvSOC *)CAL_SysMemAllocData(COMPONENT_NAME, sizeof(IoDrvSOC), NULL);
		if (pIoDrvSOC != NULL)
		{
			IBase *pI = &pIoDrvSOC->Base;
			pIoDrvSOC->pIBase = &pIoDrvSOC->Base;
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
		IoDrvSOC *pC = (IoDrvSOC *)pBase;
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
		IoDrvSOC *pC = (IoDrvSOC *)pBase;
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

static int InitBoard(void)
{
	sysOutLong (0xe000a284, 0x001fe000);   /* 设置DO方向 */
	sysOutLong (0xe000a288, 0x001fe000);   /* 输出使能 */
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
			pTmp = CAL_IoDrvCreate(hIoDrv, CLASSID_CIoDrvSOC, 0, NULL);
			s_pIBase = (IBase *)pTmp;
			CAL_IoMgrRegisterInstance(s_pIBase, NULL);
			break;
		}		
		case CH_INIT3:
			printf("===============================IoDrvSOC Init3===============================\n");
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
/*
void CDECL CDECL_EXT myexternalfunction(myexternalfunction_struct *p) {

}
*/
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
	IoDrvSOC *pIoDrvSOC;

	RTS_SETRESULT(pResult, ERR_OK);

	/* Only one instance allowed */
	if (iId > 0) {
		RTS_SETRESULT(pResult, ERR_NOMEMORY);
		return RTS_INVALID_HANDLE;
	}

#ifdef CPLUSPLUS
	pIoDrvSOC = (IoDrvSOC *)CAL_SysMemAllocData(COMPONENT_NAME, sizeof(IoDrvSOC), NULL);
	pIoDrvSOC->pIBase = (IBase *)hIIoDrv;	
	pIoDrvSOC->pIoDrv = (ICmpIoDrv *)pIoDrvSOC->pIBase->QueryInterface(pIoDrvSOC->pIBase, ITFID_ICmpIoDrv, NULL);
	pIoDrvSOC->pIoDrvParameter = (ICmpIoDrvParameter *)pIoDrvSOC->pIBase->QueryInterface(pIoDrvSOC->pIBase, ITFID_ICmpIoDrvParameter, NULL);
	pIoDrvSOC->pIBase->Release(pIoDrvSOC->pIBase);
	pIoDrvSOC->pIBase->Release(pIoDrvSOC->pIBase);
	pInfo = &pIoDrvSOC->Info;
#else
	pIoDrvSOC = (IoDrvSOC *)hIIoDrv;
	pIoDrvSOC->IoDrv.pBase = &pIoDrvSOC->Base;
	pIoDrvSOC->IoDrvParameter.pBase = &pIoDrvSOC->Base;
	pInfo = &pIoDrvSOC->Info;
#endif

	pInfo->wId = (RTS_IEC_WORD)iId;
	pInfo->wModuleType = 40100;
	pInfo->hSpecific = (RTS_IEC_HANDLE)s_ulyIO[iId];
	pInfo->dwVersion = CMP_VERSION;

	strcpy(pInfo->szDriverName, "IoDrvSOC");
	strcpy(pInfo->szDeviceName, "SOC Device");
	strcpy(pInfo->szVendorName, "Hitech");
	strcpy(pInfo->szFirmwareVersion, "Rev. 1.0.0.0");
	return (RTS_HANDLE)pInfo;
}

STATICITF RTS_RESULT CDECL IoDrvDelete(RTS_HANDLE hIoDrv, RTS_HANDLE hIIoDrv)
{
#ifdef CPLUSPLUS
	IoDrvSOC *pIoDrvSOC = (IoDrvSOC *)((unsigned char *)hIoDrv - sizeof(IoDrvSOC) + sizeof(IoDrvInfo));
	CAL_SysMemFreeData(COMPONENT_NAME, pIoDrvSOC);
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
	IoDrvSOC *pIoDrvSOC = (IoDrvSOC *)((unsigned char *)hIoDrv - sizeof(IoDrvSOC) + sizeof(IoDrvInfo));
	IBase *pIBase = pIoDrvSOC->pIBase;
	/*ICmpIoDrv *pIIoDrv = pIoDrvSOC->pIoDrv;*/

	printf("===============================IoDrvSOC IoDrvUpdateConfiguration===============================\n");
	
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
			for(i=0; i < MAX_CHANNELS; i++) {
				pParameter = CAL_IoMgrConfigGetParameter(pConnector, 1000 + i);
				if (pParameter != NULL) {
					pParameter->dwDriverSpecific = (RTS_IEC_BYTE *)&s_ulyIO[0][i];
					s_ulyIO[0][i] = i+1;
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
	int i = 0;
	unsigned long j;
	unsigned long ulData = 0x001fe000;
	unsigned char uchData = 0;
		
	if (pConnectorMapList == NULL)
		return ERR_PARAMETER;

	/* INPUT */
	/*
	uchData = (sysInLong(0xe000a068) >> 21) & 0xff;
	for(i = 0; i < 8; i++)
	{
		s_ulyIO[0][i] = TEST_BIT(uchData, i);
		printf("s_ulyIO[0][%d]=%d\n", i, s_ulyIO[0][i]);
	}
	*/
	
	for (i=0; i<nCount; i++)
	{
		for (j=0; j<pConnectorMapList[i].dwNumOfChannels; j++)
		{			
			CAL_IoMgrCopyInputLE(&(pConnectorMapList[i].pChannelMapList[j]), (char *)pConnectorMapList[i].pChannelMapList[j].pParameter->dwDriverSpecific);
		}
	}

	return ERR_OK;
}

STATICITF RTS_RESULT CDECL IoDrvWriteOutputs(RTS_HANDLE hIoDrv, IoConfigConnectorMap *pConnectorMapList, int nCount)
{
	int i;
	unsigned long j;
	
	if (pConnectorMapList == NULL)
		return ERR_PARAMETER;
	
	printf("nCount=%d,dwNumOfChannels=%d\n", nCount, pConnectorMapList[0].dwNumOfChannels);
	for (i=0; i<nCount; i++)
	{
		for (j=0; j<pConnectorMapList[i].dwNumOfChannels; j++)
		{
			printf("%d=%d\n", j, *pConnectorMapList[i].pChannelMapList[j].pParameter->dwDriverSpecific);
			CAL_IoMgrCopyOutputLE(&(pConnectorMapList[i].pChannelMapList[j]), (char *)pConnectorMapList[i].pChannelMapList[j].pParameter->dwDriverSpecific);  
		}
	}

	return ERR_OK;
}

/* 这里直接操作输入输出 */
STATICITF RTS_RESULT CDECL IoDrvStartBusCycle(RTS_HANDLE hIoDrv, IoConfigConnector *pConnector)
{
	int i = 0;
	unsigned long ulData = 0x001fe000;
	unsigned char uchData = 0;
		
	if (pConnector->wType != 40100)
		return ERR_OK;

	/*
	for (i=0; i<MAX_CHANNELS; i++)
	{
		printf("%x ", s_ulyIO[0][i]);
		if((i + 1) % 16 == 0)
			printf("\n");
	}
	printf("\n");
	*/
	
	/* INPUT */
	uchData = (sysInLong(0xe000a068) >> 21) & 0xff;
	for(i = 0; i < 8; i++)
	{
		s_ulyIO[0][i] = TEST_BIT(uchData, i);
		/*
		printf("s_ulyIO[0][%d]=%d\n", i, s_ulyIO[0][i]);*/
	}
	
	/* OUTPUT */
	for(i = 0; i < 8; i++)
	{
		if(s_ulyIO[0][i + 8])
			CLR_BIT(ulData, 13+i);	
		/*
		printf("s_ulyIO[0][%d]=%d\n", i + 8, s_ulyIO[0][i + 8]);	*/	
	}
	sysOutLong(0xe000a048, ulData);
	/*printf("\n");*/
	
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

