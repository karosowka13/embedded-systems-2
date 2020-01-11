#ifndef __COMMANDS__H_
#define __COMMANDS__H_


#include <string.h>
#include "stm32f3xx_hal.h"
#include "main.h"
#include "board_freertos.h"
#include "FreeRTOS.h"
#include "cmsis_os.h"

#define MAX_SEM 7

#define BUFFER_LEN 12
#define COMMANDS_LEN sizeof(commands) / sizeof(command_t)

typedef struct {
    char name[8];
    int8_t (*func)(uint32_t arg);
}
command_t;

extern UART_HandleTypeDef huart2;


static uint8_t command[10];
static uint32_t arg;
static uint8_t buffer[BUFFER_LEN];
static uint8_t buffer_tmp[BUFFER_LEN];

void receive_start(void);
void receive_stop(void);
void parse_commands(void);
int8_t execute_command(void);

static int8_t change_priority_task_1(uint32_t);
static int8_t change_priority_task_2(uint32_t);
static int8_t change_priority_task_3(uint32_t);
static int8_t change_duration_task_1(uint32_t);
static int8_t change_duration_task_2(uint32_t);
static int8_t change_duration_task_3(uint32_t);
static int8_t timer_start(uint32_t);
static int8_t timer_stop(uint32_t);
static int8_t timer_change_period(uint32_t);
static int8_t timer_change_semaphore_given(uint32_t);
static int8_t queue_put_value(uint32_t);
static int8_t semaphore_give(uint32_t);



#endif
