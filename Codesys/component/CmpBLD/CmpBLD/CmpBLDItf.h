 /**
 * <interfacename>CmpBLD</interfacename>
 * <description></description>
 *
 * <copyright></copyright>
 */


	
	
#ifndef _CMPBLDITF_H_
#define _CMPBLDITF_H_

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
 * <description>bld__main</description>
 */
typedef struct tagbld_struct
{
	void* __VFTABLEPOINTER;				/* Pointer to virtual function table */

	/* Member variables of BLD */

	RTS_IEC_BOOL EN;					/* VAR_INPUT */	
	RTS_IEC_WORD data;					/* VAR_INPUT */	
	RTS_IEC_USINT index;				/* VAR_INPUT */	
	RTS_IEC_BOOL result;				/* VAR_OUTPUT */	
} bld_struct;

/**
 * <description>bld_main</description>
 */
typedef struct tagbld_main_struct
{
	bld_struct *pInstance;				/* VAR_INPUT */	
} bld_main_struct;

void CDECL CDECL_EXT bld__main(bld_main_struct *p);
typedef void (CDECL CDECL_EXT* PFBLD__MAIN_IEC) (bld_main_struct *p);
#if defined(CMPBLD_NOTIMPLEMENTED) || defined(BLD__MAIN_NOTIMPLEMENTED)
	#define USE_bld__main
	#define EXT_bld__main
	#define GET_bld__main(fl)  ERR_NOTIMPLEMENTED
	#define CAL_bld__main(p0) 
	#define CHK_bld__main  FALSE
	#define EXP_bld__main  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_bld__main
	#define EXT_bld__main
	#define GET_bld__main(fl)  CAL_CMGETAPI( "bld__main" ) 
	#define CAL_bld__main  bld__main
	#define CHK_bld__main  TRUE
	#define EXP_bld__main  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"bld__main", (RTS_UINTPTR)bld__main, 1, 0x66125D34, 0x01000000) 
#elif defined(MIXED_LINK) && !defined(CMPBLD_EXTERNAL)
	#define USE_bld__main
	#define EXT_bld__main
	#define GET_bld__main(fl)  CAL_CMGETAPI( "bld__main" ) 
	#define CAL_bld__main  bld__main
	#define CHK_bld__main  TRUE
	#define EXP_bld__main  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"bld__main", (RTS_UINTPTR)bld__main, 1, 0x66125D34, 0x01000000) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpBLDbld__main
	#define EXT_CmpBLDbld__main
	#define GET_CmpBLDbld__main  ERR_OK
	#define CAL_CmpBLDbld__main  bld__main
	#define CHK_CmpBLDbld__main  TRUE
	#define EXP_CmpBLDbld__main  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"bld__main", (RTS_UINTPTR)bld__main, 1, 0x66125D34, 0x01000000) 
#elif defined(CPLUSPLUS)
	#define USE_bld__main
	#define EXT_bld__main
	#define GET_bld__main(fl)  CAL_CMGETAPI( "bld__main" ) 
	#define CAL_bld__main  bld__main
	#define CHK_bld__main  TRUE
	#define EXP_bld__main  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"bld__main", (RTS_UINTPTR)bld__main, 1, 0x66125D34, 0x01000000) 
#else /* DYNAMIC_LINK */
	#define USE_bld__main  PFBLD__MAIN_IEC pfbld__main;
	#define EXT_bld__main  extern PFBLD__MAIN_IEC pfbld__main;
	#define GET_bld__main(fl)  s_pfCMGetAPI2( "bld__main", (RTS_VOID_FCTPTR *)&pfbld__main, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0x66125D34, 0x01000000)
	#define CAL_bld__main  pfbld__main
	#define CHK_bld__main  (pfbld__main != NULL)
	#define EXP_bld__main   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"bld__main", (RTS_UINTPTR)bld__main, 1, 0x66125D34, 0x01000000) 
#endif


#ifdef __cplusplus
}
#endif

/** EXTERN LIB SECTION END **/




typedef struct
{
	IBase_C *pBase;
} ICmpBLD_C;

#ifdef CPLUSPLUS
class ICmpBLD : public IBase
{
	public:
};
	#ifndef ITF_CmpBLD
		#define ITF_CmpBLD static ICmpBLD *pICmpBLD = NULL;
	#endif
	#define EXTITF_CmpBLD
#else	/*CPLUSPLUS*/
	typedef ICmpBLD_C		ICmpBLD;
	#ifndef ITF_CmpBLD
		#define ITF_CmpBLD
	#endif
	#define EXTITF_CmpBLD
#endif

#ifdef CPLUSPLUS_ONLY
  #undef CPLUSPLUS_ONLY
#endif

#endif /*_CMPBLDITF_H_*/
