 /**
 * <interfacename>CmpPwmCtrl</interfacename>
 * <description></description>
 *
 * <copyright></copyright>
 */


	
	
#ifndef _CMPPWMCTRLITF_H_
#define _CMPPWMCTRLITF_H_

 

 




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
#ifndef ERROR
#define ERROR    RTS_IEC_INT
#endif
/**
 * <description>pou__main</description>
 */
typedef struct tagpou_struct
{
	void* __VFTABLEPOINTER;				/* Pointer to virtual function table */

	/* Member variables of POU */

	RTS_IEC_INT hz;						/* VAR_INPUT */	
	RTS_IEC_INT dutyCycle;				/* VAR_INPUT */	
} pou_struct;

/**
 * <description>pou_main</description>
 */
typedef struct tagpou_main_struct
{
	pou_struct *pInstance;				/* VAR_INPUT */	
} pou_main_struct;

void CDECL CDECL_EXT pou__main(pou_main_struct *p);
typedef void (CDECL CDECL_EXT* PFPOU__MAIN_IEC) (pou_main_struct *p);
#if defined(CMPPWMCTRL_NOTIMPLEMENTED) || defined(POU__MAIN_NOTIMPLEMENTED)
	#define USE_pou__main
	#define EXT_pou__main
	#define GET_pou__main(fl)  ERR_NOTIMPLEMENTED
	#define CAL_pou__main(p0) 
	#define CHK_pou__main  FALSE
	#define EXP_pou__main  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_pou__main
	#define EXT_pou__main
	#define GET_pou__main(fl)  CAL_CMGETAPI( "pou__main" ) 
	#define CAL_pou__main  pou__main
	#define CHK_pou__main  TRUE
	#define EXP_pou__main  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"pou__main", (RTS_UINTPTR)pou__main, 1, 0x15E68C4A, 0x01000000) 
#elif defined(MIXED_LINK) && !defined(CMPPWMCTRL_EXTERNAL)
	#define USE_pou__main
	#define EXT_pou__main
	#define GET_pou__main(fl)  CAL_CMGETAPI( "pou__main" ) 
	#define CAL_pou__main  pou__main
	#define CHK_pou__main  TRUE
	#define EXP_pou__main  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"pou__main", (RTS_UINTPTR)pou__main, 1, 0x15E68C4A, 0x01000000) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpPwmCtrlpou__main
	#define EXT_CmpPwmCtrlpou__main
	#define GET_CmpPwmCtrlpou__main  ERR_OK
	#define CAL_CmpPwmCtrlpou__main  pou__main
	#define CHK_CmpPwmCtrlpou__main  TRUE
	#define EXP_CmpPwmCtrlpou__main  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"pou__main", (RTS_UINTPTR)pou__main, 1, 0x15E68C4A, 0x01000000) 
#elif defined(CPLUSPLUS)
	#define USE_pou__main
	#define EXT_pou__main
	#define GET_pou__main(fl)  CAL_CMGETAPI( "pou__main" ) 
	#define CAL_pou__main  pou__main
	#define CHK_pou__main  TRUE
	#define EXP_pou__main  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"pou__main", (RTS_UINTPTR)pou__main, 1, 0x15E68C4A, 0x01000000) 
#else /* DYNAMIC_LINK */
	#define USE_pou__main  PFPOU__MAIN_IEC pfpou__main;
	#define EXT_pou__main  extern PFPOU__MAIN_IEC pfpou__main;
	#define GET_pou__main(fl)  s_pfCMGetAPI2( "pou__main", (RTS_VOID_FCTPTR *)&pfpou__main, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0x15E68C4A, 0x01000000)
	#define CAL_pou__main  pfpou__main
	#define CHK_pou__main  (pfpou__main != NULL)
	#define EXP_pou__main   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"pou__main", (RTS_UINTPTR)pou__main, 1, 0x15E68C4A, 0x01000000) 
#endif


#ifdef __cplusplus
}
#endif

/** EXTERN LIB SECTION END **/




typedef struct
{
	IBase_C *pBase;
} ICmpPwmCtrl_C;

#ifdef CPLUSPLUS
class ICmpPwmCtrl : public IBase
{
	public:
};
	#ifndef ITF_CmpPwmCtrl
		#define ITF_CmpPwmCtrl static ICmpPwmCtrl *pICmpPwmCtrl = NULL;
	#endif
	#define EXTITF_CmpPwmCtrl
#else	/*CPLUSPLUS*/
	typedef ICmpPwmCtrl_C		ICmpPwmCtrl;
	#ifndef ITF_CmpPwmCtrl
		#define ITF_CmpPwmCtrl
	#endif
	#define EXTITF_CmpPwmCtrl
#endif

#ifdef CPLUSPLUS_ONLY
  #undef CPLUSPLUS_ONLY
#endif

#endif /*_CMPPWMCTRLITF_H_*/
