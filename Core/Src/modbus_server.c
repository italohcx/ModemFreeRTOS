/*
 * modbus_server.c
 *
 *  Created on: Mar 13, 2024
 *      Author: italo
 */

#include <AdapterSSD1306.h>
#include <stdio.h>
#include "modbus_server.h"
#include "cmsis_os.h"
#include "modbus_map.h"
#include "lwip/sockets.h"
#include "lwip/tcp.h"
#include "lwip/tcpip.h"


#define MODBUS_SERVER_TASK_STACK_SIZE  (2048)
#define MODBUS_SERVER_TCP_PORT         (22000)
#define MODBUS_SERVER_KEEP_ALIVE       (true)
#define MODBUS_SERVER_BUF_SIZE         (512)
#define keepidle                       (5)
#define keepintvl                      (5)
#define keepcnt                        (5)

#define KB_THRESHOLD 1024
#define MB_THRESHOLD (1024 * 1024)
#define GB_THRESHOLD (1024 * 1024 * 1024)

osThreadId modbusTcpServerTaskHandle;
uint32_t bytesTx = 0;
uint32_t bytesRx = 0;
Log_t log_notify;
//#define LOG(...)
#define LOG(fmt, ...) printf(fmt "\r\n", ##__VA_ARGS__)

//#define LOG2(...)
#define LOG2 LOG


static void ModbusStatusInfo(bool open)
{
	MenuData_t menu = {0};
	if (open)
	{

		sprintf(menu.items[PAGE_1][LINE_0], "CFG:CN:PORT:%d",MODBUS_SERVER_TCP_PORT);
	}
	else
	{
		sprintf(menu.items[PAGE_1][LINE_0], "CFG:DC:PORT:%d",MODBUS_SERVER_TCP_PORT);
	}

	AdapterSSD1306_SendDataToMenuQueueUpdate(&menu);
}




static void formatBytes(uint32_t bytes, char *str)
{

	if (bytes >= MB_THRESHOLD)
	{
		sprintf(str, "%.2f MBYTES", bytes / (float) MB_THRESHOLD);
	}
	else if (bytes >= KB_THRESHOLD)
	{
		sprintf(str, "%.2f KBYTES", bytes / (float) KB_THRESHOLD);
	}
	else
	{
		sprintf(str, "%lu BYTES", bytes);
	}
}

static void Modbus_infoPacket()
{
	MenuData_t menu = { 0 };
	char rx_str[17], tx_str[17];

	formatBytes(bytesRx, rx_str);
	formatBytes(bytesTx, tx_str);

	snprintf(menu.items[PAGE_1][LINE_1], sizeof(menu.items[PAGE_1][LINE_1]), "RX: %s", rx_str);
	snprintf(menu.items[PAGE_1][LINE_2], sizeof(menu.items[PAGE_1][LINE_2]), "TX: %s", tx_str);

	AdapterSSD1306_SendDataToMenuQueueUpdate(&menu);
}



static uint8_t ModbusHandleConnection(struct netconn *connfd)

{
	unsigned char recvBuffer[MODBUS_SERVER_BUF_SIZE];

	const int RECEIVE_TIMEOUT_MS = 1; // 1 segundo

	netconn_set_recvtimeout(connfd, RECEIVE_TIMEOUT_MS);

	do
	{
		// Receber dados do cliente com um tempo limite
		struct netbuf *inbuf;

		err_t err = netconn_recv(connfd, &inbuf);

		if (err == ERR_OK)
		{
			if (netconn_err(connfd) == ERR_OK)
			{
				/* Process received data */
				netbuf_copy(inbuf, recvBuffer, sizeof(recvBuffer));
				uint16_t buffer_len = netbuf_len(inbuf);

				Log_print(log_notify, Log_level_info, "Received %u bytes", buffer_len);


				bytesRx = bytesRx + buffer_len;

				uint16_t response_len = InterpreterMODBUS(recvBuffer, buffer_len);
				netconn_write(connfd, recvBuffer, response_len, NETCONN_COPY);

			    Log_print(log_notify, Log_level_info, "Send %u bytes", response_len);

				bytesTx = bytesTx + response_len;

				Modbus_infoPacket();

				netbuf_delete(inbuf);

			    osDelay(100);
				continue;
			}
		}
		else if(err == ERR_TIMEOUT)
		{

			continue;
		}else
		{

			break;
		}

		osDelay(10);

	} while (1);

	return 1;
}


void Modbus_activateTcpKeepAlive(struct netconn *connfd, int idleTime, int interval, int count) {

    if (connfd == NULL || connfd->type != NETCONN_TCP || connfd->pcb.tcp == NULL) {
        return;
    }
    struct tcp_pcb *pcb = connfd->pcb.tcp;

    LOCK_TCPIP_CORE();
    ip_set_option(connfd->pcb.ip, SO_KEEPALIVE);
    pcb->keep_idle = idleTime * 1000;    // Tempo de ociosidade em milissegundos
    pcb->keep_intvl = interval * 1000;   // Intervalo entre as tentativas em milissegundos
    pcb->keep_cnt = count;               // Número de tentativas
    UNLOCK_TCPIP_CORE();
}

void ModbusTcpSeverTask(void const *argument)
{
	/* USER CODE BEGIN TcpSeverTask */
	struct netconn *conn, *newconn;
	uint8_t i = MODBUS_CLOSED;


	/* Create a new TCP connection handle. */
	conn = netconn_new(NETCONN_TCP);

	/* Check if the connection handle was created successfully */
	if (conn == NULL)
	{
		/* Handle error */
	    LOG("Failed to create TCP connection handle");
		return;
	}

	/* Bind the connection to the specified port. */
	if (netconn_bind(conn, IP_ADDR_ANY, MODBUS_SERVER_TCP_PORT) != ERR_OK)
	{
		/* Handle error */
	    LOG("Failed to bind to port %d", MODBUS_SERVER_TCP_PORT);
		netconn_delete(conn);
		return;
	}

	/* Put the connection into LISTEN state. */
	if (netconn_listen(conn) != ERR_OK)
	{
		/* Handle error */
	    LOG("Failed to put the connection into LISTEN state");
		netconn_delete(conn);
		return;
	}


	Log_print(log_notify, Log_level_info, "TCP server listening on port: %d", MODBUS_SERVER_TCP_PORT);


	 ModbusStatusInfo(MODBUS_CLOSED);


	/* Infinite loop */
	for (;;)
	{
		if (i == MODBUS_CLOSED)
		{
			if (netconn_accept(conn, &newconn) == ERR_OK)
			{
				if (newconn != NULL)
				{
					i = MODBUS_OPEN;

					 ModbusStatusInfo(MODBUS_OPEN);
					/* Set keepalive options if enabled */
					if (MODBUS_SERVER_KEEP_ALIVE)
					{
						Modbus_activateTcpKeepAlive(newconn, keepidle,keepintvl, keepcnt);
					}
				}
			}
		}
		else
		{
			if (newconn != NULL && ModbusHandleConnection(newconn))
			{
				i = MODBUS_CLOSED;
				netconn_close(newconn);
				netconn_delete(newconn);
				bytesRx = 0;
				bytesTx = 0;
				AdapterSSD1306_Refresh(PAGE_1, LINE_1);
				AdapterSSD1306_Refresh(PAGE_1, LINE_2);
				ModbusStatusInfo(MODBUS_CLOSED);
				Modbus_infoPacket();
				LOG("Connection closed");
			}
		}

		/* Delay for a short period */
		osDelay(100);
	}
}



void ModbusServerInit()
{

  if (!Log_init (&log_notify, NOTIFY_LOGNAME, NOTIFY_LOGLEVEL_DEFAULT))
   {
     printf ("Failed to initialize Notify log "NOTIFY_LOGNAME""Log_newLine);
   }


	/* definition and creation of tcpServerTask */
	osThreadDef(tcpServerTask, ModbusTcpSeverTask, osPriorityBelowNormal, 0, MODBUS_SERVER_TASK_STACK_SIZE);
	modbusTcpServerTaskHandle = osThreadCreate(osThread(tcpServerTask), NULL);
}


