#include "defines.h"
#include "pwm.h"
#include "soft_timer.h"




int main(void)
{
	
	// SysTick interrupt period 1ms
	RCC_ClocksTypeDef RCC_Clocks;
	RCC_GetClocksFreq(&RCC_Clocks);
	SysTick_Config(RCC_Clocks.SYSCLK_Frequency/1000);
	
	pwm1_config();
	for(int i=0;i<3000;i++);
	pwm2_config();

	while (1)
	{
		
	}
	return 0;
}
