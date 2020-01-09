#include "commands.h"


static command_t* commands = {
    'cpt1',     change_priority_task_1,
    'cpt2',     change_priority_task_2,
    'cpt3',     change_priority_task_3,
    'cdt1',     change_duration_task_1,
    'cdt2',     change_duration_task_2,
    'cdt3',     change_duration_task_3,
};

void receive_start(void){
    HAL_UART_Receive_IT(&huart2, buffer, BUFFER_LEN);
}

void receive_stop(void){
    HAL_UART_AbortReceive_IT(&huart2);
}

void parse_commands(void){
    int res = sscanf (huart2.pRxBuffPtr,"%s %d",command, &arg);
    if (res = 2) {
        int8_t res = execute_command();
        receive_start();
    }
}

int8_t execute_command(void){
    for(uint16_t i; i<COMMANDS_LEN; i++){
        if(strcmp(command, commands[i].name) == 0){
            return commands[i].func(arg);
        }
        return -1;
    }
}

static int8_t change_priority_task_1(uint32_t arg){
    return change_priority_task(0, arg);
}

static int8_t change_priority_task_2(uint32_t arg){
    return change_priority_task(1, arg);
}

static int8_t change_priority_task_3(uint32_t arg){
    return change_priority_task(2, arg);
}

static int8_t change_duration_task_1(uint32_t arg){
    return change_duration_task(0, arg);
}

static int8_t change_duration_task_2(uint32_t arg){
    return change_duration_task(1, arg);
}

static int8_t change_duration_task_3(uint32_t arg){
    return change_duration_task(2, arg);
}

static int8_t timer_start(uint32_t arg){
    return 0;
}
static int8_t timer_stop(uint32_t arg){
    return 0;
}
static int8_t timer_change_period(uint32_t arg){
    return 0;
}
static int8_t timer_change_semaphore_given(uint32_t arg){
    return 0;
}
static int8_t queue_put_value(uint32_t arg){
    return 0;
}
static int8_t semaphore_give(uint32_t arg){
    return 0;
}