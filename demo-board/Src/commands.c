#include "commands.h"


#define COMMANDS 12
static command_t commands [COMMANDS]= {
    {"cpt1",        change_priority_task_1},
    {"cpt2",        change_priority_task_2},
    {"cpt3",        change_priority_task_3},
    {"cdt1",        change_duration_task_1},
    {"cdt2",        change_duration_task_2},
    {"cdt3",        change_duration_task_3},
    {"sta_t",       timer_start},
    {"sto_t",       timer_stop},
    {"tp",          timer_change_period},
    {"ts",          timer_change_semaphore_given},
    {"pq",          queue_put_value},
    {"gs",          semaphore_give},
};


void receive_start(void){
    HAL_UART_Receive_IT(&huart2, buffer, BUFFER_LEN);
}

void receive_stop(void){
    HAL_UART_AbortReceive_IT(&huart2);
}

void send(uint32_t number){
    uint16_t size = sprintf(buffer_tx, "%d\n", number);
    HAL_UART_Transmit_IT(&huart2, buffer_tx, size);
}

void parse_commands(void){
    strncpy(buffer_tmp,buffer,12);
    int res = sscanf (buffer_tmp,"%s %d",command, &arg);
    if (res = 2) {
        int8_t res = execute_command();
        if(res != -2){
            send(res);
        }
        receive_start();
    }
}

int8_t execute_command(void){
    for(uint16_t i = 0; i<COMMANDS; i++){
        if(strcmp(command, commands[i].name) == 0){
            return commands[i].func(arg);
        }
    }
    return -1;
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
    osTimerStart(myTimer01Handle, get_timer_period());
    return 0;
}
static int8_t timer_stop(uint32_t arg){
    osTimerStop(myTimer01Handle);
    return 0;
}
static int8_t timer_change_period(uint32_t arg){
    return change_timer_period(arg);
}
static int8_t timer_change_semaphore_given(uint32_t arg){
    return change_semaphore_code_released(arg);
}
static int8_t queue_put_value(uint32_t arg){
    osMessageQueuePut(myQueue01Handle, &arg, NULL, 0);
    return 0;
}
static int8_t semaphore_give(uint32_t arg){
    return release_semaphore(arg);
}
