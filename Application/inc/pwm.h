
#ifndef PWM_H
#define PWM_H

#include "stm32f4xx_rcc.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_tim.h"
#include "math.h"
#include "stdlib.h"
#include "defines.h"
#include "soft_timer.h"

#define FREQ1			20
#define FREQ2			20

void pwm1_config (void);
void pwm2_config (void);

#endif // PWM_H
