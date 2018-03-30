/**
 * <interfacename>CmpPwmCtrl</interfacename>
 * <description></description>
 *
 * <copyright></copyright>
 */

SET_INTERFACE_NAME(`CmpPwmCtrl')

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

DEF_API(`void',`CDECL',`pou__main',`(pou_main_struct *p)',1,0x15E68C4A,0x01000000)

#ifdef __cplusplus
}
#endif

/** EXTERN LIB SECTION END **/

