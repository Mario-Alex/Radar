// TIM��ͨ��-����-�������� Ӧ��
#include "stm32f10x.h"
#include "bsp_usart.h"
#include "bsp_GeneralTim.h"
#include "bsp_SysTick.h"

/**
  * @brief  ������
  * @param  ��  
  * @retval ��
  */
int main(void)
{
	int distance;
	
	/* ���ڳ�ʼ�� */
	USART_Config();
	
	/*������PIN��ʼ��*/
	Ultra_GPIO_Config();
	
	/* ��ʱ����ʼ�� */
	GENERAL_TIM_Init();
	PWM_TIM_Init();
	
	
	while(1)
	{
		for(int i=15;i<=165;i++)
		{
			ServoWrite(i);
			SysTick_Delay_Ms(30);
			distance = calculateDistance();
			
			printf("%d",i); // Sends the current degree into the Serial Port
			printf(","); // Sends addition character right next to the previous value needed later in the Processing IDE for indexing
			printf("%d",distance); // Sends the distance value into the Serial Port
			printf("."); // Se
		}
		
		for(int i=165;i>=15;i--)
		{
			ServoWrite(i);
			SysTick_Delay_Ms(30);
			
			distance = calculateDistance();
			
			printf("%d",i); // Sends the current degree into the Serial Port
			printf(","); // Sends addition character right next to the previous value needed later in the Processing IDE for indexing
			printf("%d",distance); // Sends the distance value into the Serial Port
			printf("."); // Se
		}
	}
	
	
	
		
}


/*********************************************END OF FILE**********************/
