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


#define UPDATE_DISPLAY_TASK_STACK_SIZE 2048
int current_page = 0;



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
	// Menu 1: IP, MASK, GATEWAY
	strcpy(menu_data.items[PAGE_0][LINE_0],"IPAD:0.0.0.0");
	strcpy(menu_data.items[PAGE_0][LINE_1],"MASK:0.0.0.0");
	strcpy(menu_data.items[PAGE_0][LINE_2],"GWAY:0.0.0.0");


	// Menu 2: CFG, ROT
	strcpy(menu_data.items[1][0], "CFG:DC Port:0");
    strcpy(menu_data.items[1][1], "ROT:DC SUP:DC FAB:DC");

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
	int start_index = current_page * MENU_ITEMS_PER_PAGE;
	int end_index = start_index + MENU_ITEMS_PER_PAGE;

	for (int i = start_index; i < end_index; i++)
	{
		WriteLinetoSSD1306(menu_data->items[current_page][i - start_index], i - start_index);
	}

	// Atualiza o display
	//update_display();
}


void NextPage() {
    current_page = (current_page + 1) % NUM_MENU_PAGES;
}

void PreviousPage() {
    current_page = (current_page - 1 + NUM_MENU_PAGES) % NUM_MENU_PAGES;
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
