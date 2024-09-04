/*
 * AdapterDisplay.h
 *
 *  Created on: Apr 9, 2024
 *      Author: italo
 */

#ifndef INC_ADAPTERSSD1306_H_
#define INC_ADAPTERSSD1306_H_

#include "ssd1306.h"
#include <stdio.h>
#include <stdbool.h>

#define MENU_ITEMS_PER_PAGE 3
#define NUM_MENU_PAGES 3
#define MENU_ITEM_LENGTH 21


#define LINE_0 0
#define LINE_1 1
#define LINE_2 2


#define PAGE_0 0
#define PAGE_1 1





// Estrutura para os dados do menu
typedef struct {

    char items[NUM_MENU_PAGES][MENU_ITEMS_PER_PAGE][MENU_ITEM_LENGTH];
} MenuData_t;



void AdapterSSD1306_Init();
void AdapterSSD1306_WriteMenu(const MenuData_t *menu_data);
void AdapterSSD1306_WriteLine(const char *text, int line_number);
void AdapterSSD1306_UpdateTask(void const *argument);
void AdapterSSD1306_SendDataToMenuQueueUpdate(const MenuData_t *menu_data);
void AdapterSSD1306_Refresh(uint16_t page, uint16_t line);
void AdapterSSD1306_InitUpdateTask();
bool AdapterSSD1306_RefreshDisplay(MenuData_t *receivedMenu, MenuData_t *menuDisplay);
void AdapterSSD1306_DarkMode(bool enable);


#endif /* INC_ADAPTERSSD1306_H_ */
