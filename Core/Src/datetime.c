/*
 * datetime.c
 *
 *  Created on: Sep 10, 2024
 *      Author: italo
 */

#include "rtc.h"
#include "datetime.h"




char *DateTimeGetString ()
{
  struct tm tmTime = {0};
  RTC_TimeTypeDef sTime;
  RTC_DateTypeDef sDate;

  static char array[50];


  /* Get date time from RTC */

  HAL_RTC_GetTime(&hrtc, &sTime, RTC_FORMAT_BIN);
  HAL_RTC_GetDate(&hrtc, &sDate, RTC_FORMAT_BIN);

  tmTime.tm_hour = sTime.Hours;
  tmTime.tm_min = sTime.Minutes;
  tmTime.tm_sec = sTime.Seconds;
  tmTime.tm_mday = sDate.Date;
  tmTime.tm_mon = sDate.Month - 1;
  tmTime.tm_year = sDate.Year;

  // Usando strftime para formatar a data e a hora
     strftime(array, sizeof(array), DATETIME_STRINGFORMAT_DEFAULT, &tmTime);

    return array;

}



void DateTimeGetTm(struct tm *tmTime)
{
  RTC_TimeTypeDef sTime;
  RTC_DateTypeDef sDate;

  /* Get date time from RTC */

  HAL_RTC_GetTime(&hrtc, &sTime, RTC_FORMAT_BIN);
  HAL_RTC_GetDate(&hrtc, &sDate, RTC_FORMAT_BIN);

  tmTime->tm_hour = sTime.Hours;
  tmTime->tm_min = sTime.Minutes;
  tmTime->tm_sec = sTime.Seconds;
  tmTime->tm_mday = sDate.Date;
  tmTime->tm_mon = sDate.Month - 1;
  tmTime->tm_year = sDate.Year;

}




uint64_t DateTimeGet(void)
{

  RTC_TimeTypeDef sTime;
  RTC_DateTypeDef sDate;
  uint64_t dateTime;

  /* Get date time from RTC */

    HAL_RTC_GetTime(&hrtc, &sTime, RTC_FORMAT_BIN);
    HAL_RTC_GetDate(&hrtc, &sDate, RTC_FORMAT_BIN);
 // SNVS_LP_SRTC_GetDatetime(SNVS_PERIPHERAL, &SNVS_dateTimeStruct);

  /* rtc time struct to ms */
  struct tm tmTime;

  tmTime.tm_hour = sTime.Hours;
  tmTime.tm_min = sTime.Minutes;
  tmTime.tm_sec = sTime.Seconds;
  tmTime.tm_mday = sDate.Date;
  tmTime.tm_mon = sDate.Month - 1;
  tmTime.tm_year = sDate.Year + 100;

  /* Convert struct tm to time_t */
  time_t newDate = mktime(&tmTime);

  /* Set system datetime from RTC value */
  dateTime = (uint64_t) (newDate * 1000);

  return dateTime;

}



void DateTimeSetTm(struct tm* tmTime)
{

  RTC_TimeTypeDef sTime = { 0 };
  RTC_DateTypeDef sDate = { 0 };

  sDate.Year = tmTime->tm_year;
  sDate.Date = tmTime->tm_mday;
  sDate.Month = tmTime->tm_mon + 1;
  sTime.Hours = tmTime->tm_hour;
  sTime.Minutes = tmTime->tm_min;
  sTime.Seconds = tmTime->tm_sec;
  sTime.DayLightSaving = 0;

  if (HAL_RTC_SetTime(&hrtc, &sTime, RTC_FORMAT_BIN) != HAL_OK)
  {

	//printf("Erro ao configurar a hora no RTC \r\n");
	return;
  }

  if (HAL_RTC_SetDate(&hrtc, &sDate, RTC_FORMAT_BIN) != HAL_OK)
  {

	//printf("Erro ao configurar a data no RTC \r\n");
	return;
  }

}

void DateTimeSet (uint64_t newDateTime_ms)
{

  //OSA_InterruptDisable(); // Disable interrupts to make this atomic function

  RTC_TimeTypeDef sTime = { 0 };
  RTC_DateTypeDef sDate = { 0 };
  struct tm tmTime;

  /* Convert timestamp to time_t and ms */
  time_t timeVal = newDateTime_ms / 1000;

  /* Convert timeVal to struct tm */
  gmtime_r(&timeVal, &tmTime);

  sDate.Year = tmTime.tm_year - 100;
  sDate.Date = tmTime.tm_mday;
  sDate.Month = tmTime.tm_mon + 1;
  sTime.Hours = tmTime.tm_hour;
  sTime.Minutes = tmTime.tm_min;
  sTime.Seconds = tmTime.tm_sec;
  sTime.DayLightSaving = 0;

  if (HAL_RTC_SetTime(&hrtc, &sTime, RTC_FORMAT_BIN) != HAL_OK)
  {

	//printf("Erro ao configurar a hora no RTC \r\n");
	return;
  }

  if (HAL_RTC_SetDate(&hrtc, &sDate, RTC_FORMAT_BIN) != HAL_OK)
  {

	//printf("Erro ao configurar a data no RTC \r\n");
	return;
  }
  // Check callbacks

  //OSA_InterruptEnable();  // Enable interrupts
}





