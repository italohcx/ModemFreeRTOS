/*
 * datetime.h
 *
 *  Created on: Sep 10, 2024
 *      Author: italo
 */

#ifndef INC_DATETIME_H_
#define INC_DATETIME_H_

#include "time.h"


#define DATETIME_SIZE_STR             33
#define DATETIME_STRINGFORMAT_DEFAULT "%d/%m/%Y %H:%M:%S"

void DateTimeSet (uint64_t newDateTime_ms);
void DateTimeSetTm(struct tm* tmTime);
void DateTimeGetTm(struct tm *tmTime);

/**
 * @brief convert the current date and time UTC in milliseconds since 1/1/1970 00:00:00.000 to C string
 * @param output where to put result
 * @param maxSize max size that can be saved on output
 */
char *DateTimeGetString ();
#endif /* INC_DATETIME_H_ */
