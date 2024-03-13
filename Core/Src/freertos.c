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

/* USER CODE END Variables */
osThreadId defaultTaskHandle;
osThreadId tcpServerTaskHandle;

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

void StartDefaultTask(void const * argument);
void TcpSeverTask(void const * argument);

extern void MX_LWIP_Init(void);
void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/* GetIdleTaskMemory prototype (linked to static allocation support) */
void vApplicationGetIdleTaskMemory( StaticTask_t **ppxIdleTaskTCBBuffer, StackType_t **ppxIdleTaskStackBuffer, uint32_t *pulIdleTaskStackSize );

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

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* definition and creation of defaultTask */
  osThreadDef(defaultTask, StartDefaultTask, osPriorityNormal, 0, 2048);
  defaultTaskHandle = osThreadCreate(osThread(defaultTask), NULL);

  /* definition and creation of tcpServerTask */
  osThreadDef(tcpServerTask, TcpSeverTask, osPriorityBelowNormal, 0, 2048);
 tcpServerTaskHandle = osThreadCreate(osThread(tcpServerTask), NULL);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

}

/* USER CODE BEGIN Header_StartDefaultTask */
/**
  * @brief  Function implementing the defaultTask thread.
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END Header_StartDefaultTask */
void StartDefaultTask(void const * argument)
{
  /* init code for LWIP */
  MX_LWIP_Init();
  /* USER CODE BEGIN StartDefaultTask */
  /* Infinite loop */
  for(;;)
  {
    osDelay(1);
  }
  /* USER CODE END StartDefaultTask */
}

/* USER CODE BEGIN Header_TcpSeverTask */
/**
* @brief Function implementing the tcpServerTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_TcpSeverTask */
void TcpSeverTask(void const *argument)
{
	/* USER CODE BEGIN TcpSeverTask */
	struct netconn *conn, *newconn;
	struct netbuf *buf;
	char msg[100];
	uint16_t port = 22000;
    bool enable_keepalive = true;
	/* Create a new TCP connection handle. */
	conn = netconn_new(NETCONN_TCP);

	/* Check if the connection handle was created successfully */
	if (conn == NULL)
	{
		/* Handle error */
		printf("Failed to create TCP connection handle\r\n");
		return;
	}

	/* Bind the connection to the specified port. */
	if (netconn_bind(conn, IP_ADDR_ANY, port) != ERR_OK) {
		/* Handle error */
		printf("Failed to bind to port %d\r\n", port);
		netconn_delete(conn);
		return;
	}

	/* Put the connection into LISTEN state. */
	if (netconn_listen(conn) != ERR_OK) {
		/* Handle error */
		printf("Failed to put the connection into LISTEN state\r\n");
		netconn_delete(conn);
		return;
	}

	printf("TCP server listening on port %d\r\n", port);



	/* Infinite loop */
	for (;;) {
		/* Check for new connections */
		if (netconn_accept(conn, &newconn) == ERR_OK) {
			printf("New connection established\r\n");

		    /* Set keepalive options if enabled */
		    if (enable_keepalive) {
		        int keepalive = 1; // Enable keepalive
		        int keepidle = 10; // Idle time before sending keepalive probes (in seconds)
		        int keepintvl = 5; // Interval between keepalive probes (in seconds)
		        int keepcnt = 3;   // Number of keepalive probes before the connection is considered lost

		        /* Set keepalive options on the listening socket */
		        if (lwip_setsockopt(conn->socket, SOL_SOCKET, SO_KEEPALIVE, &keepalive, sizeof(keepalive)) != ERR_OK ||
		            lwip_setsockopt(conn->socket, IPPROTO_TCP, TCP_KEEPIDLE, &keepidle, sizeof(keepidle)) != ERR_OK ||
		            lwip_setsockopt(conn->socket, IPPROTO_TCP, TCP_KEEPINTVL, &keepintvl, sizeof(keepintvl)) != ERR_OK ||
		            lwip_setsockopt(conn->socket, IPPROTO_TCP, TCP_KEEPCNT, &keepcnt, sizeof(keepcnt)) != ERR_OK) {
		            /* Handle error */
		            printf("Failed to set keepalive options\r\n");
		            //netconn_close(conn);
		            //netconn_delete(conn);
		            return;
		        }
		    }

			/* Receive data from the new connection */
			if (netconn_recv(newconn, &buf) == ERR_OK) {
				/* Process received data */
				netbuf_copy(buf, msg, sizeof(msg));
				printf("Received data: %s\r\n", msg);

				/* Free the buffer */
				netbuf_delete(buf);
			}

			/* Close the new connection */
			netconn_close(newconn);
			netconn_delete(newconn);
			printf("Connection closed\r\n");
		}

		/* Delay for a short period */
		osDelay(100);
	}

	/* Close the main connection */
	netconn_close(conn);
	netconn_delete(conn);
	/* USER CODE END TcpSeverTask */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

/* USER CODE END Application */
