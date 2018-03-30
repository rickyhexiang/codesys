 /**
 * <interfacename>CmpModbusLib</interfacename>
 * <description></description>
 *
 * <copyright></copyright>
 */


	
	
#ifndef _CMPMODBUSLIBITF_H_
#define _CMPMODBUSLIBITF_H_

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
 * <description>closemodbus__main</description>
 */
typedef struct tagclosemodbus_struct
{
	void* __VFTABLEPOINTER;				/* Pointer to virtual function table */

	/* Member variables of CloseModbus */

	RTS_IEC_INT result;					/* VAR_OUTPUT */	
} closemodbus_struct;

/**
 * <description>closemodbus_main</description>
 */
typedef struct tagclosemodbus_main_struct
{
	closemodbus_struct *pInstance;		/* VAR_INPUT */	
} closemodbus_main_struct;

void CDECL CDECL_EXT closemodbus__main(closemodbus_main_struct *p);
typedef void (CDECL CDECL_EXT* PFCLOSEMODBUS__MAIN_IEC) (closemodbus_main_struct *p);
#if defined(CMPMODBUSLIB_NOTIMPLEMENTED) || defined(CLOSEMODBUS__MAIN_NOTIMPLEMENTED)
	#define USE_closemodbus__main
	#define EXT_closemodbus__main
	#define GET_closemodbus__main(fl)  ERR_NOTIMPLEMENTED
	#define CAL_closemodbus__main(p0) 
	#define CHK_closemodbus__main  FALSE
	#define EXP_closemodbus__main  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_closemodbus__main
	#define EXT_closemodbus__main
	#define GET_closemodbus__main(fl)  CAL_CMGETAPI( "closemodbus__main" ) 
	#define CAL_closemodbus__main  closemodbus__main
	#define CHK_closemodbus__main  TRUE
	#define EXP_closemodbus__main  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"closemodbus__main", (RTS_UINTPTR)closemodbus__main, 1, 0x32BCE1D3, 0x01000000) 
#elif defined(MIXED_LINK) && !defined(CMPMODBUSLIB_EXTERNAL)
	#define USE_closemodbus__main
	#define EXT_closemodbus__main
	#define GET_closemodbus__main(fl)  CAL_CMGETAPI( "closemodbus__main" ) 
	#define CAL_closemodbus__main  closemodbus__main
	#define CHK_closemodbus__main  TRUE
	#define EXP_closemodbus__main  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"closemodbus__main", (RTS_UINTPTR)closemodbus__main, 1, 0x32BCE1D3, 0x01000000) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpModbusLibclosemodbus__main
	#define EXT_CmpModbusLibclosemodbus__main
	#define GET_CmpModbusLibclosemodbus__main  ERR_OK
	#define CAL_CmpModbusLibclosemodbus__main  closemodbus__main
	#define CHK_CmpModbusLibclosemodbus__main  TRUE
	#define EXP_CmpModbusLibclosemodbus__main  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"closemodbus__main", (RTS_UINTPTR)closemodbus__main, 1, 0x32BCE1D3, 0x01000000) 
#elif defined(CPLUSPLUS)
	#define USE_closemodbus__main
	#define EXT_closemodbus__main
	#define GET_closemodbus__main(fl)  CAL_CMGETAPI( "closemodbus__main" ) 
	#define CAL_closemodbus__main  closemodbus__main
	#define CHK_closemodbus__main  TRUE
	#define EXP_closemodbus__main  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"closemodbus__main", (RTS_UINTPTR)closemodbus__main, 1, 0x32BCE1D3, 0x01000000) 
#else /* DYNAMIC_LINK */
	#define USE_closemodbus__main  PFCLOSEMODBUS__MAIN_IEC pfclosemodbus__main;
	#define EXT_closemodbus__main  extern PFCLOSEMODBUS__MAIN_IEC pfclosemodbus__main;
	#define GET_closemodbus__main(fl)  s_pfCMGetAPI2( "closemodbus__main", (RTS_VOID_FCTPTR *)&pfclosemodbus__main, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0x32BCE1D3, 0x01000000)
	#define CAL_closemodbus__main  pfclosemodbus__main
	#define CHK_closemodbus__main  (pfclosemodbus__main != NULL)
	#define EXP_closemodbus__main   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"closemodbus__main", (RTS_UINTPTR)closemodbus__main, 1, 0x32BCE1D3, 0x01000000) 
#endif


/**
 * <description>initmodbusrtu__main</description>
 */
typedef struct taginitmodbusrtu_struct
{
	void* __VFTABLEPOINTER;				/* Pointer to virtual function table */

	/* Member variables of InitModbusRtu */

	RTS_IEC_BYTE com;					/* VAR_INPUT */	
	RTS_IEC_DWORD baud;					/* VAR_INPUT */	
	RTS_IEC_BYTE slave;					/* VAR_INPUT */	
	RTS_IEC_WORD timeout;				/* VAR_INPUT */	
	RTS_IEC_INT result;					/* VAR_OUTPUT */	
} initmodbusrtu_struct;

/**
 * <description>initmodbusrtu_main</description>
 */
typedef struct taginitmodbusrtu_main_struct
{
	initmodbusrtu_struct *pInstance;	/* VAR_INPUT */	
} initmodbusrtu_main_struct;

void CDECL CDECL_EXT initmodbusrtu__main(initmodbusrtu_main_struct *p);
typedef void (CDECL CDECL_EXT* PFINITMODBUSRTU__MAIN_IEC) (initmodbusrtu_main_struct *p);
#if defined(CMPMODBUSLIB_NOTIMPLEMENTED) || defined(INITMODBUSRTU__MAIN_NOTIMPLEMENTED)
	#define USE_initmodbusrtu__main
	#define EXT_initmodbusrtu__main
	#define GET_initmodbusrtu__main(fl)  ERR_NOTIMPLEMENTED
	#define CAL_initmodbusrtu__main(p0) 
	#define CHK_initmodbusrtu__main  FALSE
	#define EXP_initmodbusrtu__main  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_initmodbusrtu__main
	#define EXT_initmodbusrtu__main
	#define GET_initmodbusrtu__main(fl)  CAL_CMGETAPI( "initmodbusrtu__main" ) 
	#define CAL_initmodbusrtu__main  initmodbusrtu__main
	#define CHK_initmodbusrtu__main  TRUE
	#define EXP_initmodbusrtu__main  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"initmodbusrtu__main", (RTS_UINTPTR)initmodbusrtu__main, 1, 0x28BA41FA, 0x01000000) 
#elif defined(MIXED_LINK) && !defined(CMPMODBUSLIB_EXTERNAL)
	#define USE_initmodbusrtu__main
	#define EXT_initmodbusrtu__main
	#define GET_initmodbusrtu__main(fl)  CAL_CMGETAPI( "initmodbusrtu__main" ) 
	#define CAL_initmodbusrtu__main  initmodbusrtu__main
	#define CHK_initmodbusrtu__main  TRUE
	#define EXP_initmodbusrtu__main  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"initmodbusrtu__main", (RTS_UINTPTR)initmodbusrtu__main, 1, 0x28BA41FA, 0x01000000) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpModbusLibinitmodbusrtu__main
	#define EXT_CmpModbusLibinitmodbusrtu__main
	#define GET_CmpModbusLibinitmodbusrtu__main  ERR_OK
	#define CAL_CmpModbusLibinitmodbusrtu__main  initmodbusrtu__main
	#define CHK_CmpModbusLibinitmodbusrtu__main  TRUE
	#define EXP_CmpModbusLibinitmodbusrtu__main  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"initmodbusrtu__main", (RTS_UINTPTR)initmodbusrtu__main, 1, 0x28BA41FA, 0x01000000) 
#elif defined(CPLUSPLUS)
	#define USE_initmodbusrtu__main
	#define EXT_initmodbusrtu__main
	#define GET_initmodbusrtu__main(fl)  CAL_CMGETAPI( "initmodbusrtu__main" ) 
	#define CAL_initmodbusrtu__main  initmodbusrtu__main
	#define CHK_initmodbusrtu__main  TRUE
	#define EXP_initmodbusrtu__main  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"initmodbusrtu__main", (RTS_UINTPTR)initmodbusrtu__main, 1, 0x28BA41FA, 0x01000000) 
#else /* DYNAMIC_LINK */
	#define USE_initmodbusrtu__main  PFINITMODBUSRTU__MAIN_IEC pfinitmodbusrtu__main;
	#define EXT_initmodbusrtu__main  extern PFINITMODBUSRTU__MAIN_IEC pfinitmodbusrtu__main;
	#define GET_initmodbusrtu__main(fl)  s_pfCMGetAPI2( "initmodbusrtu__main", (RTS_VOID_FCTPTR *)&pfinitmodbusrtu__main, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0x28BA41FA, 0x01000000)
	#define CAL_initmodbusrtu__main  pfinitmodbusrtu__main
	#define CHK_initmodbusrtu__main  (pfinitmodbusrtu__main != NULL)
	#define EXP_initmodbusrtu__main   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"initmodbusrtu__main", (RTS_UINTPTR)initmodbusrtu__main, 1, 0x28BA41FA, 0x01000000) 
#endif


/**
 * <description>modbusreadbit__main</description>
 */
typedef struct tagmodbusreadbit_struct
{
	void* __VFTABLEPOINTER;				/* Pointer to virtual function table */

	/* Member variables of ModbusReadBit */

	RTS_IEC_WORD addr;					/* VAR_INPUT */	
	RTS_IEC_BYTE num;					/* VAR_INPUT */	
	RTS_IEC_BYTE **data;				/* VAR_IN_OUT */	
} modbusreadbit_struct;

/**
 * <description>modbusreadbit_main</description>
 */
typedef struct tagmodbusreadbit_main_struct
{
	modbusreadbit_struct *pInstance;	/* VAR_INPUT */	
} modbusreadbit_main_struct;

void CDECL CDECL_EXT modbusreadbit__main(modbusreadbit_main_struct *p);
typedef void (CDECL CDECL_EXT* PFMODBUSREADBIT__MAIN_IEC) (modbusreadbit_main_struct *p);
#if defined(CMPMODBUSLIB_NOTIMPLEMENTED) || defined(MODBUSREADBIT__MAIN_NOTIMPLEMENTED)
	#define USE_modbusreadbit__main
	#define EXT_modbusreadbit__main
	#define GET_modbusreadbit__main(fl)  ERR_NOTIMPLEMENTED
	#define CAL_modbusreadbit__main(p0) 
	#define CHK_modbusreadbit__main  FALSE
	#define EXP_modbusreadbit__main  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_modbusreadbit__main
	#define EXT_modbusreadbit__main
	#define GET_modbusreadbit__main(fl)  CAL_CMGETAPI( "modbusreadbit__main" ) 
	#define CAL_modbusreadbit__main  modbusreadbit__main
	#define CHK_modbusreadbit__main  TRUE
	#define EXP_modbusreadbit__main  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"modbusreadbit__main", (RTS_UINTPTR)modbusreadbit__main, 1, 0x71236F41, 0x01000000) 
#elif defined(MIXED_LINK) && !defined(CMPMODBUSLIB_EXTERNAL)
	#define USE_modbusreadbit__main
	#define EXT_modbusreadbit__main
	#define GET_modbusreadbit__main(fl)  CAL_CMGETAPI( "modbusreadbit__main" ) 
	#define CAL_modbusreadbit__main  modbusreadbit__main
	#define CHK_modbusreadbit__main  TRUE
	#define EXP_modbusreadbit__main  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"modbusreadbit__main", (RTS_UINTPTR)modbusreadbit__main, 1, 0x71236F41, 0x01000000) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpModbusLibmodbusreadbit__main
	#define EXT_CmpModbusLibmodbusreadbit__main
	#define GET_CmpModbusLibmodbusreadbit__main  ERR_OK
	#define CAL_CmpModbusLibmodbusreadbit__main  modbusreadbit__main
	#define CHK_CmpModbusLibmodbusreadbit__main  TRUE
	#define EXP_CmpModbusLibmodbusreadbit__main  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"modbusreadbit__main", (RTS_UINTPTR)modbusreadbit__main, 1, 0x71236F41, 0x01000000) 
#elif defined(CPLUSPLUS)
	#define USE_modbusreadbit__main
	#define EXT_modbusreadbit__main
	#define GET_modbusreadbit__main(fl)  CAL_CMGETAPI( "modbusreadbit__main" ) 
	#define CAL_modbusreadbit__main  modbusreadbit__main
	#define CHK_modbusreadbit__main  TRUE
	#define EXP_modbusreadbit__main  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"modbusreadbit__main", (RTS_UINTPTR)modbusreadbit__main, 1, 0x71236F41, 0x01000000) 
#else /* DYNAMIC_LINK */
	#define USE_modbusreadbit__main  PFMODBUSREADBIT__MAIN_IEC pfmodbusreadbit__main;
	#define EXT_modbusreadbit__main  extern PFMODBUSREADBIT__MAIN_IEC pfmodbusreadbit__main;
	#define GET_modbusreadbit__main(fl)  s_pfCMGetAPI2( "modbusreadbit__main", (RTS_VOID_FCTPTR *)&pfmodbusreadbit__main, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0x71236F41, 0x01000000)
	#define CAL_modbusreadbit__main  pfmodbusreadbit__main
	#define CHK_modbusreadbit__main  (pfmodbusreadbit__main != NULL)
	#define EXP_modbusreadbit__main   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"modbusreadbit__main", (RTS_UINTPTR)modbusreadbit__main, 1, 0x71236F41, 0x01000000) 
#endif


/**
 * <description>modbusreadreg__main</description>
 */
typedef struct tagmodbusreadreg_struct
{
	void* __VFTABLEPOINTER;				/* Pointer to virtual function table */

	/* Member variables of ModbusReadReg */

	RTS_IEC_WORD addr;					/* VAR_INPUT */	
	RTS_IEC_BYTE num;					/* VAR_INPUT */	
	RTS_IEC_WORD **data;				/* VAR_IN_OUT */	
} modbusreadreg_struct;

/**
 * <description>modbusreadreg_main</description>
 */
typedef struct tagmodbusreadreg_main_struct
{
	modbusreadreg_struct *pInstance;	/* VAR_INPUT */	
} modbusreadreg_main_struct;

void CDECL CDECL_EXT modbusreadreg__main(modbusreadreg_main_struct *p);
typedef void (CDECL CDECL_EXT* PFMODBUSREADREG__MAIN_IEC) (modbusreadreg_main_struct *p);
#if defined(CMPMODBUSLIB_NOTIMPLEMENTED) || defined(MODBUSREADREG__MAIN_NOTIMPLEMENTED)
	#define USE_modbusreadreg__main
	#define EXT_modbusreadreg__main
	#define GET_modbusreadreg__main(fl)  ERR_NOTIMPLEMENTED
	#define CAL_modbusreadreg__main(p0) 
	#define CHK_modbusreadreg__main  FALSE
	#define EXP_modbusreadreg__main  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_modbusreadreg__main
	#define EXT_modbusreadreg__main
	#define GET_modbusreadreg__main(fl)  CAL_CMGETAPI( "modbusreadreg__main" ) 
	#define CAL_modbusreadreg__main  modbusreadreg__main
	#define CHK_modbusreadreg__main  TRUE
	#define EXP_modbusreadreg__main  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"modbusreadreg__main", (RTS_UINTPTR)modbusreadreg__main, 1, 0x3CF79B14, 0x01000000) 
#elif defined(MIXED_LINK) && !defined(CMPMODBUSLIB_EXTERNAL)
	#define USE_modbusreadreg__main
	#define EXT_modbusreadreg__main
	#define GET_modbusreadreg__main(fl)  CAL_CMGETAPI( "modbusreadreg__main" ) 
	#define CAL_modbusreadreg__main  modbusreadreg__main
	#define CHK_modbusreadreg__main  TRUE
	#define EXP_modbusreadreg__main  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"modbusreadreg__main", (RTS_UINTPTR)modbusreadreg__main, 1, 0x3CF79B14, 0x01000000) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpModbusLibmodbusreadreg__main
	#define EXT_CmpModbusLibmodbusreadreg__main
	#define GET_CmpModbusLibmodbusreadreg__main  ERR_OK
	#define CAL_CmpModbusLibmodbusreadreg__main  modbusreadreg__main
	#define CHK_CmpModbusLibmodbusreadreg__main  TRUE
	#define EXP_CmpModbusLibmodbusreadreg__main  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"modbusreadreg__main", (RTS_UINTPTR)modbusreadreg__main, 1, 0x3CF79B14, 0x01000000) 
#elif defined(CPLUSPLUS)
	#define USE_modbusreadreg__main
	#define EXT_modbusreadreg__main
	#define GET_modbusreadreg__main(fl)  CAL_CMGETAPI( "modbusreadreg__main" ) 
	#define CAL_modbusreadreg__main  modbusreadreg__main
	#define CHK_modbusreadreg__main  TRUE
	#define EXP_modbusreadreg__main  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"modbusreadreg__main", (RTS_UINTPTR)modbusreadreg__main, 1, 0x3CF79B14, 0x01000000) 
#else /* DYNAMIC_LINK */
	#define USE_modbusreadreg__main  PFMODBUSREADREG__MAIN_IEC pfmodbusreadreg__main;
	#define EXT_modbusreadreg__main  extern PFMODBUSREADREG__MAIN_IEC pfmodbusreadreg__main;
	#define GET_modbusreadreg__main(fl)  s_pfCMGetAPI2( "modbusreadreg__main", (RTS_VOID_FCTPTR *)&pfmodbusreadreg__main, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0x3CF79B14, 0x01000000)
	#define CAL_modbusreadreg__main  pfmodbusreadreg__main
	#define CHK_modbusreadreg__main  (pfmodbusreadreg__main != NULL)
	#define EXP_modbusreadreg__main   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"modbusreadreg__main", (RTS_UINTPTR)modbusreadreg__main, 1, 0x3CF79B14, 0x01000000) 
#endif


/**
 * <description>modbusslavereadbit__main</description>
 */
typedef struct tagmodbusslavereadbit_struct
{
	void* __VFTABLEPOINTER;				/* Pointer to virtual function table */

	/* Member variables of ModbusSlaveReadBit */

	RTS_IEC_WORD addr;					/* VAR_INPUT */	
	RTS_IEC_BYTE num;					/* VAR_INPUT */	
	RTS_IEC_USINT **data;				/* VAR_IN_OUT */	
} modbusslavereadbit_struct;

/**
 * <description>modbusslavereadbit_main</description>
 */
typedef struct tagmodbusslavereadbit_main_struct
{
	modbusslavereadbit_struct *pInstance;	/* VAR_INPUT */	
} modbusslavereadbit_main_struct;

void CDECL CDECL_EXT modbusslavereadbit__main(modbusslavereadbit_main_struct *p);
typedef void (CDECL CDECL_EXT* PFMODBUSSLAVEREADBIT__MAIN_IEC) (modbusslavereadbit_main_struct *p);
#if defined(CMPMODBUSLIB_NOTIMPLEMENTED) || defined(MODBUSSLAVEREADBIT__MAIN_NOTIMPLEMENTED)
	#define USE_modbusslavereadbit__main
	#define EXT_modbusslavereadbit__main
	#define GET_modbusslavereadbit__main(fl)  ERR_NOTIMPLEMENTED
	#define CAL_modbusslavereadbit__main(p0) 
	#define CHK_modbusslavereadbit__main  FALSE
	#define EXP_modbusslavereadbit__main  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_modbusslavereadbit__main
	#define EXT_modbusslavereadbit__main
	#define GET_modbusslavereadbit__main(fl)  CAL_CMGETAPI( "modbusslavereadbit__main" ) 
	#define CAL_modbusslavereadbit__main  modbusslavereadbit__main
	#define CHK_modbusslavereadbit__main  TRUE
	#define EXP_modbusslavereadbit__main  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"modbusslavereadbit__main", (RTS_UINTPTR)modbusslavereadbit__main, 1, 0x9E88DCD4, 0x01000000) 
#elif defined(MIXED_LINK) && !defined(CMPMODBUSLIB_EXTERNAL)
	#define USE_modbusslavereadbit__main
	#define EXT_modbusslavereadbit__main
	#define GET_modbusslavereadbit__main(fl)  CAL_CMGETAPI( "modbusslavereadbit__main" ) 
	#define CAL_modbusslavereadbit__main  modbusslavereadbit__main
	#define CHK_modbusslavereadbit__main  TRUE
	#define EXP_modbusslavereadbit__main  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"modbusslavereadbit__main", (RTS_UINTPTR)modbusslavereadbit__main, 1, 0x9E88DCD4, 0x01000000) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpModbusLibmodbusslavereadbit__main
	#define EXT_CmpModbusLibmodbusslavereadbit__main
	#define GET_CmpModbusLibmodbusslavereadbit__main  ERR_OK
	#define CAL_CmpModbusLibmodbusslavereadbit__main  modbusslavereadbit__main
	#define CHK_CmpModbusLibmodbusslavereadbit__main  TRUE
	#define EXP_CmpModbusLibmodbusslavereadbit__main  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"modbusslavereadbit__main", (RTS_UINTPTR)modbusslavereadbit__main, 1, 0x9E88DCD4, 0x01000000) 
#elif defined(CPLUSPLUS)
	#define USE_modbusslavereadbit__main
	#define EXT_modbusslavereadbit__main
	#define GET_modbusslavereadbit__main(fl)  CAL_CMGETAPI( "modbusslavereadbit__main" ) 
	#define CAL_modbusslavereadbit__main  modbusslavereadbit__main
	#define CHK_modbusslavereadbit__main  TRUE
	#define EXP_modbusslavereadbit__main  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"modbusslavereadbit__main", (RTS_UINTPTR)modbusslavereadbit__main, 1, 0x9E88DCD4, 0x01000000) 
#else /* DYNAMIC_LINK */
	#define USE_modbusslavereadbit__main  PFMODBUSSLAVEREADBIT__MAIN_IEC pfmodbusslavereadbit__main;
	#define EXT_modbusslavereadbit__main  extern PFMODBUSSLAVEREADBIT__MAIN_IEC pfmodbusslavereadbit__main;
	#define GET_modbusslavereadbit__main(fl)  s_pfCMGetAPI2( "modbusslavereadbit__main", (RTS_VOID_FCTPTR *)&pfmodbusslavereadbit__main, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0x9E88DCD4, 0x01000000)
	#define CAL_modbusslavereadbit__main  pfmodbusslavereadbit__main
	#define CHK_modbusslavereadbit__main  (pfmodbusslavereadbit__main != NULL)
	#define EXP_modbusslavereadbit__main   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"modbusslavereadbit__main", (RTS_UINTPTR)modbusslavereadbit__main, 1, 0x9E88DCD4, 0x01000000) 
#endif


/**
 * <description>modbusslavereadreg__main</description>
 */
typedef struct tagmodbusslavereadreg_struct
{
	void* __VFTABLEPOINTER;				/* Pointer to virtual function table */

	/* Member variables of ModbusSlaveReadReg */

	RTS_IEC_WORD addr;					/* VAR_INPUT */	
	RTS_IEC_BYTE num;					/* VAR_INPUT */	
	RTS_IEC_UINT **data;				/* VAR_IN_OUT */	
} modbusslavereadreg_struct;

/**
 * <description>modbusslavereadreg_main</description>
 */
typedef struct tagmodbusslavereadreg_main_struct
{
	modbusslavereadreg_struct *pInstance;	/* VAR_INPUT */	
} modbusslavereadreg_main_struct;

void CDECL CDECL_EXT modbusslavereadreg__main(modbusslavereadreg_main_struct *p);
typedef void (CDECL CDECL_EXT* PFMODBUSSLAVEREADREG__MAIN_IEC) (modbusslavereadreg_main_struct *p);
#if defined(CMPMODBUSLIB_NOTIMPLEMENTED) || defined(MODBUSSLAVEREADREG__MAIN_NOTIMPLEMENTED)
	#define USE_modbusslavereadreg__main
	#define EXT_modbusslavereadreg__main
	#define GET_modbusslavereadreg__main(fl)  ERR_NOTIMPLEMENTED
	#define CAL_modbusslavereadreg__main(p0) 
	#define CHK_modbusslavereadreg__main  FALSE
	#define EXP_modbusslavereadreg__main  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_modbusslavereadreg__main
	#define EXT_modbusslavereadreg__main
	#define GET_modbusslavereadreg__main(fl)  CAL_CMGETAPI( "modbusslavereadreg__main" ) 
	#define CAL_modbusslavereadreg__main  modbusslavereadreg__main
	#define CHK_modbusslavereadreg__main  TRUE
	#define EXP_modbusslavereadreg__main  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"modbusslavereadreg__main", (RTS_UINTPTR)modbusslavereadreg__main, 1, 0x0A3164DE, 0x01000000) 
#elif defined(MIXED_LINK) && !defined(CMPMODBUSLIB_EXTERNAL)
	#define USE_modbusslavereadreg__main
	#define EXT_modbusslavereadreg__main
	#define GET_modbusslavereadreg__main(fl)  CAL_CMGETAPI( "modbusslavereadreg__main" ) 
	#define CAL_modbusslavereadreg__main  modbusslavereadreg__main
	#define CHK_modbusslavereadreg__main  TRUE
	#define EXP_modbusslavereadreg__main  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"modbusslavereadreg__main", (RTS_UINTPTR)modbusslavereadreg__main, 1, 0x0A3164DE, 0x01000000) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpModbusLibmodbusslavereadreg__main
	#define EXT_CmpModbusLibmodbusslavereadreg__main
	#define GET_CmpModbusLibmodbusslavereadreg__main  ERR_OK
	#define CAL_CmpModbusLibmodbusslavereadreg__main  modbusslavereadreg__main
	#define CHK_CmpModbusLibmodbusslavereadreg__main  TRUE
	#define EXP_CmpModbusLibmodbusslavereadreg__main  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"modbusslavereadreg__main", (RTS_UINTPTR)modbusslavereadreg__main, 1, 0x0A3164DE, 0x01000000) 
#elif defined(CPLUSPLUS)
	#define USE_modbusslavereadreg__main
	#define EXT_modbusslavereadreg__main
	#define GET_modbusslavereadreg__main(fl)  CAL_CMGETAPI( "modbusslavereadreg__main" ) 
	#define CAL_modbusslavereadreg__main  modbusslavereadreg__main
	#define CHK_modbusslavereadreg__main  TRUE
	#define EXP_modbusslavereadreg__main  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"modbusslavereadreg__main", (RTS_UINTPTR)modbusslavereadreg__main, 1, 0x0A3164DE, 0x01000000) 
#else /* DYNAMIC_LINK */
	#define USE_modbusslavereadreg__main  PFMODBUSSLAVEREADREG__MAIN_IEC pfmodbusslavereadreg__main;
	#define EXT_modbusslavereadreg__main  extern PFMODBUSSLAVEREADREG__MAIN_IEC pfmodbusslavereadreg__main;
	#define GET_modbusslavereadreg__main(fl)  s_pfCMGetAPI2( "modbusslavereadreg__main", (RTS_VOID_FCTPTR *)&pfmodbusslavereadreg__main, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0x0A3164DE, 0x01000000)
	#define CAL_modbusslavereadreg__main  pfmodbusslavereadreg__main
	#define CHK_modbusslavereadreg__main  (pfmodbusslavereadreg__main != NULL)
	#define EXP_modbusslavereadreg__main   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"modbusslavereadreg__main", (RTS_UINTPTR)modbusslavereadreg__main, 1, 0x0A3164DE, 0x01000000) 
#endif


/**
 * <description>modbusslavewritebit__main</description>
 */
typedef struct tagmodbusslavewritebit_struct
{
	void* __VFTABLEPOINTER;				/* Pointer to virtual function table */

	/* Member variables of ModbusSlaveWriteBit */

	RTS_IEC_WORD addr;					/* VAR_INPUT */	
	RTS_IEC_BYTE num;					/* VAR_INPUT */	
	RTS_IEC_USINT data[256];			/* VAR_INPUT */	
} modbusslavewritebit_struct;

/**
 * <description>modbusslavewritebit_main</description>
 */
typedef struct tagmodbusslavewritebit_main_struct
{
	modbusslavewritebit_struct *pInstance;	/* VAR_INPUT */	
} modbusslavewritebit_main_struct;

void CDECL CDECL_EXT modbusslavewritebit__main(modbusslavewritebit_main_struct *p);
typedef void (CDECL CDECL_EXT* PFMODBUSSLAVEWRITEBIT__MAIN_IEC) (modbusslavewritebit_main_struct *p);
#if defined(CMPMODBUSLIB_NOTIMPLEMENTED) || defined(MODBUSSLAVEWRITEBIT__MAIN_NOTIMPLEMENTED)
	#define USE_modbusslavewritebit__main
	#define EXT_modbusslavewritebit__main
	#define GET_modbusslavewritebit__main(fl)  ERR_NOTIMPLEMENTED
	#define CAL_modbusslavewritebit__main(p0) 
	#define CHK_modbusslavewritebit__main  FALSE
	#define EXP_modbusslavewritebit__main  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_modbusslavewritebit__main
	#define EXT_modbusslavewritebit__main
	#define GET_modbusslavewritebit__main(fl)  CAL_CMGETAPI( "modbusslavewritebit__main" ) 
	#define CAL_modbusslavewritebit__main  modbusslavewritebit__main
	#define CHK_modbusslavewritebit__main  TRUE
	#define EXP_modbusslavewritebit__main  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"modbusslavewritebit__main", (RTS_UINTPTR)modbusslavewritebit__main, 1, 0xB46A3E05, 0x01000000) 
#elif defined(MIXED_LINK) && !defined(CMPMODBUSLIB_EXTERNAL)
	#define USE_modbusslavewritebit__main
	#define EXT_modbusslavewritebit__main
	#define GET_modbusslavewritebit__main(fl)  CAL_CMGETAPI( "modbusslavewritebit__main" ) 
	#define CAL_modbusslavewritebit__main  modbusslavewritebit__main
	#define CHK_modbusslavewritebit__main  TRUE
	#define EXP_modbusslavewritebit__main  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"modbusslavewritebit__main", (RTS_UINTPTR)modbusslavewritebit__main, 1, 0xB46A3E05, 0x01000000) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpModbusLibmodbusslavewritebit__main
	#define EXT_CmpModbusLibmodbusslavewritebit__main
	#define GET_CmpModbusLibmodbusslavewritebit__main  ERR_OK
	#define CAL_CmpModbusLibmodbusslavewritebit__main  modbusslavewritebit__main
	#define CHK_CmpModbusLibmodbusslavewritebit__main  TRUE
	#define EXP_CmpModbusLibmodbusslavewritebit__main  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"modbusslavewritebit__main", (RTS_UINTPTR)modbusslavewritebit__main, 1, 0xB46A3E05, 0x01000000) 
#elif defined(CPLUSPLUS)
	#define USE_modbusslavewritebit__main
	#define EXT_modbusslavewritebit__main
	#define GET_modbusslavewritebit__main(fl)  CAL_CMGETAPI( "modbusslavewritebit__main" ) 
	#define CAL_modbusslavewritebit__main  modbusslavewritebit__main
	#define CHK_modbusslavewritebit__main  TRUE
	#define EXP_modbusslavewritebit__main  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"modbusslavewritebit__main", (RTS_UINTPTR)modbusslavewritebit__main, 1, 0xB46A3E05, 0x01000000) 
#else /* DYNAMIC_LINK */
	#define USE_modbusslavewritebit__main  PFMODBUSSLAVEWRITEBIT__MAIN_IEC pfmodbusslavewritebit__main;
	#define EXT_modbusslavewritebit__main  extern PFMODBUSSLAVEWRITEBIT__MAIN_IEC pfmodbusslavewritebit__main;
	#define GET_modbusslavewritebit__main(fl)  s_pfCMGetAPI2( "modbusslavewritebit__main", (RTS_VOID_FCTPTR *)&pfmodbusslavewritebit__main, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0xB46A3E05, 0x01000000)
	#define CAL_modbusslavewritebit__main  pfmodbusslavewritebit__main
	#define CHK_modbusslavewritebit__main  (pfmodbusslavewritebit__main != NULL)
	#define EXP_modbusslavewritebit__main   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"modbusslavewritebit__main", (RTS_UINTPTR)modbusslavewritebit__main, 1, 0xB46A3E05, 0x01000000) 
#endif


/**
 * <description>modbusslavewritereg__main</description>
 */
typedef struct tagmodbusslavewritereg_struct
{
	void* __VFTABLEPOINTER;				/* Pointer to virtual function table */

	/* Member variables of ModbusSlaveWriteReg */

	RTS_IEC_WORD addr;					/* VAR_INPUT */	
	RTS_IEC_BYTE num;					/* VAR_INPUT */	
	RTS_IEC_UINT data[256];				/* VAR_INPUT */	
} modbusslavewritereg_struct;

/**
 * <description>modbusslavewritereg_main</description>
 */
typedef struct tagmodbusslavewritereg_main_struct
{
	modbusslavewritereg_struct *pInstance;	/* VAR_INPUT */	
} modbusslavewritereg_main_struct;

void CDECL CDECL_EXT modbusslavewritereg__main(modbusslavewritereg_main_struct *p);
typedef void (CDECL CDECL_EXT* PFMODBUSSLAVEWRITEREG__MAIN_IEC) (modbusslavewritereg_main_struct *p);
#if defined(CMPMODBUSLIB_NOTIMPLEMENTED) || defined(MODBUSSLAVEWRITEREG__MAIN_NOTIMPLEMENTED)
	#define USE_modbusslavewritereg__main
	#define EXT_modbusslavewritereg__main
	#define GET_modbusslavewritereg__main(fl)  ERR_NOTIMPLEMENTED
	#define CAL_modbusslavewritereg__main(p0) 
	#define CHK_modbusslavewritereg__main  FALSE
	#define EXP_modbusslavewritereg__main  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_modbusslavewritereg__main
	#define EXT_modbusslavewritereg__main
	#define GET_modbusslavewritereg__main(fl)  CAL_CMGETAPI( "modbusslavewritereg__main" ) 
	#define CAL_modbusslavewritereg__main  modbusslavewritereg__main
	#define CHK_modbusslavewritereg__main  TRUE
	#define EXP_modbusslavewritereg__main  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"modbusslavewritereg__main", (RTS_UINTPTR)modbusslavewritereg__main, 1, 0x9CB5E23D, 0x01000000) 
#elif defined(MIXED_LINK) && !defined(CMPMODBUSLIB_EXTERNAL)
	#define USE_modbusslavewritereg__main
	#define EXT_modbusslavewritereg__main
	#define GET_modbusslavewritereg__main(fl)  CAL_CMGETAPI( "modbusslavewritereg__main" ) 
	#define CAL_modbusslavewritereg__main  modbusslavewritereg__main
	#define CHK_modbusslavewritereg__main  TRUE
	#define EXP_modbusslavewritereg__main  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"modbusslavewritereg__main", (RTS_UINTPTR)modbusslavewritereg__main, 1, 0x9CB5E23D, 0x01000000) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpModbusLibmodbusslavewritereg__main
	#define EXT_CmpModbusLibmodbusslavewritereg__main
	#define GET_CmpModbusLibmodbusslavewritereg__main  ERR_OK
	#define CAL_CmpModbusLibmodbusslavewritereg__main  modbusslavewritereg__main
	#define CHK_CmpModbusLibmodbusslavewritereg__main  TRUE
	#define EXP_CmpModbusLibmodbusslavewritereg__main  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"modbusslavewritereg__main", (RTS_UINTPTR)modbusslavewritereg__main, 1, 0x9CB5E23D, 0x01000000) 
#elif defined(CPLUSPLUS)
	#define USE_modbusslavewritereg__main
	#define EXT_modbusslavewritereg__main
	#define GET_modbusslavewritereg__main(fl)  CAL_CMGETAPI( "modbusslavewritereg__main" ) 
	#define CAL_modbusslavewritereg__main  modbusslavewritereg__main
	#define CHK_modbusslavewritereg__main  TRUE
	#define EXP_modbusslavewritereg__main  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"modbusslavewritereg__main", (RTS_UINTPTR)modbusslavewritereg__main, 1, 0x9CB5E23D, 0x01000000) 
#else /* DYNAMIC_LINK */
	#define USE_modbusslavewritereg__main  PFMODBUSSLAVEWRITEREG__MAIN_IEC pfmodbusslavewritereg__main;
	#define EXT_modbusslavewritereg__main  extern PFMODBUSSLAVEWRITEREG__MAIN_IEC pfmodbusslavewritereg__main;
	#define GET_modbusslavewritereg__main(fl)  s_pfCMGetAPI2( "modbusslavewritereg__main", (RTS_VOID_FCTPTR *)&pfmodbusslavewritereg__main, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0x9CB5E23D, 0x01000000)
	#define CAL_modbusslavewritereg__main  pfmodbusslavewritereg__main
	#define CHK_modbusslavewritereg__main  (pfmodbusslavewritereg__main != NULL)
	#define EXP_modbusslavewritereg__main   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"modbusslavewritereg__main", (RTS_UINTPTR)modbusslavewritereg__main, 1, 0x9CB5E23D, 0x01000000) 
#endif


/**
 * <description>modbuswritebit__main</description>
 */
typedef struct tagmodbuswritebit_struct
{
	void* __VFTABLEPOINTER;				/* Pointer to virtual function table */

	/* Member variables of ModbusWriteBit */

	RTS_IEC_WORD addr;					/* VAR_INPUT */	
	RTS_IEC_BYTE num;					/* VAR_INPUT */	
	RTS_IEC_BYTE data[32];				/* VAR_INPUT */	
} modbuswritebit_struct;

/**
 * <description>modbuswritebit_main</description>
 */
typedef struct tagmodbuswritebit_main_struct
{
	modbuswritebit_struct *pInstance;	/* VAR_INPUT */	
} modbuswritebit_main_struct;

void CDECL CDECL_EXT modbuswritebit__main(modbuswritebit_main_struct *p);
typedef void (CDECL CDECL_EXT* PFMODBUSWRITEBIT__MAIN_IEC) (modbuswritebit_main_struct *p);
#if defined(CMPMODBUSLIB_NOTIMPLEMENTED) || defined(MODBUSWRITEBIT__MAIN_NOTIMPLEMENTED)
	#define USE_modbuswritebit__main
	#define EXT_modbuswritebit__main
	#define GET_modbuswritebit__main(fl)  ERR_NOTIMPLEMENTED
	#define CAL_modbuswritebit__main(p0) 
	#define CHK_modbuswritebit__main  FALSE
	#define EXP_modbuswritebit__main  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_modbuswritebit__main
	#define EXT_modbuswritebit__main
	#define GET_modbuswritebit__main(fl)  CAL_CMGETAPI( "modbuswritebit__main" ) 
	#define CAL_modbuswritebit__main  modbuswritebit__main
	#define CHK_modbuswritebit__main  TRUE
	#define EXP_modbuswritebit__main  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"modbuswritebit__main", (RTS_UINTPTR)modbuswritebit__main, 1, 0x65549537, 0x01000000) 
#elif defined(MIXED_LINK) && !defined(CMPMODBUSLIB_EXTERNAL)
	#define USE_modbuswritebit__main
	#define EXT_modbuswritebit__main
	#define GET_modbuswritebit__main(fl)  CAL_CMGETAPI( "modbuswritebit__main" ) 
	#define CAL_modbuswritebit__main  modbuswritebit__main
	#define CHK_modbuswritebit__main  TRUE
	#define EXP_modbuswritebit__main  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"modbuswritebit__main", (RTS_UINTPTR)modbuswritebit__main, 1, 0x65549537, 0x01000000) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpModbusLibmodbuswritebit__main
	#define EXT_CmpModbusLibmodbuswritebit__main
	#define GET_CmpModbusLibmodbuswritebit__main  ERR_OK
	#define CAL_CmpModbusLibmodbuswritebit__main  modbuswritebit__main
	#define CHK_CmpModbusLibmodbuswritebit__main  TRUE
	#define EXP_CmpModbusLibmodbuswritebit__main  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"modbuswritebit__main", (RTS_UINTPTR)modbuswritebit__main, 1, 0x65549537, 0x01000000) 
#elif defined(CPLUSPLUS)
	#define USE_modbuswritebit__main
	#define EXT_modbuswritebit__main
	#define GET_modbuswritebit__main(fl)  CAL_CMGETAPI( "modbuswritebit__main" ) 
	#define CAL_modbuswritebit__main  modbuswritebit__main
	#define CHK_modbuswritebit__main  TRUE
	#define EXP_modbuswritebit__main  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"modbuswritebit__main", (RTS_UINTPTR)modbuswritebit__main, 1, 0x65549537, 0x01000000) 
#else /* DYNAMIC_LINK */
	#define USE_modbuswritebit__main  PFMODBUSWRITEBIT__MAIN_IEC pfmodbuswritebit__main;
	#define EXT_modbuswritebit__main  extern PFMODBUSWRITEBIT__MAIN_IEC pfmodbuswritebit__main;
	#define GET_modbuswritebit__main(fl)  s_pfCMGetAPI2( "modbuswritebit__main", (RTS_VOID_FCTPTR *)&pfmodbuswritebit__main, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0x65549537, 0x01000000)
	#define CAL_modbuswritebit__main  pfmodbuswritebit__main
	#define CHK_modbuswritebit__main  (pfmodbuswritebit__main != NULL)
	#define EXP_modbuswritebit__main   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"modbuswritebit__main", (RTS_UINTPTR)modbuswritebit__main, 1, 0x65549537, 0x01000000) 
#endif


/**
 * <description>modbuswritereg__main</description>
 */
typedef struct tagmodbuswritereg_struct
{
	void* __VFTABLEPOINTER;				/* Pointer to virtual function table */

	/* Member variables of ModbusWriteReg */

	RTS_IEC_WORD addr;					/* VAR_INPUT */	
	RTS_IEC_BYTE num;					/* VAR_INPUT */	
	RTS_IEC_WORD data[32];				/* VAR_INPUT */	
} modbuswritereg_struct;

/**
 * <description>modbuswritereg_main</description>
 */
typedef struct tagmodbuswritereg_main_struct
{
	modbuswritereg_struct *pInstance;	/* VAR_INPUT */	
} modbuswritereg_main_struct;

void CDECL CDECL_EXT modbuswritereg__main(modbuswritereg_main_struct *p);
typedef void (CDECL CDECL_EXT* PFMODBUSWRITEREG__MAIN_IEC) (modbuswritereg_main_struct *p);
#if defined(CMPMODBUSLIB_NOTIMPLEMENTED) || defined(MODBUSWRITEREG__MAIN_NOTIMPLEMENTED)
	#define USE_modbuswritereg__main
	#define EXT_modbuswritereg__main
	#define GET_modbuswritereg__main(fl)  ERR_NOTIMPLEMENTED
	#define CAL_modbuswritereg__main(p0) 
	#define CHK_modbuswritereg__main  FALSE
	#define EXP_modbuswritereg__main  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_modbuswritereg__main
	#define EXT_modbuswritereg__main
	#define GET_modbuswritereg__main(fl)  CAL_CMGETAPI( "modbuswritereg__main" ) 
	#define CAL_modbuswritereg__main  modbuswritereg__main
	#define CHK_modbuswritereg__main  TRUE
	#define EXP_modbuswritereg__main  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"modbuswritereg__main", (RTS_UINTPTR)modbuswritereg__main, 1, 0x430FBCF6, 0x01000000) 
#elif defined(MIXED_LINK) && !defined(CMPMODBUSLIB_EXTERNAL)
	#define USE_modbuswritereg__main
	#define EXT_modbuswritereg__main
	#define GET_modbuswritereg__main(fl)  CAL_CMGETAPI( "modbuswritereg__main" ) 
	#define CAL_modbuswritereg__main  modbuswritereg__main
	#define CHK_modbuswritereg__main  TRUE
	#define EXP_modbuswritereg__main  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"modbuswritereg__main", (RTS_UINTPTR)modbuswritereg__main, 1, 0x430FBCF6, 0x01000000) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpModbusLibmodbuswritereg__main
	#define EXT_CmpModbusLibmodbuswritereg__main
	#define GET_CmpModbusLibmodbuswritereg__main  ERR_OK
	#define CAL_CmpModbusLibmodbuswritereg__main  modbuswritereg__main
	#define CHK_CmpModbusLibmodbuswritereg__main  TRUE
	#define EXP_CmpModbusLibmodbuswritereg__main  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"modbuswritereg__main", (RTS_UINTPTR)modbuswritereg__main, 1, 0x430FBCF6, 0x01000000) 
#elif defined(CPLUSPLUS)
	#define USE_modbuswritereg__main
	#define EXT_modbuswritereg__main
	#define GET_modbuswritereg__main(fl)  CAL_CMGETAPI( "modbuswritereg__main" ) 
	#define CAL_modbuswritereg__main  modbuswritereg__main
	#define CHK_modbuswritereg__main  TRUE
	#define EXP_modbuswritereg__main  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"modbuswritereg__main", (RTS_UINTPTR)modbuswritereg__main, 1, 0x430FBCF6, 0x01000000) 
#else /* DYNAMIC_LINK */
	#define USE_modbuswritereg__main  PFMODBUSWRITEREG__MAIN_IEC pfmodbuswritereg__main;
	#define EXT_modbuswritereg__main  extern PFMODBUSWRITEREG__MAIN_IEC pfmodbuswritereg__main;
	#define GET_modbuswritereg__main(fl)  s_pfCMGetAPI2( "modbuswritereg__main", (RTS_VOID_FCTPTR *)&pfmodbuswritereg__main, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0x430FBCF6, 0x01000000)
	#define CAL_modbuswritereg__main  pfmodbuswritereg__main
	#define CHK_modbuswritereg__main  (pfmodbuswritereg__main != NULL)
	#define EXP_modbuswritereg__main   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"modbuswritereg__main", (RTS_UINTPTR)modbuswritereg__main, 1, 0x430FBCF6, 0x01000000) 
#endif


#ifdef __cplusplus
}
#endif

/** EXTERN LIB SECTION END **/




typedef struct
{
	IBase_C *pBase;
} ICmpModbusLib_C;

#ifdef CPLUSPLUS
class ICmpModbusLib : public IBase
{
	public:
};
	#ifndef ITF_CmpModbusLib
		#define ITF_CmpModbusLib static ICmpModbusLib *pICmpModbusLib = NULL;
	#endif
	#define EXTITF_CmpModbusLib
#else	/*CPLUSPLUS*/
	typedef ICmpModbusLib_C		ICmpModbusLib;
	#ifndef ITF_CmpModbusLib
		#define ITF_CmpModbusLib
	#endif
	#define EXTITF_CmpModbusLib
#endif

#ifdef CPLUSPLUS_ONLY
  #undef CPLUSPLUS_ONLY
#endif

#endif /*_CMPMODBUSLIBITF_H_*/
