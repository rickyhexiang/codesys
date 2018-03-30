/**
 * <interfacename>CmpBLD</interfacename>
 * <description></description>
 *
 * <copyright></copyright>
 */

SET_INTERFACE_NAME(`CmpBLD')

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

DEF_API(`void',`CDECL',`bld__main',`(bld_main_struct *p)',1,0x66125D34,0x01000000)

#ifdef __cplusplus
}
#endif

/** EXTERN LIB SECTION END **/

