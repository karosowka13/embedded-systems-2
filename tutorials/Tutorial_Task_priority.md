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

..* Running -> performed task.
..* Ready -> task which is not, but CAN be executed. Is it information for the scheduler that it can run this task at the expense of another.
..* Blocked -> this task can NOT be done, because it require the passage of specific time or it waits for appearance of specific event.
..* Suspended -> task is turned off and is not considered by the scheduler. It can not be executed untill its unblocked by particular function.


#### Flow chart of the states and transitions between them
![alt text](F:\EAiIB\semestr2\embedded-systems-2\img\states_flow_chart.png "Flow chart of states")
