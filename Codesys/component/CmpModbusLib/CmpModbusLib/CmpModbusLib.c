/**
 * <name>CmpTemplate.c</name>
 * <description> 
 *  Example for an empty runtime component frame that can be used as a starting point to develop own components.
 *
 *  MANDATORY FUNCTIONS:
 *  - ComponentEntry()
 *  - ExportFunctions()
 *  - ImportFunctions()
 *  - CmpGetVersion()
 *  - HookFunction()
 * </description>
 *
 * <copyright>(c) 2003-2016 3S-Smart Software Solutions</copyright>
 */

#include "CmpStd.h"
#include "CmpModbusLibDep.h"

#include "modbus.c"
#include "modbus-rtu.c"
#include "modbus-data.c"

USE_STMT

#define bool BOOL

#define TEST_BIT(x,offset)  (1&((x)>>offset))
#define SET_BIT(x,offset)   ((x)|=(1<<offset))
#define CLR_BIT(x,offset)   ((x)&=(~(1<<(offset))))

#define GPIO_DIR_OUTPUT			0
#define GPIO_DIR_INPUT			1

#define GPIO_REG_BASE			0xE000A000

#define GPIO_REG_DATA_OUTPUT_BANK2		0x48
#define GPIO_REG_DATA_OUTPUT_BANK3		0x4C
#define GPIO_REG_DIR_BANK2		0x284
#define GPIO_REG_OEN_BANK2		0x288
#define GPIO_REG_DIR_BANK3		0x2C4
#define GPIO_REG_OEN_BANK3		0x2C8

#define SLAVE_BITS_MAX_NUMBER           1024
#define SLAVE_REGISTERS_MAX_NUMBER      256

int g_ComOverFlag = 0;
int g_ComTaskID = 0;

modbus_t *mb = NULL;
modbus_mapping_t *mb_mapping = NULL;

int InitGpioBank(int bank, bool dir)
{
	switch(bank)
	{
	case 0:
		break;
	case 1:
		break;
	case 2:
		if(dir == GPIO_DIR_OUTPUT)
		{
			sysOutLong(GPIO_REG_BASE + GPIO_REG_DIR_BANK2, 0x001fe000);
			sysOutLong(GPIO_REG_BASE + GPIO_REG_OEN_BANK2, 0x001fe000);
			sysOutLong(GPIO_REG_BASE + GPIO_REG_DATA_OUTPUT_BANK2, 0);
		}
		else
		{
			sysOutLong(GPIO_REG_BASE + GPIO_REG_DIR_BANK2, 0);
			sysOutLong(GPIO_REG_BASE + GPIO_REG_OEN_BANK2, 0);			
		}
		break;
	case 3:
		break;
	default:
		break;	
	}
	
	return 0;
}

int InitGpio(int index, bool dir, bool value)
{
    unsigned long ulData = 0;

    if((index < 32) && (index >= 0))
    {

    }
    else if((index >= 32) && (index < 53))
    {

    }
    else if((index >= 54) && (index < 86))
    {
        if(dir == GPIO_DIR_OUTPUT)
        {
            ulData = sysInLong(GPIO_REG_BASE + GPIO_REG_DIR_BANK2);
            SET_BIT(ulData, index - 54);
            sysOutLong(GPIO_REG_BASE + GPIO_REG_DIR_BANK2, ulData);

            ulData = sysInLong(GPIO_REG_BASE + GPIO_REG_OEN_BANK2);
            SET_BIT(ulData, index - 54);
            sysOutLong(GPIO_REG_BASE + GPIO_REG_OEN_BANK2, ulData);

            ulData = sysInLong(GPIO_REG_BASE + GPIO_REG_DATA_OUTPUT_BANK2);
            if(value)
                SET_BIT(ulData, index - 54);
            else
                CLR_BIT(ulData, index - 54);
            sysOutLong(GPIO_REG_BASE + GPIO_REG_DATA_OUTPUT_BANK2, ulData);
        }
    }
    else if((index >= 86) && (index <= 117))
    {
        if(dir == GPIO_DIR_OUTPUT)
        {
            ulData = sysInLong(GPIO_REG_BASE + GPIO_REG_DIR_BANK3);
            SET_BIT(ulData, index - 86);
            sysOutLong(GPIO_REG_BASE + GPIO_REG_DIR_BANK3, ulData);

            ulData = sysInLong(GPIO_REG_BASE + GPIO_REG_OEN_BANK3);
            SET_BIT(ulData, index - 86);
            sysOutLong(GPIO_REG_BASE + GPIO_REG_OEN_BANK3, ulData);

            ulData = sysInLong(GPIO_REG_BASE + GPIO_REG_DATA_OUTPUT_BANK3);
            if(value)
                SET_BIT(ulData, index - 86);
            else
                CLR_BIT(ulData, index - 86);
            sysOutLong(GPIO_REG_BASE + GPIO_REG_DATA_OUTPUT_BANK3, ulData);
        }
    }
    else
    {
        return -1;
    }

    return 0;
}


#ifndef RTS_COMPACT_MICRO

/**
 * <description>Entry function of the component. Called at startup for each component. Used to exchange function pointers with the component manager.</description>
 * <param name="pInitStruct" type="IN">Pointer to structure with:
 *		pfExportFunctions	OUT Pointer to function that exports component functions
 *		pfImportFunctions	OUT Pointer to function that imports functions from other components
 *		pfGetVersion		OUT Pointer to function to get component version
 *		pfRegisterAPI		IN	Pointer to component mangager function to register a api function
 *		pfGetAPI			IN	Pointer to component mangager function to get a api function
 *		pfCallHook			IN	Pointer to component mangager function to call a hook function
 * </param> 
 * <result>ERR_OK if component could be initialized, else error code.</result>
 */
DLL_DECL int CDECL ComponentEntry(INIT_STRUCT *pInitStruct)
{
	pInitStruct->CmpId = COMPONENT_ID;
	pInitStruct->pfExportFunctions = ExportFunctions;
	pInitStruct->pfImportFunctions = ImportFunctions;
	pInitStruct->pfGetVersion = CmpGetVersion;
	pInitStruct->pfHookFunction = HookFunction;
	pInitStruct->pfCreateInstance = NULL;
	pInitStruct->pfDeleteInstance = NULL;

	s_pfCMRegisterAPI = pInitStruct->pfCMRegisterAPI;
	s_pfCMRegisterAPI2 = pInitStruct->pfCMRegisterAPI2;
	s_pfCMGetAPI = pInitStruct->pfCMGetAPI;
	s_pfCMGetAPI2 = pInitStruct->pfCMGetAPI2;
	s_pfCMCallHook = pInitStruct->pfCMCallHook;
	s_pfCMRegisterClass = pInitStruct->pfCMRegisterClass;
	s_pfCMCreateInstance = pInitStruct->pfCMCreateInstance;
	return ERR_OK;
}

/**
 * <description>Publish exported functions to the component manager, to make them available for other components.
 * Use generated macro EXPORT_STMT.</description>
 * <result>ERR_OK or error code in case of error</result>
 */
static int CDECL ExportFunctions(void)
{
	/* Macro to export functions */
	EXPORT_STMT;
	return ERR_OK;
}

/**
 * <description>Import function pointers from other components. Use generated macro IMPORT_STMT.</description>
 * <result>ERR_OK or error code if function name could not be resolved</result>
 */
static int CDECL ImportFunctions(void)
{
	/* Macro to import functions */
	IMPORT_STMT;
	return ERR_OK;
}

/**
 * <description>Return the version of our component.</description>
 * <result>Version as defined in dep file</result>
 */
static RTS_UI32 CDECL CmpGetVersion(void)
{
	return CMP_VERSION;
}

#endif

/**
 * <description>Hook function to get all broadcast hooks of the component manager. All init and exit stuff must be implemented here!</description>
 * <param name="ulHook" type="IN">Kind of hook. See CH_ definitions in CmpItf.h for details.</param> 
 * <param name="ulParam1" type="IN">Hook specific first parameter. See definitions in CmpItf.h for details.</param> 
 * <param name="ulParam2" type="IN">Hook specific second parameter. See definitions in CmpItf.h for details.</param>  
 * <result>Error code</result>
 */
static RTS_RESULT CDECL HookFunction(RTS_UI32 ulHook, RTS_UINTPTR ulParam1, RTS_UINTPTR ulParam2)
{
	switch (ulHook)
	{
		case CH_INIT:
			if (CHK_LogAdd)
				CAL_LogAdd(STD_LOGGER, COMPONENT_ID, LOG_INFO, ERR_OK, 0, "CH_INIT");
			break;
		case CH_INIT2:
			if (CHK_LogAdd)
				CAL_LogAdd(STD_LOGGER, COMPONENT_ID, LOG_INFO, ERR_OK, 0, "CH_INIT2");
			break;
		case CH_INIT3:
			if (CHK_LogAdd)
				CAL_LogAdd(STD_LOGGER, COMPONENT_ID, LOG_INFO, ERR_OK, 0, "CH_INIT3");
			break;
		case CH_INIT_TASKS:
			if (CHK_LogAdd)
				CAL_LogAdd(STD_LOGGER, COMPONENT_ID, LOG_INFO, ERR_OK, 0, "CH_INIT_TASKS");
			break;
		case CH_INIT_COMM:
			if (CHK_LogAdd)
				CAL_LogAdd(STD_LOGGER, COMPONENT_ID, LOG_INFO, ERR_OK, 0, "CH_INIT_COMM");
			break;
		case CH_INIT_FINISHED:
			if (CHK_LogAdd)
				CAL_LogAdd(STD_LOGGER, COMPONENT_ID, LOG_INFO, ERR_OK, 0, "CH_INIT_FINISHED");
		    InitGpioBank(2, GPIO_DIR_OUTPUT);
		    InitGpio(63, GPIO_DIR_OUTPUT, 0);
			mb = NULL;
			break;

		/* Cyclic */
		case CH_COMM_CYCLE:
			break;

#ifndef RTS_COMPACT_MICRO
		case CH_EXIT_COMM:
			if (CHK_LogAdd)
				CAL_LogAdd(STD_LOGGER, COMPONENT_ID, LOG_INFO, ERR_OK, 0, "CH_EXIT_COMM");
			break;
		case CH_EXIT_TASKS:
			if (CHK_LogAdd)
				CAL_LogAdd(STD_LOGGER, COMPONENT_ID, LOG_INFO, ERR_OK, 0, "CH_EXIT_TASKS");
			break;
		case CH_EXIT3:
			if (CHK_LogAdd)
				CAL_LogAdd(STD_LOGGER, COMPONENT_ID, LOG_INFO, ERR_OK, 0, "CH_EXIT3");
			break;
		case CH_EXIT2:
			if (CHK_LogAdd)
				CAL_LogAdd(STD_LOGGER, COMPONENT_ID, LOG_INFO, ERR_OK, 0, "CH_EXIT2");
			break;
		case CH_EXIT:
		{
			if (CHK_LogAdd)
				CAL_LogAdd(STD_LOGGER, COMPONENT_ID, LOG_INFO, ERR_OK, 0, "CH_EXIT");
			EXIT_STMT;
			break;
		}
#endif

		default:
			break;
	}
	return ERR_OK;
}

int tModbusSlaveTask(modbus_t *modbus, modbus_mapping_t *mapping)
{
	uint8_t query[MODBUS_RTU_MAX_ADU_LENGTH];
    int ret = 0;
    
    modbus->debug = 0;
	while(!g_ComOverFlag)
	{
        ret = modbus_receive(modbus, query);
        if(ret > 0)
        {
            modbus_reply(modbus, query, ret, mapping);
        }
        else
        {
            //printf("modbus_receive ret %d,check state\n", ret);
            continue;
        }
        //modbus_reply[3]
    }
	
	return 0;
}

void CDECL CDECL_EXT initmodbusrtu__main(initmodbusrtu_main_struct *p)
{
#if 0
	RTS_IEC_BYTE com;					/* VAR_INPUT */	
	RTS_IEC_DWORD baud;					/* VAR_INPUT */	
	RTS_IEC_BYTE slave;					/* VAR_INPUT */	
	RTS_IEC_WORD timeout;				/* VAR_INPUT */	
	RTS_IEC_INT result;					/* VAR_OUTPUT */		
#endif
	char comName[16] = {0};
	struct timeval t;
	
	sprintf(comName, "/tyCo/%d", p->pInstance->com);

	printf("comName=%s\n", comName);

	if(mb == NULL)
	{
		mb = modbus_new_rtu(comName, p->pInstance->baud, 'N', 8, 1);
		if(mb == NULL)
		{
			p->pInstance->result = -1;
			printf("modbus_new_rtu fail\n");
			return;
		}			
		
		if(modbus_set_slave(mb, p->pInstance->slave) != 0)
		{
			p->pInstance->result = -1;
			printf("modbus_set_slave fail\n");
			return;
		}

		
		if(modbus_connect(mb) != 0)
		{
			p->pInstance->result = -2;
			printf("modbus_connect fail\n");
			return;
		}
		
		t.tv_sec=0;
		t.tv_usec=p->pInstance->timeout * 1000;
		printf("mb=%p, tv_usec=%d\n", mb, t.tv_usec);
		if(modbus_set_response_timeout(mb, t.tv_sec, t.tv_usec) != 0)
		{
			p->pInstance->result = -1;
			printf("modbus_set_response_timeout fail\n");
			return;
		}
		
	    /* modbus_mapping_new四个参数分别对应0X 1X 4X 3X，这里开辟0X 和 4X*/
	    mb_mapping = modbus_mapping_new(SLAVE_BITS_MAX_NUMBER, 0, SLAVE_REGISTERS_MAX_NUMBER, 0);
	    if(mb_mapping == NULL)
	    {
	        printf("modbus_mapping_new Failed...\n");
	    	modbus_close(mb);
	    	modbus_free(mb);

	        return;
	    }
	    memset(mb_mapping->tab_bits, 0, SLAVE_BITS_MAX_NUMBER);
	    memset(mb_mapping->tab_registers, 0, SLAVE_REGISTERS_MAX_NUMBER);
	    
	    g_ComTaskID = taskSpawn("tModbusSlaveTask", 60, 0, 1024 * 40, 
	                                (FUNCPTR)tModbusSlaveTask, mb, mb_mapping,0,0,0,0,0,0,0,0);
	    printf("g_ComTaskID=%d\n", g_ComTaskID);	    
	}
	printf("initmodbusrtu__main OK\n");
	p->pInstance->result = 0;
	return;
}

void CDECL CDECL_EXT modbusreadreg__main(modbusreadreg_main_struct *p)
{
#if 0
	RTS_IEC_WORD addr;					/* VAR_INPUT */	
	RTS_IEC_BYTE num;					/* VAR_INPUT */	
	RTS_IEC_WORD *data;					/* VAR_INPUT */	
	__ARRAY__DIM__INFO data__Array__Info[1];	/* VAR_INPUT */		
#endif
	if(mb)
		modbus_read_registers(mb, p->pInstance->addr, p->pInstance->num, p->pInstance->data); 		
}

void CDECL CDECL_EXT modbuswritereg__main(modbuswritereg_main_struct *p)
{
#if 0
	RTS_IEC_WORD addr;					/* VAR_INPUT */	
	RTS_IEC_BYTE num;					/* VAR_INPUT */	
	RTS_IEC_WORD data[32];				/* VAR_INPUT */		
#endif
	if(mb)
		modbus_write_registers(mb, p->pInstance->addr, p->pInstance->num, p->pInstance->data);
}

void CDECL CDECL_EXT modbusreadbit__main(modbusreadbit_main_struct *p)
{
#if 0
	RTS_IEC_WORD addr;					/* VAR_INPUT */ 
	RTS_IEC_BYTE num;					/* VAR_INPUT */ 
	RTS_IEC_BYTE *data; 				/* VAR_INPUT */ 
	__ARRAY__DIM__INFO data__Array__Info[1];	/* VAR_INPUT */ 
#endif
	if(mb)
		modbus_read_bits(mb, p->pInstance->addr, p->pInstance->num, p->pInstance->data);
}

void CDECL CDECL_EXT modbuswritebit__main(modbuswritebit_main_struct *p)
{
#if 0
	RTS_IEC_WORD addr;					/* VAR_INPUT */	
	RTS_IEC_BYTE num;					/* VAR_INPUT */	
	RTS_IEC_BYTE data[32];				/* VAR_INPUT */	
#endif
	if(mb)
		modbus_write_bits(mb, p->pInstance->addr, p->pInstance->num, p->pInstance->data);
}

void CDECL CDECL_EXT modbusslavereadbit__main(modbusslavereadbit_main_struct *p)
{
    int i = 0;
	
	if((mb == NULL) || (p->pInstance->data == NULL))
        return;
    
    if((p->pInstance->addr + p->pInstance->num >= SLAVE_BITS_MAX_NUMBER) || (p->pInstance->addr < 0) || (p->pInstance->num < 0))
        return;

    memcpy(p->pInstance->data, &(mb_mapping->tab_bits[mb_mapping->start_bits + p->pInstance->addr]), p->pInstance->num * sizeof(uint8_t));	
/*    
    printf("Read Bit:");
    for(i = 0; i < p->pInstance->num; i++)
    {
    	printf("%02X ", mb_mapping->tab_bits[mb_mapping->start_bits + p->pInstance->addr + i]);
    }
    printf("\n");
*/    
}

void CDECL CDECL_EXT modbusslavewritebit__main(modbusslavewritebit_main_struct *p)
{
	int i = 0;
	
	if((mb == NULL) || (p->pInstance->data == NULL))
        return;
    
    if((p->pInstance->addr + p->pInstance->num >= SLAVE_BITS_MAX_NUMBER) || (p->pInstance->addr < 0) || (p->pInstance->num < 0))
        return;

    memcpy(&(mb_mapping->tab_bits[mb_mapping->start_bits + p->pInstance->addr]), p->pInstance->data, p->pInstance->num * sizeof(uint8_t));
/*
    printf("Write Bit:");
    for(i = 0; i < p->pInstance->num; i++)
    {
    	printf("%02X ", mb_mapping->tab_bits[mb_mapping->start_bits + p->pInstance->addr + i]);
    }
    printf("\n");
*/
}

void CDECL CDECL_EXT modbusslavereadreg__main(modbusslavereadreg_main_struct *p)
{
    if((mb == NULL) || (p->pInstance->data == NULL))
        return;
    
    if((p->pInstance->addr + p->pInstance->num >= SLAVE_REGISTERS_MAX_NUMBER) || (p->pInstance->addr < 0) || (p->pInstance->num < 0))
        return;

    memcpy(p->pInstance->data, &(mb_mapping->tab_bits[mb_mapping->start_bits + p->pInstance->addr]), p->pInstance->num * sizeof(uint16_t));		
}

void CDECL CDECL_EXT modbusslavewritereg__main(modbusslavewritereg_main_struct *p)
{
    if((mb == NULL) || (p->pInstance->data == NULL))
        return;
    
    if((p->pInstance->addr + p->pInstance->num >= SLAVE_REGISTERS_MAX_NUMBER) || (p->pInstance->addr < 0) || (p->pInstance->num < 0))
        return;

    memcpy(&(mb_mapping->tab_bits[mb_mapping->start_bits + p->pInstance->addr]), p->pInstance->data, p->pInstance->num * sizeof(uint16_t));

    return;  	
}

void CDECL CDECL_EXT closemodbus__main(closemodbus_main_struct *p)
{
	modbus_close(mb);  
	modbus_free(mb);

	mb = NULL;
}

