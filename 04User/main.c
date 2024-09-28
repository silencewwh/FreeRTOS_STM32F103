#include "FreeRTOS.h"
#include "task.h"
#include "stm32f1xx_hal.h"



void MX_GPIO_Init(void);
void SystemClock_Config(void);


//??1
void vTask1(void *pvParameters)
{
	for(;;)
	{
	//	printf("this is task1\n");
		HAL_GPIO_TogglePin(GPIOC,GPIO_PIN_1);
		vTaskDelay(pdMS_TO_TICKS(1000));//??????HAL_Delay();
	}
}
//??2
void vTask2(void *pvParameters)
{
	for(;;)
	{
    HAL_GPIO_TogglePin(GPIOC,GPIO_PIN_0);
    vTaskDelay(pdMS_TO_TICKS(500));//??????HAL_Delay();
	}
}

int main(void){
	
		MX_GPIO_Init();
		SystemClock_Config();
	
		xTaskCreate(vTask1,"task1",128,NULL,1,NULL);
		xTaskCreate(vTask2,"task2",128,NULL,2,NULL);
	
		vTaskStartScheduler();
	while(1){}
}


void SystemClock_Config(void)
{
    RCC_OscInitTypeDef RCC_OscInitStruct = {0};
    RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

    // ????????? (HSE) ???? PLL ??
    RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
    RCC_OscInitStruct.HSEState = RCC_HSE_ON;
    RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
    RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
    RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;  // ?????? 72 MHz


    // ??????
    RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
    RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;  // ??????? PLL
    RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;         // AHB?? = ????
    RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;          // APB1?? = ????/2 (36 MHz)
    RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;          // APB2?? = ???? (72 MHz)


    SystemCoreClockUpdate();  // ?? SystemCoreClock ??,??????????
}



void MX_GPIO_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};

    /* GPIO Ports Clock Enable */
    __HAL_RCC_GPIOC_CLK_ENABLE();  // Enable GPIOC clock

    /* Configure GPIO pin Output Level */
    HAL_GPIO_WritePin(GPIOC, GPIO_PIN_0, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_1, GPIO_PIN_RESET);
    /* Configure GPIO pins : PC0 and PC1 */
    GPIO_InitStruct.Pin = GPIO_PIN_0 | GPIO_PIN_1;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;  // Push-pull output
    GPIO_InitStruct.Pull = GPIO_NOPULL;          // No pull-up or pull-down
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW; // Low speed
    HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);      // Initialize GPIOC pins
}