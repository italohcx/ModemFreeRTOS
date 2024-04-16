/*
 * AdapterDisplay.c
 *
 *  Created on: Apr 9, 2024
 *      Author: italo
 */
#include "AdapterDisplay.h"
#include "cmsis_os.h"
#include "FreeRTOS.h"
#include "queue.h"
#include <stdio.h>

#define UPDATE_DISPLAY_TASK_STACK_SIZE (512)
#define NUM_LINES 3
#define NUM_CARECTERS 21





osThreadId updateDisplayTaskHandle;
extern osMessageQId menuQueueHandle;

void WriteMenuToSSD1306(const MenuData_t *menu_data);
void WriteLinetoSSD1306(const char *text, int line_number);

void AdapterDisplaySSD1306Init()
{
	MenuData_t menu_data;
	ssd1306_Init();
	ssd1306_Fill(Black);

	// Inicializa as informações do menu
	sprintf(menu_data.ip_address, "IP:0.0.0.0");
	sprintf(menu_data.cfg_info, "CFG:DC Port:0");
	sprintf(menu_data.rot_info, "ROT:DC SUP:DC FAB:DCC");

	// Escreve as informações do menu no display
	WriteMenuToSSD1306(&menu_data);

	// Inicializa a tarefa de atualização do display
	AdapterDisplayInitUpdateTask();
}

void WriteMenuToSSD1306(const MenuData_t *menu_data)
{
	// Limpa o display antes de escrever as novas informações
	// clear_display();

	// Escreve cada linha do menu no display
	WriteLinetoSSD1306(menu_data->ip_address, 0);
	WriteLinetoSSD1306(menu_data->cfg_info, 1);
	WriteLinetoSSD1306(menu_data->rot_info, 2);

	// Atualiza o display
	//update_display();
}

// Função para escrever uma linha do menu no display
void WriteLinetoSSD1306(const char *text, int line_number)
{
	// Define a posição vertical da linha baseada no número da linha
	int vertical_position = 2 + line_number * 10; // Ajuste conforme necessário
	// Define as coordenadas para escrever a linha no display
	ssd1306_SetCursor(1, vertical_position);
	ssd1306_WriteString(text, Font_6x8, White);
	ssd1306_UpdateScreen();
}

void UpdateSSD1306Task(void const *argument)
{

	MenuData_t menu_data;

	while (1)
	{
		if (xQueueReceive(menuQueueHandle, &menu_data, portMAX_DELAY) == pdPASS)
		{
			WriteMenuToSSD1306(&menu_data);
		}
		osDelay(10);
	}
}

void SendDataToMenuQueueUpdate(const MenuData_t *menu_data)
{
	// Tenta enviar os dados para a fila, aguardando até que haja espaço na fila
	if (xQueueSend(menuQueueHandle, menu_data, portMAX_DELAY) != pdPASS)
	{
		vTaskDelay(pdMS_TO_TICKS(50));
	}
}

void AdapterDisplayInitUpdateTask()
{
	/* definition and creation of tcpServerTask */
	osThreadDef(updateDisplayTask, UpdateSSD1306Task, osPriorityBelowNormal, 0, UPDATE_DISPLAY_TASK_STACK_SIZE);
	updateDisplayTaskHandle = osThreadCreate(osThread(updateDisplayTask), NULL);
}
