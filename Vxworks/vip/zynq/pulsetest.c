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

#define PLC_PULSE_GEN_ENCORDER_COUNTER			 (0x40600000)
#define REG_PULSE1_INTERVAL			 (16 * 4)/* 脉冲间隔：脉冲输出低电平的时间，单位是0.1us */
#define REG_PULSE1_WIDTH 			 (17 * 4)/* 脉冲宽度：脉冲输出高电平的时间，单位是0.1us */
#define REG_PULSE1_NUM   			 (18 * 4)/* 脉冲个数：脉冲输出的个数 */
#define REG_PULSE1_CONTROL			 (19 * 4)/* bit0  PulseStart  脉冲输出启动/停止位，状态查询位.写1启动发送，写0停止发送 */

#define REG_ENCORDER_COUNTER_A	     (20 * 4)
#define REG_ENCORDER_COUNTER_Z	     (21 * 4)
#define REG_ENCORDER_COUNTER_CTRL    (22 * 4)

#define REG_PULSE2_INTERVAL			 (24 * 4)/* 脉冲间隔：脉冲输出低电平的时间，单位是0.1us */
#define REG_PULSE2_WIDTH 			 (25 * 4)/* 脉冲宽度：脉冲输出高电平的时间，单位是0.1us */
#define REG_PULSE2_NUM   			 (26 * 4)/* 脉冲个数：脉冲输出的个数 */
#define REG_PULSE2_CONTROL			 (27 * 4)/* bit0  PulseStart  脉冲输出启动/停止位，状态查询位.写1启动发送，写0停止发送 */

#define REG_PULSE3_INTERVAL			 (28 * 4)/* 脉冲间隔：脉冲输出低电平的时间，单位是0.1us */
#define REG_PULSE3_WIDTH 			 (29 * 4)/* 脉冲宽度：脉冲输出高电平的时间，单位是0.1us */
#define REG_PULSE3_NUM   			 (30 * 4)/* 脉冲个数：脉冲输出的个数 */
#define REG_PULSE3_CONTROL			 (31 * 4)/* bit0  PulseStart  脉冲输出启动/停止位，状态查询位.写1启动发送，写0停止发送 */

VXB_DEVICE_ID pInst;

int setPulseFreq(unsigned int index, unsigned long hz)
{
	/*0 < hz < 200k*/
	if((hz > 0) && (hz < 200000)) 
	{
		switch(index)
		{
		case 1:
			//以输出方波为例， 0.2 * data = 1000000(us) / hz
			sysOutLong(PLC_PULSE_GEN_ENCORDER_COUNTER + REG_PULSE1_INTERVAL, 5000000 / hz );
			sysOutLong(PLC_PULSE_GEN_ENCORDER_COUNTER + REG_PULSE1_WIDTH, 5000000 / hz);	
			break;
			
		case 2:
			//以输出方波为例， 0.2 * data = 1000000(us) / hz
			sysOutLong(PLC_PULSE_GEN_ENCORDER_COUNTER + REG_PULSE2_INTERVAL, 5000000 / hz );
			sysOutLong(PLC_PULSE_GEN_ENCORDER_COUNTER + REG_PULSE2_WIDTH, 5000000 / hz);	
			break;
			
		case 3:
			//以输出方波为例， 0.2 * data = 1000000(us) / hz
			sysOutLong(PLC_PULSE_GEN_ENCORDER_COUNTER + REG_PULSE3_INTERVAL, 5000000 / hz );
			sysOutLong(PLC_PULSE_GEN_ENCORDER_COUNTER + REG_PULSE3_WIDTH, 5000000 / hz);	
			break;
			
		default:
			return -1;
		}			
		return 0;
	}
	else
		return -1;
}

int setPulseNumAndStart(unsigned int index, unsigned long num)
{
	if(num >= 0)
	{
		switch(index)
		{
		case 1:
			sysOutLong(PLC_PULSE_GEN_ENCORDER_COUNTER + REG_PULSE1_NUM, num - 1);
			sysOutLong(PLC_PULSE_GEN_ENCORDER_COUNTER + REG_PULSE1_CONTROL, 1);
			break;
		case 2:
			sysOutLong(PLC_PULSE_GEN_ENCORDER_COUNTER + REG_PULSE2_NUM, num - 1);
			sysOutLong(PLC_PULSE_GEN_ENCORDER_COUNTER + REG_PULSE2_CONTROL, 1);
			break;
		case 3:
			sysOutLong(PLC_PULSE_GEN_ENCORDER_COUNTER + REG_PULSE3_NUM, num - 1);
			sysOutLong(PLC_PULSE_GEN_ENCORDER_COUNTER + REG_PULSE3_CONTROL, 1);
			break;	
			
		default:
			return -1;			
		}
		
		return 0;
	}
	else
		return -1;
}

int StopPulse(unsigned int index)
{
	switch(index)
	{
	case 1: sysOutLong(PLC_PULSE_GEN_ENCORDER_COUNTER + REG_PULSE1_CONTROL, 0); break;
	case 2: sysOutLong(PLC_PULSE_GEN_ENCORDER_COUNTER + REG_PULSE2_CONTROL, 0); break;
	case 3: sysOutLong(PLC_PULSE_GEN_ENCORDER_COUNTER + REG_PULSE3_CONTROL, 0); break;
	default: return -1; break;			
	}
	
	return 0;
}

int initpulse()
{
    int ret = 0;

    StopPulse(1);
    StopPulse(2);
    StopPulse(3);
    
    setPulseFreq(1, 1000);
    setPulseFreq(2, 1000);
    setPulseFreq(3, 1000);
    
    setPulseNumAndStart(1, 1000000);
    setPulseNumAndStart(2, 1000000);
    setPulseNumAndStart(3, 1000000);
    
    getchar();
    
    StopPulse(1);
    StopPulse(2);
    StopPulse(3);
    
    return ret;
}


long ReadEncorderCounterA()
{
	return sysInLong(PLC_PULSE_GEN_ENCORDER_COUNTER + REG_ENCORDER_COUNTER_A);
}

long ReadEncorderCounterZ()
{
	return sysInLong(PLC_PULSE_GEN_ENCORDER_COUNTER + REG_ENCORDER_COUNTER_Z);
}

BOOL ReadEncorderDirection()
{
	return sysInLong(PLC_PULSE_GEN_ENCORDER_COUNTER + REG_ENCORDER_COUNTER_CTRL) & 0x01;
}

int ConfigEncoder(BOOL a, BOOL b, BOOL z)
{
	long ulData = sysInLong(PLC_PULSE_GEN_ENCORDER_COUNTER + REG_ENCORDER_COUNTER_CTRL);
	
	a ? SET_BIT(ulData, 3) : CLR_BIT(ulData, 3);
	b ? SET_BIT(ulData, 2) : CLR_BIT(ulData, 2);
	z ? SET_BIT(ulData, 4) : CLR_BIT(ulData, 4);
}

int testencoder()
{
	long CounterA = 0;
	long CounterZ = 0;
	while(1)
	{
		CounterA = ReadEncorderCounterA();
		CounterZ = ReadEncorderCounterZ();
		printf("a=%d ", CounterA);
		printf("z=%d ", CounterZ);
		printf("dir=%d\n", ReadEncorderDirection());
		taskDelay(sysClkRateGet() / 2);
	}
}
