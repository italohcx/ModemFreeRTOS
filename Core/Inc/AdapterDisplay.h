/*
 * AdapterDisplay.h
 *
 *  Created on: Apr 9, 2024
 *      Author: italo
 */

#ifndef INC_ADAPTERDISPLAY_H_
#define INC_ADAPTERDISPLAY_H_

#include "ssd1306.h"

#define MENU_ITEMS_PER_PAGE 3
#define NUM_MENU_PAGES 2
#define MENU_ITEM_LENGTH 21


#define LINE_0 0
#define LINE_1 1
#define LINE_2 2


#define PAGE_0 0
#define PAGE_1 1





// Estrutura para os dados do menu
typedef struct {

	uint8_t page;
    char items[NUM_MENU_PAGES][MENU_ITEMS_PER_PAGE][MENU_ITEM_LENGTH];
} MenuData_t;



void AdapterDisplaySSD1306Init();
void WriteMenuToSSD1306(const MenuData_t *menu_data);
void WriteLinetoSSD1306(const char *text, int line_number);
void UpdateSSD1306Task(void const *argument);
void SendDataToMenuQueueUpdate(const MenuData_t *menu_data);
void AdapterDisplayInitUpdateTask();
void RefreshDisplay(MenuData_t *receivedMenu, MenuData_t *menuDisplay);

#endif /* INC_ADAPTERDISPLAY_H_ */
