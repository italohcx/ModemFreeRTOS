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
#include "api.h"
#include "logger.h"

#define NOTIFY_LOGNAME                   "MbServer"
#define NOTIFY_LOGLEVEL_DEFAULT          Log_level_trace


enum
{
  MODBUS_CLOSED,
  MODBUS_OPEN
};


/**
 * @fn void FTPServerInit()
 * @brief init FTP server
 */
void ModbusServerInit();

void ModbusServerTaskFunc(void *pvParameters);

#endif /* INC_MODBUS_SERVER_H_ */
