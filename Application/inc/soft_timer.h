#ifndef SOFT_TIMER
#define SOFT_TIMER

#include "defines.h"



void Delay_ms(__IO uint32_t nTime);

typedef struct {
	
	unsigned char Number;
	uint32_t Time;
} soft_timer_t;

typedef enum
{
	parse_timeout = 1,
	steppers_off,
	protection_update,
	leds,
	state_timeout,
	
}timer_flag_t;

void Delay_ms(__IO uint32_t nTime);
void SetTimer (unsigned char NewNumber, uint32_t NewTime);
void KillTimer (unsigned char Flag);


#endif

