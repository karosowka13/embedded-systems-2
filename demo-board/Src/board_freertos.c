#include "board_freertos.h"


osThreadId_t* threads_p[TASKS] = {
    &myTask02Handle,
    &myTask03Handle,
    &myTask04Handle
};

uint32_t tasks_duration[TASKS] = {
    500,
    500,
    500,
};

uint32_t timer_period = 1000;
int8_t semaphore_code = 1;

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



int8_t release_semaphore(uint32_t semaphore_code){
    switch (semaphore_code)
    {
    case 1:
        osSemaphoreRelease(myBinarySem01Handle);
        break;
    case 2:
        osSemaphoreRelease(myBinarySem02Handle);
        break;
    case 3:
        osSemaphoreRelease(myBinarySem03Handle);
        break;
    case 4:
        osSemaphoreRelease(myBinarySem01Handle);
        osSemaphoreRelease(myBinarySem02Handle);
        break;
    case 5:
        osSemaphoreRelease(myBinarySem02Handle);
        osSemaphoreRelease(myBinarySem03Handle);
        break;
    case 6:
        osSemaphoreRelease(myBinarySem03Handle);
        osSemaphoreRelease(myBinarySem01Handle);
        break;
    case 7:
        osSemaphoreRelease(myBinarySem01Handle);
        osSemaphoreRelease(myBinarySem02Handle);
        osSemaphoreRelease(myBinarySem03Handle);
        break;
    default:
        return 4;
        break;
    }
    return 0;
}

int8_t change_timer_period(uint32_t period) {
    if (period < MIN_TIMER_PERIOD | period > MAX_TIMER_PERIOD) {
        return 2;
    } else {
        timer_period = period;
        osTimerStart(myTimer01Handle, period);
        return 0;
    }
}

uint32_t get_timer_period() {
    return timer_period;
}

int8_t change_semaphore_code_released(uint32_t code) {
    if (code > MAX_SEMAPHORE_CODE){
        return 4;
    } else {
        semaphore_code = code;
    }
}
uint32_t get_semaphore_code_released(){
    return semaphore_code;
}
