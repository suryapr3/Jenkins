/**********************************************************************************************
* INTEL CONFIDENTIAL
* Copyright (C) 2022 Intel Corporation
* This software and the related documents ("Material") are Intel copyrighted materials,
* and your use of them is governed by the express license under which they were provided
* to you ("License"). Unless the License provides otherwise, you may not use, modify,
* copy, publish, distribute, disclose or transmit this software or the related documents
* without Intel's prior written permission.
* This software and the related documents are provided as is, with no express or implied
* warranties, other than those that are expressly stated in the License.
* No license under any patent, copyright, trade secret or other intellectual property
* right is granted to or conferred upon you by disclosure or delivery of the Materials,
* either expressly, by implication, inducement, estoppel or otherwise. Any license under
* such intellectual property rights must be expressed and approved by Intel in writing.
*********************************************************************************************/

/*********************************************************************************************
 * @file  logger.h
**********************************************************************************************/

void log_print(char* filename, int line, char* fmt, ...);

#define LOG_PRINT(...) log_print(__FILE__, __LINE__, __VA_ARGS__)

//If nospecific log level is defined, default to LOG_ALL
#if !defined(LOG_WARNING) && !defined(LOG_DEBUG) && !defined(LOG_ERROR) && !defined(LOG_INFO)
#undef LOG_ALL
#define LOG_ALL
#endif

// Define macros for different log levels with conditional checks
#if defined(LOG_ALL)                                    // If LOG_ALL is defined, all log levels are enabled.
#undef LOG_ALL
#define LOG_INFO(...) log_print(__FILE__, __LINE__, "INFO: " __VA_ARGS__ )
#define LOG_DEBUG(...) log_print(__FILE__, __LINE__, "DEBUG: " __VA_ARGS__ )
#define LOG_WARNING(...) log_print(__FILE__, __LINE__, "WARNING: " __VA_ARGS__)
#define LOG_ERROR(...) log_print(__FILE__, __LINE__, "ERROR: " __VA_ARGS__ )
#else
#define LOG_ALL(...)                                    // No operation if LOG_ALL is not defined
#endif

#if defined(LOG_WARNING)                                // If LOG_WARNING is defined, enable warning and error logs.
#undef LOG_WARNING
#define LOG_WARNING(...) log_print(__FILE__, __LINE__, "WARNING: " __VA_ARGS__)
#define LOG_ERROR(...) log_print(__FILE__, __LINE__, "ERROR: " __VA_ARGS__ )
#else
#define LOG_WARNING(...)                                // No operation if LOG_WARNING is not defined
#endif

#if defined(LOG_DEBUG)                                  // If LOG_DEBUG is defined, enable debug, warning, and error logs.
#undef LOG_DEBUG
#define LOG_DEBUG(...) log_print(__FILE__, __LINE__, "DEBUG: " __VA_ARGS__ )
#define LOG_WARNING(...) log_print(__FILE__, __LINE__, "WARNING: " __VA_ARGS__)
#define LOG_ERROR(...) log_print(__FILE__, __LINE__, "ERROR: " __VA_ARGS__ )
#else
#define LOG_DEBUG(...)                                  // No operation if LOG_DEBUG is not defined
#endif

#if defined(LOG_ERROR)                                  // If LOG_ERROR is defined, enable only error logs.
#undef LOG_ERROR
#define LOG_ERROR(...) log_print(__FILE__, __LINE__, "ERROR: " __VA_ARGS__ )
#else
#define LOG_ERROR(...)                                  // No operation if LOG_ERROR is not defined
#endif

#if defined(LOG_INFO)                                  // If LOG_ERROR is defined, enable only error logs.
#undef LOG_INFO
#define LOG_INFO(...) log_print(__FILE__, __LINE__, "INFO: " __VA_ARGS__ )
#else
#define LOG_INFO(...)                                  // No operation if LOG_ERROR is not defined
#endif










