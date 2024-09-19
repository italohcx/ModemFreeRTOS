/*
 * sntp_client.c
 *
 *  Created on: Sep 4, 2024
 *      Author: italo
 */
#include "sntp_client.h"
#include "lwip/apps/sntp.h"
#include "cmsis_os.h"
#include <sys/time.h>
#include <stdio.h>
#include "lwip/udp.h"
#include "lwip/tcp.h"
#include "sockets.h"
#include "api.h"
#include "datetime.h"
#include "logger.h"

#define SNTP_CLIENT_TASK_STACK_SIZE  (256)
#define SNTP_SERVER_IP "200.160.7.186"
#define SNTP_SERVER_PORT 123

osThreadId sntpClientTaskHandle;
Log_t log_sntp;


err_t SntpSendRequest(struct netconn *conn)
{
  uint8_t data[48] = { 0 };
  err_t err;
  struct netbuf *buf;
  data[0] = 0x1B;

  /* Create a new netbuf */
  buf = netbuf_new();

  if (buf != NULL)
  {
	/* Copy the data into the netbuf */
	netbuf_ref(buf, data, sizeof(data));

	/* Send the buffer to the connected UDP server */
	err = netconn_send(conn, buf);

	/* Free the buffer after sending */
	netbuf_delete(buf);

  }

  return err;
}

err_t SntpRecevRequest(struct netconn *conn)
{
  uint8_t data[48] = { 0 };
  time_t timestamp = 0;
  struct tm timeinfo;
  err_t recv_err;
  struct netbuf *rxbuf;
  uint16_t data_len;

  /* Optionally, receive response */
  recv_err = netconn_recv(conn, &rxbuf);
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

  Log_print(log_sntp, Log_level_trace, "TimeStamp: %d-%02d-%02d %02d:%02d:%02d",
	  (timeinfo.tm_year + 1900), (timeinfo.tm_mon + 1), timeinfo.tm_mday,
	  timeinfo.tm_hour, timeinfo.tm_min, timeinfo.tm_sec);

  /* Set hardware RTC */
  DateTimeSetTm(&timeinfo);

  /* Free the received buffer */
  netbuf_delete(rxbuf);

  /*Free buffer*/
  memset(data, 0x0, sizeof(data));

  return recv_err;
}



void SntpClientTask(void *pvParameters)

{
  /*Delay before init */
  osDelay(2000);
  struct netconn *conn;
  ip_addr_t dest_addr;

  /* Create a new connection identifier */
  conn = netconn_new(NETCONN_UDP);

  if (conn != NULL)
  {
	/* Bind connection to the port 7 */
	if (netconn_bind(conn, IP_ADDR_ANY, 7) == ERR_OK)
	{
	  /* The destination IP address of the server */
	  ipaddr_aton(SNTP_SERVER_IP, &dest_addr);

	  //IP_ADDR4(&dest_addr, 200, 160, 7, 186);
	  for (;;)
	  {
		/* Connect to the destination (server) */
		if (netconn_connect(conn, &dest_addr, SNTP_SERVER_PORT) == ERR_OK)
		{

		  Log_print(log_sntp, Log_level_info, "Connected in server SNTP:%s Port:%d", SNTP_SERVER_IP,  SNTP_SERVER_PORT);

		  /*Request TimeStamp from server*/
		  if (SntpSendRequest(conn) == ERR_OK)
		  {
			Log_print(log_sntp, Log_level_debug, "Send server Timestamp request");
		  }
		  else
		  {
			Log_print(log_sntp, Log_level_error, "Error to send timeStamp request");
		  }

		  /*Received TimeStamp from server*/
		  if (SntpRecevRequest(conn) == ERR_OK)
		  {
			Log_print(log_sntp, Log_level_debug, "Received server response");
		  }
		  else
		  {
			Log_print(log_sntp, Log_level_error, "Received server response error");
		  }

		  /* Disconnect the connection */
		  netconn_disconnect(conn);
		}
		else
		{
		  Log_print(log_sntp, Log_level_error, "Server connected error");
		}

		/* Wait for 10 minutes */
		osDelay(100000);
	  }
	}
	else
	{
	  Log_print(log_sntp, Log_level_error, "Bind connect error");
	}

	/* Close the connection and free the netconn structure */
	netconn_close(conn);
  }
  else
  {
	Log_print(log_sntp, Log_level_error, "Error to create connection");
  }
}



  void SntpClientInit()
{

  if (!Log_init(&log_sntp, SNTP_CLIENT_LOGNAME, SNTP_CLIENT_LOGLEVEL_DEFAULT))
  {

  printf ("Failed to initialize log "SNTP_CLIENT_LOGNAME""Log_newLine);

  }

  /* definition and creation of tcpServerTask */
  osThreadDef(sntpClientTask, SntpClientTask, osPriorityBelowNormal, 0,SNTP_CLIENT_TASK_STACK_SIZE);
  sntpClientTaskHandle = osThreadCreate(osThread(sntpClientTask), NULL);


}



