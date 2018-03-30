#include <vxWorks.h>
#include <stdio.h>
#include <ioLib.h>
#include <fcntl.h>
#include <cacheLib.h>
#include <intLib.h>
#include <logLib.h>
#include <muxLib.h>
#include <end.h>
#include <semLib.h>
#include <sysLib.h>
#include <sioLib.h>
#include <vxBusLib.h>

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

#define COM_1_NAME                              "/tyCo/0" //"/tyCo/3"  //wanghx test com 2017-12-27
#define COM_2_NAME                              "/tyCo/1" //"/tyCo/0"
#define COM_3_NAME                              "/tyCo/2" //"/tyCo/3"  //wanghx test com 2017-12-27
#define COM_4_NAME                              "/tyCo/3" //"/tyCo/0"

int fdCom1 = 0;
int g_Com1OverFlag = 0;
int g_Com1TaskID = 0;

int fdCom2 = 0;
int g_Com2OverFlag = 0;
int g_Com2TaskID = 0;

int fdCom3 = 0;
int g_Com3OverFlag = 0;
int g_Com3TaskID = 0;

int fdCom4 = 0;
int g_Com4OverFlag = 0;
int g_Com4TaskID = 0;

VXB_DEVICE_ID pInst;

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
			sysOutLong(GPIO_REG_BASE + GPIO_REG_DIR_BANK2, 0xffffffff);
			sysOutLong(GPIO_REG_BASE + GPIO_REG_OEN_BANK2, 0xffffffff);
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

int com_read_ex(int fd, char *buffer, size_t maxbytes, struct timeval *pTimeOut)
{
    int sum = 0;
    int ret = 0;
    fd_set fdset;
    char *p = buffer;

    /* 设置文件描述符集合 */
    FD_ZERO(&fdset);
    FD_SET(fd, &fdset);

    for (;sum < maxbytes;)
    {
        /* 使用select函数判断串口状态 */
        ret = select(fd+1, &fdset, NULL, NULL, pTimeOut);
        if (ret == 0)
        {
            /* 当超时的情况返回收到的数据 */
            return sum;
        }
        if (ret == -1)
        {
            return -1;
        }
        /* 判断当前串口是否有数据可读 */
        if (FD_ISSET(fd, &fdset))
        {
            ret = read(fd, p, 1);
            if (ret == -1)
            {
                return -1;
            }
            p += ret;
            sum += ret;
        }
    }

    return sum;
}

int tCom1Task(int fd)
{
    int ret = 0;
    unsigned char TxBuffer[256] = {0};
    unsigned char RxBuffer[256] = {0};
    unsigned char RxData[256] = {0};
    int cmd = 0;
    int Received = 0;
    int sum = 0;
    int i = 0;
    struct timeval timeout;

    /* 配置串口参数 */
    ret += ioctl(fd, SIO_MODE_SET, SIO_MODE_INT);  //SIO_MODE_INT  SIO_MODE_POLL
    ret += ioctl(fd, FIOSETOPTIONS, OPT_RAW);       /* 原始模式OPT_RAW 行模式OPT_LINE 根据情况选择 */
    ret += ioctl(fd, FIOBAUDRATE, 115200);   /* 波特率 */
    ret += ioctl(fd, FIOFLUSH, 0);                  /* 清空缓冲区 */

    /* 数据位8位 停止位1位 偶校验 本地模式 */
    ret += ioctl(fd, SIO_HW_OPTS_SET, CLOCAL | CS8 | PARODD | CREAD);
    //ret += ioctl(fd, SIO_HW_OPTS_SET, CLOCAL | CS8 | PARODD);

    printf("Reading %s..., fd=%d\n", COM_1_NAME, fd);

    for(i = 0; i < 256; i++)
    {
    	TxBuffer[i] = 0x11;
    }
    write(fd, TxBuffer, sizeof(TxBuffer));
    
    /* 死循环 */
    for (sum = 0; g_Com1OverFlag != 0; )
    {
//#if !INCLUDE_COM_TIMEOUT
#if 1
        for(i = 0; i < 256; i++)
        {
        	TxBuffer[i] = 0x11;
        }
        write(fd, TxBuffer, sizeof(TxBuffer));
        taskDelay(10);
#else
#if 1
        /* 普通读取模式 */
        Received = read(fd, RxBuffer, sizeof(RxBuffer));
#else
        /* 超时读取模式 */
        /* 设置超时时间 */
        timeout.tv_sec  = 0;         /* 0 单位s */
        timeout.tv_usec = 1000;     /* 1ms 单位us*/
        Received = com_read_ex(fd, RxBuffer, sizeof(RxBuffer), &timeout);
        if (Received == 0)
        {
            continue ;  /* 超时后继续读取 */
        }
#endif

#if 1  /* DEBUG */
        sum += Received;
        if (1)
        {
            printf("tScreenTask:--- ");
            for (i = 0; i < Received; i++)
            {
                printf("%02X ", RxBuffer[i]);
                if (((i+1) % 16) == 0) printf("\n    "); /* 16个一换行 */
            }
            printf("--- com%s\n", COM_1_NAME);
        }
        else
        {
            printf("COM%s received %4d bytes, last data = %X\n", COM_1_NAME, sum, RxBuffer[Received - 1]);
        }
#endif
#endif        
    }

    return 0;
}


int tCom2Task(int fd)
{
    int ret = 0;
    unsigned char TxBuffer[256] = {0};
    unsigned char RxBuffer[256] = {0};
    unsigned char RxData[256] = {0};
    int cmd = 0;
    int Received = 0;
    int sum = 0;
    int i = 0;
    struct timeval timeout;

    /* 配置串口参数 */
    ret += ioctl(fd, SIO_MODE_SET, SIO_MODE_INT);  //SIO_MODE_INT  SIO_MODE_POLL
    ret += ioctl(fd, FIOSETOPTIONS, OPT_RAW);       /* 原始模式OPT_RAW 行模式OPT_LINE 根据情况选择 */
    ret += ioctl(fd, FIOBAUDRATE, 115200);   /* 波特率 */
    ret += ioctl(fd, FIOFLUSH, 0);                  /* 清空缓冲区 */

    /* 数据位8位 停止位1位 偶校验 本地模式 */
    ret += ioctl(fd, SIO_HW_OPTS_SET, CLOCAL | CS8 | PARODD | CREAD);
    //ret += ioctl(fd, SIO_HW_OPTS_SET, CLOCAL | CS8 | PARODD);

    printf("Reading %s..., fd=%d\n", COM_2_NAME, fd);

    for(i = 0; i < 256; i++)
    {
    	TxBuffer[i] = i;
    }
    write(fd, TxBuffer, sizeof(TxBuffer));    
    /* 死循环 */
    for (sum = 0; g_Com1OverFlag != 0; )
    {
//#if !INCLUDE_COM_TIMEOUT
#if 1
        for(i = 0; i < 128; i++)
        {
        	TxBuffer[i] = 0x22;
        }
        write(fd, TxBuffer, 128);  
        taskDelay(10);
#else    	
#if 1
        /* 普通读取模式 */
        Received = read(fd, RxBuffer, sizeof(RxBuffer));
#else
        /* 超时读取模式 */
        /* 设置超时时间 */
        timeout.tv_sec  = 0;         /* 0 单位s */
        timeout.tv_usec = 1000;     /* 1ms 单位us*/
        Received = com_read_ex(fd, RxBuffer, sizeof(RxBuffer), &timeout);
        if (Received == 0)
        {
            continue ;  /* 超时后继续读取 */
        }
#endif

#if 1
        sum += Received;
        if (1)
        {
            printf("tScreenTask:--- ");
            for (i = 0; i < Received; i++)
            {
                printf("%02X ", RxBuffer[i]);
                if (((i+1) % 16) == 0) printf("\n    "); /* 16个一换行 */
            }
            printf("--- com%s\n", COM_2_NAME);
        }
        else
        {
            printf("COM%s received %4d bytes, last data = %X\n", COM_2_NAME, sum, RxBuffer[Received - 1]);
        }
#endif
#endif        
    }

    return 0;
}


int tCom3Task(int fd)
{
    int ret = 0;
    unsigned char TxBuffer[256] = {0};
    unsigned char RxBuffer[256] = {0};
    unsigned char RxData[256] = {0};
    int cmd = 0;
    int Received = 0;
    int sum = 0;
    int i = 0;
    struct timeval timeout;

    /* 配置串口参数 */
    ret += ioctl(fd, SIO_MODE_SET, SIO_MODE_INT);  //SIO_MODE_INT  SIO_MODE_POLL
    ret += ioctl(fd, FIOSETOPTIONS, OPT_RAW);       /* 原始模式OPT_RAW 行模式OPT_LINE 根据情况选择 */
    ret += ioctl(fd, FIOBAUDRATE, 115200);   /* 波特率 */
    ret += ioctl(fd, FIOFLUSH, 0);                  /* 清空缓冲区 */

    /* 数据位8位 停止位1位 偶校验 本地模式 */
    ret += ioctl(fd, SIO_HW_OPTS_SET, CLOCAL | CS8 | PARODD | CREAD);
    //ret += ioctl(fd, SIO_HW_OPTS_SET, CLOCAL | CS8 | PARODD);

    printf("Reading %s..., fd=%d\n", COM_3_NAME, fd);

    for(i = 0; i < 256; i++)
    {
    	TxBuffer[i] = i;
    }
    write(fd, TxBuffer, sizeof(TxBuffer));
    
    /* 死循环 */
    for (sum = 0; g_Com1OverFlag != 0; )
    {
//#if !INCLUDE_COM_TIMEOUT
#if 0
        for(i = 0; i < 128; i++)
        {
        	TxBuffer[i] = 0x33;
        }
        write(fd, TxBuffer, 128);  
        taskDelay(10);
#else    	
#if 1
        /* 普通读取模式 */
        Received = read(fd, RxBuffer, sizeof(RxBuffer));
#else
        /* 超时读取模式 */
        /* 设置超时时间 */
        timeout.tv_sec  = 0;         /* 0 单位s */
        timeout.tv_usec = 1000;     /* 1ms 单位us*/
        Received = com_read_ex(fd, RxBuffer, sizeof(RxBuffer), &timeout);
        if (Received == 0)
        {
            continue ;  /* 超时后继续读取 */
        }
#endif

#if 1
        sum += Received;
        if (1)
        {
            printf("tScreenTask:--- ");
            for (i = 0; i < Received; i++)
            {
                printf("%02X ", RxBuffer[i]);
                if (((i+1) % 16) == 0) printf("\n    "); /* 16个一换行 */
            }
            printf("--- com%s\n", COM_3_NAME);
        }
        else
        {
            printf("COM%s received %4d bytes, last data = %X\n", COM_3_NAME, sum, RxBuffer[Received - 1]);
        }
#endif
#endif        
    }

    return 0;
}


int tCom4Task(int fd)
{
    int ret = 0;
    unsigned char TxBuffer[256] = {0};
    unsigned char RxBuffer[256] = {0};
    unsigned char RxData[256] = {0};
    int cmd = 0;
    int Received = 0;
    int sum = 0;
    int i = 0;
    struct timeval timeout;

    /* 配置串口参数 */
    ret += ioctl(fd, SIO_MODE_SET, SIO_MODE_INT);  //SIO_MODE_INT  SIO_MODE_POLL
    ret += ioctl(fd, FIOSETOPTIONS, OPT_RAW);       /* 原始模式OPT_RAW 行模式OPT_LINE 根据情况选择 */
    ret += ioctl(fd, FIOBAUDRATE, 115200);   /* 波特率 */
    ret += ioctl(fd, FIOFLUSH, 0);                  /* 清空缓冲区 */

    /* 数据位8位 停止位1位 偶校验 本地模式 */
    ret += ioctl(fd, SIO_HW_OPTS_SET, CLOCAL | CS8 | CREAD);
    //ret += ioctl(fd, SIO_HW_OPTS_SET, CLOCAL | CS8 | PARODD);
    printf("config opts=%08x\n", CLOCAL | CS8 | CREAD);
    printf("Reading %s..., fd=%d\n", COM_4_NAME, fd);

    for(i = 0; i < 128; i++)
    {
    	TxBuffer[i] = i;
    }
    write(fd, TxBuffer, 128);   

    /* 死循环 */
    for (sum = 0; g_Com4OverFlag != 0; )
    {
//#if !INCLUDE_COM_TIMEOUT
#if 0
        for(i = 0; i < 128; i++)
        {
        	TxBuffer[i] = 0x44;
        }
        write(fd, TxBuffer, 128);  
        taskDelay(10);
#else
#if 0
        /* 普通读取模式 */
        Received = read(fd, RxBuffer, sizeof(RxBuffer));
#else
        /* 超时读取模式 */
        /* 设置超时时间 */
        timeout.tv_sec  = 0;         /* 0 单位s */
        timeout.tv_usec = 5000;     /* 1ms 单位us*/
        Received = com_read_ex(fd, RxBuffer, sizeof(RxBuffer), &timeout);
        if (Received == 0)
        {
            continue ;  /* 超时后继续读取 */
        }
#endif

#if 1
        sum += Received;
        if (1)
        {
            printf("tScreenTask:--- ");
            for (i = 0; i < Received; i++)
            {
                printf("%02X ", RxBuffer[i]);
                if (((i+1) % 16) == 0) printf("\n    "); /* 16个一换行 */
            }
            printf("--- com%s received %d\n", COM_4_NAME, Received);
        }
        else
        {
            printf("COM%s received %4d bytes, last data = %X\n", COM_4_NAME, sum, RxBuffer[Received - 1]);
        }
#endif
#endif
    }

    return 0;
}

int initcom()
{
    int ret = 0;
    /*
     * #define GPIO_DIR_OUTPUT			0
	   #define GPIO_DIR_INPUT			1
     */
    
    InitGpioBank(2, GPIO_DIR_OUTPUT);
    InitGpio(63, GPIO_DIR_OUTPUT, 0);
    /*InitGpio(64, GPIO_DIR_OUTPUT, 0);
    InitGpio(65, GPIO_DIR_OUTPUT, 1);*/
    
#if 1
    fdCom1 = open(COM_1_NAME, O_RDWR, 0);
    if(fdCom1 == ERROR)
    {
        printf("Open %s COM failed!\n", COM_1_NAME);
        return fdCom1;
    }
    else
    {
        g_Com1OverFlag= 1;
        g_Com1TaskID =  taskSpawn("tCom0Task", 60, 0, 1024 * 40, (FUNCPTR)tCom1Task, fdCom1,0,0,0,0,0,0,0,0,0);
        printf("g_Com1TaskID=%d\n", g_Com1TaskID);
        taskDelay(sysClkRateGet() / 10);
    }
#endif
#if 0
    /* COM2在系统中是调试输出串口 */
    fdCom2 = open(COM_2_NAME, O_RDWR, 0);
    if(fdCom2 == ERROR)
    {
        printf("Open %s COM failed!\n", COM_2_NAME);
        return fdCom2;
    }
    else
    {
        g_Com2OverFlag= 1;
        g_Com2TaskID =  taskSpawn("tCom1Task", 60, 0, 1024 * 40, (FUNCPTR)tCom2Task, fdCom2,0,0,0,0,0,0,0,0,0);
        printf("g_Com2TaskID=%d\n", g_Com2TaskID);
        taskDelay(sysClkRateGet() / 10);
    }
#endif
#if 1
    /* COM3在系统中是422 */
    fdCom3 = open(COM_3_NAME, O_RDWR, 0);
    if(fdCom3 == ERROR)
    {
        printf("Open %s COM failed!\n", COM_3_NAME);
        return fdCom3;
    }
    else
    {
        g_Com3OverFlag= 1;
        g_Com3TaskID =  taskSpawn("tCom2Task", 60, 0, 1024 * 40, (FUNCPTR)tCom3Task, fdCom3,0,0,0,0,0,0,0,0,0);
        printf("g_Com3TaskID=%d\n", g_Com3TaskID);
        taskDelay(sysClkRateGet() / 10);
    }
#endif
#if 1
    /* COM4在系统中是232/422可切换串口，需要配置EMIO63，低是232，高是422，对应芯片U22的24脚  */
    fdCom4 = open(COM_4_NAME, O_RDWR, 0);
    if(fdCom4 == ERROR)
    {
        printf("Open %s COM failed!\n", COM_4_NAME);
        return fdCom4;
    }
    else
    {
        g_Com4OverFlag= 1;
        g_Com4TaskID =  taskSpawn("tCom3Task", 60, 0, 1024 * 40, (FUNCPTR)tCom4Task, fdCom4,0,0,0,0,0,0,0,0,0);
        printf("g_Com4TaskID=%d\n", g_Com4TaskID);
        taskDelay(sysClkRateGet() / 10);
    }
#endif    
    return ret;
}
