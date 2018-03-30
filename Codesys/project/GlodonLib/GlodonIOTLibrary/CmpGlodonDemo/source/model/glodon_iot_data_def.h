/*
 * glodon_iot_data_def.h
 *
 * Create on: 2017-08-01
 *
 *    Author: feiguoyou@hotmail.com
 *
 */

#ifndef _GLODON_IOT_DATA_DEF_H_
#define _GLODON_IOT_DATA_DEF_H_

#ifdef __cplusplus
extern "C" {
#endif //  __cplusplus

#include "cJSON.h"
#include "glodon_iot_data.h"
#include "glodon_iot_data_internal.h"

struct _IGlodonIoTData {
    cJSON *cjson;
    cJSON *cjson_meta;
    cJSON *cjson_payload;
    cJSON *cjson_payload_att;
    cJSON *cjson_payload_act;
    struct _GlodonIoTData data;
};

#define GET_IGDATA(x)   (x ? container_of(x, struct _IGlodonIoTData, data) : NULL)

#ifdef __cplusplus
}
#endif //  __cplusplus

#endif    // #ifndef _GLODON_IOT_DATA_DEF_H_

