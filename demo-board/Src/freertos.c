/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : freertos.c
  * Description        : Code for freertos applications
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2019 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under Ultimate Liberty license
  * SLA0044, the "License"; You may not use this file except in compliance with
  * the License. You may obtain a copy of the License at:
  *                             www.st.com/SLA0044
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */     
#include <string.h>
#include "leds.h"
#include "commands.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define configASSERT
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN Variables */

/* USER CODE END Variables */
typedef StaticTask_t osStaticThreadDef_t;
typedef StaticQueue_t osStaticMessageQDef_t;
typedef StaticTimer_t osStaticTimerDef_t;
typedef StaticSemaphore_t osStaticSemaphoreDef_t;
osThreadId_t defaultTaskHandle;
uint32_t defaultTaskBuffer[ 128 ];
osStaticThreadDef_t defaultTaskControlBlock;
osThreadId_t myTask02Handle;
uint32_t myTask02Buffer[ 128 ];
osStaticThreadDef_t myTask02ControlBlock;
osThreadId_t myTask03Handle;
uint32_t myTask03Buffer[ 128 ];
osStaticThreadDef_t myTask03ControlBlock;
osThreadId_t myTask04Handle;
uint32_t myTask04Buffer[ 128 ];
osStaticThreadDef_t myTask04ControlBlock;
osThreadId_t uartRxHandle;
uint32_t uartRxBuffer[ 512 ];
osStaticThreadDef_t uartRxControlBlock;
osMessageQueueId_t myQueue01Handle;
uint8_t myQueue01Buffer[ 16 * sizeof( uint16_t ) ];
osStaticMessageQDef_t myQueue01ControlBlock;
osTimerId_t myTimer01Handle;
osStaticTimerDef_t myTimer01ControlBlock;
osSemaphoreId_t myBinarySem01Handle;
osStaticSemaphoreDef_t myBinarySem01ControlBlock;
osSemaphoreId_t myBinarySem02Handle;
osStaticSemaphoreDef_t myBinarySem02ControlBlock;
osSemaphoreId_t myBinarySem03Handle;
osStaticSemaphoreDef_t myBinarySem03ControlBlock;
osSemaphoreId_t uartRxSemHandle;
osStaticSemaphoreDef_t uartRxSemControlBlock;

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart){
	if(strstr(huart->pRxBuffPtr, '\n')) {
		receive_stop();
		osSemaphoreRelease(uartRxSemHandle);
	}
}
/* USER CODE END FunctionPrototypes */

void StartDefaultTask(void *argument);
void StartTask02(void *argument);
void StartTask03(void *argument);
void StartTask04(void *argument);
void uartRxEntry(void *argument);
void Callback01(void *argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/**
  * @brief  FreeRTOS initialization
  * @param  None
  * @retval None
  */
void MX_FREERTOS_Init(void) {
  /* USER CODE BEGIN Init */
       
  /* USER CODE END Init */
osKernelInitialize();

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* Create the semaphores(s) */
  /* definition and creation of myBinarySem01 */
  const osSemaphoreAttr_t myBinarySem01_attributes = {
    .name = "myBinarySem01",
    .cb_mem = &myBinarySem01ControlBlock,
    .cb_size = sizeof(myBinarySem01ControlBlock),
  };
  myBinarySem01Handle = osSemaphoreNew(1, 1, &myBinarySem01_attributes);

  /* definition and creation of myBinarySem02 */
  const osSemaphoreAttr_t myBinarySem02_attributes = {
    .name = "myBinarySem02",
    .cb_mem = &myBinarySem02ControlBlock,
    .cb_size = sizeof(myBinarySem02ControlBlock),
  };
  myBinarySem02Handle = osSemaphoreNew(1, 1, &myBinarySem02_attributes);

  /* definition and creation of myBinarySem03 */
  const osSemaphoreAttr_t myBinarySem03_attributes = {
    .name = "myBinarySem03",
    .cb_mem = &myBinarySem03ControlBlock,
    .cb_size = sizeof(myBinarySem03ControlBlock),
  };
  myBinarySem03Handle = osSemaphoreNew(1, 1, &myBinarySem03_attributes);

  /* definition and creation of uartRxSem */
  const osSemaphoreAttr_t uartRxSem_attributes = {
    .name = "uartRxSem",
    .cb_mem = &uartRxSemControlBlock,
    .cb_size = sizeof(uartRxSemControlBlock),
  };
  uartRxSemHandle = osSemaphoreNew(1, 1, &uartRxSem_attributes);

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  osSemaphoreAcquire(myBinarySem01Handle, osWaitForever);
  osSemaphoreAcquire(myBinarySem02Handle, osWaitForever);
  osSemaphoreAcquire(myBinarySem03Handle, osWaitForever);
  osSemaphoreAcquire(uartRxSemHandle, osWaitForever);
  /* USER CODE END RTOS_SEMAPHORES */

  /* Create the timer(s) */
  /* definition and creation of myTimer01 */
  const osTimerAttr_t myTimer01_attributes = {
    .name = "myTimer01",
    .cb_mem = &myTimer01ControlBlock,
    .cb_size = sizeof(myTimer01ControlBlock),
  };
  myTimer01Handle = osTimerNew(Callback01, osTimerPeriodic, NULL, &myTimer01_attributes);

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* Create the queue(s) */
  /* definition and creation of myQueue01 */
  const osMessageQueueAttr_t myQueue01_attributes = {
    .name = "myQueue01",
    .cb_mem = &myQueue01ControlBlock,
    .cb_size = sizeof(myQueue01ControlBlock),
    .mq_mem = &myQueue01Buffer,
    .mq_size = sizeof(myQueue01Buffer)
  };
  myQueue01Handle = osMessageQueueNew (16, sizeof(uint16_t), &myQueue01_attributes);

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* definition and creation of defaultTask */
  const osThreadAttr_t defaultTask_attributes = {
    .name = "defaultTask",
    .stack_mem = &defaultTaskBuffer[0],
    .stack_size = sizeof(defaultTaskBuffer),
    .cb_mem = &defaultTaskControlBlock,
    .cb_size = sizeof(defaultTaskControlBlock),
    .priority = (osPriority_t) osPriorityLow,
  };
  defaultTaskHandle = osThreadNew(StartDefaultTask, NULL, &defaultTask_attributes);

  /* definition and creation of myTask02 */
  const osThreadAttr_t myTask02_attributes = {
    .name = "myTask02",
    .stack_mem = &myTask02Buffer[0],
    .stack_size = sizeof(myTask02Buffer),
    .cb_mem = &myTask02ControlBlock,
    .cb_size = sizeof(myTask02ControlBlock),
    .priority = (osPriority_t) osPriorityBelowNormal,
  };
  myTask02Handle = osThreadNew(StartTask02, NULL, &myTask02_attributes);

  /* definition and creation of myTask03 */
  const osThreadAttr_t myTask03_attributes = {
    .name = "myTask03",
    .stack_mem = &myTask03Buffer[0],
    .stack_size = sizeof(myTask03Buffer),
    .cb_mem = &myTask03ControlBlock,
    .cb_size = sizeof(myTask03ControlBlock),
    .priority = (osPriority_t) osPriorityBelowNormal,
  };
  myTask03Handle = osThreadNew(StartTask03, NULL, &myTask03_attributes);

  /* definition and creation of myTask04 */
  const osThreadAttr_t myTask04_attributes = {
    .name = "myTask04",
    .stack_mem = &myTask04Buffer[0],
    .stack_size = sizeof(myTask04Buffer),
    .cb_mem = &myTask04ControlBlock,
    .cb_size = sizeof(myTask04ControlBlock),
    .priority = (osPriority_t) osPriorityBelowNormal,
  };
  myTask04Handle = osThreadNew(StartTask04, NULL, &myTask04_attributes);

  /* definition and creation of uartRx */
  const osThreadAttr_t uartRx_attributes = {
    .name = "uartRx",
    .stack_mem = &uartRxBuffer[0],
    .stack_size = sizeof(uartRxBuffer),
    .cb_mem = &uartRxControlBlock,
    .cb_size = sizeof(uartRxControlBlock),
    .priority = (osPriority_t) osPriorityHigh,
  };
  uartRxHandle = osThreadNew(uartRxEntry, NULL, &uartRx_attributes);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  osThreadTerminate(defaultTaskHandle);
  /* USER CODE END RTOS_THREADS */

}

/* USER CODE BEGIN Header_StartDefaultTask */
/**
  * @brief  Function implementing the defaultTask thread.
  * @param  argument: Not used 
  * @retval None
  */
/* USER CODE END Header_StartDefaultTask */
void StartDefaultTask(void *argument)
{
  /* USER CODE BEGIN StartDefaultTask */
  /* Infinite loop */
  for(;;)
  {
    osDelay(1);
  }
  /* USER CODE END StartDefaultTask */
}

/* USER CODE BEGIN Header_StartTask02 */
/**
* @brief Function implementing the myTask02 thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartTask02 */
void StartTask02(void *argument)
{
  /* USER CODE BEGIN StartTask02 */
  uint16_t to_process;
  /* Infinite loop */
  for(;;)
  {
    // osDelay(1);
    osSemaphoreAcquire(myBinarySem01Handle, osWaitForever);
    LED_turn_on(LED_TEST);
    if(osOK == osMessageQueueGet(myQueue01Handle, &to_process, NULL, 0)){
      send(to_process * 2);
    };
    osStatus_t ret = osDelay(get_duration_task1());
    LED_turn_off(LED_TEST);

  }
  /* USER CODE END StartTask02 */
}

/* USER CODE BEGIN Header_StartTask03 */
/**
* @brief Function implementing the myTask03 thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartTask03 */
void StartTask03(void *argument)
{
  /* USER CODE BEGIN StartTask03 */
	uint16_t to_process;

  /* Infinite loop */
  for(;;)
  {
	osSemaphoreAcquire(myBinarySem02Handle, osWaitForever);
	LED_turn_on(LED2);
	if(osOK == osMessageQueueGet(myQueue01Handle, &to_process, NULL, 0)){
      send(to_process * 3);
	};
	osStatus_t ret = osDelay(get_duration_task1());
	LED_turn_off(LED2);

  }
  /* USER CODE END StartTask03 */
}

/* USER CODE BEGIN Header_StartTask04 */
/**
* @brief Function implementing the myTask04 thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartTask04 */
void StartTask04(void *argument)
{
  /* USER CODE BEGIN StartTask04 */
	  uint16_t to_process;

  /* Infinite loop */
  for(;;)
  {
	osSemaphoreAcquire(myBinarySem03Handle, osWaitForever);
	LED_turn_on(LED3);
	if(osOK == osMessageQueueGet(myQueue01Handle, &to_process, NULL, 0)){
      send(to_process * 4);
	};
	osStatus_t ret = osDelay(get_duration_task1());
	LED_turn_off(LED3);
  }
  /* USER CODE END StartTask04 */
}

/* USER CODE BEGIN Header_uartRxEntry */
/**
* @brief Function implementing the uartRx thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_uartRxEntry */
void uartRxEntry(void *argument)
{
  /* USER CODE BEGIN uartRxEntry */
  /* Infinite loop */
  for(;;)
  {
	  // osDelay(1000);
   osSemaphoreAcquire(uartRxSemHandle, osWaitForever);
   parse_commands();
  }
  /* USER CODE END uartRxEntry */
}

/* Callback01 function */
void Callback01(void *argument)
{
  /* USER CODE BEGIN Callback01 */
  release_semaphore(get_semaphore_code_released());
  /* USER CODE END Callback01 */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */
     
/* USER CODE END Application */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
