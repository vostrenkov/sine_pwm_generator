
#include "pwm.h"

// Stepper motors configuration
void pwm1_config (void)
{
	
	RCC_AHB1PeriphClockCmd(	RCC_AHB1Periph_GPIOA|RCC_AHB1Periph_GPIOB|
													RCC_AHB1Periph_GPIOC|RCC_AHB1Periph_GPIOD|
													RCC_AHB1Periph_GPIOE|RCC_AHB1Periph_GPIOF|
													RCC_AHB1Periph_GPIOG, ENABLE);
	RCC_APB1PeriphClockCmd(	RCC_APB1Periph_TIM2|RCC_APB1Periph_TIM5|
													RCC_APB1Periph_TIM3|RCC_APB1Periph_TIM4, ENABLE);
	RCC_APB2PeriphClockCmd(	RCC_APB2Periph_SYSCFG, ENABLE);
	
	// PWM output pins (STEP signals)
	GPIO_PinAFConfig(GPIOC,GPIO_PinSource8,GPIO_AF_TIM3);

	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_Init(GPIOC,&GPIO_InitStructure);

	
	
	// Timers	
	TIM_TimeBaseInitTypeDef TIM_BaseInitStructure;
	TIM_OCInitTypeDef TIM_OCInitStructure;
	// PWM on TIM3 (PC8 pin)
	TIM_TimeBaseStructInit(&TIM_BaseInitStructure);
	TIM_BaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_BaseInitStructure.TIM_Prescaler = 84-1;		// 1us 
	TIM_BaseInitStructure.TIM_Period = 1000/FREQ1-1;
	TIM_TimeBaseInit(TIM3,&TIM_BaseInitStructure);
	
	TIM_OCStructInit(&TIM_OCInitStructure);
	TIM_OCInitStructure.TIM_Pulse = 0;
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OC3Init(TIM3,&TIM_OCInitStructure);
	TIM_OC3PreloadConfig(TIM3, TIM_OCPreload_Enable);
	
	TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE);
	NVIC_EnableIRQ(TIM3_IRQn);
	NVIC_SetPriority(TIM3_IRQn,2);
	
	TIM_Cmd(TIM3,ENABLE);

		

}

void pwm2_config (void)
{
	
	RCC_AHB1PeriphClockCmd(	RCC_AHB1Periph_GPIOA|RCC_AHB1Periph_GPIOB|
													RCC_AHB1Periph_GPIOC|RCC_AHB1Periph_GPIOD|
													RCC_AHB1Periph_GPIOE|RCC_AHB1Periph_GPIOF|
													RCC_AHB1Periph_GPIOG, ENABLE);
	RCC_APB1PeriphClockCmd(	RCC_APB1Periph_TIM2|RCC_APB1Periph_TIM5|
													RCC_APB1Periph_TIM3|RCC_APB1Periph_TIM4, ENABLE);
	RCC_APB2PeriphClockCmd(	RCC_APB2Periph_SYSCFG, ENABLE);
	

	GPIO_PinAFConfig(GPIOD,GPIO_PinSource14,GPIO_AF_TIM4);

	

	GPIO_InitTypeDef GPIO_InitStructure;

	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_Init(GPIOD,&GPIO_InitStructure);
	
	
	// Timers	
	TIM_TimeBaseInitTypeDef TIM_BaseInitStructure;
	TIM_OCInitTypeDef TIM_OCInitStructure;

	
	// PWM on TIM4 (PD14 pin)
	TIM_TimeBaseStructInit(&TIM_BaseInitStructure);
	TIM_BaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_BaseInitStructure.TIM_Prescaler = 84-1;		// 1us 
	TIM_BaseInitStructure.TIM_Period = 1000/FREQ2-1;
	TIM_TimeBaseInit(TIM4,&TIM_BaseInitStructure);
	
	TIM_OCStructInit(&TIM_OCInitStructure);
	TIM_OCInitStructure.TIM_Pulse = 0;
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OC3Init(TIM4,&TIM_OCInitStructure);
	TIM_OC3PreloadConfig(TIM4, TIM_OCPreload_Enable);
	
	TIM_ITConfig(TIM4,TIM_IT_Update,ENABLE);
	NVIC_EnableIRQ(TIM4_IRQn);
	NVIC_SetPriority(TIM4_IRQn,2);
	
	TIM_Cmd(TIM4,ENABLE);
		

}


// pwm
void TIM3_IRQHandler()
{
	TIM_ClearITPendingBit(TIM3, TIM_IT_Update);
	
	static uint16_t cnt;
	float arg;
	uint32_t reg;
	
	arg = 1 + sin(cnt*2*3.14/1000);				// values from 0 to 2
	reg = arg*1000/FREQ1/2;
	
	TIM3->CCR3 = reg;
	
	cnt++;
	if (cnt >= 1000)
		cnt = 0;
	
}

// pwm
void TIM4_IRQHandler()
{
	TIM_ClearITPendingBit(TIM4, TIM_IT_Update);
	
	static uint16_t cnt;
	float arg;
	uint32_t reg;
	
	arg = 1 + sin(cnt*2*3.14/1000);				// values from 0 to 2
	reg = arg*1000/FREQ2/2;
	
	TIM4->CCR3 = reg;
	
	cnt++;
	if (cnt >= 1000)
		cnt = 0;
	
}
