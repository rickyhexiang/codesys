#ifndef _GLODON_IOT_LOG_H_
#define _GLODON_IOT_LOG_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <stdlib.h>

#define IOT_LOG_LEVEL_ERROR         0
#define IOT_LOG_LEVEL_WARNING       1
#define IOT_LOG_LEVEL_INFO          2
#define IOT_LOG_LEVEL_DEBUG         3

/**
 * @brief Debug level trace logging macro.
 *
 * Macro to print message function entry and exit
 */
#ifdef ENABLE_IOT_TRACE
#define FUNC_ENTRY    \
	{\
        CRITICAL_LOG_PRINTF("FUNC_ENTRY:   %s L#%d \n", __func__, __LINE__);  \
	}
#define FUNC_EXIT    \
	{\
        CRITICAL_LOG_PRINTF("FUNC_EXIT:   %s L#%d \n", __func__, __LINE__);  \
        return; \
	}
#define FUNC_EXIT_RC(x)    \
	{\
        CRITICAL_LOG_PRINTF("FUNC_EXIT:   %s L#%d Return Code : %d \n", __func__, __LINE__, (int)(x));  \
        return (x); \
	}
#define FUNC_EXIT_RC_POINTER(x)    \
	{\
        CRITICAL_LOG_PRINTF("FUNC_EXIT:   %s L#%d Return Code : %p \n", __func__, __LINE__, (void *)(x));  \
        return (x); \
	}
#else
#define FUNC_ENTRY
#define FUNC_EXIT {return;}
#define FUNC_EXIT_RC(x) {return (x);}
#define FUNC_EXIT_RC_POINTER(x)  FUNC_EXIT_RC(x)
#endif

/**
 * @brief Debug level logging macro.
 *
 * Macro to expose function, line number as well as desired log message.
 */
#ifdef ENABLE_IOT_DEBUG
#define IOT_DEBUG(pLogData, fmt, arg...)  glodon_iot_log_output(pLogData, IOT_LOG_LEVEL_DEBUG, fmt, ##arg)
#else
#define IOT_DEBUG(pLogData, fmt, arg...)
#endif

/**
 * @brief Info level logging macro.
 *
 * Macro to expose desired log message.  Info messages do not include automatic function names and line numbers.
 */
#ifdef ENABLE_IOT_INFO
#define IOT_INFO(pLogData, fmt, arg...)  glodon_iot_log_output(pLogData, IOT_LOG_LEVEL_INFO, fmt, ##arg)
#else
#define IOT_INFO(pLogData, fmt, arg...)
#endif

/**
 * @brief Warn level logging macro.
 *
 * Macro to expose function, line number as well as desired log message.
 */
#ifdef ENABLE_IOT_WARN
#define IOT_WARN(pLogData, fmt, arg...)  glodon_iot_log_output(pLogData, IOT_LOG_LEVEL_WARNING, fmt, ##arg)
#else
#define IOT_WARN(pLogData, fmt, arg...)
#endif

/**
 * @brief Error level logging macro.
 *
 * Macro to expose function, line number as well as desired log message.
 */
#ifdef ENABLE_IOT_ERROR
#define IOT_ERROR(pLogData, fmt, arg...)  glodon_iot_log_output(pLogData, IOT_LOG_LEVEL_ERROR, fmt, ##arg)
#else
#define IOT_ERROR(pLogData, fmt, arg...)
#endif

/**
 * @brief Output a log message
 *
 * Called to Output a log message
 * @note Call is blocking.
 *
 * @param pLogData Reference to the GlodonIotClient
 * @param levle Log level(0-3)
 * @param fmt Format of ther message(...)
 *
 */
extern void (*glodon_iot_log_output)(void *pLogData, int level, const char *fmt, ...);

#ifdef __cplusplus
}
#endif

#endif // _GLODON_IOT_LOG_H_
