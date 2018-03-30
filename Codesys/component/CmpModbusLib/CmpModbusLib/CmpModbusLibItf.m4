/**
 * <interfacename>CmpModbusLib</interfacename>
 * <description></description>
 *
 * <copyright></copyright>
 */

SET_INTERFACE_NAME(`CmpModbusLib')

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

DEF_API(`void',`CDECL',`closemodbus__main',`(closemodbus_main_struct *p)',1,0x32BCE1D3,0x01000000)

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

DEF_API(`void',`CDECL',`initmodbusrtu__main',`(initmodbusrtu_main_struct *p)',1,0x28BA41FA,0x01000000)

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

DEF_API(`void',`CDECL',`modbusreadbit__main',`(modbusreadbit_main_struct *p)',1,0x71236F41,0x01000000)

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

DEF_API(`void',`CDECL',`modbusreadreg__main',`(modbusreadreg_main_struct *p)',1,0x3CF79B14,0x01000000)

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

DEF_API(`void',`CDECL',`modbusslavereadbit__main',`(modbusslavereadbit_main_struct *p)',1,0x9E88DCD4,0x01000000)

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

DEF_API(`void',`CDECL',`modbusslavereadreg__main',`(modbusslavereadreg_main_struct *p)',1,0x0A3164DE,0x01000000)

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

DEF_API(`void',`CDECL',`modbusslavewritebit__main',`(modbusslavewritebit_main_struct *p)',1,0xB46A3E05,0x01000000)

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

DEF_API(`void',`CDECL',`modbusslavewritereg__main',`(modbusslavewritereg_main_struct *p)',1,0x9CB5E23D,0x01000000)

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

DEF_API(`void',`CDECL',`modbuswritebit__main',`(modbuswritebit_main_struct *p)',1,0x65549537,0x01000000)

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

DEF_API(`void',`CDECL',`modbuswritereg__main',`(modbuswritereg_main_struct *p)',1,0x430FBCF6,0x01000000)

#ifdef __cplusplus
}
#endif

/** EXTERN LIB SECTION END **/

