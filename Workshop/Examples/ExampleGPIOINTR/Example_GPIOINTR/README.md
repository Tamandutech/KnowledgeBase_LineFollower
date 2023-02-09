# Interrupção externa
Esse exemplo utiliza uma interrupção externa acionada por uma gpio para executar uma ISR (interrupt service routine) para contar o número de vezes que um
botão é pressionado, além disso, uma fila é utilizada para informar a task principal qual gpio acionou a interrupção. Abaixo estão as principais structs e
funções utilizadas no exemplo.

# Structs

struct gpio_config_t

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

## Funções

