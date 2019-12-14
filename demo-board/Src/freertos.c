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
uint32_t uartRxBuffer[ 128 ];
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
osSemaphoreId_t myBinarySem04Handle;
osStaticSemaphoreDef_t myBinarySem04ControlBlock;
osSemaphoreId_t myBinarySem05Handle;
osStaticSemaphoreDef_t myBinarySem05ControlBlock;
osSemaphoreId_t myBinarySem06Handle;
osStaticSemaphoreDef_t myBinarySem06ControlBlock;
osSemaphoreId_t myBinarySem07Handle;
osStaticSemaphoreDef_t myBinarySem07ControlBlock;
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

  /* definition and creation of myBinarySem04 */
  const osSemaphoreAttr_t myBinarySem04_attributes = {
    .name = "myBinarySem04",
    .cb_mem = &myBinarySem04ControlBlock,
    .cb_size = sizeof(myBinarySem04ControlBlock),
  };
  myBinarySem04Handle = osSemaphoreNew(1, 1, &myBinarySem04_attributes);

  /* definition and creation of myBinarySem05 */
  const osSemaphoreAttr_t myBinarySem05_attributes = {
    .name = "myBinarySem05",
    .cb_mem = &myBinarySem05ControlBlock,
    .cb_size = sizeof(myBinarySem05ControlBlock),
  };
  myBinarySem05Handle = osSemaphoreNew(1, 1, &myBinarySem05_attributes);

  /* definition and creation of myBinarySem06 */
  const osSemaphoreAttr_t myBinarySem06_attributes = {
    .name = "myBinarySem06",
    .cb_mem = &myBinarySem06ControlBlock,
    .cb_size = sizeof(myBinarySem06ControlBlock),
  };
  myBinarySem06Handle = osSemaphoreNew(1, 1, &myBinarySem06_attributes);

  /* definition and creation of myBinarySem07 */
  const osSemaphoreAttr_t myBinarySem07_attributes = {
    .name = "myBinarySem07",
    .cb_mem = &myBinarySem07ControlBlock,
    .cb_size = sizeof(myBinarySem07ControlBlock),
  };
  myBinarySem07Handle = osSemaphoreNew(1, 1, &myBinarySem07_attributes);

  /* definition and creation of uartRxSem */
  const osSemaphoreAttr_t uartRxSem_attributes = {
    .name = "uartRxSem",
    .cb_mem = &uartRxSemControlBlock,
    .cb_size = sizeof(uartRxSemControlBlock),
  };
  uartRxSemHandle = osSemaphoreNew(1, 1, &uartRxSem_attributes);

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
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
    .priority = (osPriority_t) osPriorityNormal,
    .stack_size = 128
  };
  defaultTaskHandle = osThreadNew(StartDefaultTask, NULL, &defaultTask_attributes);

  /* definition and creation of myTask02 */
  const osThreadAttr_t myTask02_attributes = {
    .name = "myTask02",
    .stack_mem = &myTask02Buffer[0],
    .stack_size = sizeof(myTask02Buffer),
    .cb_mem = &myTask02ControlBlock,
    .cb_size = sizeof(myTask02ControlBlock),
    .priority = (osPriority_t) osPriorityLow,
  };
  myTask02Handle = osThreadNew(StartTask02, NULL, &myTask02_attributes);

  /* definition and creation of myTask03 */
  const osThreadAttr_t myTask03_attributes = {
    .name = "myTask03",
    .stack_mem = &myTask03Buffer[0],
    .stack_size = sizeof(myTask03Buffer),
    .cb_mem = &myTask03ControlBlock,
    .cb_size = sizeof(myTask03ControlBlock),
    .priority = (osPriority_t) osPriorityLow,
  };
  myTask03Handle = osThreadNew(StartTask03, NULL, &myTask03_attributes);

  /* definition and creation of myTask04 */
  const osThreadAttr_t myTask04_attributes = {
    .name = "myTask04",
    .stack_mem = &myTask04Buffer[0],
    .stack_size = sizeof(myTask04Buffer),
    .cb_mem = &myTask04ControlBlock,
    .cb_size = sizeof(myTask04ControlBlock),
    .priority = (osPriority_t) osPriorityLow,
  };
  myTask04Handle = osThreadNew(StartTask04, NULL, &myTask04_attributes);

  /* definition and creation of uartRx */
  const osThreadAttr_t uartRx_attributes = {
    .name = "uartRx",
    .stack_mem = &uartRxBuffer[0],
    .stack_size = sizeof(uartRxBuffer),
    .cb_mem = &uartRxControlBlock,
    .cb_size = sizeof(uartRxControlBlock),
    .priority = (osPriority_t) osPriorityLow,
  };
  uartRxHandle = osThreadNew(uartRxEntry, NULL, &uartRx_attributes);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
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
  /* Infinite loop */
  for(;;)
  {
    osDelay(1);
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
  /* Infinite loop */
  for(;;)
  {
    osDelay(1);
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
  /* Infinite loop */
  for(;;)
  {
    osDelay(1);
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
    osSemaphoreAcquire(uartRxSemHandle, osWaitForever);

    
  }
  /* USER CODE END uartRxEntry */
}

/* Callback01 function */
void Callback01(void *argument)
{
  /* USER CODE BEGIN Callback01 */
  
  /* USER CODE END Callback01 */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */
     
/* USER CODE END Application */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
