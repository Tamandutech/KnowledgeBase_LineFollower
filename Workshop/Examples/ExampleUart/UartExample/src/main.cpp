// Espressif (ESP-IDF)
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/uart.h"
#include "string.h"

#include "esp_log.h"

#define TX_BUFFER_SIZE 1024
#define RX_BUFFER_SIZE 1024
#define UART_NUM UART_NUM_0
extern "C"
{
  void app_main(void);
}

void app_main() 
{
    // Configuração da comunicação UART
    uart_config_t uart_config = {
        .baud_rate = 115200, // velocidade da comunicação
        // Configutação do envio do dado
        .data_bits = UART_DATA_8_BITS,
        .parity    = UART_PARITY_DISABLE,
        .stop_bits = UART_STOP_BITS_1,
        //Desabilita o controle do fluxo
        .flow_ctrl = UART_HW_FLOWCTRL_DISABLE
    };

    uart_param_config(UART_NUM_0, &uart_config); // Aplica a configuração da Uart
    uart_set_pin(UART_NUM, UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE); // Configura os pinos da UART
    uart_driver_install(UART_NUM, RX_BUFFER_SIZE, TX_BUFFER_SIZE, 0, NULL, 0); // Configura os buffers da comunicação
    int loop = 0;
    for(;;)
    {
        // Enviando dados para a UART
        char dataSend[100] = "Enviado dados para a UART.\n";
        if(loop > 5) 
        {
            uart_write_bytes(UART_NUM,dataSend,strlen(dataSend)); // Envia a string dataSend para o Tx buffer
            loop = 0;
        }
        loop++;

        int dataReceivedLen = 0;
        uart_get_buffered_data_len(UART_NUM, (size_t *)&dataReceivedLen); // coloca na variável dataReceivedLen a qunatidade de bytes prontos para a leitura
        // Verifica se há dados disponíveis para a leitura e os lê do RX buffer
        if(dataReceivedLen > 0)
        {
            char dataReceived[150];
            dataReceivedLen = uart_read_bytes(UART_NUM,dataReceived, dataReceivedLen, 100 / portTICK_PERIOD_MS); // Lê os dados do buffer e armazena na variável dataReceived retornando a quantidade de bytes lidos
            // Escreve ma Uart os dados que foram lidos
            char str[50] = "User Input: ";
            uart_write_bytes(UART_NUM, str, strlen(str));
            uart_write_bytes(UART_NUM,dataReceived,dataReceivedLen);

        }
        vTaskDelay(500 / portTICK_PERIOD_MS);

    }

}