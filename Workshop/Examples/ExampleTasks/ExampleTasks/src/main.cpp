// Espressif (ESP-IDF)
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/timers.h"
#include "freertos/semphr.h"
#include "esp_log.h"

int SharedData = 0;
SemaphoreHandle_t SharedSemaphore; // semáforo para os dados compartilhados das tasks

void vTaskFunction(void *pvParameters)
{
  int *TaskData = (int *)pvParameters;
  int counter = *TaskData;

  char *tag = pcTaskGetName(NULL);
  esp_log_level_set(tag, ESP_LOG_INFO);

  TaskHandle_t xTaskHandle = xTaskGetCurrentTaskHandle();

  // Variável necessária para a funcionalidade do vTaskDelayUtil, guarda a contagem de ticks da CPU
  TickType_t xLastWakeTime = xTaskGetTickCount();
  for(;;)
  {
    vTaskDelayUntil(&xLastWakeTime, 1000 / portTICK_PERIOD_MS);
    ESP_LOGI(tag, "Contagem: %d", counter);
    counter++;

    // Trava o semáforo do dado compartilhado entre as tasks e libera após realizar as operações com o dado
    if(xSemaphoreTake(SharedSemaphore, (TickType_t) 10) == pdTRUE)
    {
      ESP_LOGI(tag, "O Tempo percorrido é: %d s",*TaskData);
      xSemaphoreGive(SharedSemaphore);
    }
    else
    {
      ESP_LOGE(tag, "O semáforo não estava disponível");
    }
  }

}

void vTaskTimerFunction(void *pvParameters)
{

  char *tag = pcTaskGetName(NULL);
  esp_log_level_set(tag, ESP_LOG_INFO);

  int *TaskData = (int *)pvParameters; // Recebe os dados enviados para a task
  for(;;)
  {
    vTaskDelay(2000 / portTICK_PERIOD_MS); // delay de 2000ms
    // Trava o semáforo do dado compartilhado entre as tasks e libera após realizar as operações com o dado
    if(xSemaphoreTake(SharedSemaphore, (TickType_t) 10) == pdTRUE)
    {
        *TaskData = *TaskData + 2;
        xSemaphoreGive(SharedSemaphore);
    }
    else
    {
        ESP_LOGE(tag, "O semáforo não estava disponível");
    }
    
  }


}

extern "C"
{
  void app_main(void);
}
void app_main() 
{
  SharedSemaphore = xSemaphoreCreateMutex(); // inicializa o semáforo
  
  TaskHandle_t xTaskHandle = NULL;

  //Cria Tasks
  xTaskCreate(vTaskFunction,"Task1", 3000, (void *)&SharedData, 5, &xTaskHandle);
  xTaskCreate(vTaskTimerFunction,"Task2", 3000, (void *)&SharedData, 10, NULL);
}
