//#include "stdint.h"
//#include "stdbool.h"

#include "main.h"
#include "kernel.h"
#include "task.h"

void Kernel_start(void)
{
	Kernel_task_start();
}

void Kernel_yield(void)
{
	Kernel_task_scheduler();
}

