#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "driver/gpio.h"

#include "esp_log.h"

#define LED GPIO_NUM_2

static QueueHandle_t gpio_evt_queue = NULL;

static void IRAM_ATTR gpio_isr_handler(void* arg) // Função executada quando a interrupção ocorre
{
    uint32_t gpio_num = (uint32_t) arg;
    gpio_set_level(LED, !gpio_get_level(LED));
    xQueueSendFromISR(gpio_evt_queue, &gpio_num, NULL); // Informa ao programa principal os dados obtidos na interrupção
}

extern "C"
{
  void app_main(void);
}


void app_main() 
{
    esp_log_level_set("*", ESP_LOG_ERROR);
    esp_log_level_set("Main",ESP_LOG_INFO);
    ESP_LOGI("Main", "Configurando LOGs...");


    gpio_set_direction(LED,GPIO_MODE_INPUT_OUTPUT); // Configura o LED como entrada e saída

    gpio_evt_queue = xQueueCreate(10, sizeof(uint32_t)); // Cria uma fila para receber dados da função associada à interrupção

    // Configuração do GPIO para a interrupção
    gpio_config_t io_conf;
    io_conf.intr_type = GPIO_INTR_POSEDGE;
    io_conf.pin_bit_mask = (1ULL << GPIO_NUM_0);
    io_conf.mode = GPIO_MODE_INPUT;
    io_conf.pull_up_en = GPIO_PULLUP_ENABLE;
    io_conf.pull_down_en = GPIO_PULLDOWN_DISABLE;
    gpio_config(&io_conf);

    gpio_install_isr_service(0);

    gpio_isr_handler_add(GPIO_NUM_0, gpio_isr_handler, (void *)GPIO_NUM_0); // Associação da GPIO à uma função que será executada quando a interrupção acontecer

    int count = 0;
    for(;;)
    {
        uint32_t num = 0;
        xQueueReceive(gpio_evt_queue,&num,portMAX_DELAY); // Recebe um dado da função acionada pela interrupção
        if(num == GPIO_NUM_0)
        {
            count++;
            ESP_LOGI("Main","Contagem:%d | GPIO: %d",count, num);
        }

    }
}