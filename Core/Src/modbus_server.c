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
#define MODBUS_SERVER_KEEP_ALIVE       (false)
#define BLOCK_SIZE                      512
#define FTP_REQUEST_SPACE               512
static char *ResponseBuffer;
osThreadId modbusTcpServerTaskHandle;


static uint8_t ModbusHandleConnection(struct netconn *connfd, uint8_t *alloc_rq)

{

	/* Definir um tempo limite de recebimento (em milissegundos) */
	const uint32_t TIMEOUT_MS = 10000; // 10 segundos
	char msg[512];
	/* Definir um tempo limite para o socket TCP */
	struct timeval timeout;
	timeout.tv_sec = TIMEOUT_MS / 1000;
	timeout.tv_usec = (TIMEOUT_MS % 1000) * 1000;
	lwip_setsockopt(connfd->socket, SOL_SOCKET, SO_RCVTIMEO, &timeout,sizeof(timeout));

	/* Loop até que o cliente se desconecte ou ocorra um erro */
	while (1)
 	{
		// Receber dados do cliente com um tempo limite
		struct netbuf *inbuf;

		err_t err = netconn_recv(connfd, &inbuf);


	    if (err == ERR_OK)
		{
			if (netconn_err(connfd) == ERR_OK)
			{
				/* Process received data */
				netbuf_copy(inbuf, msg, sizeof(msg));
				u16_t buffer_len = netbuf_len(inbuf);
				printf("Received data: %s\r\n", msg);
				InterpreterMODBUS(msg, buffer_len);

				// Enviar a resposta de volta para o cliente
				 netconn_write(connfd, msg, buffer_len, NETCONN_COPY);


				netbuf_delete(inbuf);
				continue;
			}

		}else {

			break;

		}







//		// Verificar se ocorreu um erro
//		if (err != ERR_OK)
//		{
//			if (err == ERR_TIMEOUT)
//			{
//				// Tempo limite de recebimento atingido, verifique a conexão
//				if (netconn_err(connfd) == ERR_OK)
//				{
//					 InterpreterMODBUS(msg, err);
//
//					continue;
//				}
//				else
//				{
//					// Ocorreu um erro de conexão, o cliente se desconectou
//					break;
//				}
//			}
//			else
//			{
//				break;
//			}
//		}

		// Processar os dados recebidos (se necessário)



		osDelay(1);
	}

	// Se saímos do loop, significa que a conexão foi encerrada ou ocorreu um erro
	return 1; // Retornar 1 para indicar que a conexão foi fechada

}






void ModbusTcpSeverTask(void const *argument)
{
	/* USER CODE BEGIN TcpSeverTask */
	struct netconn *conn, *newconn;
	struct netbuf *buf;
	uint8_t *alloc_rq;
	char msg[256];
	uint8_t i = MODBUS_CLOSED;/*keep session information*/

	  if (((ResponseBuffer = (char*) malloc(BLOCK_SIZE)) == NULL) || ((alloc_rq = (uint8_t*) malloc( FTP_REQUEST_SPACE)) == NULL))
	  {
	    free(ResponseBuffer);
	    free(alloc_rq);
	    /*Task no longer needed, delete it!*/
	    vTaskDelete( NULL);
	  }


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
		printf("Failed to put the connection into LISTEN state\r\n");
		netconn_delete(conn);
		return;
	}

	printf("TCP server listening on port %d\r\n", MODBUS_SERVER_TCP_PORT);

	/* Infinite loop */
	for (;;)
	{
		if (i == MODBUS_CLOSED)

		{
			if (netconn_accept(conn, &newconn) == ERR_OK)
			{

				i = MODBUS_OPEN;
				printf("New connection established\r\n");

				/* Set keepalive options if enabled */
				if (MODBUS_SERVER_KEEP_ALIVE)
				{
					int keepalive = 1; // Enable keepalive
					int keepidle = 10; // Idle time before sending keepalive probes (in seconds)
					int keepintvl = 5; // Interval between keepalive probes (in seconds)
					int keepcnt = 3; // Number of keepalive probes before the connection is considered lost

					/* Set keepalive options on the listening socket */
					if (lwip_setsockopt(conn->socket, SOL_SOCKET, SO_KEEPALIVE, &keepalive, sizeof(keepalive)) != ERR_OK
							|| lwip_setsockopt(conn->socket, IPPROTO_TCP,TCP_KEEPIDLE, &keepidle, sizeof(keepidle)) != ERR_OK
							|| lwip_setsockopt(conn->socket, IPPROTO_TCP,TCP_KEEPINTVL, &keepintvl, sizeof(keepintvl))!= ERR_OK
							|| lwip_setsockopt(conn->socket, IPPROTO_TCP,TCP_KEEPCNT, &keepcnt, sizeof(keepcnt)) != ERR_OK)
					{
						/* Handle error */
						printf("Failed to set keepalive options\r\n");
						//netconn_close(conn);
						//netconn_delete(conn);
						return;
					}
				}
			}
		}
		else
		{
			if (ModbusHandleConnection(newconn, alloc_rq))
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


uint16_t netconn_rcv_req(void *connec, uint8_t *alloc_rq, void **nbuffer, uint8_t flag)
{
  /*joining temp pbuf*/
  struct netbuf *inbuf;
  struct pbuf *q;

  struct netconn *conn = (struct netconn*) connec;

  /*temporal len*/
  uint16_t len = 0;

  /*FSL: receive the packet*/
  err_t err = netconn_recv(conn, &inbuf);

  /*receiving from the buffer*/
  if (err == ERR_OK)
  {
    /*if receiver is expecting a big rx packet, use it directly from the network buffers*/
    if (flag)
    {
      /*use buffer directly from lwIP network buffers*/
      len = inbuf->ptr->tot_len;
      *nbuffer = (void*) inbuf;
      return len;
    }

    /*if not you can copy it to a small buffer*/

    /*start segment index*/
    q = inbuf->ptr;
    do
    {
      memcpy(&alloc_rq[len], q->payload, q->len);
      len += q->len;
    }
    while ((q = q->next) != NULL);

    /*NULL char terminator. Useful for ASCII transfers*/
    alloc_rq[len] = '\0';

    /*free pbuf memory*/
    netbuf_delete(inbuf);
  }

  return len;/*return value*/
}



void ModbusServerInit()
{
	/* definition and creation of tcpServerTask */
	osThreadDef(tcpServerTask, ModbusTcpSeverTask, osPriorityBelowNormal, 0, MODBUS_SERVER_TASK_STACK_SIZE);
	modbusTcpServerTaskHandle = osThreadCreate(osThread(tcpServerTask), NULL);
}


