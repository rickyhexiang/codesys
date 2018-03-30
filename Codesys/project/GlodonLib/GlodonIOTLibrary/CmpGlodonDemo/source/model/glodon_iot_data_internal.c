/*
 * glodon_iot_data_internal.c
 *
 * Create on: 2017-08-01
 *
 *    Author: feiguoyou@hotmail.com
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "glodon_iot_data_def.h"
#include "glodon_iot_data_internal.h"

FUNCTION_SESSION_SET
IGlodonIoTData glodon_iot_data_alloc(void)
{
    IGlodonIoTData d = (IGlodonIoTData)(malloc(sizeof(*d)));

    if(!d) {
        return NULL;
    }
    memset(d, 0, sizeof(*d));
    d->cjson = cJSON_CreateObject();
    if(!d->cjson) {
        goto errout;
    }
    // meta
    d->cjson_meta = cJSON_CreateObject();
    if(!d->cjson_meta) {
        goto errout;
    }
    cJSON_AddItemToObject(d->cjson, JSON_KEY_META, d->cjson_meta);
    // payload
    d->cjson_payload = cJSON_CreateObject();
    if(!d->cjson_payload) {
        goto errout;
    }
    cJSON_AddItemToObject(d->cjson, JSON_KEY_PAYLOAD, d->cjson_payload);
    // attrabute
    d->cjson_payload_att = cJSON_CreateArray();
    if(!d->cjson_payload_att) {
        goto errout;
    }
    cJSON_AddItemToObject(d->cjson_payload, JSON_KEY_PAYLOAD_ATTRABUTE, d->cjson_payload_att);
    // action
    d->cjson_payload_act = cJSON_CreateArray();
    if(!d->cjson_payload_act) {
        goto errout;
    }
    cJSON_AddItemToObject(d->cjson_payload, JSON_KEY_PAYLOAD_ACTION, d->cjson_payload_act);
    // default value
    cJSON_AddStringToObject(d->cjson_meta, JSON_KEY_VERSION, DEVICE_MODEL_GEN_VERSOIN);
    cJSON_AddFalseToObject(d->cjson_meta, JSON_KEY_NEEDACK);
    //cJSON_AddStringToObject(d->cjson_meta, JSON_KEY_CORRELATIONID, "");
    return d;
errout:
    if(d) {
        if(d->cjson) {
            cJSON_Delete(d->cjson);
        }
        free(d);
    }
    return NULL;
}

FUNCTION_SESSION_SET
IGlodonIoTData glodon_iot_data_from(void *userdata)
{
    return GET_IGDATA(userdata);
}

FUNCTION_SESSION_SET
void* glodon_iot_data_get(IGlodonIoTData d)
{
    return &d->data;
}

FUNCTION_SESSION_SET
void glodon_iot_data_free(IGlodonIoTData d)
{
    if(!d) {
        return;
    }
    if(d->cjson) {
        cJSON_Delete(d->cjson);
    }
    free(d);
}

FUNCTION_SESSION_SET
IGlodonIoTData glodon_iot_data_alloc_ack_for(IGlodonIoTData d)
{
    IGlodonIoTData ack = glodon_iot_data_alloc();
    // TODO
    return ack;
}

FUNCTION_SESSION_SET
int glodon_iot_data_set_id(IGlodonIoTData d, const char *id)
{
    if(!d || !id) {
        return -1;
    }
    cJSON_DeleteItemFromObject(d->cjson_meta, JSON_KEY_ID);
    cJSON_AddStringToObject(d->cjson_meta, JSON_KEY_ID, id);
    return 0;
}

FUNCTION_SESSION_SET
int glodon_iot_data_set_type(IGlodonIoTData d, const char *type)
{
    if(!d || !type) {
        return -1;
    }
    cJSON_DeleteItemFromObject(d->cjson_meta, JSON_KEY_TYPE);
    cJSON_AddStringToObject(d->cjson_meta, JSON_KEY_TYPE, type);
    return 0;
}

FUNCTION_SESSION_SET
int glodon_iot_data_set_username(IGlodonIoTData d, const char *id)
{
    if(!d || !id) {
        return -1;
    }
    cJSON_DeleteItemFromObject(d->cjson_meta, JSON_KEY_DEVID);
    cJSON_AddStringToObject(d->cjson_meta, JSON_KEY_DEVID, id);
    return 0;
}

FUNCTION_SESSION_SET
int glodon_iot_data_set_ts(IGlodonIoTData d, uint32_t ts)
{
    if(!d) {
        return -1;
    }
    cJSON_DeleteItemFromObject(d->cjson_meta, JSON_KEY_TIMESTAMP);
    cJSON_AddNumberToObject(d->cjson_meta, JSON_KEY_TIMESTAMP, ts);
    return 0;
}

FUNCTION_SESSION_SET
bool glodon_iot_data_need_ack(IGlodonIoTData d)
{
    cJSON *it;
    
    if(!(it = cJSON_GetObjectItem(d->cjson_meta, JSON_KEY_NEEDACK)) || !cJSON_IsBool(it)) {
        return false;
    }
    return cJSON_IsTrue(it);
}

FUNCTION_SESSION_SET
int glodon_iot_data_set_json(IGlodonIoTData d, const char *jsonstr)
{
    cJSON *it;

    if(!d) {
        return -1;
    }
    if(d->cjson) {
        cJSON_Delete(d->cjson);
        d->cjson = NULL;
    }
    if(!(d->cjson = cJSON_Parse(jsonstr))) {
        goto errout;
    }
    // meta
    if(!(it = cJSON_GetObjectItem(d->cjson, JSON_KEY_META)) || !cJSON_IsObject(it)) {
        goto errout;
    }
    d->cjson_meta = it;
    // payload
    if(!(it = cJSON_GetObjectItem(d->cjson, JSON_KEY_PAYLOAD)) || !cJSON_IsObject(it)) {
        goto errout;
    }
    d->cjson_payload = it;
    // attrabute
    if((it = cJSON_GetObjectItem(d->cjson_payload, JSON_KEY_PAYLOAD_ATTRABUTE)) && cJSON_IsArray(it)) {
        d->cjson_payload_att = it;
    } else if((it = cJSON_CreateObject())) {
        d->cjson_payload_att = it;
        cJSON_AddItemToObject(d->cjson_payload, JSON_KEY_PAYLOAD_ATTRABUTE, it);
    } else {
        goto errout;
    }
    // action
    if((it = cJSON_GetObjectItem(d->cjson_payload, JSON_KEY_PAYLOAD_ACTION)) && cJSON_IsArray(it)) {
        d->cjson_payload_act = it;
    } else if((it = cJSON_CreateObject())) {
        d->cjson_payload_act = it;
        cJSON_AddItemToObject(d->cjson_payload, JSON_KEY_PAYLOAD_ACTION, it);
    } else {
        goto errout;
    }
    return 0;
errout:
    if(d->cjson) {
        cJSON_Delete(d->cjson);
        d->cjson = NULL;
    }
    return -1;
}

FUNCTION_SESSION_SET
int glodon_iot_data_get_json(IGlodonIoTData d, char *buf, int max)
{
    if(!d) {
        return -1;
    }
    /*CJSON_PUBLIC(cJSON_bool) cJSON_PrintPreallocated(cJSON *item, char *buffer, const int length, const cJSON_bool format);*/
    return cJSON_PrintPreallocated(d->cjson, buf, max, 1) ? 0 : -1;
}

FUNCTION_SESSION_SET
int glodon_iot_parse_internal_write(const char *name, cJSON *value, int *evt, void *argv)
{
    return -1;
}

FUNCTION_SESSION_SET
int glodon_iot_parse_internal_action(const char *name, cJSON *params, int *evt, int *argc, void *argv[], int max)
{
    cJSON *it;

    if(!strcmp(name, GLODON_IEVENT_LOG_STR) && max >= 2) {
        *argc = 2;
        *evt = GLODON_IEVENT_LOG;
        if(!(it = cJSON_GetObjectItem(params, "isdebug"))) {
            return -1;
        }
        argv[0] = &(it->type);
        if(!(it = cJSON_GetObjectItem(params, "level"))) {
            return -1;
        }
        argv[1] = (it->valuestring);
        return 0;
    }
    return -1;
}

