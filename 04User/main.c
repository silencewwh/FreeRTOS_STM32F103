#include "sys.h"
#include "delay.h"
#include "usart.h"
/************************************************
 ALIENTEK NANO��STM32F103������ʵ��0-1
 Template����ģ��-�½������½�ʹ��-HAL��汾
 ����֧�֣�www.openedv.com
 �Ա����̣� http://eboard.taobao.com
 ��ע΢�Ź���ƽ̨΢�źţ�"����ԭ��"����ѻ�ȡSTM32���ϡ�
 ������������ӿƼ����޹�˾
 ���ߣ�����ԭ�� @ALIENTEK
************************************************/


/***ע�⣺�����̺ͽ̳��е��½�����3.3С�ڶ�Ӧ***/


void Delay(__IO uint32_t nCount);

void Delay(__IO uint32_t nCount)
{
    while (nCount--) {}
}

int main(void)
{
    GPIO_InitTypeDef GPIO_Initure;

    HAL_Init();                    	 			//��ʼ��HAL��
    Stm32_Clock_Init(RCC_PLL_MUL9);   			//����ʱ��,72M

    __HAL_RCC_GPIOC_CLK_ENABLE();           	//����GPIOCʱ��

    GPIO_Initure.Pin = GPIO_PIN_0 | GPIO_PIN_1; 	//PC0��PC1
    GPIO_Initure.Mode = GPIO_MODE_OUTPUT_PP;  	//�������
    GPIO_Initure.Pull = GPIO_PULLUP;          	//����
    GPIO_Initure.Speed = GPIO_SPEED_HIGH;    	//����
    HAL_GPIO_Init(GPIOC, &GPIO_Initure);


    while (1)
    {
        HAL_GPIO_WritePin(GPIOC, GPIO_PIN_0, GPIO_PIN_SET);		//PC0��1
        HAL_GPIO_WritePin(GPIOC, GPIO_PIN_1, GPIO_PIN_SET);		//PC1��1
        Delay(0x7FFFFF);
        HAL_GPIO_WritePin(GPIOC, GPIO_PIN_0, GPIO_PIN_RESET);		//PC0��0
        HAL_GPIO_WritePin(GPIOC, GPIO_PIN_1, GPIO_PIN_RESET);		//PC1��0
        Delay(0x7FFFFF);
    }
}
