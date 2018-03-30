/*
 * app_data.c
 *
 * Create on: 2017-09-13
 *
 *    Author: feiguoyou@hotmail.com
 *
 */

#include <stdio.h>
#include "app_data.h"
#include "CmpGlobalVar.h"
#include "string.h"

void on_app_message(GlodonIotClient pClient, int evt, int argc, void *argv[], void *ack)
{
    //IOT_DEBUG(pClient, "%s(%d) argc = %d", __func__, evt, argc);
    switch(evt)
    {

        case GLODON_EVENT_ACT_CURTASKDATA:
            {
                char * taskinfo = *(char * *)argv[0]; // 任务信息
                //if (strlen(taskinfo) >= 2)
                //{
                	//free(GVar_taskInfo);
                	//GVar_taskInfo = (char * )malloc(sizeof(char) * (strlen(taskinfo) + 1 - 2));
                	//strncpy(GVar_taskInfo, taskinfo + 1, strlen(taskinfo) - 2);                	
                //}
                free(GVar_taskInfo);
                GVar_taskInfo = (char * )malloc(sizeof(char) * (strlen(taskinfo) + 1));
                strncpy(GVar_taskInfo, taskinfo, strlen(taskinfo));
                IOT_DEBUG(pClient, "action: curtaskdata");
                IOT_DEBUG(pClient, "taskinfo : %s: ", GVar_taskInfo);
            }
            break;
        case GLODON_EVENT_ACT_CURTASKCOUNT:
            {
                int count = *(int *)argv[0]; // 数量
                GVar_nTaskCount = count;

                IOT_DEBUG(pClient, "action: curtaskcount");
            }
            break;

        defalut:
            break;
    }
}

int app_get_data(GlodonIoTData data)
{
    // 以下变量模拟设备数据, 实际需要设备采集改变
    static char * startTask = (char *)"";
    static char * endTask = (char *)"";
    static char * updateTask = (char *)"";
    static char * warningInfo = (char *)"";
    static double electricFlow = 0.0;
    static char * machineState = (char *)"";

    if (!data) {
        return -1;
    }
    data->setStartTask(data, startTask);
    data->setEndTask(data, endTask);
    data->setUpdateTask(data, updateTask);
    data->setWarningInfo(data, warningInfo);
    data->setElectricFlow(data, electricFlow);
    data->setMachineState(data, machineState);

    return 0;
}

