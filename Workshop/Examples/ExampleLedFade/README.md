# Gerando sinal pwm com o LEDC

O ledc é um periférico do esp32 desenvolvido para gerar sinais pwm, permitindo a configuração de frequência e resolução do sinal, utilizando duas structs
para a sua configuração e inicialização, abaixo serão apresentadas essas structs e funções utilizadas para a configuração do pwm

# Structs

## struct ledc_timer_config_t

Parâmetros de configuração do temporizador LEDC Timer para a função ledc_timer_config.

**ledc_mode_t speed_mode**

Velocidade LEDC speed_mode, modo de alta velocidade ou modo de baixa velocidade

**ledc_timer_bit_t duty_resolution**

Resolução de duty do canal LEDC

**ledc_timer_t timer_num**

A fonte do timer do canal (0 - (LEDC_TIMER_MAX-1))

**uint32_t freq_hz**

Frequência do temporizador LEDC (Hz)

**ledc_clk_cfg_t clk_cfg**

Configure o relógio de origem do LEDC em ledc_clk_cfg_t. Observe que LEDC_USE_RC_FAST_CLK e LEDC_USE_XTAL_CLK são fontes de relógio não específicas do temporizador. Você não pode ter um temporizador LEDC usando RC_FAST_CLK como fonte de relógio e ter outro temporizador LEDC usando XTAL_CLK como fonte de relógio. Todos os chips, exceto esp32 e esp32s2, não possuem fontes de relógio específicas do temporizador, o que significa que a fonte de relógio para todos os temporizadores deve ser a mesma.

## struct ledc_channel_config_t 

Parâmetros de configuração do canal LEDC para a função ledc_channel_config.

**int gpio_num**

a saída LEDC gpio_num, se você quiser usar gpio16, gpio_num = 16

**ledc_mode_t speed_mode**

Velocidade LEDC speed_mode, modo de alta velocidade ou modo de baixa velocidade

**ledc_channel_t channel**

Canal LEDC (0 - (LEDC_CHANNEL_MAX-1))

**ledc_intr_type_t intr_type**

configurar interrupção, habilitar interrupção de fade ou desabilitar interrupção de fade

**ledc_timer_t timer_sel**

Selecione a fonte do timer do canal (0 - LEDC_TIMER_MAX-1)

**uint32_t duty**

Serviço do canal LEDC, a faixa de configuração do serviço é [0, (2^duty_resolution) - 1]

**int hpoint**

Valor hpoint do canal LEDC, o valor máximo é 0xfffff

**unsigned int output_invert**

Habilitar (1) ou desabilitar (0) inversão de saída gpio

# Funções

## esp_err_t ledc_channel_config(const ledc_channel_config_t *ledc_conf)

Configuração do canal do LEDC, configure o canal do LEDC com o canal/saída gpio_num/interrupção/temporizador da fonte/frequência(Hz)/resolução de tarefa do LEDC fornecida.

**Parâmetros**

**ledc_conf** – Ponteiro da estrutura de configuração do canal LEDC

**Retorno**

Sucesso - ESP_OK

Erro de parâmetro - ESP_ERR_INVALID_ARG

## esp_err_t ledc_timer_config(const ledc_timer_config_t *timer_conf)

Configuração do timer do LEDC, Configure o timer do LEDC com o temporizador/frequência(Hz)/resolução do duty.

**Parâmetros**

**timer_conf** – Ponteiro da estrutura de configuração do timer do LEDC

**Retorno**

Sucesso - ESP_OK

Erro de parâmetro - ESP_ERR_INVALID_ARG

Não foi possível encontrar uma base de número de pré-divisor adequada na frequência especificada e na resolução_do_trabalho atual - ESP_FAIL.

## esp_err_t ledc_set_duty_and_update(ledc_mode_t speed_mode, ledc_channel_t channel, uint32_t duty, uint32_t hpoint)

Uma API thread-safe para definir o dever para o canal LEDC e retornar quando o dever for atualizado.

**Parâmetros**

**speed_mode** – Selecione o grupo de canais LEDC com o modo de velocidade especificado. Observe que nem todos os alvos suportam o modo de alta velocidade.

**canal** – canal LEDC (0 - (LEDC_CHANNEL_MAX-1)), selecione ledc_channel_t

**duty** – Defina o dever do LEDC, a faixa de configuração do duty é [0, (2**duty_resolution) - 1]

**hpoint** – Defina o valor do LEDC hpoint (max: 0xfffff)

## esp_err_t ledc_fade_func_install ( int intr_alloc_flags )

Instala a função de fade do LEDC. Esta função ocupará a interrupção do módulo LEDC, no caso desse exemplo
essa função dever ser chamada para possibilitar o uso da funcão ledc_set_and_duty_update.

# Passos para o uso do LEDC

1. Configurar e registrar a struct do ledc timer, fornecendo principalmente a frequência e resolução
2. Configurar e registrar a struct do ledc channel, fornecendo principalmente a gpio do pwm e o ledc mode
3. Atualizar o duty cycle de acordo com o funcionamento desejado

Mais informações: [Documentação do ledc da espressif](https://docs.espressif.com/projects/esp-idf/en/latest/esp32/api-reference/peripherals/ledc.html)

