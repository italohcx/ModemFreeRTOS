/*
 * AdapterDisplay.h
 *
 *  Created on: Apr 9, 2024
 *      Author: italo
 */

#ifndef INC_ADAPTERDISPLAY_H_
#define INC_ADAPTERDISPLAY_H_

#include "ssd1306.h"

typedef struct {
	char ip_address[16];  // Endereço IP
	char cfg_info[20];    // Informações de configuração
	char rot_info[30];    // Informações de roteamento
} MenuData_t;

void AdapterDisplaySSD1306Init();
void WriteMenuToSSD1306(const MenuData_t *menu_data);
void WriteLinetoSSD1306(const char *text, int line_number);
void UpdateSSD1306Task(void const *argument);
void SendDataToMenuQueueUpdate(const MenuData_t *menu_data);
void AdapterDisplayInitUpdateTask();

#endif /* INC_ADAPTERDISPLAY_H_ */
