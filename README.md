# FreeRTOS demo board
This project aims to design demo board for teaching principles of [FreeRTOS](https://www.freertos.org/index.html).

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

## Configuration Capabilities
 - set duration time of each `Task`,
 - set priority of each `Task`,
 - give `Semaphore`,
 - put value to `Queue`,
 - start, stop and change period of software `Timer`,
 - change `Semphore` given by timer.

There will be few semaphores, triggering both single and few tasks. Timer will be giving choosen semaphore. 

## Literature 
[Mastering The FreeRTOS](https://www.freertos.org/Documentation/161204_Mastering_the_FreeRTOS_Real_Time_Kernel-A_Hands-On_Tutorial_Guide.pdf)