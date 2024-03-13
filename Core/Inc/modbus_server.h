/*
 * modbus_server.h
 *
 *  Created on: Mar 13, 2024
 *      Author: italo
 */

#ifndef INC_MODBUS_SERVER_H_
#define INC_MODBUS_SERVER_H_

#include "stdint.h"
#include "api.h"
#include "sockets.h"
#include "stdbool.h"

enum
{
  MODBUS_CLOSED,
  MODBUS_OPEN
};





uint16_t netconn_rcv_req(void *connec, uint8_t *alloc_rq, void **nbuffer, uint8_t flag);
void ModbusServerTaskFunc(void *pvParameters);

/**
 * @fn void FTPServerInit()
 * @brief init FTP server
 */
void ModbusServerInit();

#endif /* INC_MODBUS_SERVER_H_ */
