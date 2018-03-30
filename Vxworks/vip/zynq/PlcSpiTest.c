#include <vxWorks.h>
#include <stdio.h>
#include <ioLib.h>
#include <fcntl.h>
#include <sysLib.h>
#include <sioLib.h>
#include <hwif/vxbus/vxBus.h>
#include <vxBusLib.h>
#include <hwif/vxbus/vxbSpiLib.h>

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

int spitest()
{
	VXB_DEVICE_ID pDOInst;
	VXB_DEVICE_ID pDIInst;
	SPI_TRANSFER transInfo;
	unsigned char txBuf[8] = {0};
	unsigned char rxBuf[8] = {0};
	unsigned long ulData = 0;
	int i = 0;
	int board = 2;
		
	/* 测试DO  板卡使用MAX14912芯片 */
	/* 板卡上一共有三个MAX14912芯片，连接低速DO的两个芯片已经由电路配置完毕。

	连接高速DO的芯片
	焊接R5 不焊接R6  是串行模式
	不焊接R5  焊接R6  是并行模式

	如果需要配置成串行模式，其OL、CMND、CRC、CERR、WDEN/IN5 Watchdog、WDFLT管脚是通过FPGA的EMIO来配置。
	如果配置成并行模式，则直接控制对应即可。

	CS  低电平有效    使用EMIO54
	EN  DO使能              使用EMIO62

	在并行模式下  
	高速DO 1 使用EMIO55
	高速DO 2 使用EMIO56
	高速DO 3 使用EMIO58
	高速DO 4 使用EMIO59
	高速DO 5 使用EMIO60
	高速DO 6 使用EMIO61

	在串行模式下
	27 OL/IN1
	Open-Load Select Input/IN1 Input. In serial mode (SRIAL = high), drive OL/IN1 = high to enable
	open-load detection on all eight OUT_ outputs when in high-side operation. In parallel mode
	(SRIAL = low), OL/IN1 sets OUT1 on/off/high/low.
	此处为高

	28 CMND/IN2
	Command Mode SPI Input/IN2 Logic Input. In serial mode (SRIAL = high), CMND/IN2 enables
	command-based SPI access (see Detailed Description section for details).
	In parallel mode (SRIAL = low), CMND/IN2 sets OUT2 on/off/high/low.
	此处为低

	29 CRC/IN3
	CRC Select Input/IN3 Input. In serial mode (SRIAL = high), drive CRC/IN3 = high to enable CRC
	error detection on serial data. In parallel mode (SRIAL = low), CRC/IN3 sets OUT3 on/off/high/
	low.
	此处为低

	30 CERR/IN4
	CRC Error Detection Output/IN4 Input. In serial mode (SRIAL = high) with error checking
	enabled (CRC/IN3 = high), CERR/IN4 is an open-drain output whose transistor turns on when
	the device detects an error on SDI data. In parallel mode (SRIAL = low), CERR/IN4 sets OUT4
	on/off/high/low.
	此处为高

	31 WDEN/IN5 Watchdog Enable Input/ IN5 Input. In serial mode (SRIAL= high), WDEN/IN5 enables the
	watchdog timer. In parallel mode (SRIAL= low), WDEN/IN5 sets OUT5 on/off/high/low.
	此处为低

	32 WDFLT/IN6
	Watchdog Fault Output/IN6 Input. In serial mode (SRIAL = high), WDFLT/IN6 is the open-drain
	watchdog fault output, which turns on when a watchdog fault is detected while WDEN/IN5 is
	high. In parallel mode (SRIAL = low), WDFLT/IN6 sets OUT6 on/off/high/low.
	此处为高

	33 CNFG/IN7
	Configure Input/IN7 Input. In serial mode (SRIAL = high), drive CNFG/IN7 high to enable perchannel
	configuration through the serial interface. In serial mode, drive CNFG/IN7 low to allow
	setting the OUT_ outputs through the serial interface. In parallel mode (SRIAL = low), CNFG/IN7
	sets OUT7 on/off/high/low.
	硬件配置成低

	34 S16/IN8
	16-Bit Serial Select/IN8 Input.
	In serial mode (SRIAL = high), drive S16/IN8 high to select 16-bit serial-interface operation.
	Drive S16/IN8 low in serial mode for 8-bit serial operation.
	In parallel mode (SRIAL = low), S16/IN8 sets OUT8 on/off/high/low.
	硬件配置成低
	*/		
	/*
	 * 现在代码是在连环测试时所编写版本。目前考虑到IO点数不够的问题，将两块SPI IO板卡并联。所用底板是旧底板。
	 * 由于单块板卡上已经用了两个SPI控制器（一个控制DI 一个控制DO），连线上将SPI的CLK，MISO，MOSI全部并联。
	 * 另分别控制四路CS选择不同的功能。需要注意的是，控制DI时不仅需要控制CS，还需控制隔离芯片的EN。
	 * 下面是信号定义
	 * 信号名			IO板名			底板接口26P    		EMIO		第一IO板26P		第二IO板26P	
						5V				1								1	5V			1	5V	
		DI_FAULT		B34-L17P		2	B35-L13P		GPIO53		2	NC			2	NC	
		DI_SDO			B34-L17N		3	B35-L13N		SPI1-MISO	3	SPI1-MISO	3	SPI1-MISO	
		DI_CS			B34-L19P		4	B35-L14P		GPIO63		4	P4  GPIO63	4	P7  GPIO61	
		DI_CLK			B34-L19N		5	B35-L14N		SPI1-CLK	5	SPI1-CLK	5	SPI1-CLK	
			5V			6				6	5V							6	5V	
		DO3_IN6			B34-L21P		7	B35-L15P		GPIO61		7	NC			7	NC	
		DO3_IN5			B34-L21N		8	B35-L15N		GPIO60		8	NC			8	NC	
		DO3_IN4			B34-L23P		9	B35-L16P		GPIO59		9	接第一板EN	9	NC	
		DO3_IN3			B34-L23N		10	B35-L16N		GPIO58		10	NC			10	接第二板EN
			3.3V		11				11	3.3V						11	3.3V	
		DO3_IN2			B34-L24P		12	B35-L17P		GPIO56		12	NC			12	NC	
		DO_FAULT		B34-L24N		13	B35-L17N		GPIO57		13	NC			13	NC	
		DO3_IN1			B34-L22N		14	B35-L18P		GPIO55		14	NC			14	NC	
		DO_EN			B34-L22P		15	B35-L18N		GPIO54		15	P15 GPIO54	15	P13  GPIO57											
			3.3V		16				16	3.3V						16	3.3V	
		DO_SDO			B34-L20N		17	B35-L19P		SPI0-MISO	17	SPI0-MISO	17	SPI0-MISO	
		DO_SDI			B34-L20P		18	B35-L19N		SPI0-MOSI	18	SPI0-MOSI	18	SPI0-MOSI	
		DO_CLK			B34-L18N		19	B35-L20P		SPI0-CLK	19	SPI0-CLK	19	SPI0-CLK	
		DO_CS			B34-L18P		20	B35-L20N		GPIO62		20	P20 GPIO62	20	P14  GPIO55	
	 * 
	 * */
	
	pDOInst = vxbInstByNameFind("max14912", 0);
	pDIInst = vxbInstByNameFind("max31910", 1);
	
	InitGpio(54+54, GPIO_DIR_OUTPUT, 1);    /* DO_EN */
    while(1)
    {
#if 1
    	/* TEST DO */
        memset(&transInfo, 0, sizeof(SPI_TRANSFER));
        for(i = 0; i < 2; i++)
        {
        	txBuf[i] = 0x55;
        }
        
        transInfo.txBuf = txBuf;
        transInfo.txLen = 2;
        transInfo.usDelay = 0;
        
    	InitGpio(62+54, GPIO_DIR_OUTPUT, 0);	/* BOARD 1 CS */
    	
    	/* 两块板卡并联以后已经不再使用高速DO */
    	/*
    	InitGpio(55, GPIO_DIR_OUTPUT, 0);
    	InitGpio(56, GPIO_DIR_OUTPUT, 1);
    	InitGpio(58, GPIO_DIR_OUTPUT, 0);
    	InitGpio(59, GPIO_DIR_OUTPUT, 1);
    	InitGpio(60, GPIO_DIR_OUTPUT, 0);
    	InitGpio(61, GPIO_DIR_OUTPUT, 1);
		*/
    	
    	/* 低速DO 直接通过SPI传输配置   两个MAX14912呈菊花链方式连接  统一发送SPI数据即可 */
    	vxbSpiTransfer (pDOInst, &transInfo);
    	taskDelay(1);    	
    	InitGpio(62+54, GPIO_DIR_OUTPUT, 1);	/* BOARD 1 CS */
    	
    	InitGpio(55+54, GPIO_DIR_OUTPUT, 0);	/* BOARD 2 CS */    	    	
    	vxbSpiTransfer (pDOInst, &transInfo);
    	taskDelay(1);
    	InitGpio(55+54, GPIO_DIR_OUTPUT, 1);	/* BOARD 2 CS */     
    	
    	//关闭EN会导致电压不输出
    	//InitGpio(54+54, GPIO_DIR_OUTPUT, 0);   /* DO_EN */
#endif
        /* TEST DI */
    	/* 两块板卡DI并联后，需要单独控制每一块板卡的EN和CS */
#if 1   	
    	memset(&transInfo, 0, sizeof(SPI_TRANSFER));    
    	memset(txBuf, 0, sizeof(txBuf));
    	memset(rxBuf, 0, sizeof(rxBuf));
        transInfo.txBuf = txBuf;
        transInfo.txLen = 2;
        transInfo.rxBuf = rxBuf;
        transInfo.rxLen = 2;
        
        InitGpio(61+54, GPIO_DIR_OUTPUT, 1);	/* BOARD 2 DI CS */ 
        InitGpio(58+54, GPIO_DIR_OUTPUT, 0);	/* BOARD 2 DI EN(U9 PIN7) */
    	               
        InitGpio(59+54, GPIO_DIR_OUTPUT, 1);	/* BOARD 1 DI EN */ 
        InitGpio(63+54, GPIO_DIR_OUTPUT, 0);	/* BOARD 1 DI CS */               
    	taskDelay(1);
    	
    	vxbSpiTransfer (pDIInst, &transInfo);
    	taskDelay(1);
    	
    	InitGpio(63+54, GPIO_DIR_OUTPUT, 1);	/* BOARD 1 DI CS */
    	InitGpio(59+54, GPIO_DIR_OUTPUT, 0);	/* BOARD 1 DI EN */
    	
    	logMsg("BOARD 1 DI=%02X %02X\n", rxBuf[0], rxBuf[1], 0, 0, 0, 0);
#endif  
#if 1
    	memset(&transInfo, 0, sizeof(SPI_TRANSFER)); 
    	memset(txBuf, 0, sizeof(txBuf));
    	memset(rxBuf, 0, sizeof(rxBuf));    	
        transInfo.txBuf = txBuf;
        transInfo.txLen = 2;
        transInfo.rxBuf = rxBuf;
        transInfo.rxLen = 2;
        
        InitGpio(63+54, GPIO_DIR_OUTPUT, 1);	/* BOARD 1 DI CS */
        InitGpio(59+54, GPIO_DIR_OUTPUT, 0);	/* BOARD 1 DI EN */
        
        InitGpio(58+54, GPIO_DIR_OUTPUT, 1);	/* BOARD 2 DI EN */    	
    	InitGpio(61+54, GPIO_DIR_OUTPUT, 0);	/* BOARD 2 DI CS */
    	taskDelay(1);
    	vxbSpiTransfer (pDIInst, &transInfo);
    	taskDelay(1);    	
    	InitGpio(61+54, GPIO_DIR_OUTPUT, 1);	/* BOARD 2 DI CS */
    	InitGpio(58+54, GPIO_DIR_OUTPUT, 0);	/* BOARD 2 DI EN */
    	
    	logMsg("BOARD 2 DI=%02X %02X\n", rxBuf[0], rxBuf[1], 0, 0, 0, 0);
#endif   	
    	taskDelay(sysClkRateGet());
    }
}
