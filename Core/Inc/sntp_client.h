/*
 * sntp_client.h
 *
 *  Created on: Sep 4, 2024
 *      Author: italo
 */

#ifndef INC_SNTP_CLIENT_H_
#define INC_SNTP_CLIENT_H_

#include "main.h"


#define SNTP_CLIENT_LOGNAME                   "sntp"
#define SNTP_CLIENT_LOGLEVEL_DEFAULT          Log_level_trace

void SntpClientInit();

#endif /* INC_SNTP_CLIENT_H_ */
