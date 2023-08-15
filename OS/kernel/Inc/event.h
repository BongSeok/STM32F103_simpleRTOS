#ifndef KERNEL_EVENT_H_
#define KERNEL_EVENT_H_

#include <stdbool.h>

typedef enum KernelEventFlag_t {
	KernelEventFlag_UartIn			= 0x00000001,

	KernelEventFlag_Empty			= 0x00000000
} KernelEventFlag_t;

void Kernel_event_flag_init(void);
void Kernel_event_flag_set(KernelEventFlag_t event);
void Kernel_event_flag_clear(KernelEventFlag_t event);
bool Kernel_event_flag_check(KernelEventFlag_t event);

#endif
