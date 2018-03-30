/***********************************************************************
 * DO NOT MODIFY!
 * This is a generated file. Do not modify it's contents directly
 ***********************************************************************/

/**
 *  <name>Component Template</name>
 *  <description> 
 *  An example on how to implement a component.
 *  This component does no usefull work and it exports no functions
 *  which are intended to be used for anything. Use at your own risk.
 *  </description>
 *  <copyright>
 *  (c) 2003-2016 3S-Smart Software Solutions
 *  </copyright>
 */
#ifndef _CMPPWMCTRLDEP_H_
#define _CMPPWMCTRLDEP_H_

#define COMPONENT_NAME "CmpPwmCtrl"COMPONENT_NAME_POSTFIX
#define COMPONENT_ID	ADDVENDORID(CMP_VENDORID, CMPID_CmpPwmCtrl)
#define COMPONENT_NAME_UNQUOTED CmpPwmCtrl






#define CMP_VERSION			UINT32_C(0x03050A00)
#define CMP_VERSION_STRING "3.5.10.0"
#define CMP_VERSION_RC		3,5,10,0

/* NOTE: REPLACE 0x0001 BY YOUR VENDORID */
#define CMP_VENDORID		0x0001

#ifndef WIN32_RESOURCES

#include "CmpLogItf.h"				

#define CMPID_CmpPwmCtrl		0x2000								/* NOTE: START HERE WITH YOUR COMPONENTIDS (see CmpItf.h */
#define CLASSID_CCmpPwmCtrl	ADDVENDORID(CMP_VENDORID, 0x2000)	/* NOTE: START HERE WITH YOUR CLASSIDS (see CmpItf.h */
#define ITFID_ICmpPwmCtrl		ADDVENDORID(CMP_VENDORID, 0x2000)	/* NOTE: START HERE WITH YOUR INTERFACEIDS (see CmpItf.h */


#include "CMUtilsItf.h"


#include "SysFileItf.h"







#include "CmpPwmCtrlItf.h"







	
 	 


	



 	 



 	


#ifdef CPLUSPLUS
	#define INIT_STMT \
	{\
		IBase *pIBase;\
		RTS_RESULT Result;\
		  if (pICmpLog == NULL && s_pfCMCreateInstance != NULL) \
		{ \
			pIBase = (IBase *)s_pfCMCreateInstance(CLASSID_CCmpLog, &Result); \
			if (pIBase != NULL) \
				pICmpLog = (ICmpLog *)pIBase->QueryInterface(pIBase, ITFID_ICmpLog, &Result); \
		} \
		if (pISysFile == NULL && s_pfCMCreateInstance != NULL) \
		{ \
			pIBase = (IBase *)s_pfCMCreateInstance(CLASSID_CSysFile, &Result); \
			if (pIBase != NULL) \
				pISysFile = (ISysFile *)pIBase->QueryInterface(pIBase, ITFID_ISysFile, &Result); \
		} \
		  if (pICMUtils == NULL && s_pfCMCreateInstance != NULL) \
		{ \
			pIBase = (IBase *)s_pfCMCreateInstance(CLASSID_CCMUtils, &Result); \
			if (pIBase != NULL) \
				pICMUtils = (ICMUtils *)pIBase->QueryInterface(pIBase, ITFID_ICMUtils, &Result); \
		} \
		   \
	}
#else
	#define INIT_STMT
#endif



#if defined(RTS_COMPACT) || defined(STATIC_LINK)
	#define IMPORT_STMT
#else
	#define IMPORT_STMT \
	{\
		RTS_RESULT Result = ERR_OK;\
		RTS_RESULT TempResult = ERR_OK;\
		INIT_STMT	\
		TempResult = GET_LogAdd(CM_IMPORT_OPTIONAL_FUNCTION); \
		if (ERR_OK == Result ) TempResult = GET_SysFileWrite(CM_IMPORT_OPTIONAL_FUNCTION);\
		  if (ERR_OK == Result ) TempResult = GET_SysFileRead(CM_IMPORT_OPTIONAL_FUNCTION);\
		  if (ERR_OK == Result ) TempResult = GET_SysFileClose(CM_IMPORT_OPTIONAL_FUNCTION);\
		  if (ERR_OK == Result ) TempResult = GET_SysFileOpen(CM_IMPORT_OPTIONAL_FUNCTION);\
		  if (ERR_OK == Result ) Result = GET_CMUtlSafeStrCpy(0);\
		   \
		/* To make LINT happy */\
		TempResult = TempResult;\
		if (ERR_OK != Result) return Result;\
	}
#endif



#ifndef CMPPWMCTRL_DISABLE_EXTREF
#define EXPORT_EXTREF_STMT \
		{ (RTS_VOID_FCTPTR)pou__main, "pou__main", 0x15E68C4A, 0x01000000 },\
		  
#else
#define EXPORT_EXTREF_STMT
#endif
#ifndef CMPPWMCTRL_DISABLE_EXTREF2
#define EXPORT_EXTREF2_STMT \
		  
#else
#define EXPORT_EXTREF2_STMT
#endif
#if !defined(RTS_COMPACT) && !defined(STATIC_LINK) && !defined(CPLUSPLUS) && !defined(CPLUSPLUS_ONLY)
#define EXPORT_CMPITF_STMT \
	{\
		  \
		{ ((RTS_VOID_FCTPTR)(void *)0), "", 0, 0 }\
	}
#else
#define EXPORT_CMPITF_STMT \
	{\
		{ ((RTS_VOID_FCTPTR)(void *)0), "", 0, 0 }\
	}
#endif
#define EXPORT_CPP_STMT


#if defined(RTS_COMPACT) || defined(STATIC_LINK)
	#define EXPORT_STMT\
	{\
		RTS_RESULT ExpResult;\
		if (NULL == s_pfCMRegisterAPI)\
			return ERR_NOTINITIALIZED;\
		ExpResult = s_pfCMRegisterAPI(s_ExternalsTable, 0, 1, COMPONENT_ID);\
		if (ERR_OK != ExpResult)\
			return ExpResult;\
	}
#else
	#define EXPORT_STMT\
	{\
		RTS_RESULT ExpResult;\
		if (NULL == s_pfCMRegisterAPI)\
			return ERR_NOTINITIALIZED;\
		ExpResult = s_pfCMRegisterAPI(s_ExternalsTable, 0, 1, COMPONENT_ID);\
		if (ERR_OK != ExpResult)\
			return ExpResult;\
		ExpResult = s_pfCMRegisterAPI(s_ItfTable, 0, 0, COMPONENT_ID);\
		if (ERR_OK != ExpResult)\
			return ExpResult;\
	}
#endif

#define USE_STMT \
	/*lint -save --e{528} --e{551} */ \
	static volatile PF_REGISTER_API s_pfCMRegisterAPI; \
	static volatile PF_REGISTER_API2 s_pfCMRegisterAPI2; \
	static volatile PF_GET_API s_pfCMGetAPI; \
	static volatile PF_GET_API2 s_pfCMGetAPI2; \
	static volatile PF_REGISTER_CLASS s_pfCMRegisterClass; \
	static volatile PF_CREATEINSTANCE s_pfCMCreateInstance; \
	static volatile PF_CALL_HOOK s_pfCMCallHook; \
	static const CMP_EXT_FUNCTION_REF s_ExternalsTable[] =\
	{\
		EXPORT_EXTREF_STMT\
		EXPORT_EXTREF2_STMT\
		{ ((RTS_VOID_FCTPTR)(void *)0), "", 0, 0 }\
	};\
	static const CMP_EXT_FUNCTION_REF s_ItfTable[] = EXPORT_CMPITF_STMT; \
	/*lint -restore */	\
	static int CDECL ExportFunctions(void); \
	static int CDECL ImportFunctions(void); \
	static IBase* CDECL CreateInstance(CLASSID cid, RTS_RESULT *pResult); \
	static RTS_RESULT CDECL DeleteInstance(IBase *pIBase); \
	static RTS_UI32 CDECL CmpGetVersion(void); \
	static RTS_RESULT CDECL HookFunction(RTS_UI32 ulHook, RTS_UINTPTR ulParam1, RTS_UINTPTR ulParam2); \
	ITF_CmpLog	 \
	USE_LogAdd \
	ITF_CMUtils	 \
	ITF_SysFile	  \
	USE_CMUtlSafeStrCpy 	 \
	USE_SysFileOpen 	 \
	USE_SysFileClose 	 \
	USE_SysFileRead 	 \
	USE_SysFileWrite 	
#define USEIMPORT_STMT \
	/*lint -save --e{551} */ \
	static volatile PF_REGISTER_API s_pfCMRegisterAPI; \
	static volatile PF_REGISTER_API2 s_pfCMRegisterAPI2; \
	static volatile PF_GET_API s_pfCMGetAPI; \
	static volatile PF_GET_API2 s_pfCMGetAPI2; \
	static volatile PF_REGISTER_CLASS s_pfCMRegisterClass; \
	static volatile PF_CREATEINSTANCE s_pfCMCreateInstance; \
	static volatile PF_CALL_HOOK s_pfCMCallHook; \
	/*lint -restore */	\
	ITF_CmpLog	 \
	USE_LogAdd \
	ITF_CMUtils	 \
	ITF_SysFile	  \
	USE_CMUtlSafeStrCpy 	 \
	USE_SysFileOpen 	 \
	USE_SysFileClose 	 \
	USE_SysFileRead 	 \
	USE_SysFileWrite 	
#define USEEXTERN_STMT \
	EXT_LogAdd \
	EXTITF_CMUtils	\
	EXTITF_SysFile	 \
	EXT_CMUtlSafeStrCpy  \
	EXT_SysFileOpen  \
	EXT_SysFileClose  \
	EXT_SysFileRead  \
	EXT_SysFileWrite 
#ifndef COMPONENT_NAME
	#error COMPONENT_NAME is not defined. This prevents the component from being linked statically. Use SET_COMPONENT_NAME(<name_of_your_component>) to set the name of the component in your .m4 component description.
#endif




#if defined(STATIC_LINK) || defined(MIXED_LINK) || defined(DYNAMIC_LINK) || defined(CPLUSPLUS_STATIC_LINK)
	#define ComponentEntry CmpPwmCtrl__Entry
#endif


#ifdef CPLUSPLUS

class CCmpPwmCtrl : public ICmpPwmCtrl 
{
	public:
		CCmpPwmCtrl() : hCmpPwmCtrl(RTS_INVALID_HANDLE), iRefCount(0)
		{
		}
		virtual ~CCmpPwmCtrl()
		{
		}
		IMPLEMENT_ADDREF();
		IMPLEMENT_RELEASE();
		
		virtual	void* QueryInterface(IBase *pIBase, ITFID iid, RTS_RESULT *pResult)
		{
			void *pItf;
			if (iid == ITFID_IBase)
				pItf = dynamic_cast<IBase *>((ICmpPwmCtrl *)this);			
			else if (iid == ITFID_ICmpPwmCtrl)
				pItf = dynamic_cast<ICmpPwmCtrl *>(this); 
			else
			{
				if (pResult != NULL)
					*pResult = ERR_NOTIMPLEMENTED;
				return NULL;
			}
			(reinterpret_cast<IBase *>(pItf))->AddRef();
			if (pResult != NULL)
				*pResult = ERR_OK;
			return pItf;
		}

	public:
		RTS_HANDLE hCmpPwmCtrl;
		int iRefCount;
};

#endif /*CPLUSPLUS*/
#ifdef RTS_COMPACT_MICRO
/* CmpPwmCtrl Declarations for uRTS */
/* This header is included only to have the CMP_EXT_FUNCTION_REF type definition. */
/* In final version this type could be moved to CmpItf.h, if we will use */
/* the same structure for representing an export entry. */
#include <_OptionalIncludes/Profiles/uRTS/CMMicro.h>

/* Undefine these macros if they were previously defined */

#ifdef USE_HOOK_FUNCTION
#undef USE_HOOK_FUNCTION
#endif

#ifdef USE_CMEXPORTFUNCTIONS
#undef USE_CMEXPORTFUNCTIONS
#endif

#ifdef USE_EXPORT_EXTREF
#undef USE_EXPORT_EXTREF
#endif

#ifdef USE_EXPORT_CMPITF
#undef USE_EXPORT_CMPITF
#endif

#ifdef USE_ENTRY_LINKAGE
#undef USE_ENTRY_LINKAGE
#endif

#ifdef IMPLEMENT_EXPORT_FUNCTIONS
#undef IMPLEMENT_EXPORT_FUNCTIONS
#endif

#ifdef IMPLEMENT_IMPORT_FUNCTIONS
#undef IMPLEMENT_IMPORT_FUNCTIONS
#endif

#ifdef IMPLEMENT_GETVERSION_FUNCTIONS
#undef IMPLEMENT_GETVERSION_FUNCTIONS
#endif

#ifdef EXPORT_STMT
#undef EXPORT_STMT
#endif

#ifdef USEEXTERN_STMT
#undef USEEXTERN_STMT
#endif

#ifdef USE_STMT
#undef USE_STMT
#endif

#ifdef USEIMPORT_STMT
#undef USEIMPORT_STMT
#endif

/* This wrapper is only required in uRTS */
#define USE_HOOK_FUNCTION	RTS_RESULT CmpPwmCtrl_HookFunction(RTS_UI32 ulHook, RTS_UINTPTR ulParam1, RTS_UINTPTR ulParam2)\
{\
	return HookFunction(ulHook, ulParam1, ulParam2);\
}

/******************************************************************************/
/* No s_pfCMExportFunctions in uRTS */
#define USE_CMEXPORTFUNCTIONS

/* Exports table to IEC */
#define USE_EXPORT_EXTREF const CMP_EXT_FUNCTION_REF CmpPwmCtrl_ExternalsTable[] = \
	{\
		EXPORT_EXTREF_STMT\
		EXPORT_EXTREF2_STMT\
		{ ((RTS_VOID_FCTPTR)(void *)0), "", 0 }\
	};

/* No component interface exports in uRTS */
#define USE_EXPORT_CMPITF

/* No dynamic linkage in uRTS */
#define USE_ENTRY_LINKAGE

/* No ExportFunctions() routine in uRTS */
#define IMPLEMENT_EXPORT_FUNCTIONS

/* No ImportFunctions() routine in uRTS */
#define IMPLEMENT_IMPORT_FUNCTIONS

/* No CmpGetVersion() routine in uRTS */
#define IMPLEMENT_GETVERSION_FUNCTIONS

/* No usage of externals from the component secondary C-modules in uRTS */
#define USEEXTERN_STMT

/* No need for export calling to the Component Manager in uRTS */
#define EXPORT_STMT

/* No need for importing from secondary C-modules */
#define USEIMPORT_STMT

/* Instantiation macro for a root component C-module */
#define USE_STMT\
	static RTS_RESULT CDECL HookFunction(RTS_UI32 ulHook, RTS_UINTPTR ulParam1, RTS_UINTPTR ulParam2);\
		USE_EXPORT_EXTREF;\
		USE_EXPORT_CMPITF;\
		USE_HOOK_FUNCTION;\
		USE_CMEXPORTFUNCTIONS;\


/******************************************************************************/
#endif

#endif /*WIN32_RESOURCES*/
#endif /*_DEP_H_*/
