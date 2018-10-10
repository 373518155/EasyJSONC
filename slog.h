//
// Created by 37351 on 2018/10/10.
//

#ifndef EASYJSONC_SLOG_H
#define EASYJSONC_SLOG_H


int elog(const char *logname, const char *srcfile, int srcline, const char *format, ...);
int hexlog(const char *logname, const char *srcfile, int srcline, const void *buffer, int len);

#define slog(gsLog, ...) elog(gsLog, __FILE__, __LINE__, __VA_ARGS__)  /* simple log */
#define hlog(gsLog, buffer, len) hexlog(gsLog, __FILE__, __LINE__, buffer, len)  /* hex log */

#endif //EASYJSONC_SLOG_H
