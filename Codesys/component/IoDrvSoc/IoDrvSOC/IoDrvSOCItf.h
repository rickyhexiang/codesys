 /**
 * <interfacename>test</interfacename>
 * <description></description>
 *
 * <copyright></copyright>
 */


	
	
#ifndef _IODRVSOCITF_H_
#define _IODRVSOCITF_H_

#include "CmpStd.h"

 

 




/** EXTERN LIB SECTION BEGIN **/

#ifdef __cplusplus
extern "C" {
#endif

/**
 * <description>myexternalfunction</description>
 */

typedef struct tagmyexternalfunction_struct
{
	RTS_IEC_INT MyExternalFunction;		/* VAR_OUTPUT */
} myexternalfunction_struct;

void CDECL CDECL_EXT myexternalfunction(myexternalfunction_struct *p);
typedef void (CDECL CDECL_EXT* PFMYEXTERNALFUNCTION_IEC) (myexternalfunction_struct *p);
#if defined(IODRVSOC_NOTIMPLEMENTED) || defined(MYEXTERNALFUNCTION_NOTIMPLEMENTED)
	#define USE_myexternalfunction
	#define EXT_myexternalfunction
	#define GET_myexternalfunction(fl)  ERR_NOTIMPLEMENTED
	#define CAL_myexternalfunction(p0) 
	#define CHK_myexternalfunction  FALSE
	#define EXP_myexternalfunction  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_myexternalfunction
	#define EXT_myexternalfunction
	#define GET_myexternalfunction(fl)  CAL_CMGETAPI( "myexternalfunction" ) 
	#define CAL_myexternalfunction  myexternalfunction
	#define CHK_myexternalfunction  TRUE
	#define EXP_myexternalfunction  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"myexternalfunction", (RTS_UINTPTR)myexternalfunction, 1, 0xE1C6D757, 0x3040000) 
#elif defined(MIXED_LINK) && !defined(IODRVSOC_EXTERNAL)
	#define USE_myexternalfunction
	#define EXT_myexternalfunction
	#define GET_myexternalfunction(fl)  CAL_CMGETAPI( "myexternalfunction" ) 
	#define CAL_myexternalfunction  myexternalfunction
	#define CHK_myexternalfunction  TRUE
	#define EXP_myexternalfunction  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"myexternalfunction", (RTS_UINTPTR)myexternalfunction, 1, 0xE1C6D757, 0x3040000) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_IoDrvSOCmyexternalfunction
	#define EXT_IoDrvSOCmyexternalfunction
	#define GET_IoDrvSOCmyexternalfunction  ERR_OK
	#define CAL_IoDrvSOCmyexternalfunction  myexternalfunction
	#define CHK_IoDrvSOCmyexternalfunction  TRUE
	#define EXP_IoDrvSOCmyexternalfunction  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"myexternalfunction", (RTS_UINTPTR)myexternalfunction, 1, 0xE1C6D757, 0x3040000) 
#elif defined(CPLUSPLUS)
	#define USE_myexternalfunction
	#define EXT_myexternalfunction
	#define GET_myexternalfunction(fl)  CAL_CMGETAPI( "myexternalfunction" ) 
	#define CAL_myexternalfunction  myexternalfunction
	#define CHK_myexternalfunction  TRUE
	#define EXP_myexternalfunction  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"myexternalfunction", (RTS_UINTPTR)myexternalfunction, 1, 0xE1C6D757, 0x3040000) 
#else /* DYNAMIC_LINK */
	#define USE_myexternalfunction  PFMYEXTERNALFUNCTION_IEC pfmyexternalfunction;
	#define EXT_myexternalfunction  extern PFMYEXTERNALFUNCTION_IEC pfmyexternalfunction;
	#define GET_myexternalfunction(fl)  s_pfCMGetAPI2( "myexternalfunction", (RTS_VOID_FCTPTR *)&pfmyexternalfunction, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0xE1C6D757, 0x3040000)
	#define CAL_myexternalfunction  pfmyexternalfunction
	#define CHK_myexternalfunction  (pfmyexternalfunction != NULL)
	#define EXP_myexternalfunction   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"myexternalfunction", (RTS_UINTPTR)myexternalfunction, 1, 0xE1C6D757, 0x3040000) 
#endif

#ifdef __cplusplus
}
#endif

/** EXTERN LIB SECTION END **/




typedef struct
{
	IBase_C *pBase;
} IIoDrvSOC_C;

#ifdef CPLUSPLUS
class IIoDrvSOC : public IBase
{
	public:
};
	#ifndef ITF_IoDrvSOC
		#define ITF_IoDrvSOC static IIoDrvSOC *pIIoDrvSOC = NULL;
	#endif
	#define EXTITF_IoDrvSOC
#else	/*CPLUSPLUS*/
	typedef IIoDrvSOC_C		IIoDrvSOC;
	#ifndef ITF_IoDrvSOC
		#define ITF_IoDrvSOC
	#endif
	#define EXTITF_IoDrvSOC
#endif

#ifdef CPLUSPLUS_ONLY
  #undef CPLUSPLUS_ONLY
#endif

#endif /*_IODRVSOCITF_H_*/
