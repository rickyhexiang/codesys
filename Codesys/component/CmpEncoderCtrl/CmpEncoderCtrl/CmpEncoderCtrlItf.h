 /**
 * <interfacename>CmpEncoderCtrl</interfacename>
 * <description></description>
 *
 * <copyright></copyright>
 */


	
	
#ifndef _CMPENCODERCTRLITF_H_
#define _CMPENCODERCTRLITF_H_

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
 * <description>configencoder__main</description>
 */
typedef struct tagconfigencoder_struct
{
	void* __VFTABLEPOINTER;				/* Pointer to virtual function table */

	/* Member variables of ConfigEncoder */

	RTS_IEC_BOOL A;						/* VAR_INPUT */	
	RTS_IEC_BOOL B;						/* VAR_INPUT */	
	RTS_IEC_BOOL Z;						/* VAR_INPUT */	
} configencoder_struct;

/**
 * <description>configencoder_main</description>
 */
typedef struct tagconfigencoder_main_struct
{
	configencoder_struct *pInstance;	/* VAR_INPUT */	
} configencoder_main_struct;

void CDECL CDECL_EXT configencoder__main(configencoder_main_struct *p);
typedef void (CDECL CDECL_EXT* PFCONFIGENCODER__MAIN_IEC) (configencoder_main_struct *p);
#if defined(CMPENCODERCTRL_NOTIMPLEMENTED) || defined(CONFIGENCODER__MAIN_NOTIMPLEMENTED)
	#define USE_configencoder__main
	#define EXT_configencoder__main
	#define GET_configencoder__main(fl)  ERR_NOTIMPLEMENTED
	#define CAL_configencoder__main(p0) 
	#define CHK_configencoder__main  FALSE
	#define EXP_configencoder__main  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_configencoder__main
	#define EXT_configencoder__main
	#define GET_configencoder__main(fl)  CAL_CMGETAPI( "configencoder__main" ) 
	#define CAL_configencoder__main  configencoder__main
	#define CHK_configencoder__main  TRUE
	#define EXP_configencoder__main  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"configencoder__main", (RTS_UINTPTR)configencoder__main, 1, 0x06280A78, 0x01000000) 
#elif defined(MIXED_LINK) && !defined(CMPENCODERCTRL_EXTERNAL)
	#define USE_configencoder__main
	#define EXT_configencoder__main
	#define GET_configencoder__main(fl)  CAL_CMGETAPI( "configencoder__main" ) 
	#define CAL_configencoder__main  configencoder__main
	#define CHK_configencoder__main  TRUE
	#define EXP_configencoder__main  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"configencoder__main", (RTS_UINTPTR)configencoder__main, 1, 0x06280A78, 0x01000000) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpEncoderCtrlconfigencoder__main
	#define EXT_CmpEncoderCtrlconfigencoder__main
	#define GET_CmpEncoderCtrlconfigencoder__main  ERR_OK
	#define CAL_CmpEncoderCtrlconfigencoder__main  configencoder__main
	#define CHK_CmpEncoderCtrlconfigencoder__main  TRUE
	#define EXP_CmpEncoderCtrlconfigencoder__main  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"configencoder__main", (RTS_UINTPTR)configencoder__main, 1, 0x06280A78, 0x01000000) 
#elif defined(CPLUSPLUS)
	#define USE_configencoder__main
	#define EXT_configencoder__main
	#define GET_configencoder__main(fl)  CAL_CMGETAPI( "configencoder__main" ) 
	#define CAL_configencoder__main  configencoder__main
	#define CHK_configencoder__main  TRUE
	#define EXP_configencoder__main  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"configencoder__main", (RTS_UINTPTR)configencoder__main, 1, 0x06280A78, 0x01000000) 
#else /* DYNAMIC_LINK */
	#define USE_configencoder__main  PFCONFIGENCODER__MAIN_IEC pfconfigencoder__main;
	#define EXT_configencoder__main  extern PFCONFIGENCODER__MAIN_IEC pfconfigencoder__main;
	#define GET_configencoder__main(fl)  s_pfCMGetAPI2( "configencoder__main", (RTS_VOID_FCTPTR *)&pfconfigencoder__main, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0x06280A78, 0x01000000)
	#define CAL_configencoder__main  pfconfigencoder__main
	#define CHK_configencoder__main  (pfconfigencoder__main != NULL)
	#define EXP_configencoder__main   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"configencoder__main", (RTS_UINTPTR)configencoder__main, 1, 0x06280A78, 0x01000000) 
#endif


/**
 * <description>readencodercountera__main</description>
 */
typedef struct tagreadencodercountera_struct
{
	void* __VFTABLEPOINTER;				/* Pointer to virtual function table */

	/* Member variables of ReadEncoderCounterA */

	RTS_IEC_DINT CounterA;				/* VAR_OUTPUT */	
} readencodercountera_struct;

/**
 * <description>readencodercountera_main</description>
 */
typedef struct tagreadencodercountera_main_struct
{
	readencodercountera_struct *pInstance;	/* VAR_INPUT */	
} readencodercountera_main_struct;

void CDECL CDECL_EXT readencodercountera__main(readencodercountera_main_struct *p);
typedef void (CDECL CDECL_EXT* PFREADENCODERCOUNTERA__MAIN_IEC) (readencodercountera_main_struct *p);
#if defined(CMPENCODERCTRL_NOTIMPLEMENTED) || defined(READENCODERCOUNTERA__MAIN_NOTIMPLEMENTED)
	#define USE_readencodercountera__main
	#define EXT_readencodercountera__main
	#define GET_readencodercountera__main(fl)  ERR_NOTIMPLEMENTED
	#define CAL_readencodercountera__main(p0) 
	#define CHK_readencodercountera__main  FALSE
	#define EXP_readencodercountera__main  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_readencodercountera__main
	#define EXT_readencodercountera__main
	#define GET_readencodercountera__main(fl)  CAL_CMGETAPI( "readencodercountera__main" ) 
	#define CAL_readencodercountera__main  readencodercountera__main
	#define CHK_readencodercountera__main  TRUE
	#define EXP_readencodercountera__main  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"readencodercountera__main", (RTS_UINTPTR)readencodercountera__main, 1, 0x9DA91CE6, 0x01000000) 
#elif defined(MIXED_LINK) && !defined(CMPENCODERCTRL_EXTERNAL)
	#define USE_readencodercountera__main
	#define EXT_readencodercountera__main
	#define GET_readencodercountera__main(fl)  CAL_CMGETAPI( "readencodercountera__main" ) 
	#define CAL_readencodercountera__main  readencodercountera__main
	#define CHK_readencodercountera__main  TRUE
	#define EXP_readencodercountera__main  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"readencodercountera__main", (RTS_UINTPTR)readencodercountera__main, 1, 0x9DA91CE6, 0x01000000) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpEncoderCtrlreadencodercountera__main
	#define EXT_CmpEncoderCtrlreadencodercountera__main
	#define GET_CmpEncoderCtrlreadencodercountera__main  ERR_OK
	#define CAL_CmpEncoderCtrlreadencodercountera__main  readencodercountera__main
	#define CHK_CmpEncoderCtrlreadencodercountera__main  TRUE
	#define EXP_CmpEncoderCtrlreadencodercountera__main  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"readencodercountera__main", (RTS_UINTPTR)readencodercountera__main, 1, 0x9DA91CE6, 0x01000000) 
#elif defined(CPLUSPLUS)
	#define USE_readencodercountera__main
	#define EXT_readencodercountera__main
	#define GET_readencodercountera__main(fl)  CAL_CMGETAPI( "readencodercountera__main" ) 
	#define CAL_readencodercountera__main  readencodercountera__main
	#define CHK_readencodercountera__main  TRUE
	#define EXP_readencodercountera__main  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"readencodercountera__main", (RTS_UINTPTR)readencodercountera__main, 1, 0x9DA91CE6, 0x01000000) 
#else /* DYNAMIC_LINK */
	#define USE_readencodercountera__main  PFREADENCODERCOUNTERA__MAIN_IEC pfreadencodercountera__main;
	#define EXT_readencodercountera__main  extern PFREADENCODERCOUNTERA__MAIN_IEC pfreadencodercountera__main;
	#define GET_readencodercountera__main(fl)  s_pfCMGetAPI2( "readencodercountera__main", (RTS_VOID_FCTPTR *)&pfreadencodercountera__main, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0x9DA91CE6, 0x01000000)
	#define CAL_readencodercountera__main  pfreadencodercountera__main
	#define CHK_readencodercountera__main  (pfreadencodercountera__main != NULL)
	#define EXP_readencodercountera__main   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"readencodercountera__main", (RTS_UINTPTR)readencodercountera__main, 1, 0x9DA91CE6, 0x01000000) 
#endif


/**
 * <description>readencodercounterz__main</description>
 */
typedef struct tagreadencodercounterz_struct
{
	void* __VFTABLEPOINTER;				/* Pointer to virtual function table */

	/* Member variables of ReadEncoderCounterZ */

	RTS_IEC_DINT CounterZ;				/* VAR_OUTPUT */	
} readencodercounterz_struct;

/**
 * <description>readencodercounterz_main</description>
 */
typedef struct tagreadencodercounterz_main_struct
{
	readencodercounterz_struct *pInstance;	/* VAR_INPUT */	
} readencodercounterz_main_struct;

void CDECL CDECL_EXT readencodercounterz__main(readencodercounterz_main_struct *p);
typedef void (CDECL CDECL_EXT* PFREADENCODERCOUNTERZ__MAIN_IEC) (readencodercounterz_main_struct *p);
#if defined(CMPENCODERCTRL_NOTIMPLEMENTED) || defined(READENCODERCOUNTERZ__MAIN_NOTIMPLEMENTED)
	#define USE_readencodercounterz__main
	#define EXT_readencodercounterz__main
	#define GET_readencodercounterz__main(fl)  ERR_NOTIMPLEMENTED
	#define CAL_readencodercounterz__main(p0) 
	#define CHK_readencodercounterz__main  FALSE
	#define EXP_readencodercounterz__main  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_readencodercounterz__main
	#define EXT_readencodercounterz__main
	#define GET_readencodercounterz__main(fl)  CAL_CMGETAPI( "readencodercounterz__main" ) 
	#define CAL_readencodercounterz__main  readencodercounterz__main
	#define CHK_readencodercounterz__main  TRUE
	#define EXP_readencodercounterz__main  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"readencodercounterz__main", (RTS_UINTPTR)readencodercounterz__main, 1, 0x3A4B34EB, 0x01000000) 
#elif defined(MIXED_LINK) && !defined(CMPENCODERCTRL_EXTERNAL)
	#define USE_readencodercounterz__main
	#define EXT_readencodercounterz__main
	#define GET_readencodercounterz__main(fl)  CAL_CMGETAPI( "readencodercounterz__main" ) 
	#define CAL_readencodercounterz__main  readencodercounterz__main
	#define CHK_readencodercounterz__main  TRUE
	#define EXP_readencodercounterz__main  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"readencodercounterz__main", (RTS_UINTPTR)readencodercounterz__main, 1, 0x3A4B34EB, 0x01000000) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpEncoderCtrlreadencodercounterz__main
	#define EXT_CmpEncoderCtrlreadencodercounterz__main
	#define GET_CmpEncoderCtrlreadencodercounterz__main  ERR_OK
	#define CAL_CmpEncoderCtrlreadencodercounterz__main  readencodercounterz__main
	#define CHK_CmpEncoderCtrlreadencodercounterz__main  TRUE
	#define EXP_CmpEncoderCtrlreadencodercounterz__main  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"readencodercounterz__main", (RTS_UINTPTR)readencodercounterz__main, 1, 0x3A4B34EB, 0x01000000) 
#elif defined(CPLUSPLUS)
	#define USE_readencodercounterz__main
	#define EXT_readencodercounterz__main
	#define GET_readencodercounterz__main(fl)  CAL_CMGETAPI( "readencodercounterz__main" ) 
	#define CAL_readencodercounterz__main  readencodercounterz__main
	#define CHK_readencodercounterz__main  TRUE
	#define EXP_readencodercounterz__main  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"readencodercounterz__main", (RTS_UINTPTR)readencodercounterz__main, 1, 0x3A4B34EB, 0x01000000) 
#else /* DYNAMIC_LINK */
	#define USE_readencodercounterz__main  PFREADENCODERCOUNTERZ__MAIN_IEC pfreadencodercounterz__main;
	#define EXT_readencodercounterz__main  extern PFREADENCODERCOUNTERZ__MAIN_IEC pfreadencodercounterz__main;
	#define GET_readencodercounterz__main(fl)  s_pfCMGetAPI2( "readencodercounterz__main", (RTS_VOID_FCTPTR *)&pfreadencodercounterz__main, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0x3A4B34EB, 0x01000000)
	#define CAL_readencodercounterz__main  pfreadencodercounterz__main
	#define CHK_readencodercounterz__main  (pfreadencodercounterz__main != NULL)
	#define EXP_readencodercounterz__main   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"readencodercounterz__main", (RTS_UINTPTR)readencodercounterz__main, 1, 0x3A4B34EB, 0x01000000) 
#endif


/**
 * <description>readencoderdirection__main</description>
 */
typedef struct tagreadencoderdirection_struct
{
	void* __VFTABLEPOINTER;				/* Pointer to virtual function table */

	/* Member variables of ReadEncoderDirection */

	RTS_IEC_BOOL Direction;				/* VAR_OUTPUT */	
} readencoderdirection_struct;

/**
 * <description>readencoderdirection_main</description>
 */
typedef struct tagreadencoderdirection_main_struct
{
	readencoderdirection_struct *pInstance;	/* VAR_INPUT */	
} readencoderdirection_main_struct;

void CDECL CDECL_EXT readencoderdirection__main(readencoderdirection_main_struct *p);
typedef void (CDECL CDECL_EXT* PFREADENCODERDIRECTION__MAIN_IEC) (readencoderdirection_main_struct *p);
#if defined(CMPENCODERCTRL_NOTIMPLEMENTED) || defined(READENCODERDIRECTION__MAIN_NOTIMPLEMENTED)
	#define USE_readencoderdirection__main
	#define EXT_readencoderdirection__main
	#define GET_readencoderdirection__main(fl)  ERR_NOTIMPLEMENTED
	#define CAL_readencoderdirection__main(p0) 
	#define CHK_readencoderdirection__main  FALSE
	#define EXP_readencoderdirection__main  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_readencoderdirection__main
	#define EXT_readencoderdirection__main
	#define GET_readencoderdirection__main(fl)  CAL_CMGETAPI( "readencoderdirection__main" ) 
	#define CAL_readencoderdirection__main  readencoderdirection__main
	#define CHK_readencoderdirection__main  TRUE
	#define EXP_readencoderdirection__main  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"readencoderdirection__main", (RTS_UINTPTR)readencoderdirection__main, 1, 0x6DFB027B, 0x01000000) 
#elif defined(MIXED_LINK) && !defined(CMPENCODERCTRL_EXTERNAL)
	#define USE_readencoderdirection__main
	#define EXT_readencoderdirection__main
	#define GET_readencoderdirection__main(fl)  CAL_CMGETAPI( "readencoderdirection__main" ) 
	#define CAL_readencoderdirection__main  readencoderdirection__main
	#define CHK_readencoderdirection__main  TRUE
	#define EXP_readencoderdirection__main  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"readencoderdirection__main", (RTS_UINTPTR)readencoderdirection__main, 1, 0x6DFB027B, 0x01000000) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpEncoderCtrlreadencoderdirection__main
	#define EXT_CmpEncoderCtrlreadencoderdirection__main
	#define GET_CmpEncoderCtrlreadencoderdirection__main  ERR_OK
	#define CAL_CmpEncoderCtrlreadencoderdirection__main  readencoderdirection__main
	#define CHK_CmpEncoderCtrlreadencoderdirection__main  TRUE
	#define EXP_CmpEncoderCtrlreadencoderdirection__main  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"readencoderdirection__main", (RTS_UINTPTR)readencoderdirection__main, 1, 0x6DFB027B, 0x01000000) 
#elif defined(CPLUSPLUS)
	#define USE_readencoderdirection__main
	#define EXT_readencoderdirection__main
	#define GET_readencoderdirection__main(fl)  CAL_CMGETAPI( "readencoderdirection__main" ) 
	#define CAL_readencoderdirection__main  readencoderdirection__main
	#define CHK_readencoderdirection__main  TRUE
	#define EXP_readencoderdirection__main  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"readencoderdirection__main", (RTS_UINTPTR)readencoderdirection__main, 1, 0x6DFB027B, 0x01000000) 
#else /* DYNAMIC_LINK */
	#define USE_readencoderdirection__main  PFREADENCODERDIRECTION__MAIN_IEC pfreadencoderdirection__main;
	#define EXT_readencoderdirection__main  extern PFREADENCODERDIRECTION__MAIN_IEC pfreadencoderdirection__main;
	#define GET_readencoderdirection__main(fl)  s_pfCMGetAPI2( "readencoderdirection__main", (RTS_VOID_FCTPTR *)&pfreadencoderdirection__main, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0x6DFB027B, 0x01000000)
	#define CAL_readencoderdirection__main  pfreadencoderdirection__main
	#define CHK_readencoderdirection__main  (pfreadencoderdirection__main != NULL)
	#define EXP_readencoderdirection__main   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"readencoderdirection__main", (RTS_UINTPTR)readencoderdirection__main, 1, 0x6DFB027B, 0x01000000) 
#endif


/**
 * <description>setencodercounter__main</description>
 */
typedef struct tagsetencodercounter_struct
{
	void* __VFTABLEPOINTER;				/* Pointer to virtual function table */

	/* Member variables of SetEncoderCounter */

	RTS_IEC_DINT CounterA;				/* VAR_INPUT */	
	RTS_IEC_DINT CounterZ;				/* VAR_INPUT */	
} setencodercounter_struct;

/**
 * <description>setencodercounter_main</description>
 */
typedef struct tagsetencodercounter_main_struct
{
	setencodercounter_struct *pInstance;	/* VAR_INPUT */	
} setencodercounter_main_struct;

void CDECL CDECL_EXT setencodercounter__main(setencodercounter_main_struct *p);
typedef void (CDECL CDECL_EXT* PFSETENCODERCOUNTER__MAIN_IEC) (setencodercounter_main_struct *p);
#if defined(CMPENCODERCTRL_NOTIMPLEMENTED) || defined(SETENCODERCOUNTER__MAIN_NOTIMPLEMENTED)
	#define USE_setencodercounter__main
	#define EXT_setencodercounter__main
	#define GET_setencodercounter__main(fl)  ERR_NOTIMPLEMENTED
	#define CAL_setencodercounter__main(p0) 
	#define CHK_setencodercounter__main  FALSE
	#define EXP_setencodercounter__main  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_setencodercounter__main
	#define EXT_setencodercounter__main
	#define GET_setencodercounter__main(fl)  CAL_CMGETAPI( "setencodercounter__main" ) 
	#define CAL_setencodercounter__main  setencodercounter__main
	#define CHK_setencodercounter__main  TRUE
	#define EXP_setencodercounter__main  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"setencodercounter__main", (RTS_UINTPTR)setencodercounter__main, 1, 0x7E81583C, 0x01000000) 
#elif defined(MIXED_LINK) && !defined(CMPENCODERCTRL_EXTERNAL)
	#define USE_setencodercounter__main
	#define EXT_setencodercounter__main
	#define GET_setencodercounter__main(fl)  CAL_CMGETAPI( "setencodercounter__main" ) 
	#define CAL_setencodercounter__main  setencodercounter__main
	#define CHK_setencodercounter__main  TRUE
	#define EXP_setencodercounter__main  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"setencodercounter__main", (RTS_UINTPTR)setencodercounter__main, 1, 0x7E81583C, 0x01000000) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpEncoderCtrlsetencodercounter__main
	#define EXT_CmpEncoderCtrlsetencodercounter__main
	#define GET_CmpEncoderCtrlsetencodercounter__main  ERR_OK
	#define CAL_CmpEncoderCtrlsetencodercounter__main  setencodercounter__main
	#define CHK_CmpEncoderCtrlsetencodercounter__main  TRUE
	#define EXP_CmpEncoderCtrlsetencodercounter__main  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"setencodercounter__main", (RTS_UINTPTR)setencodercounter__main, 1, 0x7E81583C, 0x01000000) 
#elif defined(CPLUSPLUS)
	#define USE_setencodercounter__main
	#define EXT_setencodercounter__main
	#define GET_setencodercounter__main(fl)  CAL_CMGETAPI( "setencodercounter__main" ) 
	#define CAL_setencodercounter__main  setencodercounter__main
	#define CHK_setencodercounter__main  TRUE
	#define EXP_setencodercounter__main  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"setencodercounter__main", (RTS_UINTPTR)setencodercounter__main, 1, 0x7E81583C, 0x01000000) 
#else /* DYNAMIC_LINK */
	#define USE_setencodercounter__main  PFSETENCODERCOUNTER__MAIN_IEC pfsetencodercounter__main;
	#define EXT_setencodercounter__main  extern PFSETENCODERCOUNTER__MAIN_IEC pfsetencodercounter__main;
	#define GET_setencodercounter__main(fl)  s_pfCMGetAPI2( "setencodercounter__main", (RTS_VOID_FCTPTR *)&pfsetencodercounter__main, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0x7E81583C, 0x01000000)
	#define CAL_setencodercounter__main  pfsetencodercounter__main
	#define CHK_setencodercounter__main  (pfsetencodercounter__main != NULL)
	#define EXP_setencodercounter__main   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"setencodercounter__main", (RTS_UINTPTR)setencodercounter__main, 1, 0x7E81583C, 0x01000000) 
#endif


#ifdef __cplusplus
}
#endif

/** EXTERN LIB SECTION END **/




typedef struct
{
	IBase_C *pBase;
} ICmpEncoderCtrl_C;

#ifdef CPLUSPLUS
class ICmpEncoderCtrl : public IBase
{
	public:
};
	#ifndef ITF_CmpEncoderCtrl
		#define ITF_CmpEncoderCtrl static ICmpEncoderCtrl *pICmpEncoderCtrl = NULL;
	#endif
	#define EXTITF_CmpEncoderCtrl
#else	/*CPLUSPLUS*/
	typedef ICmpEncoderCtrl_C		ICmpEncoderCtrl;
	#ifndef ITF_CmpEncoderCtrl
		#define ITF_CmpEncoderCtrl
	#endif
	#define EXTITF_CmpEncoderCtrl
#endif

#ifdef CPLUSPLUS_ONLY
  #undef CPLUSPLUS_ONLY
#endif

#endif /*_CMPENCODERCTRLITF_H_*/
