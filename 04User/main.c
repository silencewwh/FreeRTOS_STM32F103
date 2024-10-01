#include "includes.h"
#include "led.h"



/*
**********************************************************************************************************
????
**********************************************************************************************************
*/
static void vTaskTaskUserIF(void *pvParameters);
static void vTaskLED(void *pvParameters);
static void vTaskMsgPro(void *pvParameters);
static void vTaskStart(void *pvParameters);
static void AppTaskCreate (void);
/*
**********************************************************************************************************
????
**********************************************************************************************************
*/
static TaskHandle_t xHandleTaskUserIF = NULL;
static TaskHandle_t xHandleTaskLED = NULL;
static TaskHandle_t xHandleTaskMsgPro = NULL;
static TaskHandle_t xHandleTaskStart = NULL;
/*
*********************************************************************************************************
* ? ? ?: main
* ????: ?? c ?????
* ? ?: ?
* ? ? ?: ?
*********************************************************************************************************
*/
int main(void)
{
/*
??????,??????? STM32 ????????????,????????(?? NMI ? HardFault)?
???????:
1. ????????????? FreeRTOS ? API ???
2. ????????,?????????
3. ??????????,????????????????
????? port.c ???? prvStartFirstTask ??????????????? cpsie i ??, __set_PRIMASK(1)
? cpsie i ?????
*/
__set_PRIMASK(1);
/* ????? */
LED_Init();
/* ???? */
AppTaskCreate();
HAL_GPIO_TogglePin(GPIOC,GPIO_PIN_7);
/* ????,?????? */
vTaskStartScheduler();
/*
?????????????????,????????????????????????
heap ??????????,???? FreeRTOSConfig.h ?????? heap ??:
#define configTOTAL_HEAP_SIZE ( ( size_t ) ( 17 * 1024 ) )
*/
while(1);
}
/*
*********************************************************************************************************
* ? ? ?: vTaskTaskUserIF
* ????: ??????,???? LED ??
* ? ?: pvParameters ?????????????
* ? ? ?: ?
* ? ? ?: 1 (?????????,??? uCOS ??)
*********************************************************************************************************
*/
static void vTaskTaskUserIF(void *pvParameters)
{
while(1)
{
HAL_GPIO_TogglePin(GPIOC,GPIO_PIN_0);
vTaskDelay(100);
}
}
/*
*********************************************************************************************************
* ? ? ?: vTaskLED
* ????: LED ??
* ? ?: pvParameters ?????????????
* ? ? ?: ?
* ? ? ?: 2
*********************************************************************************************************
*/
static void vTaskLED(void *pvParameters)
{
while(1)
{
HAL_GPIO_TogglePin(GPIOC,GPIO_PIN_1);
vTaskDelay(200);
}
}
/*
*********************************************************************************************************
* ? ? ?: vTaskMsgPro
* ????: ????,????? LED ??
* ? ?: pvParameters ?????????????
* ? ? ?: ?
* ? ? ?: 3
*********************************************************************************************************
*/
static void vTaskMsgPro(void *pvParameters)
{
while(1)
{
HAL_GPIO_TogglePin(GPIOC,GPIO_PIN_2);
vTaskDelay(300);
}
}
/*
*********************************************************************************************************
* ? ? ?: vTaskStart
* ????: ????,??????????,???? LED ??
* ? ?: pvParameters ?????????????
* ? ? ?: ?
* ? ? ?: 4
*********************************************************************************************************
*/
static void vTaskStart(void *pvParameters)
{
while(1)
{
/* LED ?? */
HAL_GPIO_TogglePin(GPIOC,GPIO_PIN_3);
vTaskDelay(400);
}
}
/*
*********************************************************************************************************
* ? ? ?: AppTaskCreate
* ????: ??????
* ? ?: ?
* ? ? ?: ?
*********************************************************************************************************
*/
static void AppTaskCreate (void)
{
xTaskCreate( vTaskTaskUserIF, /* ???? */
	"vTaskUserIF", /* ??? */
	128, /* ?????,?? word,??? 4 ?? */
	NULL, /* ???? */
	1, /* ?????*/
	&xHandleTaskUserIF ); /* ???? */
	xTaskCreate( vTaskLED, /* ???? */
	"vTaskLED", /* ??? */
	128, /* ?????,?? word,??? 4 ?? */
	NULL, /* ???? */
	2, /* ?????*/
	&xHandleTaskLED ); /* ???? */
	xTaskCreate( vTaskMsgPro, /* ???? */
	"vTaskMsgPro", /* ??? */
	128, /* ?????,?? word,??? 4 ?? */
	NULL, /* ???? */
	3, /* ?????*/
	&xHandleTaskMsgPro ); /* ???? */
	xTaskCreate( vTaskStart, /* ???? */
	"vTaskStart", /* ??? */
	128, /* ?????,?? word,??? 4 ?? */
	NULL, /* ???? */
	4, /* ?????*/
	&xHandleTaskStart ); /* ???? */
}

