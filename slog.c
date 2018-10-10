//
// Created by 37351 on 2018/10/10.
//

#include "slog.h"

#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <ctype.h> /* isprint */
#include <time.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/time.h>



int elog(const char *logname, const char *srcfile, int srcline, const char *format, ...) {
    /* get system time */
    char timestamp[120] = "";
    struct timeval tms;
    char tstr[100] = "";
    timerclear(&tms);
    gettimeofday(&tms, NULL);
    strftime(tstr, 100, "%Y-%m-%d %H:%M:%S", localtime(&tms.tv_sec));
    sprintf(timestamp, "%s.%03d", tstr, tms.tv_usec / 1000); /* tv_usec是微秒，除以1000转换为毫秒 */
    /* end of get system time */

    char today[10 + 1] = ""; /* 格式：yyyy-mm-dd */
    memcpy(today, timestamp, 10);

    /* 组建logfilename */
    char logfilename[300] = "/tmp/";
    strcat(logfilename, logname);
    strcat(logfilename, ".");
    strcat(logfilename, today);
    strcat(logfilename, ".log");

    struct stat filestat;
    /* 检测日志文件是否存在 */
    if (0 != stat(logfilename, &filestat)) {
        // return -1;
    }

    /* 检测日志文件是否超过50,000,000B */
    if (filestat.st_size > 50000000) {
        // return -2;
    }

    FILE *fp = fopen(logfilename, "a");
    if (NULL == fp) {
        return -3;
    }

    fprintf(fp, "[%s][%s][%05d]", timestamp, srcfile, srcline);
    va_list ap;

    va_start(ap, format);
    vfprintf(fp, format, ap);
    va_end(ap);

    fprintf(fp, "\n");
    fflush(fp);
    fclose(fp);

    return 0;
}

/*
hexlog
参数：
logname:
      日志名

  srcfile:
      源文件名，传入__FILE__

  srcline:
      行号，传入__LINE__

  buffer:
      要打印的数据buffer

  len:
    要打印的数据长度

  返回值:
      0  --  成功
      -1 --  日志文件不存在，需要使用touch命令创建
      -2 --  日志文件大小超过限定范围（目前设定为最大不超过50MB)
      -3 --  打开日志文件失败
*/
int hexlog(const char *logname, const char *srcfile, int srcline, const void *buffer, int len) {
    const char *table_head = "| OFFSET | 0  1  2  3  4  5  6  7  8  9  A  B  C  D  E  F  | 0123456789ABCDEF |\n";
    const char *table_border = "-------------------------------------------------------------------------------\n";
    const unsigned char *buf = (const unsigned char *) buffer;

    int offset = 0; /* 每一行的偏移量（每行16字节） */
    int i;

    if (len < 1) {
        return 0;
    }

    /* get system time */
    char timestamp[120] = "";
    struct timeval tms;
    char tstr[100] = "";
    timerclear(&tms);
    gettimeofday(&tms, NULL);
    strftime(tstr, 100, "%Y-%m-%d %H:%M:%S", localtime(&tms.tv_sec));
    sprintf(timestamp, "%s.%03d", tstr, tms.tv_usec / 1000); /* tv_usec是微秒，除以1000转换为毫秒 */
    /* end of get system time */

    char today[10 + 1] = ""; /* 格式：yyyy-mm-dd */
    memcpy(today, timestamp, 10);

    /* 组建logfilename */
    char logfilename[300] = "/tmp/";
    strcat(logfilename, logname);
    strcat(logfilename, ".");
    strcat(logfilename, today);
    strcat(logfilename, ".log");

    struct stat filestat;
    /* 检测日志文件是否存在 */
    if (0 != stat(logfilename, &filestat)) {
        // return -1;
    }

    /* 检测日志文件是否超过50,000,000B */
    if (filestat.st_size > 50000000) {
        // return -2;
    }

    FILE *fp = fopen(logfilename, "a");
    if (NULL == fp) {
        return -3;
    }

    fprintf(fp, "[%s][%s][%05d]", timestamp, srcfile, srcline);
    fprintf(fp, "data-length: %d Byte(s)\n", len);
    fprintf(fp, table_border);
    fprintf(fp, table_head);
    fprintf(fp, table_border);

    while (offset < len) {
        fprintf(fp, "| %06d | ", offset);
        /* 打印hex部分 */
        for (i = 0; i < 16; ++i) {
            if (offset + i < len) {
                fprintf(fp, "%02X ", buf[offset + i]);
            } else {
                fprintf(fp, "   "); /* 超出真实数据长度用空白代替 */
            }
        }
        fprintf(fp, "| ");

        /* 打印ascii部分 */
        for (i = 0; i < 16; ++i) {
            if (offset + i < len) {
                unsigned char ch = buf[offset + i];
                if (isprint(ch)) {
                    fprintf(fp, "%c", ch);
                } else {
                    fprintf(fp, ".");
                }
            } else {
                fprintf(fp, " "); /* 超出真实数据长度用空白代替 */
            }
        }
        fprintf(fp, " |\n");
        offset += 16;
    }
    fprintf(fp, table_border);
    fflush(fp);
    fclose(fp);
    return 0;
}
