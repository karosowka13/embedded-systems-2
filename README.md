# FreeRTOS demo board
This project aims to design demo board for teaching principles of [FreeRTOS](https://www.freertos.org/index.html). The demo board can be used i.e. during lectures for quick demonstration of basic features of FreeRTOS.

## Assumptions
Project based on Nucleo board with [STM32F303RE](https://www.st.com/en/microcontrollers-microprocessors/stm32f303re.html) microcontroller. Controlled and powered by host device via USB connection. `FreeRTOS` support provided via project generator [CubeMX](https://www.st.com/en/development-tools/stm32cubemx.html).

## Functionalities

 - task scheduling demonstration by switching diodes and sending commands by UART,
 - configuration by UART interface,
 - API for configuration on host device.

## FreeRTOS features demonstrated
 - Tasks
 - Semaphores
 - Queues
 - Timers

## Configuration Capabilities
 - set duration time of each `Task`,
 - set priority of each `Task`,
 - give `Semaphore`,
 - put value to `Queue`,
 - start, stop and change period of software `Timer`,
 - change `Semphore` given by timer.

There will be few semaphores, triggering both single and few tasks. Timer will be giving choosen semaphore. 

# FreeRTOS Architecture

### Tasks

There are 3 `Tasks` defined for purpuse of teaching: `Task1`, `Task2`, `Task3`. On start, each tasks turns on LED assigned to it. On exit, it turns off the diode.
There are 2 `Tasks` defined for purpose od communication: `UartRX`, `UartTX`. They have the highest priority.

### Semaphores

7 Semaphores are defined. Each `Semaphore` triggers individuall group of [Tasks](#tasks).

 | Semaphore | Task triggered |
 | - | - |
 | 1 | Task1 | 
 | 1 | Task2 |
 | 3 | Task3 |
 | 4 | Task1, Task2 |
 | 5 | Task2, Task3 |
 | 6 | Task3, Task1 |
 | 7 | Task1, Task2, Task3 |

Tasks `UartRX`, `UartTX` are triggered via semaphores `UartRX`, `UartTX` respectively. 

`UartRX` sempahore is set in UART Rx interrupt.
`UartTX` sempahore is set in tasks whether there are data ready to be sent.

### Queue
One `Queue` is defined. It stores data sent by UART interface. Each [Task](#tasks) tries to acquire data from `Queue`. If succeded, task sends processed data to UART via `UartTX` task. 

| Task | Data processing - f(x) |
| - | - |
| Task1 | x*2 |
| Task2 | x*3 |
| Task3 | x*4 |

### Software timers

Software timer gives choosen semaphore with set period to trigger specific tasks.

### Parameters

| Parameter | Function |
| - | - |
| taskX_duration | duration time in miliseconds for task X |
| taskX_proprity | priority of task X |
| timer_period | period of software timer in miliseconds |
| timer_given_semaphore | number of semaphore given by timer |


## Literature 
[Mastering The FreeRTOS](https://www.freertos.org/Documentation/161204_Mastering_the_FreeRTOS_Real_Time_Kernel-A_Hands-On_Tutorial_Guide.pdf)