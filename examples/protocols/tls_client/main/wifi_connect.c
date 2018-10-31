/*ESP specific */
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/event_groups.h"

#include "wifi_connect.h"

#include "lwip/sockets.h"
#include "lwip/netdb.h"
#include "lwip/apps/sntp.h"

#include "nvs_flash.h"

/* The event group allows multiple bits for each event,
   but we only care about one event - are we connected
   to the AP with an IP? */
const static int CONNECTED_BIT = BIT0;
static EventGroupHandle_t wifi_event_group;
/* prefix for logging */
/* proto-type */
extern void tls_smp_client_task();
static void tls_smp_client_init();
static void wifi_conn_init();
static int  sntp_time();

const static char *TAG = "tls_client";

static EventGroupHandle_t wifi_event_group;
extern void tls_smp_client_task();

/* initializa sntp component */
static void initialize_sntp()
{
    ESP_LOGI(TAG, "Initializing SNTP");
    sntp_setoperatingmode(SNTP_OPMODE_POLL);
    sntp_setservername(0, "pool.ntp.org");
    sntp_init();
}

/* start wifi, and trying to connect sntp site. */
/* after setting time, the task will be started.*/
static void obtain_time()
{
    ESP_ERROR_CHECK(nvs_flash_init());

    wifi_conn_init( );
    xEventGroupWaitBits(wifi_event_group, CONNECTED_BIT, 
                                            false, true, portMAX_DELAY);

    initialize_sntp();

    /* wait for time to be set */
    time_t now = 0;
    struct tm timeinfo = { 0 };
    int retry = 0;
    int retry_count = 10;

    while(timeinfo.tm_year < (2018 - 1900) && ++retry < retry_count) {
        ESP_LOGI(TAG, "Waiting for system time to be set ...(%d/%d)", retry, 
                                                            retry_count);
        vTaskDelay(2000 / portTICK_PERIOD_MS);
        time(&now);
        localtime_r(&now, &timeinfo);
    }

    /* ESP_ERROR_CHECK( esp_wifi_stop()); */

}

/* check if the time is in reasonable range. */
/* if not, it connects sntp site.            */
static int sntp_time(void)
{
    char strftime_buf[64];
    time_t now;
    struct tm timeinfo;
    int sntp = 0;
    time(&now);
    localtime_r(&now, &timeinfo);
    
    if(timeinfo.tm_year < (2018 - 1900)) {
        ESP_LOGI(TAG, "Time is not set yet. Connecting to WiFi and getting time"
                        " NTP.");
        obtain_time();
        /* upsate 'now' variable with current time */
        time(&now);
        localtime_r(&now, &timeinfo);

        sntp = 1;
    }

    strftime(strftime_buf, sizeof(strftime_buf), "%c", &timeinfo);

    ESP_LOGI(TAG, "The current date/time in XXX is: %s", strftime_buf);

    /* start server task */
    ESP_LOGI(TAG, "Now start the task");
    tls_smp_client_init();

    return sntp;
}
static void tls_smp_client_init(void)
{
    int ret;
    xTaskHandle _handle;

    ret = xTaskCreate(tls_smp_client_task,
                      TLS_SMP_CLIENT_TASK_NAME,
                      TLS_SMP_CLIENT_TASK_WORDS,
                      NULL,
                      TLS_SMP_CLIENT_TASK_PRIORITY,
                      &_handle);

    if (ret != pdPASS)
    {
        ESP_LOGI(TAG, "create thread %s failed", TLS_SMP_CLIENT_TASK_NAME);
    }
}

static esp_err_t wifi_event_handler(void *ctx, system_event_t *event)
{
    switch (event->event_id)
    {
    case SYSTEM_EVENT_STA_START:
        esp_wifi_connect();
        break;
    case SYSTEM_EVENT_STA_GOT_IP:
        
        ESP_LOGI(TAG, "got ip:%s",
                 ip4addr_ntoa(&event->event_info.got_ip.ip_info.ip));
        xEventGroupSetBits(wifi_event_group, CONNECTED_BIT);
        break;
    case SYSTEM_EVENT_STA_DISCONNECTED:
        /* This is a workaround as ESP32 WiFi libs don't currently
           auto-reassociate. */
        esp_wifi_connect();
        xEventGroupClearBits(wifi_event_group, CONNECTED_BIT);
        break;
    default:
        break;
    }
    return ESP_OK;
}
/* wifi connection */
static void wifi_conn_init(void)
{
    tcpip_adapter_init();

    wifi_event_group = xEventGroupCreate();

    ESP_ERROR_CHECK(esp_event_loop_init(wifi_event_handler, NULL));
    
    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();

    ESP_ERROR_CHECK(esp_wifi_init(&cfg));
    
    ESP_ERROR_CHECK(esp_wifi_set_storage(WIFI_STORAGE_RAM));

    wifi_config_t wifi_config = {
        .sta = {
            .ssid = TLS_SMP_WIFI_SSID,
            .password = TLS_SMP_WIFI_PASS,
        },
    };
    
    ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_STA) );
    ESP_ERROR_CHECK(esp_wifi_set_config(ESP_IF_WIFI_STA, &wifi_config) );
    ESP_ERROR_CHECK(esp_wifi_start() );

    ESP_LOGI(TAG, "wifi_init_sta finished.");
    ESP_LOGI(TAG, "connect to ap SSID:%s password:%s",
                                        TLS_SMP_WIFI_SSID, TLS_SMP_WIFI_PASS);

}
/* entry point */
void app_main(void)
{
    ESP_LOGI(TAG, "Start app_main...");
    ESP_LOGI(TAG, "Check time...");
    int wifi_on = sntp_time();

    //Initialize NVS
    if(!wifi_on) {
        
        esp_err_t ret = nvs_flash_init();
        if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND) {
            ESP_ERROR_CHECK(nvs_flash_erase());
            ret = nvs_flash_init();
        }
        ESP_ERROR_CHECK(ret);
        wifi_conn_init();
    }
}
