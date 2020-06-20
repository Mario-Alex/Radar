#ifndef __BSP_GENERALTIME_H
#define __BSP_GENERALTIME_H


#include "stm32f10x.h"


/************ͨ�ö�ʱ��TIM�������壬ֻ��TIM2��3��4��5************/
// ��ʹ�ò�ͬ�Ķ�ʱ����ʱ�򣬶�Ӧ��GPIO�ǲ�һ���ģ����Ҫע��
// ��������Ĭ��ʹ��TIM4

#define            GENERAL_TIM                   TIM2
#define            GENERAL_TIM_APBxClock_FUN     RCC_APB1PeriphClockCmd
#define            GENERAL_TIM_CLK               RCC_APB1Periph_TIM2
#define            GENERAL_TIM_PERIOD            0XFFFF
#define            GENERAL_TIM_PSC              (72-1)

// TIM ���벶��ͨ��GPIO��غ궨��
#define            GENERAL_TIM_CH1_GPIO_CLK      RCC_APB2Periph_GPIOA
#define            GENERAL_TIM_CH1_PORT          GPIOA
#define            GENERAL_TIM_CH1_PIN           GPIO_Pin_0
#define            GENERAL_TIM_CHANNEL_x         TIM_Channel_1



#define            PWM_TIM                   TIM3
#define            PWM_TIM_APBxClock_FUN     RCC_APB1PeriphClockCmd
#define            PWM_TIM_CLK               RCC_APB1Periph_TIM3
#define            PWM_TIM_Period            (1800-1)
#define            PWM_TIM_Prescaler         (800-1)
// TIM3 ����Ƚ�ͨ��1
#define            PWM_TIM_CH1_GPIO_CLK      RCC_APB2Periph_GPIOB
#define            PWM_TIM_CH1_PORT          GPIOB
#define            PWM_TIM_CH1_PIN           GPIO_Pin_0


// �ж���غ궨��

#define            GENERAL_TIM_IT_CCx            TIM_IT_CC1
#define            GENERAL_TIM_IRQ               TIM2_IRQn
#define            GENERAL_TIM_INT_FUN           TIM2_IRQHandler

// ��ȡ����Ĵ���ֵ�����궨��
#define            GENERAL_TIM_GetCapturex_FUN                 TIM_GetCapture1
// �����źż��Ժ����궨��
#define            GENERAL_TIM_OCxPolarityConfig_FUN           TIM_OC1PolarityConfig

// ��������ʼ����
#define            GENERAL_TIM_STRAT_ICPolarity                TIM_ICPolarity_Rising
// �����Ľ�������
#define            GENERAL_TIM_END_ICPolarity                  TIM_ICPolarity_Falling


//������
#define TRIG_GPIO_PORT    	GPIOB			              
#define TRIG_GPIO_CLK 	    RCC_APB2Periph_GPIOB		
#define TRIG_GPIO_PIN		GPIO_Pin_5			        

//���ն�
#define ECHO_GPIO_PORT    	GPIOB			              
#define ECHO_GPIO_CLK 	    RCC_APB2Periph_GPIOB		
#define ECHO_GPIO_PIN		GPIO_Pin_6			        






// ��ʱ�����벶���û��Զ�������ṹ������
typedef struct
{   
	uint8_t   Capture_FinishFlag;   // ���������־λ
	uint8_t   Capture_StartFlag;    // ����ʼ��־λ
	uint16_t  Capture_CcrValue;     // ����Ĵ�����ֵ
	uint16_t  Capture_Period;       // �Զ���װ�ؼĴ������±�־ 
}TIM_ICUserValueTypeDef;

extern TIM_ICUserValueTypeDef TIM_ICUserValueStructure;

/**************************��������********************************/
void GENERAL_TIM_Init(void);
float pulseIn(void);
void Ultra_GPIO_Config(void);
int calculateDistance(void);


void PWM_TIM_Init(void);
void ServoWrite(int angle);


#endif	/* __BSP_GENERALTIME_H */


