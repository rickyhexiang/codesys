/*
 * glodon_iot_data.h
 *
 * Create on: 2017-07-18
 *
 *    Author: feiguoyou@hotmail.com
 *
 */

#ifndef _GLODON_IOT_DATA_H_
#define _GLODON_IOT_DATA_H_

#ifdef __cplusplus
extern "C" {
#endif //  __cplusplus

#include <stdbool.h>

#define DEVICE_MODEL_GEN_VERSOIN     "1.0.0"
//#define DEVICE_MODEL_DATA_VERSOIN    "{dev_model_data_version}"

typedef struct _GlodonIoTData* GlodonIoTData;

typedef enum {
    GLODON_EVENT_ACT_START = 1000,
    // ( char * taskInfo : 任务信息; ) 任务信息: 
    GLODON_EVENT_ACT_CURTASKDATA,
    // ( int count : 数量; ) 当前任务数量: 
    GLODON_EVENT_ACT_CURTASKCOUNT,

    GLODON_EVENT_SET_START = 3000,

} GlodonEvent;

struct _GlodonIoTData {

    int (*setStartTask)(GlodonIoTData data, char * startTask); // 开始加工任务: 
    int (*setEndTask)(GlodonIoTData data, char * endTask); // 结束加工任务: 
    int (*setUpdateTask)(GlodonIoTData data, char * updateTask); // 更新加工任务: 
    int (*setWarningInfo)(GlodonIoTData data, char * warningInfo); // 报警信息: 
    int (*setElectricFlow)(GlodonIoTData data, double electricFlow); // 设备电流: 
    int (*setMachineState)(GlodonIoTData data, char * machineState); // 更新设备状态: 

};

GlodonIoTData glodon_iot_data_init(void);
void glodon_iot_data_destory(GlodonIoTData data);

#ifdef __cplusplus
}
#endif //  __cplusplus

#endif    // #ifndef _GLODON_IOT_DATA_H_

