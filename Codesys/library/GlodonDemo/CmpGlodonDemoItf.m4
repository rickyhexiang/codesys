/**
 * <interfacename>CmpGlodonDemo</interfacename>
 * <description></description>
 *
 * <copyright></copyright>
 */

SET_INTERFACE_NAME(`CmpGlodonDemo')

/** EXTERN LIB SECTION BEGIN **/
/*  Comments are ignored for m4 compiler so restructured text can be used. changecom(`/*', `*/') */

#ifdef __cplusplus
extern "C" {
#endif

/**
 *{attribute 'conditionalshow'}
 *{attribute 'conditionalshow' := 'SomeText'}
 *{attribute 'hide'}
 */
#define ERROR_NO_ERROR    RTS_IEC_INT_C(0x0)	
#define ERROR_TIME_OUT    RTS_IEC_INT_C(0x1)	
/* Typed enum definition */
#define ERROR    RTS_IEC_INT

/**
 *一个待加工边的结构体，一个加工任务有多个边，使用时以数组方式实现
 */
typedef struct tagOneSideParam
{
	RTS_IEC_INT length;		/* 长度 */
	RTS_IEC_INT lengthCompensation;		/* 长度补偿 */
	RTS_IEC_INT angle;		/* 角度 */
	RTS_IEC_INT angleCompensation;		/* 角度补偿 */
} OneSideParam;

/**
 *保持物联网心跳，收发数据
 */
typedef struct tagdo_access_iot_struct
{
	void* __VFTABLEPOINTER;				/* Pointer to virtual function table */

	/* Member variables of do_access_IOT */

} do_access_iot_struct;

/**
 * <description>do_access_iot_main</description>
 */
typedef struct tagdo_access_iot_main_struct
{
	do_access_iot_struct *pInstance;	/* VAR_INPUT */	
} do_access_iot_main_struct;

DEF_API(`void',`CDECL',`do_access_iot__main',`(do_access_iot_main_struct *p)',1,0x3E484BF2,0x01000000)

/**
 *结束物联网访问，释放资源，可在关机时调用
 */
typedef struct tagend_access_iot_struct
{
	void* __VFTABLEPOINTER;				/* Pointer to virtual function table */

	/* Member variables of end_access_IOT */

} end_access_iot_struct;

/**
 * <description>end_access_iot_main</description>
 */
typedef struct tagend_access_iot_main_struct
{
	end_access_iot_struct *pInstance;	/* VAR_INPUT */	
} end_access_iot_main_struct;

DEF_API(`void',`CDECL',`end_access_iot__main',`(end_access_iot_main_struct *p)',1,0x1CA99AFC,0x01000000)

/**
 *结束任务时发送的信息
 */
typedef struct tagend_one_task_struct
{
	void* __VFTABLEPOINTER;				/* Pointer to virtual function table */

	/* Member variables of end_one_task */

	RTS_IEC_STRING taskID[81];			/* VAR_INPUT */	/* 任务ID */
	RTS_IEC_INT nCount;					/* VAR_INPUT */	/* 实际加工的钢筋数量 */
	RTS_IEC_INT nReturnValue;			/* VAR_OUTPUT */	/* 错误码，0为上传数据成功 */
} end_one_task_struct;

/**
 * <description>end_one_task_main</description>
 */
typedef struct tagend_one_task_main_struct
{
	end_one_task_struct *pInstance;		/* VAR_INPUT */	
} end_one_task_main_struct;

DEF_API(`void',`CDECL',`end_one_task__main',`(end_one_task_main_struct *p)',1,0x68170C11,0x01000000)

/**
 *获取待加工任务数量
 */
typedef struct tagget_task_count_struct
{
	void* __VFTABLEPOINTER;				/* Pointer to virtual function table */

	/* Member variables of get_task_count */

	RTS_IEC_INT nTaskCount;				/* VAR_OUTPUT */	/* 输出为加工任务数量 */
} get_task_count_struct;

/**
 * <description>get_task_count_main</description>
 */
typedef struct tagget_task_count_main_struct
{
	get_task_count_struct *pInstance;	/* VAR_INPUT */	
} get_task_count_main_struct;

DEF_API(`void',`CDECL',`get_task_count__main',`(get_task_count_main_struct *p)',1,0x4B225203,0x01000000)

/**
 *获取加工任务参数
 */
typedef struct tagget_task_data_struct
{
	void* __VFTABLEPOINTER;				/* Pointer to virtual function table */

	/* Member variables of get_task_data */

	RTS_IEC_INT nIndex;					/* VAR_INPUT */	/* 待加工任务序号 */
	RTS_IEC_INT nBarLevel;				/* VAR_OUTPUT */	/* 钢筋级别 */
	RTS_IEC_REAL rBarDiameter;			/* VAR_OUTPUT */	/* 钢筋直径 */
	OneSideParam taskParams[10];		/* VAR_OUTPUT */	/* 钢筋加工边的参数 */
	RTS_IEC_INT nParamCount;			/* VAR_OUTPUT */	/* 待加工边的个数 */
	RTS_IEC_INT nTaskCount;				/* VAR_OUTPUT */	/* 待加工个数 */
	RTS_IEC_STRING taskID[81];			/* VAR_OUTPUT */	/* 待加工任务ID */
	RTS_IEC_INT nReturnValue;			/* VAR_OUTPUT */	/* 错误码，0为上传数据成功 */
} get_task_data_struct;

/**
 * <description>get_task_data_main</description>
 */
typedef struct tagget_task_data_main_struct
{
	get_task_data_struct *pInstance;	/* VAR_INPUT */	
} get_task_data_main_struct;

DEF_API(`void',`CDECL',`get_task_data__main',`(get_task_data_main_struct *p)',1,0x72113503,0x01000000)

/**
 *是否连接到物联网
 */
typedef struct tagis_internet_connected_struct
{
	void* __VFTABLEPOINTER;				/* Pointer to virtual function table */

	/* Member variables of is_internet_connected */

	RTS_IEC_BOOL bConnected;			/* VAR_OUTPUT */	/* 返回值 */
} is_internet_connected_struct;

/**
 * <description>is_internet_connected_main</description>
 */
typedef struct tagis_internet_connected_main_struct
{
	is_internet_connected_struct *pInstance;	/* VAR_INPUT */	
} is_internet_connected_main_struct;

DEF_API(`void',`CDECL',`is_internet_connected__main',`(is_internet_connected_main_struct *p)',1,0xBCD4A05B,0x01000000)

/**
 *开始任务发送消息，参数为真实的加工数据
 */
typedef struct tagstart_one_task_struct
{
	void* __VFTABLEPOINTER;				/* Pointer to virtual function table */

	/* Member variables of start_one_task */

	RTS_IEC_INT nBarLevel;				/* VAR_INPUT */	/* 钢筋级别 */
	RTS_IEC_REAL rBarDiameter;			/* VAR_INPUT */	/* 钢筋直径 */
	OneSideParam taskParams[10];		/* VAR_INPUT */	/* 钢筋边的参数 */
	RTS_IEC_INT nParamCount;			/* VAR_INPUT */	/* 钢筋边的个数 */
	RTS_IEC_STRING taskID[81];			/* VAR_INPUT */	/* 加工的任务ID */
	RTS_IEC_INT nReturnValue;			/* VAR_OUTPUT */	/* 错误码，0为上传数据成功 */
} start_one_task_struct;

/**
 * <description>start_one_task_main</description>
 */
typedef struct tagstart_one_task_main_struct
{
	start_one_task_struct *pInstance;	/* VAR_INPUT */	
} start_one_task_main_struct;

DEF_API(`void',`CDECL',`start_one_task__main',`(start_one_task_main_struct *p)',1,0x7CE1EAB1,0x01000000)

/**
 *上传机械设备数据，待定业务需求
 */
typedef struct tagupdate_machine_data_struct
{
	void* __VFTABLEPOINTER;				/* Pointer to virtual function table */

	/* Member variables of update_machine_data */

	RTS_IEC_INT iElectircFlow;			/* VAR_INPUT */	
	RTS_IEC_STRING iOther[81];			/* VAR_INPUT */	
	RTS_IEC_INT nReturnValue;			/* VAR_OUTPUT */	/* 错误码，0为上传数据成功 */
} update_machine_data_struct;

/**
 * <description>update_machine_data_main</description>
 */
typedef struct tagupdate_machine_data_main_struct
{
	update_machine_data_struct *pInstance;	/* VAR_INPUT */	
} update_machine_data_main_struct;

DEF_API(`void',`CDECL',`update_machine_data__main',`(update_machine_data_main_struct *p)',1,0x93B879B0,0x01000000)

/**
 *更新正在加工的任务信息
 */
typedef struct tagupdate_one_task_struct
{
	void* __VFTABLEPOINTER;				/* Pointer to virtual function table */

	/* Member variables of update_one_task */

	RTS_IEC_STRING taskID[81];			/* VAR_INPUT */	/* 任务id */
	RTS_IEC_INT nCount;					/* VAR_INPUT */	/* 当前加工的根数 */
	RTS_IEC_INT nReturnValue;			/* VAR_OUTPUT */	/* 错误码，0为上传数据成功 */
} update_one_task_struct;

/**
 * <description>update_one_task_main</description>
 */
typedef struct tagupdate_one_task_main_struct
{
	update_one_task_struct *pInstance;	/* VAR_INPUT */	
} update_one_task_main_struct;

DEF_API(`void',`CDECL',`update_one_task__main',`(update_one_task_main_struct *p)',1,0xD5DDFCFA,0x01000000)

#ifdef __cplusplus
}
#endif

/** EXTERN LIB SECTION END **/

