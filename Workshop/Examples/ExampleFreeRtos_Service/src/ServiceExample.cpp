#include "ServiceExample.hpp"

ServiceExample::ServiceExample(std::string name, uint32_t stackDepth, UBaseType_t priority, int initialValue):Thread(name, stackDepth, priority)
{
    counter = initialValue;
    esp_log_level_set(name.c_str(), ESP_LOG_INFO);
    ESP_LOGI(GetName().c_str(), "Contando com o valor inicial: %d", initialValue);
}

void ServiceExample::Run()
{
    TickType_t xLastTimeWake = xTaskGetTickCount();
    for(;;)
    {
        counter++;
        ESP_LOGI(GetName().c_str(), "Contando: %d", counter);
        xTaskDelayUntil(&xLastTimeWake, 1000 / portTICK_PERIOD_MS);
    }
    
}