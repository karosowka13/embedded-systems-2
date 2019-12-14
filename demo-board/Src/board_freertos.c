#include "board_freertos.h"


osThreadId_t* threads_p[TASKS] = {
    &myTask02Handle,
    &myTask03Handle,
    &myTask04Handle
};

uint32_t tasks_duration[TASKS] = {
    1000,
    1000,
    1000,
};

int8_t change_priority_task(uint8_t task, uint32_t priority) {
    if (task >= TASKS) {
        return 0;
    }
    if (priority > MAX_TASK_PRIORITY){
        return 1;
    }
    osThreadSetPriority(threads_p[task][0], priority);
    return 0;
}

int8_t change_duration_task(uint8_t task, uint32_t duration) {
    if (task >= TASKS) {
        return 0;
    }
    if (duration < MIN_TASK_DURATION) {
        return 3;
    }
    tasks_duration[task] = duration;
    return 0;
}

uint32_t get_duration_task1(){
    return tasks_duration[0];
}
uint32_t get_duration_task2(){
    return tasks_duration[1];
}
uint32_t get_duration_task3(){
    return tasks_duration[2];
}