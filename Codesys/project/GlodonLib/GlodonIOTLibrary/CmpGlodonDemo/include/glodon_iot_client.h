/*
 * glodon_iot_client.h
 *
 * Create on: 2017-06-20
 *
 *    Author: feiguoyou@hotmail.com
 *
 */

#ifndef _GLODON_IOT_CLIENT_H_
#define _GLODON_IOT_CLIENT_H_

#ifdef __cplusplus
extern "C" {
#endif // #ifdef __cplusplus

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include "glodon_iot_error.h"

typedef struct _GlodonIotClient* GlodonIotClient;
typedef struct _GlodonIotInitParams GlodonIotInitParams;

/**
 * @brief log Callback Handler Type
 *
 * @param pClient Pointer to GlodonIotClient
 * 
 * @param level, log level(IOT_LOG_LEVEL_xxx)
 * 
 * @param str Pointer to log string
 * 
 * @param len, Log string length
 * 
 * Defining a TYPE for definition of Log callback function pointers.
 *
 */
typedef void (*GlodonIotLogOutput)(GlodonIotClient pClient, int level, char *str, size_t len);

/**
 * @brief connect Callback Handler Type
 *
 * @param pClient Pointer to GlodonIotClient
 * 
 * @param flag, connect state. true - connected, false - disconnected
 * 
 * Defining a TYPE for definition of connect callback function pointers.
 *
 */
typedef void (*GlodonIotOnConnectCallback)(GlodonIotClient pClient, bool flag);

/**
 * @brief message Callback Handler Type
 *
 * @param pClient Pointer to GlodonIotClient
 * 
 * @param evt, Message event id(GlodonEvent)
 * 
 * @param ack Pointer to GlodonIoTData
 * 
 * Defining a TYPE for definition of message callback function pointers.
 *
 */
typedef void (*GlodonIotOnMessageCallback)(GlodonIotClient pClient, int evt, int argc, void *argv[], void *ack);

/**
 * @brief Glodon Client
 *
 * Defines a type for Glodon Client
 *
 */
struct _GlodonIotInitParams {
    char *username;                         ///< Pointer to a cstring defining the IoT useranme
    char *password;                         ///< Pointer to a cstring defining the IoT password
    void *userdata;                         ///< Pointer to a userdata, defined by application
    bool useMqtts;                          ///< Enable MQTTS
    GlodonIotLogOutput onLogOutput;         ///< Callback to be invoked upon log outputting
    GlodonIotOnConnectCallback onConnect;   ///< Callback to be invoked upon connection success or loss
    GlodonIotOnMessageCallback onMessage;   ///< Callback to be invoked upon messge coming
};

/**
 * @brief Get the library vesion
 *
 * Called to get the version of the glodon library
 *
 * @return library version
 */
const char* glodon_iot_get_version(void);

/**
 * @brief GlodonIotClient Initialization Function
 *
 * Called to initialize the GlodonIotClient
 *
 * @param pParams Pointer to GlodonIotClient parameters
 *
 * @return Handler of GlodonIotClient / or NULL
 */
GlodonIotClient glodon_iot_init(GlodonIotInitParams *pParams);

/**
 * @brief GlodonIotClient destory Function
 *
 * Called to release the GlodonIotClient
 *
 * @param pClient Pointer to GlodonIotClient
 *
 */
void glodon_iot_destory(GlodonIotClient pClient);

/**
 * @brief GlodonIotClient Connection Function
 *
 * Called to establish an GlodonIotClient connection with the GLODON IoT Service
 *
 * @param pClient Reference to the GlodonIotClient
 *
 * @return An IoT Error Type defining successful/failed connection
 */
IoTError glodon_iot_connect(GlodonIotClient pClient);

/**
 * @brief Yield to the GlodonIotClient
 *
 * Called to yield the current thread to the underlying GlodonIotClient.  This time is used by
 * the GlodonIotClient to manage PING requests to monitor the health of the TCP connection as
 * well as periodically check the socket receive buffer for subscribe messages.  Yield()
 * must be called at a rate faster than the keepalive interval.  It must also be called
 * at a rate faster than the incoming message rate as this is the only way the client receives
 * processing time to manage incoming messages.
 *
 * @param pClient Reference to the GlodonIotClient
 * @param timeout_ms Maximum number of milliseconds to pass thread execution to the client.
 *
 */
void glodon_iot_yield(GlodonIotClient pClient, uint32_t timeout); // ms

/**
 * @brief Is the GlodonIotClient currently connected?
 *
 * Called to determine if the GlodonIotClient is currently connected.  Used to support logic
 * managing offline state.
 *
 * @param pClient Reference to the GlodonIotClient
 *
 * @return true = connected, false = not currently connected
 */
bool glodon_iot_is_client_connected(GlodonIotClient pClient);

/**
 * @brief Send a Glodon IoT message
 *
 * Called to send an Glodon IoT message
 * @note Call is blocking.  
 *
 * @param pClient Reference to the GlodonIotClient
 * @param pData Pointer GlodonIoTData
 *
 * @return An IoT Error Type defining successful/failed send
 */
IoTError glodon_iot_send(GlodonIotClient pClient, void *pData);

/**
 * @brief is the same as glodon_iot_send() except that it append a parameter of timeout
 */
IoTError glodon_iot_send_ex(GlodonIotClient pClient, void *pData, uint32_t timeout); // ms

/**
 * @brief get a userdata of application
 *
 * Called to get userdata
 * @note Call is blocking.  
 *
 * @param pClient Reference to the GlodonIotClient
 *
 * @return userdata
 */
void* glodon_iot_get_userdata(GlodonIotClient pClient);

#ifdef __cplusplus
}
#endif // #ifdef __cplusplus
#endif    // #ifndef _GLODON_IOT_CLIENT_H_

