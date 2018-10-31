/*
    
*/
#ifndef _TLS_WIFI_H_
#define _TLS_WIFI_H_

#include "esp_log.h"
#include "esp_wifi.h"
#include "esp_event_loop.h"

#define DEFAULT_PORT                     11111

#define TLS_SMP_SERVER_TASK_NAME         "tls_sever_example"
#define TLS_SMP_SERVER_TASK_WORDS        10240
#define TLS_SMP_SERVER_TASK_PRIORITY     8

#define TLS_SMP_WIFI_SSID                CONFIG_WIFI_SSID
#define TLS_SMP_WIFI_PASS                CONFIG_WIFI_PASSWORD

#endif
