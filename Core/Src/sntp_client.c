/*
 * sntp_client.c
 *
 *  Created on: Sep 4, 2024
 *      Author: italo
 */


#include "lwip/apps/sntp.h"
#include "cmsis_os.h"
#include <sys/time.h>
#include <stdio.h>
#include "sntp_client.h"

#include "lwip/udp.h"
#include "lwip/tcp.h"
#include "sockets.h"
#include "api.h"


#define SNTP_CLIENT_TASK_STACK_SIZE  (2048)

osThreadId sntpClientTaskHandle;


void ntp_task(void *pvParameters)

{
  uint8_t data[48] =  { 0 };
  struct netconn *conn;
  struct netbuf *buf, *rxbuf;
  err_t err, recv_err;
  ip_addr_t dest_addr;
  uint16_t data_len;
  time_t timestamp = 0;
  struct tm timeinfo;

  /* Create a new connection identifier */
  conn = netconn_new(NETCONN_UDP);

  if (conn != NULL)
  {
	/* Bind connection to the port 7 */
	err = netconn_bind(conn, IP_ADDR_ANY, 7);

	if (err == ERR_OK)
	{
	  /* The destination IP address of the server */
	  IP_ADDR4(&dest_addr, 200, 160, 7, 186);

	  /* Infinite loop to send data every 10 seconds */
	  for (;;)
	  {
		data[0] = 0x1B;

		/* Connect to the destination (server) at port 123 */
		err = netconn_connect(conn, &dest_addr, 123);

		if (err == ERR_OK)
		{
		  /* Create a new netbuf */
		  buf = netbuf_new();
		  if (buf != NULL)
		  {
			/* Copy the data into the netbuf */
			netbuf_ref(buf, data, sizeof(data));

			/* Send the buffer to the connected UDP server */
			err = netconn_send(conn, buf);
			if (err == ERR_OK)
			{
			  printf("Buffer enviado com sucesso!\r\n");
			}
			else
			{
			  printf("Erro ao enviar o buffer: %d\r\n", err);
			}

			/* Free the buffer after sending */
			netbuf_delete(buf);
		  }

		  /* Optionally, receive response */
		  recv_err = netconn_recv(conn, &rxbuf);

		  if (recv_err == ERR_OK)
		  {
			void *data_ptr;
			netbuf_data(rxbuf, &data_ptr, &data_len);

			/* Copy received data */
			netbuf_copy(rxbuf, data, sizeof(data));

			/* Extract the timestamp and convert to UNIX format */
			timestamp = ntohl(*(u32_t *)&data[40]) - 2208988800U; // Subtract 70 years

			/* Adjust timestamp to São Paulo timezone (UTC-3) */
			timestamp -= 3 * 3600; // Subtract 3 hours

			/* Convert UNIX timestamp to `tm` structure adjusted to local timezone */
			localtime_r(&timestamp, &timeinfo);

			printf("Hora atual: %d-%02d-%02d %02d:%02d:%02d\r\n",
				(timeinfo.tm_year + 1900), (timeinfo.tm_mon + 1),
				 timeinfo.tm_mday, timeinfo.tm_hour, timeinfo.tm_min,
				 timeinfo.tm_sec);

			/* Free the received buffer */
			netbuf_delete(rxbuf);
			memset(data, 0x0, sizeof(data));
		  }

		  /* Disconnect the connection */
		  netconn_disconnect(conn);
		}
		else
		{
		  printf("Erro ao conectar: %d\r\n", err);
		}

		/* Wait for 10 seconds */
		osDelay(10000);
	  }
	}
	else
	{
	  printf("Erro ao fazer o bind da conexão: %d\r\n", err);
	}

	/* Close the connection and free the netconn structure */
	netconn_close(conn);
  }
  else
  {
	printf("Erro ao criar a conexão.\r\n");
  }
}






  void SntpClientInit()
  {

  	/* definition and creation of tcpServerTask */
  	osThreadDef(sntpClientTask, ntp_task, osPriorityBelowNormal, 0, SNTP_CLIENT_TASK_STACK_SIZE);
  	sntpClientTaskHandle = osThreadCreate(osThread(sntpClientTask), NULL);
  }



