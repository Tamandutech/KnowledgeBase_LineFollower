// Espressif (ESP-IDF)
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/timers.h"
#include "freertos/semphr.h"
#include "driver/timer.h"
#include "esp_log.h"

int SharedData = 0;
SemaphoreHandle_t SharedSemaphore; // semáforo para os dados compartilhados das tasks
SemaphoreHandle_t SemaphoreTimer; // semáforo para sincronização do timer com a task timer

// ISR(Interrupt Service Routine) - Função executada quando o timer atinge uma determinada contagem
static bool IRAM_ATTR timer_group_isr_callback(void * args) {
    BaseType_t high_task_awoken = pdFALSE;
    xSemaphoreGiveFromISR(SemaphoreTimer, &high_task_awoken);
    return (high_task_awoken == pdTRUE);
}


void vTaskFunction(void *pvParameters)
{
  int *TaskData = (int *)pvParameters;

  char *tag = pcTaskGetName(NULL);
  esp_log_level_set(tag, ESP_LOG_INFO);

  TaskHandle_t xTaskHandle = xTaskGetCurrentTaskHandle();

  // Variavel necerraria para funcionalidade do vTaskDelayUtil, guarda a contagem de ticks da CPU
  TickType_t xLastWakeTime = xTaskGetTickCount();
  for(;;)
  {
    vTaskDelayUntil(&xLastWakeTime, 1000 / portTICK_PERIOD_MS);
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

  SemaphoreTimer = xSemaphoreCreateBinary(); // Inicializa o semáforo

  int *TaskData = (int *)pvParameters; // Recebe os dados enviados para a task

  // Configura o timer
  timer_config_t config;
  config.alarm_en = TIMER_ALARM_EN;
  config.counter_en = TIMER_PAUSE; 
  config.counter_dir = TIMER_COUNT_UP;
  config.auto_reload = TIMER_AUTORELOAD_EN; // define se o contador do timer deve reiniciar automaticamente
  config.divider = 16; // Define o valor pelo qual o clock deve ser dividido

  timer_init(TIMER_GROUP_0, TIMER_0, &config); // inicializa timer
  timer_set_counter_value(TIMER_GROUP_0, TIMER_0, 0); // zera o contador do timer
  timer_set_alarm_value(TIMER_GROUP_0, TIMER_0, 2*(TIMER_BASE_CLK / 16)); // define até quando o timer deve contar
  timer_enable_intr(TIMER_GROUP_0, TIMER_0); // ativa interrupção
  timer_isr_callback_add(TIMER_GROUP_0, TIMER_0, timer_group_isr_callback, NULL, 0); // define a função executada quando ocorre interrupção
  timer_start(TIMER_GROUP_0, TIMER_0);

  for(;;)
  {
    if(xSemaphoreTake(SemaphoreTimer, portMAX_DELAY) == pdTRUE) // Trava o semáforo e espera a interrupção ocorrer
    {
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


}

extern "C"
{
  void app_main(void);
}
void app_main() 
{
  SharedSemaphore = xSemaphoreCreateMutex(); // inicializa semáforo
  
  TaskHandle_t xTaskHandle = NULL;

  //Cria Tasks
  xTaskCreate(vTaskFunction,"Test_Task", 3000, (void *)&SharedData, 5, &xTaskHandle);
  xTaskCreate(vTaskTimerFunction,"Timer_Task", 3000, (void *)&SharedData, 10, NULL);
}