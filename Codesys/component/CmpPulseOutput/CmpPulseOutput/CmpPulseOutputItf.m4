/**
 * <interfacename>CmpPulseOutput</interfacename>
 * <description></description>
 *
 * <copyright></copyright>
 */

SET_INTERFACE_NAME(`CmpPulseOutput')

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

DEF_API(`void',`CDECL',`ispulseover__main',`(ispulseover_main_struct *p)',1,0xCD4A0220,0x01000000)

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

DEF_API(`void',`CDECL',`setpulseamountandstart__main',`(setpulseamountandstart_main_struct *p)',1,0x32C1BCFE,0x01000000)

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

DEF_API(`void',`CDECL',`setpulsefreq__main',`(setpulsefreq_main_struct *p)',1,0x1B741B61,0x01000000)

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

DEF_API(`void',`CDECL',`stoppulse__main',`(stoppulse_main_struct *p)',1,0x4D0AB68B,0x01000000)

#ifdef __cplusplus
}
#endif

/** EXTERN LIB SECTION END **/

