// Espressif (ESP-IDF)
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/timers.h"
#include "freertos/semphr.h"
#include "driver/gpio.h"
#include "driver/ledc.h"

#include "esp_log.h"

#define BUTTON GPIO_NUM_0
#define LED GPIO_NUM_2

#define LEDC_TIMER              LEDC_TIMER_0 // Timer do LEDC utilizado
#define LEDC_MODE               LEDC_HIGH_SPEED_MODE // Modo de velocidade do LEDC
#define LEDC_CHANNEL            LEDC_CHANNEL_0 // Canal do LEDC utilizado
#define LEDC_DUTY_RES           LEDC_TIMER_13_BIT // Resolução do PWM
#define LEDC_FREQUENCY          5000 // Frequência em Hertz do sinal PWM


extern "C"
{
  void app_main(void);
}

void app_main() 
{
    esp_log_level_set("*", ESP_LOG_ERROR);
    esp_log_level_set("Main",ESP_LOG_INFO);
    ESP_LOGI("Main", "Configurando LOGs...");

    // Prepara e aplica a configuração do Timer do LEDC
    ledc_timer_config_t ledc_timer;
    ledc_timer.speed_mode      = LEDC_MODE;
    ledc_timer.duty_resolution = LEDC_DUTY_RES;    
    ledc_timer.timer_num       = LEDC_TIMER;
    ledc_timer.freq_hz         = LEDC_FREQUENCY; // Frequência de 5Khz
    ledc_timer.clk_cfg         = LEDC_AUTO_CLK; // Configuração da fonte de clock
    ledc_timer_config(&ledc_timer);

    // Prepara e aplica a configuração do canal do LEDC
    ledc_channel_config_t ledc_channel;
    ledc_channel.gpio_num       = LED;
    ledc_channel.speed_mode     = LEDC_MODE;
    ledc_channel.channel        = LEDC_CHANNEL;
    ledc_channel.intr_type      = LEDC_INTR_DISABLE;
    ledc_channel.timer_sel      = LEDC_TIMER;
    ledc_channel.duty           = 0; 
    ledc_channel.hpoint         = 0; // Ponto de início do duty cycle
    ledc_channel_config(&ledc_channel);

    ledc_fade_func_install(0);
    gpio_set_direction(BUTTON,GPIO_MODE_INPUT);

    int bright = 0;
    bool lastState = true;
    bool conutUp = true;
    for(;;)
    {
        bool stateButton = gpio_get_level(BUTTON);
        if(stateButton == 1)
        {
            lastState = true;
        }
        // Verifica se o botão foi pressionado
        if(stateButton == 0 && lastState == 1)
        {
            lastState = false;
            /* Cada vez que o botão é pressionado o brilho aumenta
                e caso ele esteja no máximo, diminui até zero e depois
                volta a aumentar.
            */
            if(conutUp == true)
            {
                bright = bright + 500;
                if(bright > 8191)
                {
                    conutUp = false;
                    bright = 8191;
                }
            }
            else
            {
                bright = bright - 500;
                if(bright < 0)
                {
                    conutUp = true;
                    bright = 0;
                }

            }

            ledc_set_duty_and_update(LEDC_MODE,LEDC_CHANNEL,bright,0); // Atribui um novo duty para o PWM
            ESP_LOGI("Main","Duty Cycle atual: %d", bright);
        }
        vTaskDelay(100 / portTICK_PERIOD_MS);
    }
}