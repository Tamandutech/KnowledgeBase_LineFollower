# Lendo o ADC
Nesse exemplo, um potenciômetro será utilizado para enviar um sinal analôgico para o adc do esp e esse sinal será utilizado para controlar o brilho de um led, utilizando sinal pwm com o periférico ledc.
Esse readme focará nas funções e usos referentes ao adc.

## esp_err_t adc1_config_channel_atten( canal adc1_channel_t , adc_atten_t atten )

Defina a atenuação de um canal específico no ADC1 e configure seu mux de pino GPIO associado.

A atenuação padrão do ADC é 0 dB. Ao definir uma atenuação mais alta, é possível ler tensões mais altas.

**Retorno**

ESP_OK - sucesso

Erro de parâmetro - ESP_ERR_INVALID_ARG

**Parâmetros**

**channel**: Canal ADC1 para configurar

**atten**: Nível de atenuação

## esp_err_t adc1_config_width(adc_bits_width_twidth_bit)

Configura a resolução de captura ADC1. A configuração é para todos os canais do ADC1.

**Retorno**

ESP_OK - sucesso

Erro de parâmetro - ESP_ERR_INVALID_ARG

**Parâmetros**

**width_bit**: resolução de captura de bits para ADC1

## int adc1_get_raw( canal adc1_channel_t )

Faça uma leitura ADC1 de um único canal.

**Retorno**

-1: Erro de parâmetro

**Parâmetros**

**channel**: Canal ADC1 para ler

# Passos para a leitura do ADC

1. Configure a atenuação do ADC
2. Configura a resolução do ADC em bits (width)
3. Leia o valor de algum dos canias do ADC com adc_get_raw, no caso do adc 2 a resolução é configurada no momento da leitura.

Mais informações: [Documentação do ADC do esp32](https://docs.espressif.com/projects/esp-idf/en/v4.4/esp32/api-reference/peripherals/adc.html)
