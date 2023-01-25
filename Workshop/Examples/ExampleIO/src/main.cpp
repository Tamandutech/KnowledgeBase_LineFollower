// Espressif (ESP-IDF)
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/timers.h"
#include "freertos/semphr.h"
#include "driver/gpio.h"

#include "esp_log.h"

#define BUTTON GPIO_NUM_0
#define LED GPIO_NUM_2

extern "C"
{
  void app_main(void);
}

void app_main() 
{

  // Configurando IOs  
  gpio_set_direction(LED, GPIO_MODE_OUTPUT);
  gpio_set_direction(BUTTON,GPIO_MODE_INPUT);

  for(;;)
  {
    bool stateButton = gpio_get_level(BUTTON); // Lendo estado do botão
    
    // Acionando o LED à partir do botão
    if(stateButton == 0)
    {
      gpio_set_level(LED,1);
    }
    else
    {
      gpio_set_level(LED,0);
    }

    vTaskDelay(500 / portTICK_PERIOD_MS); // delay para a main task não ficar presa no laço for e acionar o watchdog
  }
}