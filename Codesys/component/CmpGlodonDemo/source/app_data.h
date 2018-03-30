/*
 * app_data.h
 *
 * Create on: 2017-09-13
 *
 *    Author: feiguoyou@hotmail.com
 *
 */

#ifndef _APP_DATA_H_
#define _APP_DATA_H_

#ifdef __cplusplus
extern "C" {
#endif //  __cplusplus

#include "glodon_iot_log.h"
#include "model/glodon_iot_data.h"
#include "glodon_iot_client.h"

/*
 *  云端消息
 */ 
void on_app_message(GlodonIotClient pClient, int evt, int argc, void *argv[], void *ack);

/*
 *  获取设备数据, 用于上报到云端. 
 */
int app_get_data(GlodonIoTData data);

#ifdef __cplusplus
}
#endif //  __cplusplus

#endif    // #ifndef _APP_DATA_H_

