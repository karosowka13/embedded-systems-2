#ifndef __BOARD_FREERTOS__H_
#define __BOARD_FREERTOS__H_

#include "FreeRTOS.h"
#include "cmsis_os.h"

#define TASKS 3
#define MAX_TASK_PRIORITY osPriorityHigh6
#define MIN_TASK_DURATION 200

extern osThreadId_t myTask02Handle;
extern osThreadId_t myTask03Handle;
extern osThreadId_t myTask04Handle;
extern osSemaphoreId_t myBinarySem01Handle;
extern osSemaphoreId_t myBinarySem02Handle;
extern osSemaphoreId_t myBinarySem03Handle;

int8_t change_priority_task(uint8_t, uint32_t);
int8_t change_duration_task(uint8_t, uint32_t);

uint32_t get_duration_task1();
uint32_t get_duration_task2();
uint32_t get_duration_task3();

uint32_t release_semaphore(uint32_t);


#endif

