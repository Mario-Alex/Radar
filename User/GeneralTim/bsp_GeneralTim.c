
#include "bsp_GeneralTim.h"
#include "bsp_SysTick.h"


// ��ʱ�����벶���û��Զ�������ṹ�嶨��
TIM_ICUserValueTypeDef TIM_ICUserValueStructure = {0,0,0,0};

// �ж����ȼ�����
static void GENERAL_TIM_NVIC_Config(void)
{
    NVIC_InitTypeDef NVIC_InitStructure; 
    // �����ж���Ϊ0
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);		
		// �����ж���Դ
    NVIC_InitStructure.NVIC_IRQChannel = GENERAL_TIM_IRQ ;	
		// ���������ȼ�Ϊ 0
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;	 
	  // ������ռ���ȼ�Ϊ3
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;	
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
}

static void GENERAL_TIM_GPIO_Config(void) 
{
  GPIO_InitTypeDef GPIO_InitStructure;

  // ���벶��ͨ�� GPIO ��ʼ��
	RCC_APB2PeriphClockCmd(GENERAL_TIM_CH1_GPIO_CLK, ENABLE);
  GPIO_InitStructure.GPIO_Pin =  GENERAL_TIM_CH1_PIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_Init(GENERAL_TIM_CH1_PORT, &GPIO_InitStructure);	
}


///*
// * ע�⣺TIM_TimeBaseInitTypeDef�ṹ��������5����Ա��TIM6��TIM7�ļĴ�������ֻ��
// * TIM_Prescaler��TIM_Period������ʹ��TIM6��TIM7��ʱ��ֻ���ʼ����������Ա���ɣ�
// * ����������Ա��ͨ�ö�ʱ���͸߼���ʱ������.
// *-----------------------------------------------------------------------------
// *typedef struct
// *{ TIM_Prescaler            ����
// *	TIM_CounterMode			     TIMx,x[6,7]û�У���������
// *  TIM_Period               ����
// *  TIM_ClockDivision        TIMx,x[6,7]û�У���������
// *  TIM_RepetitionCounter    TIMx,x[1,8,15,16,17]����
// *}TIM_TimeBaseInitTypeDef; 
// *-----------------------------------------------------------------------------
// */

/* ----------------   PWM�ź� ���ں�ռ�ձȵļ���--------------- */
// ARR ���Զ���װ�ؼĴ�����ֵ
// CLK_cnt����������ʱ�ӣ����� Fck_int / (psc+1) = 72M/(psc+1)
// PWM �źŵ����� T = ARR * (1/CLK_cnt) = ARR*(PSC+1) / 72M
// ռ�ձ�P=CCR/(ARR+1)

static void GENERAL_TIM_Mode_Config(void)
{
  // ������ʱ��ʱ��,���ڲ�ʱ��CK_INT=72M
	GENERAL_TIM_APBxClock_FUN(GENERAL_TIM_CLK,ENABLE);

/*--------------------ʱ���ṹ���ʼ��-------------------------*/	
  TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	// �Զ���װ�ؼĴ�����ֵ���ۼ�TIM_Period+1��Ƶ�ʺ����һ�����»����ж�
	TIM_TimeBaseStructure.TIM_Period=GENERAL_TIM_PERIOD;	
	// ����CNT��������ʱ�� = Fck_int/(psc+1)
	TIM_TimeBaseStructure.TIM_Prescaler= GENERAL_TIM_PSC;	
	// ʱ�ӷ�Ƶ���� ����������ʱ��ʱ��Ҫ�õ�
	TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1;		
	// ����������ģʽ������Ϊ���ϼ���
	TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up;		
	// �ظ���������ֵ��û�õ����ù�
	TIM_TimeBaseStructure.TIM_RepetitionCounter=0;	
	// ��ʼ����ʱ��
	TIM_TimeBaseInit(GENERAL_TIM, &TIM_TimeBaseStructure);

	/*--------------------���벶��ṹ���ʼ��-------------------*/	
	TIM_ICInitTypeDef TIM_ICInitStructure;
	// �������벶���ͨ������Ҫ���ݾ����GPIO������
	TIM_ICInitStructure.TIM_Channel = GENERAL_TIM_CHANNEL_x;
	// ���벶���źŵļ�������
	TIM_ICInitStructure.TIM_ICPolarity = GENERAL_TIM_STRAT_ICPolarity;
	// ����ͨ���Ͳ���ͨ����ӳ���ϵ����ֱ���ͷ�ֱ������
	TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI;
	// �������Ҫ��������źŵķ�Ƶϵ��
	TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;
	// �������Ҫ��������źŵ��˲�ϵ��
	TIM_ICInitStructure.TIM_ICFilter = 0;
	// ��ʱ�����벶���ʼ��
	TIM_ICInit(GENERAL_TIM, &TIM_ICInitStructure);
	
	// ������ºͲ����жϱ�־λ
  TIM_ClearFlag(GENERAL_TIM, TIM_FLAG_Update|GENERAL_TIM_IT_CCx);
	GPIO_ResetBits(GPIOA, GPIO_Pin_0);	
  // �������ºͲ����ж�  
	//TIM_ITConfig (GENERAL_TIM, TIM_IT_Update | GENERAL_TIM_IT_CCx, ENABLE );
	
	// ʹ�ܼ�����
//	TIM_Cmd(GENERAL_TIM, ENABLE);
}

void GENERAL_TIM_Init(void)
{
	GENERAL_TIM_GPIO_Config();
	GENERAL_TIM_NVIC_Config();
	GENERAL_TIM_Mode_Config();
	
}





void PWM_TIM_Init(void)
{

	GPIO_InitTypeDef GPIO_InitStructure;

  // ����Ƚ�ͨ��1 GPIO ��ʼ��
	RCC_APB2PeriphClockCmd(PWM_TIM_CH1_GPIO_CLK, ENABLE);
  GPIO_InitStructure.GPIO_Pin =  PWM_TIM_CH1_PIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(PWM_TIM_CH1_PORT, &GPIO_InitStructure);
	
	PWM_TIM_APBxClock_FUN(PWM_TIM_CLK,ENABLE);

/*--------------------ʱ���ṹ���ʼ��-------------------------*/
	// �������ڣ���������Ϊ100K
	
  TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	// �Զ���װ�ؼĴ�����ֵ���ۼ�TIM_Period+1��Ƶ�ʺ����һ�����»����ж�
	TIM_TimeBaseStructure.TIM_Period=PWM_TIM_Period;	
	// ����CNT��������ʱ�� = Fck_int/(psc+1)
	TIM_TimeBaseStructure.TIM_Prescaler= PWM_TIM_Prescaler;	
	// ʱ�ӷ�Ƶ���� ����������ʱ��ʱ��Ҫ�õ�
	TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1;		
	// ����������ģʽ������Ϊ���ϼ���
	TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up;		
	// �ظ���������ֵ��û�õ����ù�
	TIM_TimeBaseStructure.TIM_RepetitionCounter=0;	
	// ��ʼ����ʱ��
	TIM_TimeBaseInit(PWM_TIM, &TIM_TimeBaseStructure);

	/*--------------------����ȽϽṹ���ʼ��-------------------*/	
	// ռ�ձ�����
//	uint16_t CCR1_Val = 5;
//	uint16_t CCR2_Val = 4;
//	uint16_t CCR3_Val = 3;
//	uint16_t CCR4_Val = 2;
TIM_OCInitTypeDef  TIM_OCInitStructure;
	// ����ΪPWMģʽ1
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	// ���ʹ��
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	// ���ͨ����ƽ��������	
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	
	// ����Ƚ�ͨ�� 1
	TIM_OCInitStructure.TIM_Pulse = 900;
	TIM_OC3Init(PWM_TIM, &TIM_OCInitStructure);
	TIM_OC3PreloadConfig(PWM_TIM, TIM_OCPreload_Enable);	
	
	
//	// ����Ƚ�ͨ�� 2
//	TIM_OCInitStructure.TIM_Pulse = CCR2_Val;
//	TIM_OC2Init(PWM_TIM, &TIM_OCInitStructure);
//	TIM_OC2PreloadConfig(PWM_TIM, TIM_OCPreload_Enable);
//	
//	// ����Ƚ�ͨ�� 3
//	TIM_OCInitStructure.TIM_Pulse = CCR3_Val;
//	TIM_OC3Init(PWM_TIM, &TIM_OCInitStructure);
//	TIM_OC3PreloadConfig(PWM_TIM, TIM_OCPreload_Enable);
//	
//	// ����Ƚ�ͨ�� 4
//	TIM_OCInitStructure.TIM_Pulse = CCR4_Val;
//	TIM_OC4Init(PWM_TIM, &TIM_OCInitStructure);
//	TIM_OC4PreloadConfig(PWM_TIM, TIM_OCPreload_Enable);
//	
	// ʹ�ܼ�����
	TIM_Cmd(PWM_TIM, ENABLE);
}

void ServoWrite(int angle)
{
	TIM_SetCompare3(TIM3,(angle+45));
}



float pulseIn(void)
{	
	// TIM ������������ʱ��
	uint32_t TIM_PscCLK = 72000000 / (GENERAL_TIM_PSC+1);
	float pretime;
	float time;
	// �������ºͲ����ж�  
	TIM_ITConfig (GENERAL_TIM, TIM_IT_Update | GENERAL_TIM_IT_CCx, ENABLE );
//	
//	// ʹ�ܼ�����
	TIM_Cmd(GENERAL_TIM, ENABLE);
	while ( 1 )
	{
		if(TIM_ICUserValueStructure.Capture_FinishFlag == 1)
		{
			// ����ߵ�ƽʱ��ļ�������ֵ
			pretime = TIM_ICUserValueStructure.Capture_Period * (GENERAL_TIM_PERIOD+1) + 
			       (TIM_ICUserValueStructure.Capture_CcrValue+1);
			
			time = pretime/TIM_PscCLK;
			TIM_ICUserValueStructure.Capture_FinishFlag = 0;
			return time;
		}
	}
}


void Ultra_GPIO_Config(void)
{		
		/*����һ��GPIO_InitTypeDef���͵Ľṹ��*/
		GPIO_InitTypeDef GPIO_InitStructure;

		/*����LED��ص�GPIO����ʱ��*/
		RCC_APB2PeriphClockCmd( TRIG_GPIO_CLK, ENABLE);
		/*ѡ��Ҫ���Ƶ�GPIO����*/
		GPIO_InitStructure.GPIO_Pin = TRIG_GPIO_PIN;	

		/*��������ģʽΪͨ���������*/
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;   

		/*������������Ϊ50MHz */   
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 

		/*���ÿ⺯������ʼ��GPIO*/
		GPIO_Init(TRIG_GPIO_PORT, &GPIO_InitStructure);	
		
//		/*ѡ��Ҫ���Ƶ�GPIO����*/
//		GPIO_InitStructure.GPIO_Pin = ECHO_GPIO_PIN;

//		/*���ÿ⺯������ʼ��GPIO*/
//		GPIO_Init(ECHO_GPIO_PORT, &GPIO_InitStructure);
	
		/* �ر�����led��	*/
		GPIO_ResetBits(TRIG_GPIO_PORT, TRIG_GPIO_PIN);
//		GPIO_ResetBits(ECHO_GPIO_PORT, ECHO_GPIO_PIN);
		
}


int calculateDistance(void)
{ 
  float duration;
	float predistance;
	int distance;
//	GPIO_ResetBits(TRIG_GPIO_PORT, TRIG_GPIO_PIN);
//	SysTick_Delay_Us(2);
  GPIO_SetBits(TRIG_GPIO_PORT, TRIG_GPIO_PIN);
  SysTick_Delay_Us(10);
  GPIO_ResetBits(TRIG_GPIO_PORT, TRIG_GPIO_PIN);
  duration = pulseIn(); // Reads the echoPin, returns the sound wave travel time in microseconds
  predistance= duration*340*100/2;
	distance = (int)predistance;
  return distance;
	
}

/*********************************************END OF FILE**********************/
