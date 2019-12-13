#include "commands.h"


static command_t* commands = {
    'cpt1', change_priority_task_1,
    'cpt2', change_priority_task_2,
};

void receive_start(void){
    HAL_UART_Transmit_IT(&huart2, buffer, BUFFER_LEN);
}

void receive_stop(void){
    HAL_UART_AbortTransmit_IT(&huart2);
}

void parse_commands(void){
    int res = sscanf (huart2.pRxBuffPtr,"%s %d",command, &arg);
    if (res = 2) {
        execute_command();
        receive_start();
    }
}

void execute_command(void){

}

static uint8_t change_priority_task_1(uint32_t arg){
    return 0;
}

static uint8_t change_priority_task_2(uint32_t arg){
    return 0;
}