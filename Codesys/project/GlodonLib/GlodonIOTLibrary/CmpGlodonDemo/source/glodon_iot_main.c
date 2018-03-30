/*
 * main.c
 *
 * Create on: 2017-06-20
 *
 *    Author: feiguoyou@hotmail.com
 *
 */

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>
#include "app_data.h"
#include "glodon_iot_log.h"
#include "glodon_iot_client.h"

#ifndef GLODON_IOT_MQTT_USERNAME
#define GLODON_IOT_MQTT_USERNAME          "36d87fda-ee0f-4e2c-98bb-703e351031f7"
#endif
#ifndef GLODON_IOT_MQTT_PASSWORD
#define GLODON_IOT_MQTT_PASSWORD          "3bc78186-b125-4551-8c90-5b315f39e6b8"
#endif

/*
 * 日志输出接口
 */
static void on_log_output(GlodonIotClient pClient, int level, char *str, size_t len)
{
    printf("%s", str);
}

/*
 * 连接反馈
 */
static void on_connect(GlodonIotClient pClient, bool flag)
{
    IOT_INFO(pClient, "on_connect, flag = %d", flag);
}

