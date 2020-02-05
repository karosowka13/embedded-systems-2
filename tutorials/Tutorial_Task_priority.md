# Task priority FreeRTOS

## Introduction

Tasks enable us to divide whole programme into smaller tasks in order to make implementation of functionalities easiest. Moreover the communication between tasks and time dependencies are assigned to the system not to the programmer.

#### What is the TASK

Each task is responsible for implementation of a cpecific functionality, which is performed in infinite loop.
What is more, every task has its own stack and set of processor registers. The size of the stack is implemented during its creation therfore it is tailored to the assignment.
While task is switched, actual contexts is saved. So task continue its work from the point which lately was finished, NOT from the begginig. 
As you can see context switching required numerous activities from processor and this time taken for working of the system, not execution of task. What is more, the time is longer on the basis of number of registers and size of the stack.

#### States of the task

In one moment only one task is executed. So what are the others statuses?

* Running -> performed task.
* Ready -> task which is not, but CAN be executed. Is it information for the scheduler that it can run this task at the expense of another.
* Blocked -> this task can NOT be done, because it require the passage of specific time or it waits for appearance of specific event.
* Suspended -> task is turned off and is not considered by the scheduler. It can not be executed untill its unblocked by particular function.


## Programme 

Now you can consider how tasks are changed and how often operating system verify wheter the change of the context is needed. Everything is happening because of System Tick. Frequency of the System Tick is much more lower in comparision with frequency of processor clock. The time is configured manually via macro configTICK_RATE_HZ in configuation file. 

```c
 BaseType_t xTaskCreate( TaskFunction_t pvTaskCode,
                         const char * const pcName,
                         unsigned short usStackDepth,
                         void *pvParameters,
                         UBaseType_t uxPriority,
                         TaskHandle_t *pxCreatedTask
                        );
```
## FreeRTOS API Details

**xTaskCreate()**: This interface is used to create a new Task, if the task is successfully created then it returns pdPass(1) or else errCOULD_NOT_ALLOCATE_REQUIRED_MEMORY(-1). 

**vTaskDelay()**: This function is used to delay/block the task for specified delay time(ticks). INCLUDE_vTaskDelay needs to be set to 1 in FreeRtosConfig.h file for using this function. 

**vTaskPrioritySet()**: This function is used to change/Set the priority of a task.
For this we need to pass the handle of the task and new priority to vTaskPrioritySet() function. 

**vTaskPriorityGet()**: This function is used to get the priority of a task.
For this, we need to pass the handle of the task and it will return the task. 

# To do 

### Prequisites

 - STM32F303RE nucleo board
 - [CubeIDE](https://www.st.com/en/development-tools/stm32cubeide.html) v1.1.0 or higher
 - [Base project](foo.com) downloaded

Create two tasks with priorities 1 and 2. Moreover idle task should be also created which priority is by defaul 0.

```c
 xTaskCreate(MyTask1, "Task1", 100, NULL, 1, NULL);
 xTaskCreate(MyTask2, "Task2", 100, NULL, 2, NULL);
 xTaskCreate(MyIdleTask, "IdleTask", 100, NULL, 0, NULL);
```

Apply delay 100, 150 and 50 to each task and match the LED to them to.

```c
static void MyTask1(void* pvParameters)
{
  while(1)
  { 
    LED_turn_on(LED1);
    vTaskDelay(100/portTICK_PERIOD_MS);
  }
}
```

### Expected results:

The controller starts the execution from setup function. The Serial port is initialized at 9600 baud rate and setup message is printed.

Later 3-Tasks(Task1, Task2 and Idle) are created in order with priorities 2,1,0. At the end of the Setup function, scheduler/kernel takes the control.

There are 3-tasks in the Ready state and since Task2 has the highest priority it will run first and goes to block state for 150ms.

Now 2-tasks are available for scheduler and it chooses Task1 as it is the available higher priority task.
Now Task1 runs for some time and then goes to blocked state for 100ms.

CPU is left out with the Idle task and it starts running.

Task2 will be in blocked state for 150ms and task1 will 100ms. So task1 will come out of blocked state first.

After Task1 waiting time is elapsed, it comes to the Ready state. Since it has got higher priority compared to the Idle task, it will preempt Idle task and starts running. It again goes to blocked state for 100ms.

Now CPU is left out with IDLE task and it starts running it.

After Task2 waiting time is elapsed, it comes to the Ready state. Since it has got higher priority compared to the Idle task, it will preempt Idle task and starts running. It again goes to blocked state for 150ms.

Same thing continues.
