#ifndef __BSP_GENERALTIME_H
#define __BSP_GENERALTIME_H


#include "stm32f10x.h"


/************通用定时器TIM参数定义，只限TIM2、3、4、5************/
// 当使用不同的定时器的时候，对应的GPIO是不一样的，这点要注意
// 我们这里默认使用TIM4

#define            GENERAL_TIM                   TIM2
#define            GENERAL_TIM_APBxClock_FUN     RCC_APB1PeriphClockCmd
#define            GENERAL_TIM_CLK               RCC_APB1Periph_TIM2
#define            GENERAL_TIM_PERIOD            0XFFFF
#define            GENERAL_TIM_PSC              (72-1)

// TIM 输入捕获通道GPIO相关宏定义
#define            GENERAL_TIM_CH1_GPIO_CLK      RCC_APB2Periph_GPIOA
#define            GENERAL_TIM_CH1_PORT          GPIOA
#define            GENERAL_TIM_CH1_PIN           GPIO_Pin_0
#define            GENERAL_TIM_CHANNEL_x         TIM_Channel_1



#define            PWM_TIM                   TIM3
#define            PWM_TIM_APBxClock_FUN     RCC_APB1PeriphClockCmd
#define            PWM_TIM_CLK               RCC_APB1Periph_TIM3
#define            PWM_TIM_Period            (1800-1)
#define            PWM_TIM_Prescaler         (800-1)
// TIM3 输出比较通道1
#define            PWM_TIM_CH1_GPIO_CLK      RCC_APB2Periph_GPIOB
#define            PWM_TIM_CH1_PORT          GPIOB
#define            PWM_TIM_CH1_PIN           GPIO_Pin_0


// 中断相关宏定义

#define            GENERAL_TIM_IT_CCx            TIM_IT_CC1
#define            GENERAL_TIM_IRQ               TIM2_IRQn
#define            GENERAL_TIM_INT_FUN           TIM2_IRQHandler

// 获取捕获寄存器值函数宏定义
#define            GENERAL_TIM_GetCapturex_FUN                 TIM_GetCapture1
// 捕获信号极性函数宏定义
#define            GENERAL_TIM_OCxPolarityConfig_FUN           TIM_OC1PolarityConfig

// 测量的起始边沿
#define            GENERAL_TIM_STRAT_ICPolarity                TIM_ICPolarity_Rising
// 测量的结束边沿
#define            GENERAL_TIM_END_ICPolarity                  TIM_ICPolarity_Falling


//触发端
#define TRIG_GPIO_PORT    	GPIOB			              
#define TRIG_GPIO_CLK 	    RCC_APB2Periph_GPIOB		
#define TRIG_GPIO_PIN		GPIO_Pin_5			        

//接收端
#define ECHO_GPIO_PORT    	GPIOB			              
#define ECHO_GPIO_CLK 	    RCC_APB2Periph_GPIOB		
#define ECHO_GPIO_PIN		GPIO_Pin_6			        






// 定时器输入捕获用户自定义变量结构体声明
typedef struct
{   
	uint8_t   Capture_FinishFlag;   // 捕获结束标志位
	uint8_t   Capture_StartFlag;    // 捕获开始标志位
	uint16_t  Capture_CcrValue;     // 捕获寄存器的值
	uint16_t  Capture_Period;       // 自动重装载寄存器更新标志 
}TIM_ICUserValueTypeDef;

extern TIM_ICUserValueTypeDef TIM_ICUserValueStructure;

/**************************函数声明********************************/
void GENERAL_TIM_Init(void);
float pulseIn(void);
void Ultra_GPIO_Config(void);
int calculateDistance(void);


void PWM_TIM_Init(void);
void ServoWrite(int angle);


#endif	/* __BSP_GENERALTIME_H */


