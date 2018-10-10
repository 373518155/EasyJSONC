//
// Created by 37351 on 2018/10/10.
//

#include "cJSON.h"
#include "EasyJSON.h"
#include "slog.h"

const char *gsLog = "EasyJSON"; /* gsLog不需要带扩展名，一般定义为进程的名称或Sub的名称 */

int main() {
    slog(gsLog, "Hello world");

    cJSON *json = EASY_JSON_ARRAY(JSON_NUMBER(1), JSON_BOOL(1), JSON_STRING("Hello"));
    slog(gsLog, "jsonString[%s]", cJSON_Print(json));

    json = EASY_JSON_OBJECT("a", JSON_NUMBER(1), "b", JSON_OBJECT());
    slog(gsLog, "jsonString[%s]", cJSON_Print(json));

    return 0;
}

