/*
 * glodon_iot_data_internal.h
 *
 * Create on: 2017-08-01
 *
 *    Author: feiguoyou@hotmail.com
 *
 */

#ifndef _GLODON_IOT_DATA_INTERNAL_H_
#define _GLODON_IOT_DATA_INTERNAL_H_

#include <stdint.h>
#include <stdbool.h>
#include "cJSON.h"

#ifdef __cplusplus
extern "C" {
#endif //  __cplusplus

#define DATA_TYPE_AS_STRING         0 // 所有Json以字符串存入
#define DATA_INDEX_AS_NAME          0 // 数据名称用INDEX代替

// meta
#define JSON_KEY_META           "meta"
#define JSON_KEY_ID             "id"            // STRING
#define JSON_KEY_TYPE           "type"          // Enum<STRING>
#define JSON_KEY_DEVID          "deviceid"      // STRING
#define JSON_KEY_VERSION        "version"       // STRING
#define JSON_KEY_TIMESTAMP      "ts"            // LONG
#define JSON_KEY_NEEDACK        "needack"       // Boolean
#define JSON_KEY_CORRELATIONID  "correlationId" // STRING

// payload
#define JSON_KEY_PAYLOAD                "payload"
#define JSON_KEY_PAYLOAD_ATTRABUTE      "attrs"
#define JSON_KEY_PD_ATT_NAME            "code"
#define JSON_KEY_PD_ATT_VALUE           "value"
#define JSON_KEY_PD_ATT_CHANNEL         "channel"
#define JSON_KEY_PAYLOAD_ACTION         "actions"
#define JSON_KEY_PD_ACT_CODE            "code"
#define JSON_KEY_PD_ACT_PARAM           "params"

#define DATA_TYPE_META          "m"
#define DATA_TYPE_CONFIG        "c"
typedef enum {
    IOT_DATA_TYPE_META,
    IOT_DATA_TYPE_CONFIG,
    IOT_DATA_TYPE_NULL,
} IOTDataType;

#define GLODON_IEVENT_LOG_STR    "log"
typedef enum {
    GLODON_IEVENT_START = 100,
    GLODON_IEVENT_LOG, // "isdebug": true, "level": "INFO"
    GLODON_IEVENT_END = 1000,
} GlodonInternalEvent;

#ifndef offsetof
#define offsetof(type, member) ((unsigned long) &((type *)0)->member)
#endif
#ifndef container_of
#define container_of(ptr, type, member) ({                      \
    (type *)( (unsigned long)ptr - offsetof(type, member) );})
#endif

typedef struct _IGlodonIoTData* IGlodonIoTData;

IGlodonIoTData glodon_iot_data_alloc(void);
IGlodonIoTData glodon_iot_data_alloc_ack_for(IGlodonIoTData d);
void glodon_iot_data_free(IGlodonIoTData d);

IGlodonIoTData glodon_iot_data_from(void *userdata);
void* glodon_iot_data_get(IGlodonIoTData d);

int glodon_iot_data_set_id(IGlodonIoTData d, const char *id);
int glodon_iot_data_set_type(IGlodonIoTData d, const char *type);
int glodon_iot_data_set_username(IGlodonIoTData d, const char *username);
int glodon_iot_data_set_ts(IGlodonIoTData d, uint32_t ts); // sec
bool glodon_iot_data_need_ack(IGlodonIoTData d);

int glodon_iot_data_set_json(IGlodonIoTData d, const char *jsonstr);
int glodon_iot_data_get_json(IGlodonIoTData d, char *buf, int max);

int glodon_iot_data_callback(IGlodonIoTData d, void (*callback)(void *callbackdata, int evt, int argc, void *argv[]), void *callbackdata);
int glodon_iot_parse_internal_write(const char *name, cJSON *value, int *evt, void *argv);
int glodon_iot_parse_internal_action(const char *name, cJSON *params, int *evt, int *argc, void *argv[], int max);

#ifdef __cplusplus
}
#endif //  __cplusplus

#endif    // #ifndef _GLODON_IOT_DATA_INTERNAL_H_

