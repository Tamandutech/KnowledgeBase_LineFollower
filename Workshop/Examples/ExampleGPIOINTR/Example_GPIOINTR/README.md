# Interrupção externa
Esse exemplo utiliza uma interrupção externa acionada por uma gpio para executar uma ISR (interrupt service routine) para contar o número de vezes que um
botão é pressionado, além disso, uma fila é utilizada para informar a task principal qual gpio acionou a interrupção. Abaixo estão as principais structs e
funções utilizadas no exemplo.

# Structs

**struct gpio_config_t**

Parâmetros de configuração do GPIO pad para a função gpio_config.

**Membros públicos**

**uint64_t pin_bit_mask**

GPIO pin: definido com máscara de bit, cada bit é mapeado para um GPIO

**gpio_mode_t mode**

GPIO mode: defina o modo de entrada/saída

**gpio_pullup_t pull_up_en**

GPIO pull-up

**gpio_pulldown_t pull_down_en**

GPIO pull-down

**gpio_int_type_t intr_type**

Tipo de interrupção da GPIO

# Funções

## esp_err_t gpio_config ( const gpio_config_t * pGPIOConfig )

Configuração comum do GPIO.

**Parâmetros**

**pGPIOConfig** – Ponteiro para a struct de configuração da GPIO

**Retorno**

ESP_OK - sucesso

Erro de parâmetro - ESP_ERR_INVALID_ARG

## esp_err_t gpio_install_isr_service ( int intr_alloc_flags )

Instale o serviço de manipulador ISR ETS_GPIO_INTR_SOURCE do driver GPIO, que permite manipuladores de interrupção GPIO por pino.

**Parâmetros**

**intr_alloc_flags** – sinalizadores usados para alocar a interrupção. Um ou vários (ORred) valores ESP_INTR_FLAG_*. Consulte esp_intr_alloc.h para obter mais informações.

**Retorno**

Sucesso - ESP_OK

ESP_ERR_NO_MEM - Sem memória para instalar este serviço

ESP_ERR_INVALID_STATE - Serviço ISR já instalado.

ESP_ERR_NOT_FOUND - Nenhuma interrupção livre encontrada com os sinalizadores especificados

Erro de GPIO - ESP_ERR_INVALID_ARG

## esp_err_t gpio_isr_handler_add ( gpio_num_t gpio_num , gpio_isr_t isr_handler , void * args )

Adicione o manipulador ISR para o pino GPIO correspondente.

Chame esta função depois de usar gpio_install_isr_service() para instalar o serviço do manipulador GPIO ISR do driver.

**Parâmetros**

gpio_num – número do GPIO

isr_handler – função de manipulador ISR para o número GPIO correspondente.

args – parâmetro para o manipulador ISR.

**Retorno**

Sucesso - ESP_OK

ESP_ERR_INVALID_STATE - Estado errado, o serviço ISR não foi inicializado.

Erro de parâmetro - ESP_ERR_INVALID_ARG

# Passos para usar a interrupção externa

1. Configurar a gpio com o modo de interrupção desejado.
2. Habilitar a interrupção.
3. Criar uma ISR (função) para ser executada quanda a interrupção ocorrer, o protótipo da função deve ser **static void IRAM_ATTR gpio_isr_handler(void \*arg)**.
4. Vincular a ISR à interrupção.

Mais informações: [Documentação da espressif sobre GPIOs e GPIO interrupt](https://docs.espressif.com/projects/esp-idf/en/latest/esp32/api-reference/peripherals/gpio.html)
