 /**
 * <interfacename>CmpGlodonDemo</interfacename>
 * <description></description>
 *
 * <copyright></copyright>
 */


	
	
#ifndef _CMPGLODONDEMOITF_H_
#define _CMPGLODONDEMOITF_H_

#include "CmpStd.h"

 

 




/** EXTERN LIB SECTION BEGIN **/
/*  Comments are ignored for m4 compiler so restructured text can be used.  */

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

void CDECL CDECL_EXT do_access_iot__main(do_access_iot_main_struct *p);
typedef void (CDECL CDECL_EXT* PFDO_ACCESS_IOT__MAIN_IEC) (do_access_iot_main_struct *p);
#if defined(CMPGLODONDEMO_NOTIMPLEMENTED) || defined(DO_ACCESS_IOT__MAIN_NOTIMPLEMENTED)
	#define USE_do_access_iot__main
	#define EXT_do_access_iot__main
	#define GET_do_access_iot__main(fl)  ERR_NOTIMPLEMENTED
	#define CAL_do_access_iot__main(p0) 
	#define CHK_do_access_iot__main  FALSE
	#define EXP_do_access_iot__main  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_do_access_iot__main
	#define EXT_do_access_iot__main
	#define GET_do_access_iot__main(fl)  CAL_CMGETAPI( "do_access_iot__main" ) 
	#define CAL_do_access_iot__main  do_access_iot__main
	#define CHK_do_access_iot__main  TRUE
	#define EXP_do_access_iot__main  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"do_access_iot__main", (RTS_UINTPTR)do_access_iot__main, 1, 0x3E484BF2, 0x01000000) 
#elif defined(MIXED_LINK) && !defined(CMPGLODONDEMO_EXTERNAL)
	#define USE_do_access_iot__main
	#define EXT_do_access_iot__main
	#define GET_do_access_iot__main(fl)  CAL_CMGETAPI( "do_access_iot__main" ) 
	#define CAL_do_access_iot__main  do_access_iot__main
	#define CHK_do_access_iot__main  TRUE
	#define EXP_do_access_iot__main  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"do_access_iot__main", (RTS_UINTPTR)do_access_iot__main, 1, 0x3E484BF2, 0x01000000) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpGlodonDemodo_access_iot__main
	#define EXT_CmpGlodonDemodo_access_iot__main
	#define GET_CmpGlodonDemodo_access_iot__main  ERR_OK
	#define CAL_CmpGlodonDemodo_access_iot__main  do_access_iot__main
	#define CHK_CmpGlodonDemodo_access_iot__main  TRUE
	#define EXP_CmpGlodonDemodo_access_iot__main  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"do_access_iot__main", (RTS_UINTPTR)do_access_iot__main, 1, 0x3E484BF2, 0x01000000) 
#elif defined(CPLUSPLUS)
	#define USE_do_access_iot__main
	#define EXT_do_access_iot__main
	#define GET_do_access_iot__main(fl)  CAL_CMGETAPI( "do_access_iot__main" ) 
	#define CAL_do_access_iot__main  do_access_iot__main
	#define CHK_do_access_iot__main  TRUE
	#define EXP_do_access_iot__main  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"do_access_iot__main", (RTS_UINTPTR)do_access_iot__main, 1, 0x3E484BF2, 0x01000000) 
#else /* DYNAMIC_LINK */
	#define USE_do_access_iot__main  PFDO_ACCESS_IOT__MAIN_IEC pfdo_access_iot__main;
	#define EXT_do_access_iot__main  extern PFDO_ACCESS_IOT__MAIN_IEC pfdo_access_iot__main;
	#define GET_do_access_iot__main(fl)  s_pfCMGetAPI2( "do_access_iot__main", (RTS_VOID_FCTPTR *)&pfdo_access_iot__main, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0x3E484BF2, 0x01000000)
	#define CAL_do_access_iot__main  pfdo_access_iot__main
	#define CHK_do_access_iot__main  (pfdo_access_iot__main != NULL)
	#define EXP_do_access_iot__main   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"do_access_iot__main", (RTS_UINTPTR)do_access_iot__main, 1, 0x3E484BF2, 0x01000000) 
#endif


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

void CDECL CDECL_EXT end_access_iot__main(end_access_iot_main_struct *p);
typedef void (CDECL CDECL_EXT* PFEND_ACCESS_IOT__MAIN_IEC) (end_access_iot_main_struct *p);
#if defined(CMPGLODONDEMO_NOTIMPLEMENTED) || defined(END_ACCESS_IOT__MAIN_NOTIMPLEMENTED)
	#define USE_end_access_iot__main
	#define EXT_end_access_iot__main
	#define GET_end_access_iot__main(fl)  ERR_NOTIMPLEMENTED
	#define CAL_end_access_iot__main(p0) 
	#define CHK_end_access_iot__main  FALSE
	#define EXP_end_access_iot__main  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_end_access_iot__main
	#define EXT_end_access_iot__main
	#define GET_end_access_iot__main(fl)  CAL_CMGETAPI( "end_access_iot__main" ) 
	#define CAL_end_access_iot__main  end_access_iot__main
	#define CHK_end_access_iot__main  TRUE
	#define EXP_end_access_iot__main  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"end_access_iot__main", (RTS_UINTPTR)end_access_iot__main, 1, 0x1CA99AFC, 0x01000000) 
#elif defined(MIXED_LINK) && !defined(CMPGLODONDEMO_EXTERNAL)
	#define USE_end_access_iot__main
	#define EXT_end_access_iot__main
	#define GET_end_access_iot__main(fl)  CAL_CMGETAPI( "end_access_iot__main" ) 
	#define CAL_end_access_iot__main  end_access_iot__main
	#define CHK_end_access_iot__main  TRUE
	#define EXP_end_access_iot__main  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"end_access_iot__main", (RTS_UINTPTR)end_access_iot__main, 1, 0x1CA99AFC, 0x01000000) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpGlodonDemoend_access_iot__main
	#define EXT_CmpGlodonDemoend_access_iot__main
	#define GET_CmpGlodonDemoend_access_iot__main  ERR_OK
	#define CAL_CmpGlodonDemoend_access_iot__main  end_access_iot__main
	#define CHK_CmpGlodonDemoend_access_iot__main  TRUE
	#define EXP_CmpGlodonDemoend_access_iot__main  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"end_access_iot__main", (RTS_UINTPTR)end_access_iot__main, 1, 0x1CA99AFC, 0x01000000) 
#elif defined(CPLUSPLUS)
	#define USE_end_access_iot__main
	#define EXT_end_access_iot__main
	#define GET_end_access_iot__main(fl)  CAL_CMGETAPI( "end_access_iot__main" ) 
	#define CAL_end_access_iot__main  end_access_iot__main
	#define CHK_end_access_iot__main  TRUE
	#define EXP_end_access_iot__main  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"end_access_iot__main", (RTS_UINTPTR)end_access_iot__main, 1, 0x1CA99AFC, 0x01000000) 
#else /* DYNAMIC_LINK */
	#define USE_end_access_iot__main  PFEND_ACCESS_IOT__MAIN_IEC pfend_access_iot__main;
	#define EXT_end_access_iot__main  extern PFEND_ACCESS_IOT__MAIN_IEC pfend_access_iot__main;
	#define GET_end_access_iot__main(fl)  s_pfCMGetAPI2( "end_access_iot__main", (RTS_VOID_FCTPTR *)&pfend_access_iot__main, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0x1CA99AFC, 0x01000000)
	#define CAL_end_access_iot__main  pfend_access_iot__main
	#define CHK_end_access_iot__main  (pfend_access_iot__main != NULL)
	#define EXP_end_access_iot__main   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"end_access_iot__main", (RTS_UINTPTR)end_access_iot__main, 1, 0x1CA99AFC, 0x01000000) 
#endif


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

void CDECL CDECL_EXT end_one_task__main(end_one_task_main_struct *p);
typedef void (CDECL CDECL_EXT* PFEND_ONE_TASK__MAIN_IEC) (end_one_task_main_struct *p);
#if defined(CMPGLODONDEMO_NOTIMPLEMENTED) || defined(END_ONE_TASK__MAIN_NOTIMPLEMENTED)
	#define USE_end_one_task__main
	#define EXT_end_one_task__main
	#define GET_end_one_task__main(fl)  ERR_NOTIMPLEMENTED
	#define CAL_end_one_task__main(p0) 
	#define CHK_end_one_task__main  FALSE
	#define EXP_end_one_task__main  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_end_one_task__main
	#define EXT_end_one_task__main
	#define GET_end_one_task__main(fl)  CAL_CMGETAPI( "end_one_task__main" ) 
	#define CAL_end_one_task__main  end_one_task__main
	#define CHK_end_one_task__main  TRUE
	#define EXP_end_one_task__main  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"end_one_task__main", (RTS_UINTPTR)end_one_task__main, 1, 0x68170C11, 0x01000000) 
#elif defined(MIXED_LINK) && !defined(CMPGLODONDEMO_EXTERNAL)
	#define USE_end_one_task__main
	#define EXT_end_one_task__main
	#define GET_end_one_task__main(fl)  CAL_CMGETAPI( "end_one_task__main" ) 
	#define CAL_end_one_task__main  end_one_task__main
	#define CHK_end_one_task__main  TRUE
	#define EXP_end_one_task__main  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"end_one_task__main", (RTS_UINTPTR)end_one_task__main, 1, 0x68170C11, 0x01000000) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpGlodonDemoend_one_task__main
	#define EXT_CmpGlodonDemoend_one_task__main
	#define GET_CmpGlodonDemoend_one_task__main  ERR_OK
	#define CAL_CmpGlodonDemoend_one_task__main  end_one_task__main
	#define CHK_CmpGlodonDemoend_one_task__main  TRUE
	#define EXP_CmpGlodonDemoend_one_task__main  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"end_one_task__main", (RTS_UINTPTR)end_one_task__main, 1, 0x68170C11, 0x01000000) 
#elif defined(CPLUSPLUS)
	#define USE_end_one_task__main
	#define EXT_end_one_task__main
	#define GET_end_one_task__main(fl)  CAL_CMGETAPI( "end_one_task__main" ) 
	#define CAL_end_one_task__main  end_one_task__main
	#define CHK_end_one_task__main  TRUE
	#define EXP_end_one_task__main  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"end_one_task__main", (RTS_UINTPTR)end_one_task__main, 1, 0x68170C11, 0x01000000) 
#else /* DYNAMIC_LINK */
	#define USE_end_one_task__main  PFEND_ONE_TASK__MAIN_IEC pfend_one_task__main;
	#define EXT_end_one_task__main  extern PFEND_ONE_TASK__MAIN_IEC pfend_one_task__main;
	#define GET_end_one_task__main(fl)  s_pfCMGetAPI2( "end_one_task__main", (RTS_VOID_FCTPTR *)&pfend_one_task__main, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0x68170C11, 0x01000000)
	#define CAL_end_one_task__main  pfend_one_task__main
	#define CHK_end_one_task__main  (pfend_one_task__main != NULL)
	#define EXP_end_one_task__main   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"end_one_task__main", (RTS_UINTPTR)end_one_task__main, 1, 0x68170C11, 0x01000000) 
#endif


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

void CDECL CDECL_EXT get_task_count__main(get_task_count_main_struct *p);
typedef void (CDECL CDECL_EXT* PFGET_TASK_COUNT__MAIN_IEC) (get_task_count_main_struct *p);
#if defined(CMPGLODONDEMO_NOTIMPLEMENTED) || defined(GET_TASK_COUNT__MAIN_NOTIMPLEMENTED)
	#define USE_get_task_count__main
	#define EXT_get_task_count__main
	#define GET_get_task_count__main(fl)  ERR_NOTIMPLEMENTED
	#define CAL_get_task_count__main(p0) 
	#define CHK_get_task_count__main  FALSE
	#define EXP_get_task_count__main  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_get_task_count__main
	#define EXT_get_task_count__main
	#define GET_get_task_count__main(fl)  CAL_CMGETAPI( "get_task_count__main" ) 
	#define CAL_get_task_count__main  get_task_count__main
	#define CHK_get_task_count__main  TRUE
	#define EXP_get_task_count__main  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"get_task_count__main", (RTS_UINTPTR)get_task_count__main, 1, 0x4B225203, 0x01000000) 
#elif defined(MIXED_LINK) && !defined(CMPGLODONDEMO_EXTERNAL)
	#define USE_get_task_count__main
	#define EXT_get_task_count__main
	#define GET_get_task_count__main(fl)  CAL_CMGETAPI( "get_task_count__main" ) 
	#define CAL_get_task_count__main  get_task_count__main
	#define CHK_get_task_count__main  TRUE
	#define EXP_get_task_count__main  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"get_task_count__main", (RTS_UINTPTR)get_task_count__main, 1, 0x4B225203, 0x01000000) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpGlodonDemoget_task_count__main
	#define EXT_CmpGlodonDemoget_task_count__main
	#define GET_CmpGlodonDemoget_task_count__main  ERR_OK
	#define CAL_CmpGlodonDemoget_task_count__main  get_task_count__main
	#define CHK_CmpGlodonDemoget_task_count__main  TRUE
	#define EXP_CmpGlodonDemoget_task_count__main  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"get_task_count__main", (RTS_UINTPTR)get_task_count__main, 1, 0x4B225203, 0x01000000) 
#elif defined(CPLUSPLUS)
	#define USE_get_task_count__main
	#define EXT_get_task_count__main
	#define GET_get_task_count__main(fl)  CAL_CMGETAPI( "get_task_count__main" ) 
	#define CAL_get_task_count__main  get_task_count__main
	#define CHK_get_task_count__main  TRUE
	#define EXP_get_task_count__main  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"get_task_count__main", (RTS_UINTPTR)get_task_count__main, 1, 0x4B225203, 0x01000000) 
#else /* DYNAMIC_LINK */
	#define USE_get_task_count__main  PFGET_TASK_COUNT__MAIN_IEC pfget_task_count__main;
	#define EXT_get_task_count__main  extern PFGET_TASK_COUNT__MAIN_IEC pfget_task_count__main;
	#define GET_get_task_count__main(fl)  s_pfCMGetAPI2( "get_task_count__main", (RTS_VOID_FCTPTR *)&pfget_task_count__main, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0x4B225203, 0x01000000)
	#define CAL_get_task_count__main  pfget_task_count__main
	#define CHK_get_task_count__main  (pfget_task_count__main != NULL)
	#define EXP_get_task_count__main   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"get_task_count__main", (RTS_UINTPTR)get_task_count__main, 1, 0x4B225203, 0x01000000) 
#endif


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

void CDECL CDECL_EXT get_task_data__main(get_task_data_main_struct *p);
typedef void (CDECL CDECL_EXT* PFGET_TASK_DATA__MAIN_IEC) (get_task_data_main_struct *p);
#if defined(CMPGLODONDEMO_NOTIMPLEMENTED) || defined(GET_TASK_DATA__MAIN_NOTIMPLEMENTED)
	#define USE_get_task_data__main
	#define EXT_get_task_data__main
	#define GET_get_task_data__main(fl)  ERR_NOTIMPLEMENTED
	#define CAL_get_task_data__main(p0) 
	#define CHK_get_task_data__main  FALSE
	#define EXP_get_task_data__main  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_get_task_data__main
	#define EXT_get_task_data__main
	#define GET_get_task_data__main(fl)  CAL_CMGETAPI( "get_task_data__main" ) 
	#define CAL_get_task_data__main  get_task_data__main
	#define CHK_get_task_data__main  TRUE
	#define EXP_get_task_data__main  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"get_task_data__main", (RTS_UINTPTR)get_task_data__main, 1, 0x72113503, 0x01000000) 
#elif defined(MIXED_LINK) && !defined(CMPGLODONDEMO_EXTERNAL)
	#define USE_get_task_data__main
	#define EXT_get_task_data__main
	#define GET_get_task_data__main(fl)  CAL_CMGETAPI( "get_task_data__main" ) 
	#define CAL_get_task_data__main  get_task_data__main
	#define CHK_get_task_data__main  TRUE
	#define EXP_get_task_data__main  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"get_task_data__main", (RTS_UINTPTR)get_task_data__main, 1, 0x72113503, 0x01000000) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpGlodonDemoget_task_data__main
	#define EXT_CmpGlodonDemoget_task_data__main
	#define GET_CmpGlodonDemoget_task_data__main  ERR_OK
	#define CAL_CmpGlodonDemoget_task_data__main  get_task_data__main
	#define CHK_CmpGlodonDemoget_task_data__main  TRUE
	#define EXP_CmpGlodonDemoget_task_data__main  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"get_task_data__main", (RTS_UINTPTR)get_task_data__main, 1, 0x72113503, 0x01000000) 
#elif defined(CPLUSPLUS)
	#define USE_get_task_data__main
	#define EXT_get_task_data__main
	#define GET_get_task_data__main(fl)  CAL_CMGETAPI( "get_task_data__main" ) 
	#define CAL_get_task_data__main  get_task_data__main
	#define CHK_get_task_data__main  TRUE
	#define EXP_get_task_data__main  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"get_task_data__main", (RTS_UINTPTR)get_task_data__main, 1, 0x72113503, 0x01000000) 
#else /* DYNAMIC_LINK */
	#define USE_get_task_data__main  PFGET_TASK_DATA__MAIN_IEC pfget_task_data__main;
	#define EXT_get_task_data__main  extern PFGET_TASK_DATA__MAIN_IEC pfget_task_data__main;
	#define GET_get_task_data__main(fl)  s_pfCMGetAPI2( "get_task_data__main", (RTS_VOID_FCTPTR *)&pfget_task_data__main, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0x72113503, 0x01000000)
	#define CAL_get_task_data__main  pfget_task_data__main
	#define CHK_get_task_data__main  (pfget_task_data__main != NULL)
	#define EXP_get_task_data__main   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"get_task_data__main", (RTS_UINTPTR)get_task_data__main, 1, 0x72113503, 0x01000000) 
#endif


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

void CDECL CDECL_EXT is_internet_connected__main(is_internet_connected_main_struct *p);
typedef void (CDECL CDECL_EXT* PFIS_INTERNET_CONNECTED__MAIN_IEC) (is_internet_connected_main_struct *p);
#if defined(CMPGLODONDEMO_NOTIMPLEMENTED) || defined(IS_INTERNET_CONNECTED__MAIN_NOTIMPLEMENTED)
	#define USE_is_internet_connected__main
	#define EXT_is_internet_connected__main
	#define GET_is_internet_connected__main(fl)  ERR_NOTIMPLEMENTED
	#define CAL_is_internet_connected__main(p0) 
	#define CHK_is_internet_connected__main  FALSE
	#define EXP_is_internet_connected__main  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_is_internet_connected__main
	#define EXT_is_internet_connected__main
	#define GET_is_internet_connected__main(fl)  CAL_CMGETAPI( "is_internet_connected__main" ) 
	#define CAL_is_internet_connected__main  is_internet_connected__main
	#define CHK_is_internet_connected__main  TRUE
	#define EXP_is_internet_connected__main  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"is_internet_connected__main", (RTS_UINTPTR)is_internet_connected__main, 1, 0xBCD4A05B, 0x01000000) 
#elif defined(MIXED_LINK) && !defined(CMPGLODONDEMO_EXTERNAL)
	#define USE_is_internet_connected__main
	#define EXT_is_internet_connected__main
	#define GET_is_internet_connected__main(fl)  CAL_CMGETAPI( "is_internet_connected__main" ) 
	#define CAL_is_internet_connected__main  is_internet_connected__main
	#define CHK_is_internet_connected__main  TRUE
	#define EXP_is_internet_connected__main  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"is_internet_connected__main", (RTS_UINTPTR)is_internet_connected__main, 1, 0xBCD4A05B, 0x01000000) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpGlodonDemois_internet_connected__main
	#define EXT_CmpGlodonDemois_internet_connected__main
	#define GET_CmpGlodonDemois_internet_connected__main  ERR_OK
	#define CAL_CmpGlodonDemois_internet_connected__main  is_internet_connected__main
	#define CHK_CmpGlodonDemois_internet_connected__main  TRUE
	#define EXP_CmpGlodonDemois_internet_connected__main  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"is_internet_connected__main", (RTS_UINTPTR)is_internet_connected__main, 1, 0xBCD4A05B, 0x01000000) 
#elif defined(CPLUSPLUS)
	#define USE_is_internet_connected__main
	#define EXT_is_internet_connected__main
	#define GET_is_internet_connected__main(fl)  CAL_CMGETAPI( "is_internet_connected__main" ) 
	#define CAL_is_internet_connected__main  is_internet_connected__main
	#define CHK_is_internet_connected__main  TRUE
	#define EXP_is_internet_connected__main  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"is_internet_connected__main", (RTS_UINTPTR)is_internet_connected__main, 1, 0xBCD4A05B, 0x01000000) 
#else /* DYNAMIC_LINK */
	#define USE_is_internet_connected__main  PFIS_INTERNET_CONNECTED__MAIN_IEC pfis_internet_connected__main;
	#define EXT_is_internet_connected__main  extern PFIS_INTERNET_CONNECTED__MAIN_IEC pfis_internet_connected__main;
	#define GET_is_internet_connected__main(fl)  s_pfCMGetAPI2( "is_internet_connected__main", (RTS_VOID_FCTPTR *)&pfis_internet_connected__main, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0xBCD4A05B, 0x01000000)
	#define CAL_is_internet_connected__main  pfis_internet_connected__main
	#define CHK_is_internet_connected__main  (pfis_internet_connected__main != NULL)
	#define EXP_is_internet_connected__main   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"is_internet_connected__main", (RTS_UINTPTR)is_internet_connected__main, 1, 0xBCD4A05B, 0x01000000) 
#endif


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

void CDECL CDECL_EXT start_one_task__main(start_one_task_main_struct *p);
typedef void (CDECL CDECL_EXT* PFSTART_ONE_TASK__MAIN_IEC) (start_one_task_main_struct *p);
#if defined(CMPGLODONDEMO_NOTIMPLEMENTED) || defined(START_ONE_TASK__MAIN_NOTIMPLEMENTED)
	#define USE_start_one_task__main
	#define EXT_start_one_task__main
	#define GET_start_one_task__main(fl)  ERR_NOTIMPLEMENTED
	#define CAL_start_one_task__main(p0) 
	#define CHK_start_one_task__main  FALSE
	#define EXP_start_one_task__main  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_start_one_task__main
	#define EXT_start_one_task__main
	#define GET_start_one_task__main(fl)  CAL_CMGETAPI( "start_one_task__main" ) 
	#define CAL_start_one_task__main  start_one_task__main
	#define CHK_start_one_task__main  TRUE
	#define EXP_start_one_task__main  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"start_one_task__main", (RTS_UINTPTR)start_one_task__main, 1, 0x7CE1EAB1, 0x01000000) 
#elif defined(MIXED_LINK) && !defined(CMPGLODONDEMO_EXTERNAL)
	#define USE_start_one_task__main
	#define EXT_start_one_task__main
	#define GET_start_one_task__main(fl)  CAL_CMGETAPI( "start_one_task__main" ) 
	#define CAL_start_one_task__main  start_one_task__main
	#define CHK_start_one_task__main  TRUE
	#define EXP_start_one_task__main  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"start_one_task__main", (RTS_UINTPTR)start_one_task__main, 1, 0x7CE1EAB1, 0x01000000) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpGlodonDemostart_one_task__main
	#define EXT_CmpGlodonDemostart_one_task__main
	#define GET_CmpGlodonDemostart_one_task__main  ERR_OK
	#define CAL_CmpGlodonDemostart_one_task__main  start_one_task__main
	#define CHK_CmpGlodonDemostart_one_task__main  TRUE
	#define EXP_CmpGlodonDemostart_one_task__main  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"start_one_task__main", (RTS_UINTPTR)start_one_task__main, 1, 0x7CE1EAB1, 0x01000000) 
#elif defined(CPLUSPLUS)
	#define USE_start_one_task__main
	#define EXT_start_one_task__main
	#define GET_start_one_task__main(fl)  CAL_CMGETAPI( "start_one_task__main" ) 
	#define CAL_start_one_task__main  start_one_task__main
	#define CHK_start_one_task__main  TRUE
	#define EXP_start_one_task__main  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"start_one_task__main", (RTS_UINTPTR)start_one_task__main, 1, 0x7CE1EAB1, 0x01000000) 
#else /* DYNAMIC_LINK */
	#define USE_start_one_task__main  PFSTART_ONE_TASK__MAIN_IEC pfstart_one_task__main;
	#define EXT_start_one_task__main  extern PFSTART_ONE_TASK__MAIN_IEC pfstart_one_task__main;
	#define GET_start_one_task__main(fl)  s_pfCMGetAPI2( "start_one_task__main", (RTS_VOID_FCTPTR *)&pfstart_one_task__main, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0x7CE1EAB1, 0x01000000)
	#define CAL_start_one_task__main  pfstart_one_task__main
	#define CHK_start_one_task__main  (pfstart_one_task__main != NULL)
	#define EXP_start_one_task__main   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"start_one_task__main", (RTS_UINTPTR)start_one_task__main, 1, 0x7CE1EAB1, 0x01000000) 
#endif


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

void CDECL CDECL_EXT update_machine_data__main(update_machine_data_main_struct *p);
typedef void (CDECL CDECL_EXT* PFUPDATE_MACHINE_DATA__MAIN_IEC) (update_machine_data_main_struct *p);
#if defined(CMPGLODONDEMO_NOTIMPLEMENTED) || defined(UPDATE_MACHINE_DATA__MAIN_NOTIMPLEMENTED)
	#define USE_update_machine_data__main
	#define EXT_update_machine_data__main
	#define GET_update_machine_data__main(fl)  ERR_NOTIMPLEMENTED
	#define CAL_update_machine_data__main(p0) 
	#define CHK_update_machine_data__main  FALSE
	#define EXP_update_machine_data__main  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_update_machine_data__main
	#define EXT_update_machine_data__main
	#define GET_update_machine_data__main(fl)  CAL_CMGETAPI( "update_machine_data__main" ) 
	#define CAL_update_machine_data__main  update_machine_data__main
	#define CHK_update_machine_data__main  TRUE
	#define EXP_update_machine_data__main  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"update_machine_data__main", (RTS_UINTPTR)update_machine_data__main, 1, 0x93B879B0, 0x01000000) 
#elif defined(MIXED_LINK) && !defined(CMPGLODONDEMO_EXTERNAL)
	#define USE_update_machine_data__main
	#define EXT_update_machine_data__main
	#define GET_update_machine_data__main(fl)  CAL_CMGETAPI( "update_machine_data__main" ) 
	#define CAL_update_machine_data__main  update_machine_data__main
	#define CHK_update_machine_data__main  TRUE
	#define EXP_update_machine_data__main  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"update_machine_data__main", (RTS_UINTPTR)update_machine_data__main, 1, 0x93B879B0, 0x01000000) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpGlodonDemoupdate_machine_data__main
	#define EXT_CmpGlodonDemoupdate_machine_data__main
	#define GET_CmpGlodonDemoupdate_machine_data__main  ERR_OK
	#define CAL_CmpGlodonDemoupdate_machine_data__main  update_machine_data__main
	#define CHK_CmpGlodonDemoupdate_machine_data__main  TRUE
	#define EXP_CmpGlodonDemoupdate_machine_data__main  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"update_machine_data__main", (RTS_UINTPTR)update_machine_data__main, 1, 0x93B879B0, 0x01000000) 
#elif defined(CPLUSPLUS)
	#define USE_update_machine_data__main
	#define EXT_update_machine_data__main
	#define GET_update_machine_data__main(fl)  CAL_CMGETAPI( "update_machine_data__main" ) 
	#define CAL_update_machine_data__main  update_machine_data__main
	#define CHK_update_machine_data__main  TRUE
	#define EXP_update_machine_data__main  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"update_machine_data__main", (RTS_UINTPTR)update_machine_data__main, 1, 0x93B879B0, 0x01000000) 
#else /* DYNAMIC_LINK */
	#define USE_update_machine_data__main  PFUPDATE_MACHINE_DATA__MAIN_IEC pfupdate_machine_data__main;
	#define EXT_update_machine_data__main  extern PFUPDATE_MACHINE_DATA__MAIN_IEC pfupdate_machine_data__main;
	#define GET_update_machine_data__main(fl)  s_pfCMGetAPI2( "update_machine_data__main", (RTS_VOID_FCTPTR *)&pfupdate_machine_data__main, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0x93B879B0, 0x01000000)
	#define CAL_update_machine_data__main  pfupdate_machine_data__main
	#define CHK_update_machine_data__main  (pfupdate_machine_data__main != NULL)
	#define EXP_update_machine_data__main   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"update_machine_data__main", (RTS_UINTPTR)update_machine_data__main, 1, 0x93B879B0, 0x01000000) 
#endif


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

void CDECL CDECL_EXT update_one_task__main(update_one_task_main_struct *p);
typedef void (CDECL CDECL_EXT* PFUPDATE_ONE_TASK__MAIN_IEC) (update_one_task_main_struct *p);
#if defined(CMPGLODONDEMO_NOTIMPLEMENTED) || defined(UPDATE_ONE_TASK__MAIN_NOTIMPLEMENTED)
	#define USE_update_one_task__main
	#define EXT_update_one_task__main
	#define GET_update_one_task__main(fl)  ERR_NOTIMPLEMENTED
	#define CAL_update_one_task__main(p0) 
	#define CHK_update_one_task__main  FALSE
	#define EXP_update_one_task__main  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_update_one_task__main
	#define EXT_update_one_task__main
	#define GET_update_one_task__main(fl)  CAL_CMGETAPI( "update_one_task__main" ) 
	#define CAL_update_one_task__main  update_one_task__main
	#define CHK_update_one_task__main  TRUE
	#define EXP_update_one_task__main  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"update_one_task__main", (RTS_UINTPTR)update_one_task__main, 1, 0xD5DDFCFA, 0x01000000) 
#elif defined(MIXED_LINK) && !defined(CMPGLODONDEMO_EXTERNAL)
	#define USE_update_one_task__main
	#define EXT_update_one_task__main
	#define GET_update_one_task__main(fl)  CAL_CMGETAPI( "update_one_task__main" ) 
	#define CAL_update_one_task__main  update_one_task__main
	#define CHK_update_one_task__main  TRUE
	#define EXP_update_one_task__main  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"update_one_task__main", (RTS_UINTPTR)update_one_task__main, 1, 0xD5DDFCFA, 0x01000000) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpGlodonDemoupdate_one_task__main
	#define EXT_CmpGlodonDemoupdate_one_task__main
	#define GET_CmpGlodonDemoupdate_one_task__main  ERR_OK
	#define CAL_CmpGlodonDemoupdate_one_task__main  update_one_task__main
	#define CHK_CmpGlodonDemoupdate_one_task__main  TRUE
	#define EXP_CmpGlodonDemoupdate_one_task__main  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"update_one_task__main", (RTS_UINTPTR)update_one_task__main, 1, 0xD5DDFCFA, 0x01000000) 
#elif defined(CPLUSPLUS)
	#define USE_update_one_task__main
	#define EXT_update_one_task__main
	#define GET_update_one_task__main(fl)  CAL_CMGETAPI( "update_one_task__main" ) 
	#define CAL_update_one_task__main  update_one_task__main
	#define CHK_update_one_task__main  TRUE
	#define EXP_update_one_task__main  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"update_one_task__main", (RTS_UINTPTR)update_one_task__main, 1, 0xD5DDFCFA, 0x01000000) 
#else /* DYNAMIC_LINK */
	#define USE_update_one_task__main  PFUPDATE_ONE_TASK__MAIN_IEC pfupdate_one_task__main;
	#define EXT_update_one_task__main  extern PFUPDATE_ONE_TASK__MAIN_IEC pfupdate_one_task__main;
	#define GET_update_one_task__main(fl)  s_pfCMGetAPI2( "update_one_task__main", (RTS_VOID_FCTPTR *)&pfupdate_one_task__main, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0xD5DDFCFA, 0x01000000)
	#define CAL_update_one_task__main  pfupdate_one_task__main
	#define CHK_update_one_task__main  (pfupdate_one_task__main != NULL)
	#define EXP_update_one_task__main   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"update_one_task__main", (RTS_UINTPTR)update_one_task__main, 1, 0xD5DDFCFA, 0x01000000) 
#endif


#ifdef __cplusplus
}
#endif

/** EXTERN LIB SECTION END **/




typedef struct
{
	IBase_C *pBase;
} ICmpGlodonDemo_C;

#ifdef CPLUSPLUS
class ICmpGlodonDemo : public IBase
{
	public:
};
	#ifndef ITF_CmpGlodonDemo
		#define ITF_CmpGlodonDemo static ICmpGlodonDemo *pICmpGlodonDemo = NULL;
	#endif
	#define EXTITF_CmpGlodonDemo
#else	/*CPLUSPLUS*/
	typedef ICmpGlodonDemo_C		ICmpGlodonDemo;
	#ifndef ITF_CmpGlodonDemo
		#define ITF_CmpGlodonDemo
	#endif
	#define EXTITF_CmpGlodonDemo
#endif

#ifdef CPLUSPLUS_ONLY
  #undef CPLUSPLUS_ONLY
#endif

#endif /*_CMPGLODONDEMOITF_H_*/
