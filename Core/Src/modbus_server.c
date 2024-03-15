/*
 * modbus_server.c
 *
 *  Created on: Mar 13, 2024
 *      Author: italo
 */


#include "modbus_server.h"
#include "cmsis_os.h"
#include "modbus_map.h"


#define MODBUS_SERVER_TASK_STACK_SIZE  (1024)
#define MODBUS_SERVER_TCP_PORT         (22000)
#define MODBUS_SERVER_KEEP_ALIVE       (true)
#define BLOCK_SIZE                     (512)
#define FTP_REQUEST_SPACE              (512)
#define keepidle                       (10)  // Idle time before sending keepalive probes (in seconds)
#define keepintvl                      (5)   // Interval between keepalive probes (in seconds)
#define keepcnt                        (3)   // Number of keepalive probes before the connection is considered lost

osThreadId modbusTcpServerTaskHandle;


static uint8_t ModbusHandleConnection(struct netconn *connfd)

{
	const uint32_t TIMEOUT_MS = 10000; // 10 segundos
	unsigned char recvBuffer[512];
	struct timeval timeout;
	timeout.tv_sec = TIMEOUT_MS / 1000;
	timeout.tv_usec = (TIMEOUT_MS % 1000) * 1000;

	lwip_setsockopt(connfd->socket, SOL_SOCKET, SO_RCVTIMEO, &timeout,sizeof(timeout));

	/* Loop até que o cliente se desconecte ou ocorra um erro */
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
		else
		{
			break;

		}

		osDelay(1);

	} while (1);

	return 1;

}


void Modbus_activateTcpKeepAlive(struct netconn *connfd, int idleTime, int interval, int count)
{
    int optval;
    socklen_t optlen = sizeof(optval);

    // Enable SO_KEEPALIVE
    optval = 1;
    if (lwip_setsockopt(connfd->socket, SOL_SOCKET, SO_KEEPALIVE, &optval, optlen) < 0) {
    	 printf("Failed to set SO_KEEPALIVE option");
        // Handle error
    }

    // Set TCP_KEEPIDLE
    optval = idleTime;
    if (lwip_setsockopt(connfd->socket, IPPROTO_TCP, TCP_KEEPIDLE, &optval, optlen) < 0) {
    	 printf("Failed to set TCP_KEEPIDLE option");
        // Handle error
    }

    // Set TCP_KEEPINTVL
    optval = interval;
    if (lwip_setsockopt(connfd->socket, IPPROTO_TCP, TCP_KEEPINTVL, &optval, optlen) < 0) {
    	 printf("Failed to set TCP_KEEPINTVL option");
        // Handle error
    }

    // Set TCP_KEEPCNT
    optval = count;
    if (lwip_setsockopt(connfd->socket, IPPROTO_TCP, TCP_KEEPCNT, &optval, optlen) < 0) {
    	 printf("Failed to set TCP_KEEPCNT option");
        // Handle error
    }
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

				if (newconn != NULL) {

					printf("Is vali pointer \r\n");
				}


				i = MODBUS_OPEN;
				printf("New connection established \r\n");

				/* Set keepalive options if enabled */
				if (MODBUS_SERVER_KEEP_ALIVE)
				{
					Modbus_activateTcpKeepAlive(newconn, keepidle, keepintvl, keepcnt);
				}
			}
		}
		else
		{
			if (ModbusHandleConnection(newconn))
			{
				i = MODBUS_CLOSED;
				netconn_close(newconn);
				netconn_delete(newconn);
				printf("Conection closed \r\n");
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


