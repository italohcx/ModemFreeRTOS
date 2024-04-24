/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : freertos.c
  * Description        : Code for freertos applications
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
/* ------------------------ lwIP includes --------------------------------- */
#include "api.h"
#include "sockets.h"
#include "stdbool.h"
#include "ssd1306.h"
#include "AdapterDisplay.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN Variables */

extern struct netif gnetif;
/* USER CODE END Variables */
osThreadId ethernetStatusTHandle;
osThreadId buttonsTaskHandle;
osMessageQId menuQueueHandle;

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

void EthernetStatusTask(void const * argument);
void ButtonsTask(void const * argument);

extern void MX_LWIP_Init(void);
void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/* GetIdleTaskMemory prototype (linked to static allocation support) */
void vApplicationGetIdleTaskMemory( StaticTask_t **ppxIdleTaskTCBBuffer, StackType_t **ppxIdleTaskStackBuffer, uint32_t *pulIdleTaskStackSize );

/* GetTimerTaskMemory prototype (linked to static allocation support) */
void vApplicationGetTimerTaskMemory( StaticTask_t **ppxTimerTaskTCBBuffer, StackType_t **ppxTimerTaskStackBuffer, uint32_t *pulTimerTaskStackSize );

/* USER CODE BEGIN GET_IDLE_TASK_MEMORY */
static StaticTask_t xIdleTaskTCBBuffer;
static StackType_t xIdleStack[configMINIMAL_STACK_SIZE];

void vApplicationGetIdleTaskMemory( StaticTask_t **ppxIdleTaskTCBBuffer, StackType_t **ppxIdleTaskStackBuffer, uint32_t *pulIdleTaskStackSize )
{
  *ppxIdleTaskTCBBuffer = &xIdleTaskTCBBuffer;
  *ppxIdleTaskStackBuffer = &xIdleStack[0];
  *pulIdleTaskStackSize = configMINIMAL_STACK_SIZE;
  /* place for user code */
}
/* USER CODE END GET_IDLE_TASK_MEMORY */

/* USER CODE BEGIN GET_TIMER_TASK_MEMORY */
static StaticTask_t xTimerTaskTCBBuffer;
static StackType_t xTimerStack[configTIMER_TASK_STACK_DEPTH];

void vApplicationGetTimerTaskMemory( StaticTask_t **ppxTimerTaskTCBBuffer, StackType_t **ppxTimerTaskStackBuffer, uint32_t *pulTimerTaskStackSize )
{
  *ppxTimerTaskTCBBuffer = &xTimerTaskTCBBuffer;
  *ppxTimerTaskStackBuffer = &xTimerStack[0];
  *pulTimerTaskStackSize = configTIMER_TASK_STACK_DEPTH;
  /* place for user code */
}
/* USER CODE END GET_TIMER_TASK_MEMORY */

/**
  * @brief  FreeRTOS initialization
  * @param  None
  * @retval None
  */
void MX_FREERTOS_Init(void) {
  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* Create the queue(s) */
  /* definition and creation of menuQueue */
  osMessageQDef(menuQueue, 6, MenuData_t);
  menuQueueHandle = osMessageCreate(osMessageQ(menuQueue), NULL);

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* definition and creation of ethernetStatusT */
  osThreadDef(ethernetStatusT, EthernetStatusTask, osPriorityNormal, 0, 1024);
  ethernetStatusTHandle = osThreadCreate(osThread(ethernetStatusT), NULL);

  /* definition and creation of buttonsTask */
  osThreadDef(buttonsTask, ButtonsTask, osPriorityBelowNormal, 0, 1024);
  buttonsTaskHandle = osThreadCreate(osThread(buttonsTask), NULL);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */


  /* USER CODE END RTOS_THREADS */

}

/* USER CODE BEGIN Header_EthernetStatusTask */
/**
  * @brief  Function implementing the ethernetStatusT thread.
  * @param  argument: Not used
  * @retval None
 */
/* USER CODE END Header_EthernetStatusTask */
void EthernetStatusTask(void const *argument)
{
	/* init code for LWIP */
	MX_LWIP_Init();
	/* USER CODE BEGIN EthernetStatusTask */
	MenuData_t menu_data = {0};
	char ipad[21] = {0};
	char mask[21] = {0};
	char gway[21] = {0};

	/* Infinite loop */
	for (;;)
	{
		if (netif_is_up(&gnetif))
		{
			sprintf(ipad, "IPAD:%s", ip4addr_ntoa(netif_ip4_addr(&gnetif)));
			sprintf(mask, "MASK:%s", ip4addr_ntoa(netif_ip4_netmask(&gnetif)));
			sprintf(gway, "GWAY:%s", ip4addr_ntoa(netif_ip4_gw(&gnetif)));

			if (strcmp(menu_data.items[PAGE_0][LINE_0], ipad) != 0 ||
				strcmp(menu_data.items[PAGE_0][LINE_1], mask) != 0 ||
				strcmp(menu_data.items[PAGE_0][LINE_2], gway) != 0)
			{
				strcpy(menu_data.items[PAGE_0][LINE_0], ipad);
				strcpy(menu_data.items[PAGE_0][LINE_1], mask);
				strcpy(menu_data.items[PAGE_0][LINE_2], gway);
				SendDataToMenuQueueUpdate(&menu_data);
				osDelay(100);
			}

		}
		/* USER CODE END EthernetStatusTask */
		osDelay(1);
	}

}

/* USER CODE BEGIN Header_ButtonsTask */
/**
* @brief Function implementing the buttonsTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_ButtonsTask */
void ButtonsTask(void const *argument)
{
	/* USER CODE BEGIN ButtonsTask */
	/* Infinite loop */
	for (;;)
	{

		if (HAL_GPIO_ReadPin(BT_SW1_GPIO_Port, BT_SW1_Pin) == RESET)
		{

			NextPage();
			HAL_GPIO_TogglePin(LED1_GPIO_Port, LED1_Pin);

			osDelay(250);
		}

		if (HAL_GPIO_ReadPin(BT_SW2_GPIO_Port, BT_SW2_Pin) == RESET)
		{

			PreviousPage();
			HAL_GPIO_TogglePin(LED2_GPIO_Port, LED2_Pin);

			osDelay(250);
		}

		osDelay(10);
	}
	/* USER CODE END ButtonsTask */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

/* USER CODE END Application */
