#include <AdapterSSD1306.h>
#include "cmsis_os.h"
#include "FreeRTOS.h"
#include "queue.h"
#include "string.h"

#define UPDATE_DISPLAY_TASK_STACK_SIZE 512

int current_page = 0;
osThreadId updateDisplayTaskHandle;
extern osMessageQId menuQueueHandle;
static MenuData_t menuDisplay = {0};

bool darkMode = true;

void AdapterSSD1306_WriteMenu(const MenuData_t *menu_data);
void AdapterSSD1306_WriteLine(const char *text, int line_number);
void AdapterSSD1306_SetDisplayColor(bool dark_mode);



void AdapterSSD1306_Init()
{
    ssd1306_Init();
    AdapterSSD1306_SetDisplayColor(darkMode);

    MenuData_t menuItems[NUM_MENU_PAGES] =
    {
        {{"LUPA TECNOLOGIA LTDA", "HORUS GATEWAY", "FIRWARE 0.0.0.1"}},  // Menu 1
        {{"CFG:DC Port:0", "ROT:DC SUP:DC FAB:DC", "MODBUS_DRIVER 1.0"}} // Menu 2
        // Adicione mais menus aqui, se necessário
    };

    // Escreve as informações do menu no display
    AdapterSSD1306_WriteMenu( menuItems);

    // Inicializa a tarefa de atualização do display
    AdapterSSD1306_InitUpdateTask();
}


void AdapterSSD1306_LoadMenus()
{

	AdapterSSD1306_SetDisplayColor(darkMode);
  // Definição dos itens do menu
	MenuData_t menuItems[NUM_MENU_PAGES] =
	{
		{{"IPAD:0.0.0.0", "MASK:0.0.0.0", "GWAY:0.0.0.0"}},  // Menu 1
		{{"CFG:DC Port:0", "TX: 100bytes", "RX: 340Bytes"}},
		{{"ROT:Port:22000","SUP:Port:22001", "FAB:Port:22002"}}// Menu 2
		// Adicione mais menus aqui, se necessário
	};

	// Copiar os itens definidos para a estrutura menuDisplay
	for (int page = 0; page < NUM_MENU_PAGES; ++page)
	{
		memcpy(menuDisplay.items[page], menuItems[page].items, sizeof(menuItems[page].items));
	}

	// Escreve as informações do menu no display
	AdapterSSD1306_WriteMenu(&menuDisplay);


}




void AdapterSSD1306_SetDisplayColor(bool dark_mode)
{
    darkMode = dark_mode;
    if (darkMode)
    {
        ssd1306_Fill(Black);
    }
    else
    {
        ssd1306_Fill(White);
    }
    osDelay(50);
}

void AdapterSSD1306_WriteMenu(const MenuData_t *menu_data)
{
    // Limpa o display antes de escrever as novas informações
    // clear_display();

    // Escreve cada linha do menu no display
    int start_index = current_page * MENU_ITEMS_PER_PAGE;
    int end_index = start_index + MENU_ITEMS_PER_PAGE;

    for (int i = start_index; i < end_index; i++)
    {
        AdapterSSD1306_WriteLine(menu_data->items[current_page][i - start_index], i - start_index);
    }
    // Atualiza o display
    //update_display();
}

// Função para escrever uma linha do menu no display
void AdapterSSD1306_WriteLine(const char *text, int line_number)
{
    // Define a posição vertical da linha baseada no número da linha
    int vertical_position = 2 + line_number * 10; // Ajuste conforme necessário
    ssd1306_SetCursor(1, vertical_position);

    if (darkMode)
    {
        ssd1306_WriteString(text, Font_6x8, White);
    }
    else
    {
        ssd1306_WriteString(text, Font_6x8, Black);
    }

    ssd1306_UpdateScreen();
}

void AdapterSSD1306_NextPage()
{
    current_page = (current_page + 1) % NUM_MENU_PAGES;
    AdapterSSD1306_SetDisplayColor(darkMode);
    AdapterSSD1306_WriteMenu(&menuDisplay);
}

void AdapterSSD1306_PreviousPage()
{
    current_page = (current_page - 1 + NUM_MENU_PAGES) % NUM_MENU_PAGES;
    AdapterSSD1306_SetDisplayColor(darkMode);
    AdapterSSD1306_WriteMenu(&menuDisplay);
}

void AdapterSSD1306_DarkMode(bool enable)
{
    AdapterSSD1306_SetDisplayColor(enable);
    AdapterSSD1306_WriteMenu(&menuDisplay);
}


void AdapterSSD1306_UpdateTask(void const *argument)
{

	osDelay(2000);

	AdapterSSD1306_LoadMenus();
    MenuData_t receivedMenu = {0};

    while (1)
    {
        if (xQueueReceive(menuQueueHandle, &receivedMenu, portMAX_DELAY) == pdPASS)
        {
            if (AdapterSSD1306_RefreshDisplay(&receivedMenu, &menuDisplay))
            {
                AdapterSSD1306_WriteMenu(&menuDisplay);
            }
            memset(&receivedMenu, 0, sizeof(MenuData_t));
        }
        osDelay(10);
    }
}

bool AdapterSSD1306_RefreshDisplay(MenuData_t *receivedMenu, MenuData_t *menuDisplay)
{
    bool ret = false;
    // Verificar se receivedMenu e menuDisplay são válidos
    if (receivedMenu == NULL || menuDisplay == NULL)
    {
        return ret; // Retorna sem fazer nada se algum deles for nulo
    }

    // Iterar sobre todas as páginas e itens do menu
    for (int i = 0; i < NUM_MENU_PAGES; ++i)
    {
        for (int j = 0; j < MENU_ITEMS_PER_PAGE; ++j)
        {
            // Verificar se o índice está dentro dos limites do array
            if (i < NUM_MENU_PAGES && j < MENU_ITEMS_PER_PAGE)
            {
                // Verificar se o item atual difere do item recebido
                if (strcmp(menuDisplay->items[i][j], receivedMenu->items[i][j]) != 0)
                {
                    // Se houver diferença, copiar o novo item para o menuDisplay
                    if (strcmp(receivedMenu->items[i][j], "") != 0)
                    {
                        strcpy(menuDisplay->items[i][j], receivedMenu->items[i][j]);
                        ret = true;
                    }
                }
            }
        }
    }
    return ret;
}

void AdapterSSD1306_SendDataToMenuQueueUpdate(const MenuData_t *menu_data)
{
    // Tenta enviar os dados para a fila, aguardando até que haja espaço na fila
    if (xQueueSend(menuQueueHandle, menu_data, portMAX_DELAY) != pdPASS)
    {
        vTaskDelay(pdMS_TO_TICKS(50));
    }
}

void AdapterSSD1306_InitUpdateTask()
{
    /* definition and creation of tcpServerTask */
    osThreadDef(updateDisplayTask, AdapterSSD1306_UpdateTask, osPriorityBelowNormal, 0, UPDATE_DISPLAY_TASK_STACK_SIZE);
    updateDisplayTaskHandle = osThreadCreate(osThread(updateDisplayTask), NULL);
}
