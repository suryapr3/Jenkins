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

/********************************************************************************************
 * @file    logger.c
*********************************************************************************************/

#include <stdio.h>
#include <stdarg.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>
#include "logger.h"

static int SESSION_TRACKER;                            // Keeps track of session

char* print_time()
{
    int size = 0;
    time_t t;
    char *buf;
    t = time(NULL);                                    // get current calendar time

    char *timestr = asctime(localtime(&t));
    timestr[strlen(timestr) - 1] = 0;                  // Getting rid of \n
    size = strlen(timestr)+ 1 + 2;                     // Additional +2 for square braces
    buf = (char*)malloc(size);
    memset(buf, 0x0, size);
    snprintf(buf,size,"[%s]", timestr);

    return buf;
}

void log_print(char* filename, int line, char* fmt, ...)
{
    FILE *fp;
    va_list       list;
    char          *p, *r;
    int           e;
    char *clog = getenv("C_LOG");

    if(SESSION_TRACKER > 0)
      fp = fopen(clog, "a+");
    else
      fp = fopen(clog, "a+");
#ifndef DISABLE_TIMESTAMP
    fprintf(fp, "%s ", print_time());
    fprintf(fp, "[%s][line: %d] ", filename, line);
#endif
    va_start(list, fmt);

    for(p = fmt ; *p ; ++p)
    {
        if(*p != '%')                                  // If simple string
        {
            fputc(*p, fp);
        }
        else
        {
            switch(*++p)
            {

            case 's':                                  // string
            {
                r = va_arg(list, char *);

                fprintf(fp, "%s", r);
                continue;
            }


            case 'd':                                  // integer
            {
                e = va_arg(list, int);

                fprintf(fp, "%d", e);
                continue;
            }

            case 'x':                                  // hex
            {
                e = va_arg(list, int);

                fprintf(fp, "%x", e);
                continue;
            }

            default:
                fputc(*p, fp);
            }
        }
    }
    va_end(list);
    fputc('\n', fp);
    SESSION_TRACKER++;
    fclose(fp);
}
