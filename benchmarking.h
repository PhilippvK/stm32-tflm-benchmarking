/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under Ultimate Liberty license
  * SLA0044, the "License"; You may not use this file except in compliance with
  * the License. You may obtain a copy of the License at:
  *                             www.st.com/SLA0044
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef SRC_MISC_BENCHMARKING_H_
#define SRC_MISC_BENCHMARKING_H_

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/

/* Exported types ------------------------------------------------------------*/

/* Exported constants --------------------------------------------------------*/

/* Exported macro ------------------------------------------------------------*/
// Inspired by :https://aishack.in/tutorials/timing-macros/
#ifdef BENCHMARKING
#define DECLARE_BENCHMARK(s)\
  uint32_t timeStart_##s;\
  uint32_t timeDiff_##s;\
  static uint32_t timeTotal_##s = 0;\
  static uint32_t countTotal_##s = 0;\
  static uint32_t timeMin_##s = 4294967295;\
  static uint32_t timeMax_##s = 0;

#define START_BENCHMARK(s)\
  timeStart_##s = HAL_GetTick()

#define STOP_BENCHMARK(s)\
  timeDiff_##s = HAL_GetTick() - timeStart_##s;\
  timeTotal_##s += timeDiff_##s;\
  countTotal_##s++;\
  timeMin_##s = timeDiff_##s < timeMin_##s ? timeDiff_##s : timeMin_##s;\
  timeMax_##s = timeDiff_##s > timeMax_##s ? timeDiff_##s : timeMax_##s

#define GET_BENCHMARK_CURRENT_MS(s)\
  (uint32_t)(timeDiff_##s / HAL_GetTickFreq())

#define GET_BENCHMARK_MIN_MS(s)\
  (uint32_t)(timeMin_##s / HAL_GetTickFreq())

#define GET_BENCHMARK_MAX_MS(s)\
  (uint32_t)(timeMax_##s / HAL_GetTickFreq())

#define GET_BENCHMARK_AVG_MS(s)\
  (uint32_t)(countTotal_##s ? timeTotal_##s / (countTotal_##s * HAL_GetTickFreq()) : 0)

#define RESET_BENCHMARK(s)\
  timeTotal_##s = 0;\
  countTotal_##s = 0;\
  timeMin_##s = 0;\
  timeMax_##s = 0;

#define PRINT_BENCHMARK(s)\
  fprintf(stderr,\
      "%s_ms(cur/min/max/avg)=%ld/%ld/%ld/%ld\n\r",\
      #s,\
      GET_BENCHMARK_CURRENT_MS(s),\
      GET_BENCHMARK_MIN_MS(s),\
      GET_BENCHMARK_MAX_MS(s),\
      GET_BENCHMARK_AVG_MS(s)\
  )

#define PRINT_TIMESTAMP() fprintf(stderr,"Time: %ld ms:\n\r", HAL_GetTick()/HAL_GetTickFreq())
#else
#define DECLARE_BENCHMARK(s)
#define START_BENCHMARK(s)
#define STOP_BENCHMARK(s)
#define GET_BENCHMARK_CURRENT_MS(s)
#define GET_BENCHMARK_AVERAGE_MS(s)
#define GET_BENCHMARK_MIN_MS(s)
#define GET_BENCHMARK_MAX_MS(s)
#define RESET_BENCHMARK(s)
#define PRINT_BENCHMARK(s)
#define PRINT_TIMESTAMP()
#endif /* BENCHMARKING */

/* Exported functions prototypes ---------------------------------------------*/
//void print_summary(int types);

/* Private defines -----------------------------------------------------------*/

#ifdef __cplusplus
}
#endif
// Record the execution time of some code, in milliseconds.

#endif  // SRC_MISC_BENCHMARKING_H_
