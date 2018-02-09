#include "soft_timer.h"

uint32_t timer_flags;
__IO uint32_t TimingDelay;

#define Max_Num_Of_Timers 					10

soft_timer_t SoftTimer[Max_Num_Of_Timers];



void SysTick_Handler(void)
{

	for (int i=0;i<Max_Num_Of_Timers;i++)						
	{
		if (SoftTimer[i].Number == 0) continue;
		if (SoftTimer[i].Time != 0) SoftTimer[i].Time--;
		else 
		{
			timer_flags	|=	(1<<SoftTimer[i].Number);
			SoftTimer[i].Number = 0;
		}
	}
	
	if (TimingDelay != 0x00)										
  {
    TimingDelay--;
  }
	
}

void Delay_ms(__IO uint32_t nTime)
{
  TimingDelay = nTime;
  while(TimingDelay != 0);
}

void SetTimer (unsigned char NewNumber, uint32_t NewTime)			
{
	unsigned char i;
	for (i=0;i!=Max_Num_Of_Timers;i++)			
	{
		if (SoftTimer[i].Number == NewNumber)	
		{
			SoftTimer[i].Time = NewTime;				
			return;
		}
	}
	for (i=0;i!=Max_Num_Of_Timers;i++)			
	{																				
		if (SoftTimer[i].Number == 0)
		{
			SoftTimer[i].Number = NewNumber;	
			SoftTimer[i].Time = NewTime;
			return;			
		}
	}
}

void KillTimer (unsigned char Flag)
{
	int i;
	for (i=0;i<Max_Num_Of_Timers;i++)			
	{
		if (SoftTimer[i].Number == Flag)
		{
			SoftTimer[i].Number = 0;					
			return;
		}
	}
}


