/*
 * modbus_server.c
 *
 *  Created on: Mar 13, 2024
 *      Author: italo
 */


#include "modbus_server.h"
#include "cmsis_os.h"
#include "modbus_map.h"
#include "lwip/sockets.h"
#include "lwip/tcp.h"


#define MODBUS_SERVER_TASK_STACK_SIZE  (1024)
#define MODBUS_SERVER_TCP_PORT         (22000)
#define MODBUS_SERVER_KEEP_ALIVE       (true)
#define MODBUS_SERVER_BUF_SIZE         (512)
#define keepidle                       (5)
#define keepintvl                      (5)
#define keepcnt                        (5)

osThreadId modbusTcpServerTaskHandle;




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
				uint16_t response_len = InterpreterMODBUS(recvBuffer, buffer_len);
				netconn_write(connfd, recvBuffer, response_len, NETCONN_COPY);
				netbuf_delete(inbuf);
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

		osDelay(1);

	} while (1);

	return 1;
}


void Modbus_activateTcpKeepAlive(struct netconn *connfd, int idleTime, int interval, int count) {

    if (connfd == NULL || connfd->type != NETCONN_TCP || connfd->pcb.tcp == NULL) {
        return;
    }
    struct tcp_pcb *pcb = connfd->pcb.tcp;


    ip_set_option(connfd->pcb.ip, SO_KEEPALIVE);
    pcb->keep_idle = idleTime * 1000;    // Tempo de ociosidade em milissegundos
    pcb->keep_intvl = interval * 1000;   // Intervalo entre as tentativas em milissegundos
    pcb->keep_cnt = count;               // Número de tentativas

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
		printf("Failed to create TCP connection handle\r\n");
		return;
	}


	/* Bind the connection to the specified port. */
	if (netconn_bind(conn, IP_ADDR_ANY, MODBUS_SERVER_TCP_PORT) != ERR_OK)
	{
		/* Handle error */
		printf("Failed to bind to port %d\r\n", MODBUS_SERVER_TCP_PORT);
		netconn_delete(conn);
		return;
	}

	/* Put the connection into LISTEN state. */
	if (netconn_listen(conn) != ERR_OK)
	{
		/* Handle error */
		printf("Failed to put the connection into LISTEN state \r\n");
		netconn_delete(conn);
		return;
	}

	printf("TCP server listening on port %d \r\n", MODBUS_SERVER_TCP_PORT);

	/* Infinite loop */
	for (;;)
	{
		if (i == MODBUS_CLOSED)
		{
			if (netconn_accept(conn, &newconn) == ERR_OK)
			{
				if (newconn != NULL)
				{
					printf("Valid pointer \r\n");
					i = MODBUS_OPEN;

					/* Set keepalive options if enabled */
					if (MODBUS_SERVER_KEEP_ALIVE)
					{
						Modbus_activateTcpKeepAlive(newconn, keepidle, keepintvl, keepcnt);
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
				printf("Connection closed \r\n");
			}
		}

		/* Delay for a short period */
		osDelay(100);
	}
}





void ModbusServerInit()
{
	/* definition and creation of tcpServerTask */
	LoadHoldingRegisterRAM();
	LoadInputRegisterRAM();
	LoadEspelhoRAM();
	osThreadDef(tcpServerTask, ModbusTcpSeverTask, osPriorityBelowNormal, 0, MODBUS_SERVER_TASK_STACK_SIZE);
	modbusTcpServerTaskHandle = osThreadCreate(osThread(tcpServerTask), NULL);
}


