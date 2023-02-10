#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "ServiceExample.cpp"

#include "esp_log.h"

ServiceExample *service1;

extern "C"
{
  void app_main(void);
}

void app_main() 
{
    esp_log_level_set("*", ESP_LOG_ERROR);
    esp_log_level_set("main", ESP_LOG_INFO);
    service1 = new ServiceExample("TaskCounter", 4096, 5, 20);
    service1->Start();
    for(;;)
    {
        ESP_LOGI("main", "ServiceExample: %d", eTaskGetState(service1->GetHandle()));
        vTaskDelay(2000 / portTICK_PERIOD_MS);
    }
}