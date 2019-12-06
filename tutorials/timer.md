# `foo` - FreeRTOS
Ih this tutorial you will learn about [Software Timers](http://www.keil.com/pack/doc/CMSIS_Dev/RTOS2/html/group__CMSIS__RTOS__TimerMgmt.html) in FreeRTOS.

## The 'WHY' part

In this part you will observe how `foo` influences behaviour of FreeRTOS.
Try to think why this features was implemented and what are possible aplacations.

### Prequisities
 - demo board

### Setup

Please find IP adress of RPi using [Wireshark](https://www.wireshark.org/).
Visit type IP of RPi in browser to use application.

### Steps

## The 'HOW' part
In this part your will learn how to use FreeRTOS API to program `Software Timer` functionality.

### Prequisites

 - STM32F303RE nucleo board
 - [CubeIDE](https://www.st.com/en/development-tools/stm32cubeide.html) v1.1.0 or higher
 - [Base project](foo.com) downloaded

Please open `base-project`. Variables neccessary for Timer are already declared. We will use [osTimerStart](http://www.keil.com/pack/doc/CMSIS_Dev/RTOS2/html/group__CMSIS__RTOS__TimerMgmt.html#gab6ee2859ea657641b7adfac599b8121d) function in order to start Timer:

```c
/* USER CODE BEGIN PD */
#define TIMER_PERIOD 1000
/* USER CODE END PD */
```

```c
/* USER CODE BEGIN RTOS_TIMERS */
/* start timers, add new ones, ... */
osTimerStart(myTimer01Handle, TIMER_PERIOD);
/* USER CODE END RTOS_TIMERS */
```

Next, we want to [release](https://www.keil.com/pack/doc/CMSIS/RTOS/html/group__CMSIS__RTOS__SemaphoreMgmt.html#gab108914997c49e14d8ff1ae0d1988ca0) semaphore in order to trigger Task01.

```c
/* USER CODE BEGIN Callback01 */
osSemaphoreRelease(myBinarySem01Handle);
/* USER CODE END Callback01 */
```

In the task02 we want to [wait](https://www.keil.com/pack/doc/CMSIS/RTOS/html/group__CMSIS__RTOS__SemaphoreMgmt.html#gacc15b0fc8ce1167fe43da33042e62098) for semaphore - the task will be trigger by this semaphore. Please note that one can specify wait time.
We also call functions to switch diodes in order to indicate task execution time.
`osDelay` represents any function that is computationally expensive.
```c
/* USER CODE BEGIN StartTask02 */
/* Infinite loop */
for(;;)
{
    osSemaphoreAcquire(myBinarySem01Handle, osWaitForever);
    LED_turn_on(LED1);
    osDelay(500);
    LED_turn_off(LED1);
}
/* USER CODE END StartTask02 */
```

Now compile project and load it onto boards. 

### Expected results

Diode should blink with 1s period and 50% duty.
