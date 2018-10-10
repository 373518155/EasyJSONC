//
// Created by 37351 on 2018/10/10.
//

#ifndef EASYJSONC_EASYJSON_H
#define EASYJSONC_EASYJSON_H


#ifndef true
#define true 1
#endif

#ifndef false
#define false 0
#endif


/*
 * 三要素
 * name
 * type
 * value
 */

// 魔串
// https://en.wikipedia.org/wiki/Magic_string
// 这个特殊的字符串 ZpsWTsOiRHI0TBW7jUVXJ3PslTEBh9as 表示参数结束，仿照 HTTP协议 multipart/form-data用于分隔内容的字符串
#define MAGIC_STRING "ZpsWTsOiRHI0TBW7jUVXJ3PslTEBh9as"


// 用于给
#define EASY_JSON_ARGS_BEGIN "BEGIN"

// EasyJSON类型定义
#define EASY_JSON_TYPE_STRING "string"
#define EASY_JSON_TYPE_NUMBER "number"
#define EASY_JSON_TYPE_OBJECT "object"
#define EASY_JSON_TYPE_ARRAY "array"
#define EASY_JSON_TYPE_BOOL "bool"
#define EASY_JSON_TYPE_NULL "null"



// 创建EasyJSON的宏
#define EASY_JSON_OBJECT(...) createEasyJSONObject(EASY_JSON_ARGS_BEGIN, ##__VA_ARGS__, MAGIC_STRING)
#define EASY_JSON_ARRAY(...) createEasyJSONArray(EASY_JSON_ARGS_BEGIN, ##__VA_ARGS__, MAGIC_STRING)

// 类型包装宏
#define JSON_STRING(val) EASY_JSON_TYPE_STRING, val
#define JSON_NUMBER(val) EASY_JSON_TYPE_NUMBER, (double)val
#define JSON_OBJECT(...) EASY_JSON_TYPE_OBJECT, createEasyJSONObject(EASY_JSON_ARGS_BEGIN, ##__VA_ARGS__, MAGIC_STRING)
#define JSON_ARRAY(...) EASY_JSON_TYPE_ARRAY, createEasyJSONArray(EASY_JSON_ARGS_BEGIN, ##__VA_ARGS__, MAGIC_STRING)
#define JSON_BOOL(val) EASY_JSON_TYPE_BOOL, val
#define JSON_NULL EASY_JSON_TYPE_NULL, 0  // 写0是为了占位

cJSON *createEasyJSONObject(const char *begin, ...);
cJSON *createEasyJSONArray(const char *begin, ...);

#endif //EASYJSONC_EASYJSON_H
