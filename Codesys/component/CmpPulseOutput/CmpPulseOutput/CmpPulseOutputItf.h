 /**
 * <interfacename>CmpPulseOutput</interfacename>
 * <description></description>
 *
 * <copyright></copyright>
 */


	
	
#ifndef _CMPPULSEOUTPUTITF_H_
#define _CMPPULSEOUTPUTITF_H_

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
 * <description>ispulseover__main</description>
 */
typedef struct tagispulseover_struct
{
	void* __VFTABLEPOINTER;				/* Pointer to virtual function table */

	/* Member variables of IsPulseOver */

	RTS_IEC_BOOL isOver;				/* VAR_OUTPUT */	
} ispulseover_struct;

/**
 * <description>ispulseover_main</description>
 */
typedef struct tagispulseover_main_struct
{
	ispulseover_struct *pInstance;		/* VAR_INPUT */	
} ispulseover_main_struct;

void CDECL CDECL_EXT ispulseover__main(ispulseover_main_struct *p);
typedef void (CDECL CDECL_EXT* PFISPULSEOVER__MAIN_IEC) (ispulseover_main_struct *p);
#if defined(CMPPULSEOUTPUT_NOTIMPLEMENTED) || defined(ISPULSEOVER__MAIN_NOTIMPLEMENTED)
	#define USE_ispulseover__main
	#define EXT_ispulseover__main
	#define GET_ispulseover__main(fl)  ERR_NOTIMPLEMENTED
	#define CAL_ispulseover__main(p0) 
	#define CHK_ispulseover__main  FALSE
	#define EXP_ispulseover__main  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_ispulseover__main
	#define EXT_ispulseover__main
	#define GET_ispulseover__main(fl)  CAL_CMGETAPI( "ispulseover__main" ) 
	#define CAL_ispulseover__main  ispulseover__main
	#define CHK_ispulseover__main  TRUE
	#define EXP_ispulseover__main  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"ispulseover__main", (RTS_UINTPTR)ispulseover__main, 1, 0xCD4A0220, 0x01000000) 
#elif defined(MIXED_LINK) && !defined(CMPPULSEOUTPUT_EXTERNAL)
	#define USE_ispulseover__main
	#define EXT_ispulseover__main
	#define GET_ispulseover__main(fl)  CAL_CMGETAPI( "ispulseover__main" ) 
	#define CAL_ispulseover__main  ispulseover__main
	#define CHK_ispulseover__main  TRUE
	#define EXP_ispulseover__main  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"ispulseover__main", (RTS_UINTPTR)ispulseover__main, 1, 0xCD4A0220, 0x01000000) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpPulseOutputispulseover__main
	#define EXT_CmpPulseOutputispulseover__main
	#define GET_CmpPulseOutputispulseover__main  ERR_OK
	#define CAL_CmpPulseOutputispulseover__main  ispulseover__main
	#define CHK_CmpPulseOutputispulseover__main  TRUE
	#define EXP_CmpPulseOutputispulseover__main  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"ispulseover__main", (RTS_UINTPTR)ispulseover__main, 1, 0xCD4A0220, 0x01000000) 
#elif defined(CPLUSPLUS)
	#define USE_ispulseover__main
	#define EXT_ispulseover__main
	#define GET_ispulseover__main(fl)  CAL_CMGETAPI( "ispulseover__main" ) 
	#define CAL_ispulseover__main  ispulseover__main
	#define CHK_ispulseover__main  TRUE
	#define EXP_ispulseover__main  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"ispulseover__main", (RTS_UINTPTR)ispulseover__main, 1, 0xCD4A0220, 0x01000000) 
#else /* DYNAMIC_LINK */
	#define USE_ispulseover__main  PFISPULSEOVER__MAIN_IEC pfispulseover__main;
	#define EXT_ispulseover__main  extern PFISPULSEOVER__MAIN_IEC pfispulseover__main;
	#define GET_ispulseover__main(fl)  s_pfCMGetAPI2( "ispulseover__main", (RTS_VOID_FCTPTR *)&pfispulseover__main, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0xCD4A0220, 0x01000000)
	#define CAL_ispulseover__main  pfispulseover__main
	#define CHK_ispulseover__main  (pfispulseover__main != NULL)
	#define EXP_ispulseover__main   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"ispulseover__main", (RTS_UINTPTR)ispulseover__main, 1, 0xCD4A0220, 0x01000000) 
#endif


/**
 * <description>setpulseamountandstart__main</description>
 */
typedef struct tagsetpulseamountandstart_struct
{
	void* __VFTABLEPOINTER;				/* Pointer to virtual function table */

	/* Member variables of SetPulseAmountAndStart */

	RTS_IEC_DWORD amount;				/* VAR_INPUT */	
} setpulseamountandstart_struct;

/**
 * <description>setpulseamountandstart_main</description>
 */
typedef struct tagsetpulseamountandstart_main_struct
{
	setpulseamountandstart_struct *pInstance;	/* VAR_INPUT */	
} setpulseamountandstart_main_struct;

void CDECL CDECL_EXT setpulseamountandstart__main(setpulseamountandstart_main_struct *p);
typedef void (CDECL CDECL_EXT* PFSETPULSEAMOUNTANDSTART__MAIN_IEC) (setpulseamountandstart_main_struct *p);
#if defined(CMPPULSEOUTPUT_NOTIMPLEMENTED) || defined(SETPULSEAMOUNTANDSTART__MAIN_NOTIMPLEMENTED)
	#define USE_setpulseamountandstart__main
	#define EXT_setpulseamountandstart__main
	#define GET_setpulseamountandstart__main(fl)  ERR_NOTIMPLEMENTED
	#define CAL_setpulseamountandstart__main(p0) 
	#define CHK_setpulseamountandstart__main  FALSE
	#define EXP_setpulseamountandstart__main  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_setpulseamountandstart__main
	#define EXT_setpulseamountandstart__main
	#define GET_setpulseamountandstart__main(fl)  CAL_CMGETAPI( "setpulseamountandstart__main" ) 
	#define CAL_setpulseamountandstart__main  setpulseamountandstart__main
	#define CHK_setpulseamountandstart__main  TRUE
	#define EXP_setpulseamountandstart__main  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"setpulseamountandstart__main", (RTS_UINTPTR)setpulseamountandstart__main, 1, 0x32C1BCFE, 0x01000000) 
#elif defined(MIXED_LINK) && !defined(CMPPULSEOUTPUT_EXTERNAL)
	#define USE_setpulseamountandstart__main
	#define EXT_setpulseamountandstart__main
	#define GET_setpulseamountandstart__main(fl)  CAL_CMGETAPI( "setpulseamountandstart__main" ) 
	#define CAL_setpulseamountandstart__main  setpulseamountandstart__main
	#define CHK_setpulseamountandstart__main  TRUE
	#define EXP_setpulseamountandstart__main  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"setpulseamountandstart__main", (RTS_UINTPTR)setpulseamountandstart__main, 1, 0x32C1BCFE, 0x01000000) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpPulseOutputsetpulseamountandstart__main
	#define EXT_CmpPulseOutputsetpulseamountandstart__main
	#define GET_CmpPulseOutputsetpulseamountandstart__main  ERR_OK
	#define CAL_CmpPulseOutputsetpulseamountandstart__main  setpulseamountandstart__main
	#define CHK_CmpPulseOutputsetpulseamountandstart__main  TRUE
	#define EXP_CmpPulseOutputsetpulseamountandstart__main  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"setpulseamountandstart__main", (RTS_UINTPTR)setpulseamountandstart__main, 1, 0x32C1BCFE, 0x01000000) 
#elif defined(CPLUSPLUS)
	#define USE_setpulseamountandstart__main
	#define EXT_setpulseamountandstart__main
	#define GET_setpulseamountandstart__main(fl)  CAL_CMGETAPI( "setpulseamountandstart__main" ) 
	#define CAL_setpulseamountandstart__main  setpulseamountandstart__main
	#define CHK_setpulseamountandstart__main  TRUE
	#define EXP_setpulseamountandstart__main  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"setpulseamountandstart__main", (RTS_UINTPTR)setpulseamountandstart__main, 1, 0x32C1BCFE, 0x01000000) 
#else /* DYNAMIC_LINK */
	#define USE_setpulseamountandstart__main  PFSETPULSEAMOUNTANDSTART__MAIN_IEC pfsetpulseamountandstart__main;
	#define EXT_setpulseamountandstart__main  extern PFSETPULSEAMOUNTANDSTART__MAIN_IEC pfsetpulseamountandstart__main;
	#define GET_setpulseamountandstart__main(fl)  s_pfCMGetAPI2( "setpulseamountandstart__main", (RTS_VOID_FCTPTR *)&pfsetpulseamountandstart__main, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0x32C1BCFE, 0x01000000)
	#define CAL_setpulseamountandstart__main  pfsetpulseamountandstart__main
	#define CHK_setpulseamountandstart__main  (pfsetpulseamountandstart__main != NULL)
	#define EXP_setpulseamountandstart__main   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"setpulseamountandstart__main", (RTS_UINTPTR)setpulseamountandstart__main, 1, 0x32C1BCFE, 0x01000000) 
#endif


/**
 * <description>setpulsefreq__main</description>
 */
typedef struct tagsetpulsefreq_struct
{
	void* __VFTABLEPOINTER;				/* Pointer to virtual function table */

	/* Member variables of SetPulseFreq */

	RTS_IEC_DWORD freq;					/* VAR_INPUT */	
} setpulsefreq_struct;

/**
 * <description>setpulsefreq_main</description>
 */
typedef struct tagsetpulsefreq_main_struct
{
	setpulsefreq_struct *pInstance;		/* VAR_INPUT */	
} setpulsefreq_main_struct;

void CDECL CDECL_EXT setpulsefreq__main(setpulsefreq_main_struct *p);
typedef void (CDECL CDECL_EXT* PFSETPULSEFREQ__MAIN_IEC) (setpulsefreq_main_struct *p);
#if defined(CMPPULSEOUTPUT_NOTIMPLEMENTED) || defined(SETPULSEFREQ__MAIN_NOTIMPLEMENTED)
	#define USE_setpulsefreq__main
	#define EXT_setpulsefreq__main
	#define GET_setpulsefreq__main(fl)  ERR_NOTIMPLEMENTED
	#define CAL_setpulsefreq__main(p0) 
	#define CHK_setpulsefreq__main  FALSE
	#define EXP_setpulsefreq__main  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_setpulsefreq__main
	#define EXT_setpulsefreq__main
	#define GET_setpulsefreq__main(fl)  CAL_CMGETAPI( "setpulsefreq__main" ) 
	#define CAL_setpulsefreq__main  setpulsefreq__main
	#define CHK_setpulsefreq__main  TRUE
	#define EXP_setpulsefreq__main  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"setpulsefreq__main", (RTS_UINTPTR)setpulsefreq__main, 1, 0x1B741B61, 0x01000000) 
#elif defined(MIXED_LINK) && !defined(CMPPULSEOUTPUT_EXTERNAL)
	#define USE_setpulsefreq__main
	#define EXT_setpulsefreq__main
	#define GET_setpulsefreq__main(fl)  CAL_CMGETAPI( "setpulsefreq__main" ) 
	#define CAL_setpulsefreq__main  setpulsefreq__main
	#define CHK_setpulsefreq__main  TRUE
	#define EXP_setpulsefreq__main  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"setpulsefreq__main", (RTS_UINTPTR)setpulsefreq__main, 1, 0x1B741B61, 0x01000000) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpPulseOutputsetpulsefreq__main
	#define EXT_CmpPulseOutputsetpulsefreq__main
	#define GET_CmpPulseOutputsetpulsefreq__main  ERR_OK
	#define CAL_CmpPulseOutputsetpulsefreq__main  setpulsefreq__main
	#define CHK_CmpPulseOutputsetpulsefreq__main  TRUE
	#define EXP_CmpPulseOutputsetpulsefreq__main  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"setpulsefreq__main", (RTS_UINTPTR)setpulsefreq__main, 1, 0x1B741B61, 0x01000000) 
#elif defined(CPLUSPLUS)
	#define USE_setpulsefreq__main
	#define EXT_setpulsefreq__main
	#define GET_setpulsefreq__main(fl)  CAL_CMGETAPI( "setpulsefreq__main" ) 
	#define CAL_setpulsefreq__main  setpulsefreq__main
	#define CHK_setpulsefreq__main  TRUE
	#define EXP_setpulsefreq__main  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"setpulsefreq__main", (RTS_UINTPTR)setpulsefreq__main, 1, 0x1B741B61, 0x01000000) 
#else /* DYNAMIC_LINK */
	#define USE_setpulsefreq__main  PFSETPULSEFREQ__MAIN_IEC pfsetpulsefreq__main;
	#define EXT_setpulsefreq__main  extern PFSETPULSEFREQ__MAIN_IEC pfsetpulsefreq__main;
	#define GET_setpulsefreq__main(fl)  s_pfCMGetAPI2( "setpulsefreq__main", (RTS_VOID_FCTPTR *)&pfsetpulsefreq__main, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0x1B741B61, 0x01000000)
	#define CAL_setpulsefreq__main  pfsetpulsefreq__main
	#define CHK_setpulsefreq__main  (pfsetpulsefreq__main != NULL)
	#define EXP_setpulsefreq__main   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"setpulsefreq__main", (RTS_UINTPTR)setpulsefreq__main, 1, 0x1B741B61, 0x01000000) 
#endif


/**
 * <description>stoppulse__main</description>
 */
typedef struct tagstoppulse_struct
{
	void* __VFTABLEPOINTER;				/* Pointer to virtual function table */

	/* Member variables of StopPulse */

} stoppulse_struct;

/**
 * <description>stoppulse_main</description>
 */
typedef struct tagstoppulse_main_struct
{
	stoppulse_struct *pInstance;		/* VAR_INPUT */	
} stoppulse_main_struct;

void CDECL CDECL_EXT stoppulse__main(stoppulse_main_struct *p);
typedef void (CDECL CDECL_EXT* PFSTOPPULSE__MAIN_IEC) (stoppulse_main_struct *p);
#if defined(CMPPULSEOUTPUT_NOTIMPLEMENTED) || defined(STOPPULSE__MAIN_NOTIMPLEMENTED)
	#define USE_stoppulse__main
	#define EXT_stoppulse__main
	#define GET_stoppulse__main(fl)  ERR_NOTIMPLEMENTED
	#define CAL_stoppulse__main(p0) 
	#define CHK_stoppulse__main  FALSE
	#define EXP_stoppulse__main  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_stoppulse__main
	#define EXT_stoppulse__main
	#define GET_stoppulse__main(fl)  CAL_CMGETAPI( "stoppulse__main" ) 
	#define CAL_stoppulse__main  stoppulse__main
	#define CHK_stoppulse__main  TRUE
	#define EXP_stoppulse__main  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"stoppulse__main", (RTS_UINTPTR)stoppulse__main, 1, 0x4D0AB68B, 0x01000000) 
#elif defined(MIXED_LINK) && !defined(CMPPULSEOUTPUT_EXTERNAL)
	#define USE_stoppulse__main
	#define EXT_stoppulse__main
	#define GET_stoppulse__main(fl)  CAL_CMGETAPI( "stoppulse__main" ) 
	#define CAL_stoppulse__main  stoppulse__main
	#define CHK_stoppulse__main  TRUE
	#define EXP_stoppulse__main  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"stoppulse__main", (RTS_UINTPTR)stoppulse__main, 1, 0x4D0AB68B, 0x01000000) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpPulseOutputstoppulse__main
	#define EXT_CmpPulseOutputstoppulse__main
	#define GET_CmpPulseOutputstoppulse__main  ERR_OK
	#define CAL_CmpPulseOutputstoppulse__main  stoppulse__main
	#define CHK_CmpPulseOutputstoppulse__main  TRUE
	#define EXP_CmpPulseOutputstoppulse__main  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"stoppulse__main", (RTS_UINTPTR)stoppulse__main, 1, 0x4D0AB68B, 0x01000000) 
#elif defined(CPLUSPLUS)
	#define USE_stoppulse__main
	#define EXT_stoppulse__main
	#define GET_stoppulse__main(fl)  CAL_CMGETAPI( "stoppulse__main" ) 
	#define CAL_stoppulse__main  stoppulse__main
	#define CHK_stoppulse__main  TRUE
	#define EXP_stoppulse__main  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"stoppulse__main", (RTS_UINTPTR)stoppulse__main, 1, 0x4D0AB68B, 0x01000000) 
#else /* DYNAMIC_LINK */
	#define USE_stoppulse__main  PFSTOPPULSE__MAIN_IEC pfstoppulse__main;
	#define EXT_stoppulse__main  extern PFSTOPPULSE__MAIN_IEC pfstoppulse__main;
	#define GET_stoppulse__main(fl)  s_pfCMGetAPI2( "stoppulse__main", (RTS_VOID_FCTPTR *)&pfstoppulse__main, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0x4D0AB68B, 0x01000000)
	#define CAL_stoppulse__main  pfstoppulse__main
	#define CHK_stoppulse__main  (pfstoppulse__main != NULL)
	#define EXP_stoppulse__main   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"stoppulse__main", (RTS_UINTPTR)stoppulse__main, 1, 0x4D0AB68B, 0x01000000) 
#endif


#ifdef __cplusplus
}
#endif

/** EXTERN LIB SECTION END **/




typedef struct
{
	IBase_C *pBase;
} ICmpPulseOutput_C;

#ifdef CPLUSPLUS
class ICmpPulseOutput : public IBase
{
	public:
};
	#ifndef ITF_CmpPulseOutput
		#define ITF_CmpPulseOutput static ICmpPulseOutput *pICmpPulseOutput = NULL;
	#endif
	#define EXTITF_CmpPulseOutput
#else	/*CPLUSPLUS*/
	typedef ICmpPulseOutput_C		ICmpPulseOutput;
	#ifndef ITF_CmpPulseOutput
		#define ITF_CmpPulseOutput
	#endif
	#define EXTITF_CmpPulseOutput
#endif

#ifdef CPLUSPLUS_ONLY
  #undef CPLUSPLUS_ONLY
#endif

#endif /*_CMPPULSEOUTPUTITF_H_*/
