/**
 * <name>CmpTemplate.c</name>
 * <description> 
 *  Example for an empty runtime component frame that can be used as a starting point to develop own components.
 *
 *  MANDATORY FUNCTIONS:
 *  - ComponentEntry()
 *  - ExportFunctions()
 *  - ImportFunctions()
 *  - CmpGetVersion()
 *  - HookFunction()
 * </description>
 *
 * <copyright>(c) 2003-2016 3S-Smart Software Solutions</copyright>
 */

#include "CmpStd.h"
#include "CmpEncoderCtrlDep.h"

USE_STMT

#define bool BOOL

#define TEST_BIT(x,offset)  (1&((x)>>offset))
#define SET_BIT(x,offset)   ((x)|=(1<<offset))
#define CLR_BIT(x,offset)   ((x)&=(~(1<<(offset))))

#define PLC_PULSE_GEN_ENCORDER_COUNTER			 	(0x40600000)
#define REG_ENCORDER_COUNTER_A	     					(20 * 4)
#define REG_ENCORDER_COUNTER_Z	     					(21 * 4)
#define REG_ENCORDER_COUNTER_CTRL    					(22 * 4)

#ifndef RTS_COMPACT_MICRO

/**
 * <description>Entry function of the component. Called at startup for each component. Used to exchange function pointers with the component manager.</description>
 * <param name="pInitStruct" type="IN">Pointer to structure with:
 *		pfExportFunctions	OUT Pointer to function that exports component functions
 *		pfImportFunctions	OUT Pointer to function that imports functions from other components
 *		pfGetVersion		OUT Pointer to function to get component version
 *		pfRegisterAPI		IN	Pointer to component mangager function to register a api function
 *		pfGetAPI			IN	Pointer to component mangager function to get a api function
 *		pfCallHook			IN	Pointer to component mangager function to call a hook function
 * </param> 
 * <result>ERR_OK if component could be initialized, else error code.</result>
 */
DLL_DECL int CDECL ComponentEntry(INIT_STRUCT *pInitStruct)
{
	pInitStruct->CmpId = COMPONENT_ID;
	pInitStruct->pfExportFunctions = ExportFunctions;
	pInitStruct->pfImportFunctions = ImportFunctions;
	pInitStruct->pfGetVersion = CmpGetVersion;
	pInitStruct->pfHookFunction = HookFunction;
	pInitStruct->pfCreateInstance = NULL;
	pInitStruct->pfDeleteInstance = NULL;

	s_pfCMRegisterAPI = pInitStruct->pfCMRegisterAPI;
	s_pfCMRegisterAPI2 = pInitStruct->pfCMRegisterAPI2;
	s_pfCMGetAPI = pInitStruct->pfCMGetAPI;
	s_pfCMGetAPI2 = pInitStruct->pfCMGetAPI2;
	s_pfCMCallHook = pInitStruct->pfCMCallHook;
	s_pfCMRegisterClass = pInitStruct->pfCMRegisterClass;
	s_pfCMCreateInstance = pInitStruct->pfCMCreateInstance;
	return ERR_OK;
}

/**
 * <description>Publish exported functions to the component manager, to make them available for other components.
 * Use generated macro EXPORT_STMT.</description>
 * <result>ERR_OK or error code in case of error</result>
 */
static int CDECL ExportFunctions(void)
{
	/* Macro to export functions */
	EXPORT_STMT;
	return ERR_OK;
}

/**
 * <description>Import function pointers from other components. Use generated macro IMPORT_STMT.</description>
 * <result>ERR_OK or error code if function name could not be resolved</result>
 */
static int CDECL ImportFunctions(void)
{
	/* Macro to import functions */
	IMPORT_STMT;
	return ERR_OK;
}

/**
 * <description>Return the version of our component.</description>
 * <result>Version as defined in dep file</result>
 */
static RTS_UI32 CDECL CmpGetVersion(void)
{
	return CMP_VERSION;
}

#endif

/**
 * <description>Hook function to get all broadcast hooks of the component manager. All init and exit stuff must be implemented here!</description>
 * <param name="ulHook" type="IN">Kind of hook. See CH_ definitions in CmpItf.h for details.</param> 
 * <param name="ulParam1" type="IN">Hook specific first parameter. See definitions in CmpItf.h for details.</param> 
 * <param name="ulParam2" type="IN">Hook specific second parameter. See definitions in CmpItf.h for details.</param>  
 * <result>Error code</result>
 */
static RTS_RESULT CDECL HookFunction(RTS_UI32 ulHook, RTS_UINTPTR ulParam1, RTS_UINTPTR ulParam2)
{
	switch (ulHook)
	{
		case CH_INIT:
			if (CHK_LogAdd)
				CAL_LogAdd(STD_LOGGER, COMPONENT_ID, LOG_INFO, ERR_OK, 0, "CH_INIT");
			break;
		case CH_INIT2:
			if (CHK_LogAdd)
				CAL_LogAdd(STD_LOGGER, COMPONENT_ID, LOG_INFO, ERR_OK, 0, "CH_INIT2");
			break;
		case CH_INIT3:
			if (CHK_LogAdd)
				CAL_LogAdd(STD_LOGGER, COMPONENT_ID, LOG_INFO, ERR_OK, 0, "CH_INIT3");
			break;
		case CH_INIT_TASKS:
			if (CHK_LogAdd)
				CAL_LogAdd(STD_LOGGER, COMPONENT_ID, LOG_INFO, ERR_OK, 0, "CH_INIT_TASKS");
			break;
		case CH_INIT_COMM:
			if (CHK_LogAdd)
				CAL_LogAdd(STD_LOGGER, COMPONENT_ID, LOG_INFO, ERR_OK, 0, "CH_INIT_COMM");
			break;
		case CH_INIT_FINISHED:
			if (CHK_LogAdd)
				CAL_LogAdd(STD_LOGGER, COMPONENT_ID, LOG_INFO, ERR_OK, 0, "CH_INIT_FINISHED");
			break;

		/* Cyclic */
		case CH_COMM_CYCLE:
			break;

#ifndef RTS_COMPACT_MICRO
		case CH_EXIT_COMM:
			if (CHK_LogAdd)
				CAL_LogAdd(STD_LOGGER, COMPONENT_ID, LOG_INFO, ERR_OK, 0, "CH_EXIT_COMM");
			break;
		case CH_EXIT_TASKS:
			if (CHK_LogAdd)
				CAL_LogAdd(STD_LOGGER, COMPONENT_ID, LOG_INFO, ERR_OK, 0, "CH_EXIT_TASKS");
			break;
		case CH_EXIT3:
			if (CHK_LogAdd)
				CAL_LogAdd(STD_LOGGER, COMPONENT_ID, LOG_INFO, ERR_OK, 0, "CH_EXIT3");
			break;
		case CH_EXIT2:
			if (CHK_LogAdd)
				CAL_LogAdd(STD_LOGGER, COMPONENT_ID, LOG_INFO, ERR_OK, 0, "CH_EXIT2");
			break;
		case CH_EXIT:
		{
			if (CHK_LogAdd)
				CAL_LogAdd(STD_LOGGER, COMPONENT_ID, LOG_INFO, ERR_OK, 0, "CH_EXIT");
			EXIT_STMT;
			break;
		}
#endif

		default:
			break;
	}
	return ERR_OK;
}

void CDECL CDECL_EXT configencoder__main(configencoder_main_struct *p)
{
	long ulData = sysInLong(PLC_PULSE_GEN_ENCORDER_COUNTER + REG_ENCORDER_COUNTER_CTRL);
	
	p->pInstance->A ? SET_BIT(ulData, 3) : CLR_BIT(ulData, 3);
	p->pInstance->B ? SET_BIT(ulData, 2) : CLR_BIT(ulData, 2);
	p->pInstance->Z ? SET_BIT(ulData, 4) : CLR_BIT(ulData, 4);
		
	sysOutLong(PLC_PULSE_GEN_ENCORDER_COUNTER + REG_ENCORDER_COUNTER_CTRL, ulData);
}
	
void CDECL CDECL_EXT readencodercountera__main(readencodercountera_main_struct *p)
{
	int i = 0;
	int retry = 0;
	long lData[2] = {0};
	
	/* 连续读两次寄存器的值 */
	for(retry = 0; retry < 3; retry++)
	{
		memset(lData, 0, sizeof(lData));
		
		for(i = 0; i < 2; i++)		
			lData[i] = sysInLong(PLC_PULSE_GEN_ENCORDER_COUNTER + REG_ENCORDER_COUNTER_A);
		
		if(lData[0] == lData[1])
		{
			p->pInstance->CounterA = lData[0];
			return;
		}
	}
	
	p->pInstance->CounterA = lData[0];
	return;
}
	
void CDECL CDECL_EXT readencodercounterz__main(readencodercounterz_main_struct *p)
{
	p->pInstance->CounterZ = sysInLong(PLC_PULSE_GEN_ENCORDER_COUNTER + REG_ENCORDER_COUNTER_Z);
}
	
void CDECL CDECL_EXT readencoderdirection__main(readencoderdirection_main_struct *p)
{
	p->pInstance->Direction = sysInLong(PLC_PULSE_GEN_ENCORDER_COUNTER + REG_ENCORDER_COUNTER_CTRL) & 0x01;
}
			
void CDECL CDECL_EXT setencodercounter__main(setencodercounter_main_struct *p)
{
	sysOutLong(PLC_PULSE_GEN_ENCORDER_COUNTER + REG_ENCORDER_COUNTER_A, p->pInstance->CounterA);
	sysOutLong(PLC_PULSE_GEN_ENCORDER_COUNTER + REG_ENCORDER_COUNTER_Z, p->pInstance->CounterZ);
}
