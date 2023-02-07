# Leitura/escrita de GPIO

Exemplo de como ler e escrever nas GPIOs do esp32 com o framework esp-idf, abaixo estão as funções utilizadas mais importantes para esse exemplo.

## esp_err_t gpio_set_direction ( gpio_num_t gpio_num , gpio_mode_t mode)

define a direção a direção do GPIO.

Configure a direção do GPIO, como output_only, input_only, output_and_input.

**Parâmetros**

**gpio_num** – Configure o número dos pinos GPIO, deve ser o número GPIO. Se você deseja definir a direção de, por exemplo, GPIO16, gpio_num deve ser **GPIO_NUM_16** (16);

**mode** – direção GPIO

**Retorno**

Sucesso - ESP_OK

Erro de GPIO - ESP_ERR_INVALID_ARG

## esp_err_t gpio_set_level ( gpio_num_t gpio_num , uint32_t level)

define o nível de saída da GPIO.

**Parâmetros**

gpio_num – número do GPIO. Se você deseja definir o nível de saída de, por exemplo, GPIO16, gpio_num deve ser **GPIO_NUM_16** (16);

level – Nível de saída ( 0: baixo ou 1: alto)

**Retorno**

Sucesso - ESP_OK

Erro de número - ESP_ERR_INVALID_ARG GPIO

## int gpio_get_level(gpio_num_t gpio_num)

obter nível de entrada da GPIO.

**Parâmetros**

gpio_num – número do GPIO. Se você deseja obter o nível lógico, por exemplo, do pino GPIO16, gpio_num deve ser **GPIO_NUM_16** (16);

**Retorno**

0, o nível de entrada da GPIO é 0

1, o nível de entrada da GPIO é 1

# Passos para o uso da GPIO

1. Configurar a direção da GPIO (input, output, etx)
2. Configurar o pull-mode (pull up,pull down, etc) - opcional
3. Ler ou escrever um nível lógico na GPIO 
