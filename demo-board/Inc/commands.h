#include "stm32f3xx_hal.h"
#include "main.h"

#define BUFFER_LEN 30

typedef struct {
    char* name;
    uint8_t (*func)(uint32_t arg);
}
command_t;

extern UART_HandleTypeDef huart2;

static char command[10];
static uint32_t arg;
static int8_t buffer[BUFFER_LEN];

void receive_start(void);
void receive_stop(void);
void parse_commands(void);
void execute_command(void);

static uint8_t change_priority_task_1(uint32_t arg);
static uint8_t change_priority_task_2(uint32_t arg);