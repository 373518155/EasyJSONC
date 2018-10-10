//
// Created by 37351 on 2018/10/10.
//

#include <stdarg.h>
#include "cJSON.h"
#include "EasyJSON.h"
#include "slog.h"

extern const char *gsLog;

cJSON *createEasyJSONObject(const char *begin, ...) {
    slog(gsLog, "createEasyJSONObject begin...");
    cJSON *object =  cJSON_CreateObject();

    va_list ap;
    va_start(ap, begin);
    char *name;
    char *type;

    double numberVal;
    char *stringVal;
    int boolVal;
    cJSON *objectVal;
    cJSON *arrayVal;
    int nullVal;

    name = va_arg(ap, char *);
    slog(gsLog, "name[%s]", name);
    while (strcmp(name, MAGIC_STRING)) { // 如果遇到MAGIC_STRING，表示结束
        type = va_arg(ap, char *);
        slog(gsLog, "type[%s]", type);
        if (strcmp(type, EASY_JSON_TYPE_STRING) == 0) {  // 字符串类型
            stringVal = va_arg(ap, char *);  // 读取值
            slog(gsLog, "val[%s]", stringVal);
            cJSON_AddItemToObject(object, name, cJSON_CreateString(stringVal));
        } else if (strcmp(type, EASY_JSON_TYPE_NUMBER) == 0) {  // Number类型
            numberVal = va_arg(ap, double);  // 读取值
            slog(gsLog, "val[%f]", numberVal);
            cJSON_AddItemToObject(object, name, cJSON_CreateNumber(numberVal));
        } else if (strcmp(type, EASY_JSON_TYPE_OBJECT) == 0) {
            objectVal = va_arg(ap, cJSON *);
            cJSON_AddItemToObject(object, name, objectVal);
        } else if (strcmp(type, EASY_JSON_TYPE_ARRAY) == 0) {
            arrayVal = va_arg(ap, cJSON *);
            cJSON_AddItemToObject(object, name, arrayVal);
        } else if (strcmp(type, EASY_JSON_TYPE_BOOL) == 0) {  // 布尔类型
            boolVal = va_arg(ap, int);  // 读取值
            slog(gsLog, "val[%d]", boolVal);
            if (boolVal) {
                cJSON_AddItemToObject(object, name, cJSON_CreateTrue());
            } else {
                cJSON_AddItemToObject(object, name, cJSON_CreateFalse());
            }
        } else if (strcmp(type, EASY_JSON_TYPE_NULL) == 0) {
            nullVal = va_arg(ap, int);  // 读取值
            cJSON_AddItemToObject(object, name, cJSON_CreateNull());
        }

        name = va_arg(ap, char *);  // 读取下一个name
        slog(gsLog, "name[%s]", name);
    }
    va_end(ap);
    slog(gsLog, "createEasyJSONObject end...");

    return object;
}


cJSON *createEasyJSONArray(const char *begin, ...) {
    slog(gsLog, "createEasyJSONArray begin...");
    cJSON *array =  cJSON_CreateArray();

    va_list ap;
    va_start(ap, begin);
    char *type;

    char *stringVal;
    double numberVal;
    cJSON *objectVal;
    cJSON *arrayVal;
    int boolVal;
    int nullVal;

    type = va_arg(ap, char *);
    slog(gsLog, "type[%s]", type);
    while (strcmp(type, MAGIC_STRING)) { // 如果遇到MAGIC_STRING，表示结束
        if (strcmp(type, EASY_JSON_TYPE_STRING) == 0) {  // 字符串类型
            stringVal = va_arg(ap, char *);  // 读取值
            slog(gsLog, "val[%s]", stringVal);
            cJSON_AddItemToArray(array, cJSON_CreateString(stringVal));
        } else if (strcmp(type, EASY_JSON_TYPE_NUMBER) == 0) {  // Number类型
            numberVal = va_arg(ap, double);  // 读取值
            slog(gsLog, "val[%f]", numberVal);
            cJSON_AddItemToArray(array, cJSON_CreateNumber(numberVal));
        } else if (strcmp(type, EASY_JSON_TYPE_OBJECT) == 0) {
            objectVal = va_arg(ap, cJSON *);
            cJSON_AddItemToArray(array, objectVal);
        } else if (strcmp(type, EASY_JSON_TYPE_ARRAY) == 0) {
            arrayVal = va_arg(ap, cJSON *);
            cJSON_AddItemToArray(array, arrayVal);
        } else if (strcmp(type, EASY_JSON_TYPE_BOOL) == 0) {  // 布尔类型
            boolVal = va_arg(ap, int);  // 读取值
            slog(gsLog, "val[%d]", boolVal);
            if (boolVal) {
                cJSON_AddItemToArray(array, cJSON_CreateTrue());
            } else {
                cJSON_AddItemToArray(array, cJSON_CreateFalse());
            }
        } else if (strcmp(type, EASY_JSON_TYPE_NULL) == 0) {
            nullVal = va_arg(ap, int);  // 读取值
            cJSON_AddItemToArray(array, cJSON_CreateNull());
        }

        type = va_arg(ap, char *);  // 读取下一个type
        slog(gsLog, "type[%s]", type);
    }
    va_end(ap);
    slog(gsLog, "createEasyJSONArray end...");

    return array;
}


