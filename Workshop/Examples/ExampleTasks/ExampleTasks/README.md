# FreeRTOS
Exemplo de como criar tasks e trocar informações entre elas, com o framework esp-idf, abaixo estão as funções utilizadas mais importantes para esse exemplo.

## static inline BaseType_t xTaskCreate(TaskFunction_t pxTaskCode, const char *const pcName, const configSTACK_DEPTH_TYPE usStackDepth, void *const pvParameters, UBaseType_t uxPriority, TaskHandle_t *const pxCreatedTask)

Cria uma nova task e adiciona ela à lista de tasks que estão prontas para rodar.

Parâmetros

**pxTaskCode** – Ponteiro para a função de entrada da tarefa. As tarefas devem ser implementadas para nunca retornar (ou seja, loop contínuo) ou devem ser encerradas usando a função vTaskDelete.

**pcName** – um nome descritivo para a tarefa. Isso é usado principalmente para facilitar a depuração. Comprimento máximo definido por configMAX_TASK_NAME_LEN - o padrão é 16.

**usStackDepth** – O tamanho da pilha de tarefas especificado como o número de bytes. Observe que isso difere do FreeRTOS padrão.

**pvParameters** – Ponteiro que será utilizado como parâmetro para a tarefa que está sendo criada.

uxPriority – a prioridade na qual a tarefa deve ser executada. Os sistemas que incluem suporte a MPU podem, opcionalmente, criar tarefas em um modo privilegiado definindo o bit portPRIVILEGE_BIT do parâmetro priority. Por exemplo, para criar uma tarefa privilegiada com prioridade 2, o parâmetro uxPriority deve ser definido como ( 2 | portPRIVILEGE_BIT ).

**pxCreatedTask** – usado para passar de volta um identificador pelo qual a tarefa criada pode ser referenciada.

Retorno

pdPASS se a tarefa foi criada com sucesso e adicionada a uma lista pronta, caso contrário, um código de erro definido no arquivo projdefs.h

## xSemaphoreCreateMutex()

Cria uma nova instância de semáforo de tipo mutex e retorna um identificador pelo qual o novo mutex pode ser referenciado.

Retorno

Se o mutex foi criado com sucesso, um identificador para o semáforo criado é retornado. Se não houver heap suficiente para alocar as estruturas de dados mutex, NULL será retornado.

## xSemaphoreTake ( xSemaphore , xBlockTime )

Função para obter um semáforo. O semáforo deve ter sido previamente criado com uma chamada para xSemaphoreCreateBinary(), xSemaphoreCreateMutex() ou xSemaphoreCreateCounting().

Parâmetros

**xSemaphore** – Um identificador para o semáforo que está sendo obtido - obtido quando o semáforo foi criado.

**xBlockTime** – O tempo em ticks para esperar o semáforo ficar disponível. A macro portTICK_PERIOD_MS pode ser usada para converter isso em tempo real. Um tempo de bloqueio de zero pode ser usado para pesquisar o semáforo. Um tempo de bloqueio de portMAX_DELAY pode ser usado para bloquear indefinidamente (desde que INCLUDE_vTaskSuspend esteja definido como 1 em FreeRTOSConfig.h).

Retorno

pdTRUE se o semáforo foi obtido. pdFALSE se xBlockTime expirou sem que o semáforo se tornasse disponível.

## xSemaphoreGive(xSemaphore)

Função para liberar um semáforo. O semáforo deve ter sido previamente criado com uma chamada para xSemaphoreCreateBinary(), xSemaphoreCreateMutex() ou xSemaphoreCreateCounting() e obtido usando SemaphoreTake().

Parâmetros

**xSemaphore** – Um identificador para o semáforo que está sendo liberado. Este é o identificador retornado quando o semáforo foi criado.

Retorno

pdTRUE se o semáforo foi liberado. pdFALSE se ocorreu um erro. Semáforos são implementados usando filas. Pode ocorrer um erro se não houver espaço na fila para postar uma mensagem - indicando que o semáforo não foi obtido corretamente.
