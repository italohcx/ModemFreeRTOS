/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    rtc.c
  * @brief   This file provides code for the configuration
  *          of the RTC instances.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "rtc.h"

/* USER CODE BEGIN 0 */
#include "time.h"
/* USER CODE END 0 */

RTC_HandleTypeDef hrtc;

/* RTC init function */
void MX_RTC_Init(void)
{

  /* USER CODE BEGIN RTC_Init 0 */

  /* USER CODE END RTC_Init 0 */

  /* USER CODE BEGIN RTC_Init 1 */

  /* USER CODE END RTC_Init 1 */

  /** Initialize RTC Only
  */
  hrtc.Instance = RTC;
  hrtc.Init.HourFormat = RTC_HOURFORMAT_24;
  hrtc.Init.AsynchPrediv = 127;
  hrtc.Init.SynchPrediv = 255;
  hrtc.Init.OutPut = RTC_OUTPUT_DISABLE;
  hrtc.Init.OutPutPolarity = RTC_OUTPUT_POLARITY_HIGH;
  hrtc.Init.OutPutType = RTC_OUTPUT_TYPE_OPENDRAIN;
  if (HAL_RTC_Init(&hrtc) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN RTC_Init 2 */

  /* USER CODE END RTC_Init 2 */

}

void HAL_RTC_MspInit(RTC_HandleTypeDef* rtcHandle)
{

  RCC_PeriphCLKInitTypeDef PeriphClkInitStruct = {0};
  if(rtcHandle->Instance==RTC)
  {
  /* USER CODE BEGIN RTC_MspInit 0 */

  /* USER CODE END RTC_MspInit 0 */

  /** Initializes the peripherals clock
  */
    PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_RTC;
    PeriphClkInitStruct.RTCClockSelection = RCC_RTCCLKSOURCE_LSE;
    if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct) != HAL_OK)
    {
      Error_Handler();
    }

    /* RTC clock enable */
    __HAL_RCC_RTC_ENABLE();
  /* USER CODE BEGIN RTC_MspInit 1 */

  /* USER CODE END RTC_MspInit 1 */
  }
}

void HAL_RTC_MspDeInit(RTC_HandleTypeDef* rtcHandle)
{

  if(rtcHandle->Instance==RTC)
  {
  /* USER CODE BEGIN RTC_MspDeInit 0 */

  /* USER CODE END RTC_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_RTC_DISABLE();
  /* USER CODE BEGIN RTC_MspDeInit 1 */

  /* USER CODE END RTC_MspDeInit 1 */
  }
}

/* USER CODE BEGIN 1 */
uint64_t getCurrentTimeRTC(void)
{
  RTC_TimeTypeDef sTime;
  RTC_DateTypeDef sDate;
  struct tm ts = {0};
  time_t now, ms;

  //do
  {
    HAL_RTC_GetTime(&hrtc, &sTime, RTC_FORMAT_BIN);
    HAL_RTC_GetDate(&hrtc, &sDate, RTC_FORMAT_BIN);
  }
  //while (hrtc.Instance->SSR != sTime.SubSeconds);
  ms = 1000L * (sTime.SecondFraction - sTime.SubSeconds) / (sTime.SecondFraction + 1);

  ts.tm_year = sDate.Year + 100;  // In fact: 2000 + 18 - 1900
  ts.tm_mday = sDate.Date;
  ts.tm_mon  = sDate.Month - 1;

  ts.tm_hour = sTime.Hours;
  ts.tm_min  = sTime.Minutes;
  ts.tm_sec  = sTime.Seconds;
  ts.tm_isdst = 0;
  now = (mktime(&ts) * 1000L) + ms;


  // Exibir a data completa no console
//   printf("Data data: %04d-%02d-%02d %02d:%02d:%02d.%03ld \r\n",
//          ts.tm_year + 1900, ts.tm_mon + 1, ts.tm_mday,
//          ts.tm_hour, ts.tm_min, ts.tm_sec, ms);


  return(now);
}


void setCurrentTimeRTC(uint64_t now)
{
  RTC_TimeTypeDef sTime = {0};
  RTC_DateTypeDef sDate = {0};
  struct tm *ts;
  time_t tnow;//, ms;

  // Converta o timestamp para struct tm
  tnow = now / 1000L;
  ts = localtime(&tnow);

  // Calcule os milissegundos
  //ms = now - (tnow * 1000L);

  // Configure a struct tm
  ts->tm_isdst = 0;
  sDate.Year = ts->tm_year - 100;
  sDate.Date = ts->tm_mday;
  sDate.Month = ts->tm_mon + 1;
  sTime.Hours = ts->tm_hour;
  sTime.Minutes = ts->tm_min;
  sTime.Seconds = ts->tm_sec;
  sTime.DayLightSaving = 0;


  if (HAL_RTC_SetTime(&hrtc, &sTime, RTC_FORMAT_BIN) != HAL_OK) {

    //printf("Erro ao configurar a hora no RTC \r\n");
    return;
  }

  if (HAL_RTC_SetDate(&hrtc, &sDate, RTC_FORMAT_BIN) != HAL_OK) {

    //printf("Erro ao configurar a data no RTC \r\n");
    return;
  }
}


/* USER CODE END 1 */
