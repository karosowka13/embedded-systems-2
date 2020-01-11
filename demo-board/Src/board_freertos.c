#include "board_freertos.h"


osThreadId_t* threads_p[TASKS] = {
    &myTask02Handle,
    &myTask03Handle,
    &myTask04Handle
};

uint32_t tasks_duration[TASKS] = {
    100,
    100,
    100,
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

uint32_t release_semaphore(uint32_t semaphore_code){
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
        break;
    }
}