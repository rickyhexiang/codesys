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
#include "CmpGlodonDemoDep.h"
#include "glodon_iot_main.c"
#include "CmpGlobalVar.h"
#include "cJSON.h"
#include <time.h>

USE_STMT

#ifndef RTS_COMPACT_MICRO

void do_destroy();

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
			do_destroy();
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
			//EXIT_STMT;
			break;
		}
#endif

		default:
			break;
	}
	return ERR_OK;
}

GlodonIoTData GVar_iotData = NULL;
GlodonIotClient GVar_iotClient = NULL;
#define TIME_OUT 3000

bool reset_iot_data()
{
	if (GVar_iotData != NULL)
	{
		glodon_iot_data_destory(GVar_iotData);
	}
	GVar_iotData = glodon_iot_data_init();
	if (GVar_iotData == NULL){
		IOT_ERROR(NULL, "error %s L#%d", __func__, __LINE__);
		return false;
	}
	return true;
}
bool GVar_biotInitialized = false;
/*
 * 初始化物联网平台资源
 */
void CDECL CDECL_EXT init_iot_resource()
{
	if (GVar_biotInitialized) return;
	GlodonIotInitParams initParams = {
		.username = (char *)GLODON_IOT_MQTT_USERNAME, 
		.password = (char *)GLODON_IOT_MQTT_PASSWORD,
		.userdata = NULL,
		//.useMqtts = true,
		.onLogOutput = on_log_output,
		.onConnect = on_connect,
		.onMessage = on_app_message,
	};

	/* 1、查看sdk版本 */
	IOT_INFO(NULL, "Glodon Iot Version: %s", glodon_iot_get_version());
	/* 2、初始sdk */
	if(!(GVar_iotClient = glodon_iot_init(&initParams))) {
		IOT_ERROR(NULL, "error %s L#%d", __func__, __LINE__);
		return;
	}
	/* 3、开启连接服务器 */
	if(glodon_iot_connect(GVar_iotClient)) {
		IOT_ERROR(GVar_iotClient, "error %s L#%d", __func__, __LINE__);
		return;
	}
    /* 4、数据模型初始 */
	
	if (!reset_iot_data()){
		return;
	}
	GVar_biotInitialized = true;
}

//test
void test_access_iot()
{
	while(1)
	{
		init_iot_resource();
		if (GVar_biotInitialized)
		{
			//IOT_INFO(NULL, "info %s L#%d", __func__, __LINE__);
			glodon_iot_yield(GVar_iotClient, 100);
		}
		sleep(2);
	}
}

//访问物联网平台，保持心跳
void CDECL CDECL_EXT do_access_iot__main(do_access_iot_main_struct *p)
{
	init_iot_resource();
	if (GVar_biotInitialized)
	{
		//IOT_INFO(NULL, "info %s L#%d", __func__, __LINE__);
		glodon_iot_yield(GVar_iotClient, 100);
	}
}

void do_destroy()
{
	if (GVar_iotClient != NULL)
	{
		glodon_iot_destory(GVar_iotClient);
	}
	if (GVar_iotData != NULL)
	{
		glodon_iot_data_destory(GVar_iotData);
	}
	if (GVar_taskInfo != NULL)
	{
		free(GVar_taskInfo);
	}
}

//结束物联网访问，释放资源
void CDECL CDECL_EXT end_access_iot__main(end_access_iot_main_struct *p)
{
	do_destroy();
}

/*
 * 单个任务开始发送消息
 */
void CDECL CDECL_EXT start_one_task__main(start_one_task_main_struct *p)
{
	//先设置为-1
	p->pInstance->nReturnValue = -1;
	if (GVar_iotData == NULL) return;
	cJSON * taskInfo = cJSON_CreateObject();
	if (taskInfo == NULL)
	{
		IOT_ERROR(GVar_iotClient, "error %s L#%d", __func__, __LINE__);
		goto errout;
	}
	//钢筋级别
	cJSON_AddNumberToObject(taskInfo, BAR_LEVEL, p->pInstance->nBarLevel);
	//钢筋直径
	cJSON_AddNumberToObject(taskInfo, BAR_DIAMETER, p->pInstance->rBarDiameter);
	//参数数量
	cJSON_AddNumberToObject(taskInfo, TASK_PARAMS_COUNT, p->pInstance->nParamCount);
	//taskID
	cJSON_AddStringToObject(taskInfo, TASK_ID, p->pInstance->taskID);
	//加工参数
	cJSON * params = cJSON_CreateArray();
	if (params == NULL)
	{
		IOT_ERROR(GVar_iotClient, "error %s L#%d", __func__, __LINE__);
		goto errout;
	}
	cJSON * oneParam = cJSON_CreateObject();
	if (oneParam == NULL)
	{
		IOT_ERROR(GVar_iotClient, "error %s L#%d", __func__, __LINE__);
		goto errout;
	}
	
	for (int i = 0; i < p->pInstance->nParamCount; ++i)
	{
		cJSON * oneParam = cJSON_CreateObject();
		if (oneParam == NULL)
		{
			IOT_ERROR(GVar_iotClient, "error %s L#%d", __func__, __LINE__);
			goto errout;
		}
		cJSON_AddNumberToObject(oneParam, BAR_LENGTH, p->pInstance->taskParams[i].length);
		cJSON_AddNumberToObject(oneParam, BAR_ANGLE, p->pInstance->taskParams[i].angle);
		cJSON_AddNumberToObject(oneParam, BAR_LENGTH_COMPENSATION, p->pInstance->taskParams[i].lengthCompensation);
		cJSON_AddNumberToObject(oneParam, BAR_ANGLE_COMPENSATION, p->pInstance->taskParams[i].angleCompensation);
		cJSON_AddItemToArray(params, oneParam);
	}
	cJSON_AddItemToObject(taskInfo, TASK_PARAMS, params);
	
	char * taskInfostr = cJSON_Print(taskInfo);
	IOT_INFO(GVar_iotClient, taskInfostr);
	if (reset_iot_data())
	{
		GVar_iotData->setStartTask(GVar_iotData, taskInfostr);
		if (glodon_iot_is_client_connected(GVar_iotClient))
		{
			p->pInstance->nReturnValue = glodon_iot_send_ex(GVar_iotClient, GVar_iotData, TIME_OUT);
			IOT_INFO(GVar_iotClient, "send rc = %d", p->pInstance->nReturnValue);
		}
	}
	free(taskInfostr);
errout:
	if(taskInfo) {
		cJSON_Delete(taskInfo);
		taskInfo = NULL;
	}
}

/*
 * 单个任务更新发送消息
 */
void CDECL CDECL_EXT update_one_task__main(update_one_task_main_struct *p)
{
	p->pInstance->nReturnValue = -1;
	if (GVar_iotData == NULL) return;
	cJSON * taskInfo = cJSON_CreateObject();
	if (taskInfo == NULL)
	{
		IOT_ERROR(NULL, "error %s L#%d", __func__, __LINE__);
		return;
	}
	cJSON_AddStringToObject(taskInfo, TASK_ID, p->pInstance->taskID);
	cJSON_AddNumberToObject(taskInfo, BAR_COUNT, p->pInstance->nCount);
	char * taskInfostr = cJSON_Print(taskInfo);
	IOT_INFO(GVar_iotClient, taskInfostr);
	if (reset_iot_data())
	{
		GVar_iotData->setUpdateTask(GVar_iotData, taskInfostr);
		if (glodon_iot_is_client_connected(GVar_iotClient))
		{
			p->pInstance->nReturnValue = glodon_iot_send_ex(GVar_iotClient, GVar_iotData, TIME_OUT);
			IOT_INFO(GVar_iotClient, "send rc = %d", p->pInstance->nReturnValue);
		}
	}
}
/*
 * 单个任务发送结束消息
 */
void CDECL CDECL_EXT end_one_task__main(end_one_task_main_struct *p)
{
	p->pInstance->nReturnValue = -1;
	if (GVar_iotData == NULL) return;
	cJSON * taskInfo = cJSON_CreateObject();
	if (taskInfo == NULL)
	{
		IOT_ERROR(NULL, "error %s L#%d", __func__, __LINE__);
		return;
	}
	cJSON_AddStringToObject(taskInfo, TASK_ID, p->pInstance->taskID);
	cJSON_AddNumberToObject(taskInfo, BAR_COUNT, p->pInstance->nCount);
	char * taskInfostr = cJSON_Print(taskInfo);
	IOT_INFO(GVar_iotClient, taskInfostr);
	if (reset_iot_data())
	{
		GVar_iotData->setEndTask(GVar_iotData, taskInfostr);
		if (glodon_iot_is_client_connected(GVar_iotClient))
		{
			p->pInstance->nReturnValue = glodon_iot_send_ex(GVar_iotClient, GVar_iotData, TIME_OUT);
			IOT_INFO(GVar_iotClient, "send rc = %d", p->pInstance->nReturnValue);
		}
	}
}

void CDECL CDECL_EXT get_task_count__main(get_task_count_main_struct *p)
{
	p->pInstance->nTaskCount = GVar_nTaskCount;
}

void CDECL CDECL_EXT is_internet_connected__main(is_internet_connected_main_struct *p)
{
	p->pInstance->bConnected = glodon_iot_is_client_connected(GVar_iotClient);
}

void CDECL CDECL_EXT update_machine_data__main(update_machine_data_main_struct *p)
{
	p->pInstance->nReturnValue = -1;
	if (GVar_iotData == NULL) return;
	cJSON * taskInfo = cJSON_CreateObject();
	if (taskInfo == NULL)
	{
		IOT_ERROR(NULL, "error %s L#%d", __func__, __LINE__);
		return;
	}
	cJSON_AddStringToObject(taskInfo, TASK_ID, p->pInstance->iOther);
	cJSON_AddNumberToObject(taskInfo, BAR_COUNT, p->pInstance->iElectircFlow);
	char * taskInfostr = cJSON_Print(taskInfo);
	IOT_INFO(GVar_iotClient, taskInfostr);
	if (reset_iot_data())
	{
		GVar_iotData->setMachineState(GVar_iotData, taskInfostr);
		if (glodon_iot_is_client_connected(GVar_iotClient))
		{
			p->pInstance->nReturnValue = glodon_iot_send_ex(GVar_iotClient, GVar_iotData, TIME_OUT);
			IOT_INFO(GVar_iotClient, "send rc = %d", p->pInstance->nReturnValue);
		}
	}
}

char * GVar_taskInfo = NULL;

void CDECL CDECL_EXT get_task_data__main(get_task_data_main_struct *p)
{
	if (!glodon_iot_is_client_connected(GVar_iotClient)) return;
	
	//todo 要和余老师联调，上传任务nIndex（要哪个任务的数据），然后等待GVar_taskInfo数据回传
	if ((GVar_taskInfo == NULL) || (strlen(GVar_taskInfo) == 0)) return;
	
	cJSON * taskInfo = NULL;
	if (!(taskInfo = cJSON_Parse(GVar_taskInfo)))
	{
		IOT_ERROR(NULL, "error %s L#%d", __func__, __LINE__);
		goto errout;
	}
		
	
	cJSON *it;
	//barlevel
	if (!(it = cJSON_GetObjectItem(taskInfo, BAR_LEVEL)) || !cJSON_IsNumber(it)) 
	{
		IOT_ERROR(NULL, "error %s L#%d", __func__, __LINE__);
	    goto errout;
	}
	p->pInstance->nBarLevel = it->valueint;

	//barDiameter
	if (!(it = cJSON_GetObjectItem(taskInfo, BAR_DIAMETER)) || !cJSON_IsNumber(it))
	{
		IOT_ERROR(NULL, "error %s L#%d", __func__, __LINE__);
		goto errout;
	}
	p->pInstance->rBarDiameter = it->valuedouble;

	//barCount
	if (!(it = cJSON_GetObjectItem(taskInfo, BAR_COUNT)) || !cJSON_IsNumber(it))
	{
		IOT_ERROR(NULL, "error %s L#%d", __func__, __LINE__);
		goto errout;
	}
	p->pInstance->nTaskCount = it->valueint;
	//taskID
	if (!(it = cJSON_GetObjectItem(taskInfo, TASK_ID)) || !cJSON_IsString(it))
	{
		IOT_ERROR(NULL, "error %s L#%d", __func__, __LINE__);
		goto errout;
	}
	strcpy(p->pInstance->taskID, it->valuestring);

	//Params
	if (!(it = cJSON_GetObjectItem(taskInfo, TASK_PARAMS)) || !cJSON_IsArray(it))
	{
		IOT_ERROR(NULL, "error %s L#%d", __func__, __LINE__);
		goto errout;
	}
	int nArraySize = cJSON_GetArraySize(it);
	nArraySize = min(nArraySize, 10);
	cJSON * param = NULL;
	cJSON * length = NULL;
	cJSON * angle = NULL;
	cJSON * lengthCompensation = NULL;
	cJSON * angleCompensation = NULL;
	p->pInstance->nParamCount = nArraySize;
	for (int i = 0; i < nArraySize; ++i)
	{
		if (!(param = cJSON_GetArrayItem(it, i)) || !cJSON_IsObject(param))
		{
			IOT_ERROR(NULL, "error %s L#%d", __func__, __LINE__);
			goto errout;
		}
		//长度
		if (!(length = cJSON_GetObjectItem(param, BAR_LENGTH)) || !cJSON_IsNumber(length))
		{
			IOT_ERROR(NULL, "error %s L#%d", __func__, __LINE__);
			goto errout;
		}
		p->pInstance->taskParams[i].length = length->valueint;
		//角度
		if (!(angle = cJSON_GetObjectItem(param, BAR_ANGLE)) || !cJSON_IsNumber(angle))
		{
			IOT_ERROR(NULL, "error %s L#%d", __func__, __LINE__);
			goto errout;
		}
		p->pInstance->taskParams[i].angle = angle->valueint;
		//长度补偿
		if (!(lengthCompensation = cJSON_GetObjectItem(param, BAR_LENGTH_COMPENSATION)) || !cJSON_IsNumber(lengthCompensation))
		{
			IOT_ERROR(NULL, "error %s L#%d", __func__, __LINE__);
			goto errout;
		}
    	p->pInstance->taskParams[i].lengthCompensation = lengthCompensation->valueint;
		//角度补偿
		if (!(angleCompensation = cJSON_GetObjectItem(param, BAR_ANGLE_COMPENSATION)) || !cJSON_IsNumber(angleCompensation))
		{
			IOT_ERROR(NULL, "error %s L#%d", __func__, __LINE__);
			goto errout;
		}
		p->pInstance->taskParams[i].angleCompensation = angleCompensation->valueint;
	}	
	//destroy
	if(taskInfo) {
		cJSON_Delete(taskInfo);
		taskInfo = NULL;
	}
errout:
	if(taskInfo) {
		cJSON_Delete(taskInfo);
		taskInfo = NULL;
	}
}


