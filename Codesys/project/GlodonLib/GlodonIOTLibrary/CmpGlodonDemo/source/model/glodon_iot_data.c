/*
 * glodon_iot_data.c
 *
 * Create on: 2017-07-18
 *
 *    Author: feiguoyou@hotmail.com
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "glodon_iot_data_def.h"

static int glodon_iot_data_find_attrabute_item(IGlodonIoTData d, char *key);


static int glodon_iot_data_set_startTask(GlodonIoTData data, char * startTask);
static int glodon_iot_data_set_endTask(GlodonIoTData data, char * endTask);
static int glodon_iot_data_set_updateTask(GlodonIoTData data, char * updateTask);
static int glodon_iot_data_set_warningInfo(GlodonIoTData data, char * warningInfo);
static int glodon_iot_data_set_electricFlow(GlodonIoTData data, double electricFlow);
static int glodon_iot_data_set_machineState(GlodonIoTData data, char * machineState);

FUNCTION_SESSION_SET
GlodonIoTData glodon_iot_data_init(void)
{
    IGlodonIoTData d = glodon_iot_data_alloc();

    if(!d) {
        return NULL;
    }

    d->data.setStartTask = glodon_iot_data_set_startTask;
    d->data.setEndTask = glodon_iot_data_set_endTask;
    d->data.setUpdateTask = glodon_iot_data_set_updateTask;
    d->data.setWarningInfo = glodon_iot_data_set_warningInfo;
    d->data.setElectricFlow = glodon_iot_data_set_electricFlow;
    d->data.setMachineState = glodon_iot_data_set_machineState;

    return &d->data;
}

FUNCTION_SESSION_SET
void glodon_iot_data_destory(GlodonIoTData data)
{
    glodon_iot_data_free(GET_IGDATA(data));
}

FUNCTION_SESSION_SET
static int glodon_iot_data_find_attrabute_item(IGlodonIoTData d, char *key)
{
    cJSON *it;
    int i, n, item = -1;

    n = cJSON_GetArraySize(d->cjson_payload_att);
    for(i = 0; i < n; i++) {
        it = cJSON_GetArrayItem(d->cjson_payload_att, i);
        it = cJSON_GetObjectItem(it, JSON_KEY_PD_ATT_NAME);
        if(!strcmp(it->valuestring, key)) {
            item = i;
            break;
        }
    }

    return item;
}


FUNCTION_SESSION_SET
static int glodon_iot_data_set_startTask(GlodonIoTData data, char * startTask)
{
#define _DATA_TYPE_SET_startTask_String
    int item;
    cJSON *it;
    IGlodonIoTData d = GET_IGDATA(data);
    char *_key = DATA_INDEX_AS_NAME ? "0" : "startTask";

    if(!d) {
        return -1;
    }
    if(!(it = cJSON_CreateObject())) {
        return -1;
    }
    cJSON_AddStringToObject(it, JSON_KEY_PD_ATT_NAME, _key);
#if DATA_TYPE_AS_STRING
    char *_p, _buf[32];
    _p = _buf;
#if defined(_DATA_TYPE_SET_startTask_String)
    _p = startTask;
#elif defined(_DATA_TYPE_SET_startTask_Float)
    snprintf(_buf, sizeof(_buf), "%.2f", startTask);
#elif defined(_DATA_TYPE_SET_startTask_Integer)
    snprintf(_buf, sizeof(_buf), "%d", startTask);
#endif
    cJSON_AddStringToObject(it, JSON_KEY_PD_ATT_VALUE, _p);
#else //  DATA_TYPE_AS_STRING
#if defined(_DATA_TYPE_SET_startTask_String)
    cJSON_AddStringToObject(it, JSON_KEY_PD_ATT_VALUE, startTask);
#elif defined(_DATA_TYPE_SET_startTask_Float)
    cJSON_AddNumberToObject(it, JSON_KEY_PD_ATT_VALUE, startTask);
#elif defined(_DATA_TYPE_SET_startTask_Integer)
    cJSON_AddNumberToObject(it, JSON_KEY_PD_ATT_VALUE, startTask);
#endif
#endif // DATA_TYPE_AS_STRING
    cJSON_AddStringToObject(it, JSON_KEY_PD_ATT_CHANNEL, "m");
    if((item = glodon_iot_data_find_attrabute_item(d, _key)) >= 0) {
        cJSON_ReplaceItemInArray(d->cjson_payload_att, item, it);
    } else {
        cJSON_AddItemToArray(d->cjson_payload_att, it);
    }
    return 0;
}
FUNCTION_SESSION_SET
static int glodon_iot_data_set_endTask(GlodonIoTData data, char * endTask)
{
#define _DATA_TYPE_SET_endTask_String
    int item;
    cJSON *it;
    IGlodonIoTData d = GET_IGDATA(data);
    char *_key = DATA_INDEX_AS_NAME ? "0" : "endTask";

    if(!d) {
        return -1;
    }
    if(!(it = cJSON_CreateObject())) {
        return -1;
    }
    cJSON_AddStringToObject(it, JSON_KEY_PD_ATT_NAME, _key);
#if DATA_TYPE_AS_STRING
    char *_p, _buf[32];
    _p = _buf;
#if defined(_DATA_TYPE_SET_endTask_String)
    _p = endTask;
#elif defined(_DATA_TYPE_SET_endTask_Float)
    snprintf(_buf, sizeof(_buf), "%.2f", endTask);
#elif defined(_DATA_TYPE_SET_endTask_Integer)
    snprintf(_buf, sizeof(_buf), "%d", endTask);
#endif
    cJSON_AddStringToObject(it, JSON_KEY_PD_ATT_VALUE, _p);
#else //  DATA_TYPE_AS_STRING
#if defined(_DATA_TYPE_SET_endTask_String)
    cJSON_AddStringToObject(it, JSON_KEY_PD_ATT_VALUE, endTask);
#elif defined(_DATA_TYPE_SET_endTask_Float)
    cJSON_AddNumberToObject(it, JSON_KEY_PD_ATT_VALUE, endTask);
#elif defined(_DATA_TYPE_SET_endTask_Integer)
    cJSON_AddNumberToObject(it, JSON_KEY_PD_ATT_VALUE, endTask);
#endif
#endif // DATA_TYPE_AS_STRING
    cJSON_AddStringToObject(it, JSON_KEY_PD_ATT_CHANNEL, "m");
    if((item = glodon_iot_data_find_attrabute_item(d, _key)) >= 0) {
        cJSON_ReplaceItemInArray(d->cjson_payload_att, item, it);
    } else {
        cJSON_AddItemToArray(d->cjson_payload_att, it);
    }
    return 0;
}
FUNCTION_SESSION_SET
static int glodon_iot_data_set_updateTask(GlodonIoTData data, char * updateTask)
{
#define _DATA_TYPE_SET_updateTask_String
    int item;
    cJSON *it;
    IGlodonIoTData d = GET_IGDATA(data);
    char *_key = DATA_INDEX_AS_NAME ? "0" : "updateTask";

    if(!d) {
        return -1;
    }
    if(!(it = cJSON_CreateObject())) {
        return -1;
    }
    cJSON_AddStringToObject(it, JSON_KEY_PD_ATT_NAME, _key);
#if DATA_TYPE_AS_STRING
    char *_p, _buf[32];
    _p = _buf;
#if defined(_DATA_TYPE_SET_updateTask_String)
    _p = updateTask;
#elif defined(_DATA_TYPE_SET_updateTask_Float)
    snprintf(_buf, sizeof(_buf), "%.2f", updateTask);
#elif defined(_DATA_TYPE_SET_updateTask_Integer)
    snprintf(_buf, sizeof(_buf), "%d", updateTask);
#endif
    cJSON_AddStringToObject(it, JSON_KEY_PD_ATT_VALUE, _p);
#else //  DATA_TYPE_AS_STRING
#if defined(_DATA_TYPE_SET_updateTask_String)
    cJSON_AddStringToObject(it, JSON_KEY_PD_ATT_VALUE, updateTask);
#elif defined(_DATA_TYPE_SET_updateTask_Float)
    cJSON_AddNumberToObject(it, JSON_KEY_PD_ATT_VALUE, updateTask);
#elif defined(_DATA_TYPE_SET_updateTask_Integer)
    cJSON_AddNumberToObject(it, JSON_KEY_PD_ATT_VALUE, updateTask);
#endif
#endif // DATA_TYPE_AS_STRING
    cJSON_AddStringToObject(it, JSON_KEY_PD_ATT_CHANNEL, "m");
    if((item = glodon_iot_data_find_attrabute_item(d, _key)) >= 0) {
        cJSON_ReplaceItemInArray(d->cjson_payload_att, item, it);
    } else {
        cJSON_AddItemToArray(d->cjson_payload_att, it);
    }
    return 0;
}
FUNCTION_SESSION_SET
static int glodon_iot_data_set_warningInfo(GlodonIoTData data, char * warningInfo)
{
#define _DATA_TYPE_SET_warningInfo_String
    int item;
    cJSON *it;
    IGlodonIoTData d = GET_IGDATA(data);
    char *_key = DATA_INDEX_AS_NAME ? "0" : "warningInfo";

    if(!d) {
        return -1;
    }
    if(!(it = cJSON_CreateObject())) {
        return -1;
    }
    cJSON_AddStringToObject(it, JSON_KEY_PD_ATT_NAME, _key);
#if DATA_TYPE_AS_STRING
    char *_p, _buf[32];
    _p = _buf;
#if defined(_DATA_TYPE_SET_warningInfo_String)
    _p = warningInfo;
#elif defined(_DATA_TYPE_SET_warningInfo_Float)
    snprintf(_buf, sizeof(_buf), "%.2f", warningInfo);
#elif defined(_DATA_TYPE_SET_warningInfo_Integer)
    snprintf(_buf, sizeof(_buf), "%d", warningInfo);
#endif
    cJSON_AddStringToObject(it, JSON_KEY_PD_ATT_VALUE, _p);
#else //  DATA_TYPE_AS_STRING
#if defined(_DATA_TYPE_SET_warningInfo_String)
    cJSON_AddStringToObject(it, JSON_KEY_PD_ATT_VALUE, warningInfo);
#elif defined(_DATA_TYPE_SET_warningInfo_Float)
    cJSON_AddNumberToObject(it, JSON_KEY_PD_ATT_VALUE, warningInfo);
#elif defined(_DATA_TYPE_SET_warningInfo_Integer)
    cJSON_AddNumberToObject(it, JSON_KEY_PD_ATT_VALUE, warningInfo);
#endif
#endif // DATA_TYPE_AS_STRING
    cJSON_AddStringToObject(it, JSON_KEY_PD_ATT_CHANNEL, "m");
    if((item = glodon_iot_data_find_attrabute_item(d, _key)) >= 0) {
        cJSON_ReplaceItemInArray(d->cjson_payload_att, item, it);
    } else {
        cJSON_AddItemToArray(d->cjson_payload_att, it);
    }
    return 0;
}
FUNCTION_SESSION_SET
static int glodon_iot_data_set_electricFlow(GlodonIoTData data, double electricFlow)
{
#define _DATA_TYPE_SET_electricFlow_Float
    int item;
    cJSON *it;
    IGlodonIoTData d = GET_IGDATA(data);
    char *_key = DATA_INDEX_AS_NAME ? "0" : "electricFlow";

    if(!d) {
        return -1;
    }
    if(!(it = cJSON_CreateObject())) {
        return -1;
    }
    cJSON_AddStringToObject(it, JSON_KEY_PD_ATT_NAME, _key);
#if DATA_TYPE_AS_STRING
    char *_p, _buf[32];
    _p = _buf;
#if defined(_DATA_TYPE_SET_electricFlow_String)
    _p = electricFlow;
#elif defined(_DATA_TYPE_SET_electricFlow_Float)
    snprintf(_buf, sizeof(_buf), "%.2f", electricFlow);
#elif defined(_DATA_TYPE_SET_electricFlow_Integer)
    snprintf(_buf, sizeof(_buf), "%d", electricFlow);
#endif
    cJSON_AddStringToObject(it, JSON_KEY_PD_ATT_VALUE, _p);
#else //  DATA_TYPE_AS_STRING
#if defined(_DATA_TYPE_SET_electricFlow_String)
    cJSON_AddStringToObject(it, JSON_KEY_PD_ATT_VALUE, electricFlow);
#elif defined(_DATA_TYPE_SET_electricFlow_Float)
    cJSON_AddNumberToObject(it, JSON_KEY_PD_ATT_VALUE, electricFlow);
#elif defined(_DATA_TYPE_SET_electricFlow_Integer)
    cJSON_AddNumberToObject(it, JSON_KEY_PD_ATT_VALUE, electricFlow);
#endif
#endif // DATA_TYPE_AS_STRING
    cJSON_AddStringToObject(it, JSON_KEY_PD_ATT_CHANNEL, "m");
    if((item = glodon_iot_data_find_attrabute_item(d, _key)) >= 0) {
        cJSON_ReplaceItemInArray(d->cjson_payload_att, item, it);
    } else {
        cJSON_AddItemToArray(d->cjson_payload_att, it);
    }
    return 0;
}
FUNCTION_SESSION_SET
static int glodon_iot_data_set_machineState(GlodonIoTData data, char * machineState)
{
#define _DATA_TYPE_SET_machineState_String
    int item;
    cJSON *it;
    IGlodonIoTData d = GET_IGDATA(data);
    char *_key = DATA_INDEX_AS_NAME ? "0" : "machineState";

    if(!d) {
        return -1;
    }
    if(!(it = cJSON_CreateObject())) {
        return -1;
    }
    cJSON_AddStringToObject(it, JSON_KEY_PD_ATT_NAME, _key);
#if DATA_TYPE_AS_STRING
    char *_p, _buf[32];
    _p = _buf;
#if defined(_DATA_TYPE_SET_machineState_String)
    _p = machineState;
#elif defined(_DATA_TYPE_SET_machineState_Float)
    snprintf(_buf, sizeof(_buf), "%.2f", machineState);
#elif defined(_DATA_TYPE_SET_machineState_Integer)
    snprintf(_buf, sizeof(_buf), "%d", machineState);
#endif
    cJSON_AddStringToObject(it, JSON_KEY_PD_ATT_VALUE, _p);
#else //  DATA_TYPE_AS_STRING
#if defined(_DATA_TYPE_SET_machineState_String)
    cJSON_AddStringToObject(it, JSON_KEY_PD_ATT_VALUE, machineState);
#elif defined(_DATA_TYPE_SET_machineState_Float)
    cJSON_AddNumberToObject(it, JSON_KEY_PD_ATT_VALUE, machineState);
#elif defined(_DATA_TYPE_SET_machineState_Integer)
    cJSON_AddNumberToObject(it, JSON_KEY_PD_ATT_VALUE, machineState);
#endif
#endif // DATA_TYPE_AS_STRING
    cJSON_AddStringToObject(it, JSON_KEY_PD_ATT_CHANNEL, "m");
    if((item = glodon_iot_data_find_attrabute_item(d, _key)) >= 0) {
        cJSON_ReplaceItemInArray(d->cjson_payload_att, item, it);
    } else {
        cJSON_AddItemToArray(d->cjson_payload_att, it);
    }
    return 0;
}

FUNCTION_SESSION_SET
int glodon_iot_data_callback(IGlodonIoTData d, void (*callback)(void *callbackdata, int evt, int argc, void *argv[]), void *callbackdata)
{
    void *argv[16];
    int evt, argc = 0;
    cJSON *element, *name, *value, *it;
    IOTDataType dataType = IOT_DATA_TYPE_NULL;

#define DEF_AND_GET_Boolean(it, x)      bool *x = (bool *)&(it->type)
#define DEF_AND_GET_Integer(it, x)      int *x = &(it->valueint)
#define DEF_AND_GET_Float(it, x)        double *x = &(it->valuedouble)
#define DEF_AND_GET_String(it, x)       char **x = &(it->valuestring)
    if(!d || !d->cjson_meta || !d->cjson_payload || !callback) {
        return -1;
    }
    it = cJSON_GetObjectItem(d->cjson_meta, JSON_KEY_TYPE);
    if(!it || !cJSON_IsString(it)) {
        return -1;
    }
    if(!strcmp(it->valuestring, DATA_TYPE_CONFIG)) {
        dataType = IOT_DATA_TYPE_CONFIG;
    } else if(!strcmp(it->valuestring, DATA_TYPE_META)) {
        dataType = IOT_DATA_TYPE_META;
    } else {
        return -1;
    }
    if(d->cjson_payload_att) {
        cJSON_ArrayForEach(element, d->cjson_payload_att) {
            argc = 0;
            name = cJSON_GetObjectItem(element, JSON_KEY_PD_ATT_NAME);
            value = cJSON_GetObjectItem(element, JSON_KEY_PD_ATT_VALUE);
            if(!name || !value) {
                continue;
            }
            if(dataType == IOT_DATA_TYPE_CONFIG) {
                if(!glodon_iot_parse_internal_write(name->valuestring, value, &evt, argv[0])) {
                    callback(callbackdata, evt, argc, argv);
                }
                continue;
            }

            { // else
            }
        }
    }
    if(d->cjson_payload_act) {
        cJSON_ArrayForEach(element, d->cjson_payload_act) {
            argc = 0;
            name = cJSON_GetObjectItem(element, JSON_KEY_PD_ACT_CODE);
            value = cJSON_GetObjectItem(element, JSON_KEY_PD_ACT_PARAM);
            if(!name) {
                continue;
            }
            if(dataType == IOT_DATA_TYPE_CONFIG) {
                if(!glodon_iot_parse_internal_action(name->valuestring, value, &evt, &argc, argv, (sizeof(argv)/sizeof(argv[0])))) {
                    callback(callbackdata, evt, argc, argv);
                }
                continue;
            }
            // 任务信息: 
            if(!strcmp(name->valuestring, "curTaskData")) {
                // 任务信息
                if(!value || !(it = cJSON_GetObjectItem(value, "taskInfo"))) {
                    continue;
                }
                DEF_AND_GET_String(it, _taskInfo_String);
                argv[argc++] = _taskInfo_String;

                callback(callbackdata, GLODON_EVENT_ACT_CURTASKDATA, argc, argv);
            } else
            // 当前任务数量: 
            if(!strcmp(name->valuestring, "curTaskCount")) {
                // 数量
                if(!value || !(it = cJSON_GetObjectItem(value, "count"))) {
                    continue;
                }
                DEF_AND_GET_Integer(it, _count_Integer);
                argv[argc++] = _count_Integer;

                callback(callbackdata, GLODON_EVENT_ACT_CURTASKCOUNT, argc, argv);
            } else

            { // else
            }
        }
    }
    return 0;
}

