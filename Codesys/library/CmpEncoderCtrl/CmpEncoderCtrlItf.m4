/**
 * <interfacename>CmpEncoderCtrl</interfacename>
 * <description></description>
 *
 * <copyright></copyright>
 */

SET_INTERFACE_NAME(`CmpEncoderCtrl')

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

DEF_API(`void',`CDECL',`configencoder__main',`(configencoder_main_struct *p)',1,0x06280A78,0x01000000)

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

DEF_API(`void',`CDECL',`readencodercountera__main',`(readencodercountera_main_struct *p)',1,0x9DA91CE6,0x01000000)

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

DEF_API(`void',`CDECL',`readencodercounterz__main',`(readencodercounterz_main_struct *p)',1,0x3A4B34EB,0x01000000)

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

DEF_API(`void',`CDECL',`readencoderdirection__main',`(readencoderdirection_main_struct *p)',1,0x6DFB027B,0x01000000)

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

DEF_API(`void',`CDECL',`setencodercounter__main',`(setencodercounter_main_struct *p)',1,0x7E81583C,0x01000000)

#ifdef __cplusplus
}
#endif

/** EXTERN LIB SECTION END **/

