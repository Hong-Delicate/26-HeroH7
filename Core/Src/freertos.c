/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : freertos.c
  * Description        : Code for freertos applications
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
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
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
typedef StaticTask_t osStaticThreadDef_t;
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN Variables */

/* USER CODE END Variables */
/* Definitions for defaultTask */
osThreadId_t defaultTaskHandle;
uint32_t defaultTaskBuffer[ 128 ];
osStaticThreadDef_t defaultTaskControlBlock;
const osThreadAttr_t defaultTask_attributes = {
  .name = "defaultTask",
  .cb_mem = &defaultTaskControlBlock,
  .cb_size = sizeof(defaultTaskControlBlock),
  .stack_mem = &defaultTaskBuffer[0],
  .stack_size = sizeof(defaultTaskBuffer),
  .priority = (osPriority_t) osPriorityNormal,
};
/* Definitions for Chasis_Task */
osThreadId_t Chasis_TaskHandle;
uint32_t Chasis_TaskBuffer[ 512 ];
osStaticThreadDef_t Chasis_TaskControlBlock;
const osThreadAttr_t Chasis_Task_attributes = {
  .name = "Chasis_Task",
  .cb_mem = &Chasis_TaskControlBlock,
  .cb_size = sizeof(Chasis_TaskControlBlock),
  .stack_mem = &Chasis_TaskBuffer[0],
  .stack_size = sizeof(Chasis_TaskBuffer),
  .priority = (osPriority_t) osPriorityAboveNormal,
};
/* Definitions for Gimbal_Task */
osThreadId_t Gimbal_TaskHandle;
uint32_t Gimbal_TaskBuffer[ 512 ];
osStaticThreadDef_t Gimbal_TaskControlBlock;
const osThreadAttr_t Gimbal_Task_attributes = {
  .name = "Gimbal_Task",
  .cb_mem = &Gimbal_TaskControlBlock,
  .cb_size = sizeof(Gimbal_TaskControlBlock),
  .stack_mem = &Gimbal_TaskBuffer[0],
  .stack_size = sizeof(Gimbal_TaskBuffer),
  .priority = (osPriority_t) osPriorityAboveNormal,
};
/* Definitions for Shoot_Task */
osThreadId_t Shoot_TaskHandle;
uint32_t Shoot_TaskBuffer[ 512 ];
osStaticThreadDef_t Shoot_TaskControlBlock;
const osThreadAttr_t Shoot_Task_attributes = {
  .name = "Shoot_Task",
  .cb_mem = &Shoot_TaskControlBlock,
  .cb_size = sizeof(Shoot_TaskControlBlock),
  .stack_mem = &Shoot_TaskBuffer[0],
  .stack_size = sizeof(Shoot_TaskBuffer),
  .priority = (osPriority_t) osPriorityAboveNormal,
};

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

void StartDefaultTask(void *argument);
extern void chassis_task(void *argument);
extern void gimbal_task(void *argument);
extern void shoot_task(void *argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/**
  * @brief  FreeRTOS initialization
  * @param  None
  * @retval None
  */
void MX_FREERTOS_Init(void) {
  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* creation of defaultTask */
  defaultTaskHandle = osThreadNew(StartDefaultTask, NULL, &defaultTask_attributes);

  /* creation of Chasis_Task */
  Chasis_TaskHandle = osThreadNew(chassis_task, NULL, &Chasis_Task_attributes);

  /* creation of Gimbal_Task */
  Gimbal_TaskHandle = osThreadNew(gimbal_task, NULL, &Gimbal_Task_attributes);

  /* creation of Shoot_Task */
  Shoot_TaskHandle = osThreadNew(shoot_task, NULL, &Shoot_Task_attributes);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

  /* USER CODE BEGIN RTOS_EVENTS */
  /* add events, ... */
  /* USER CODE END RTOS_EVENTS */

}

/* USER CODE BEGIN Header_StartDefaultTask */
/**
  * @brief  Function implementing the defaultTask thread.
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END Header_StartDefaultTask */
void StartDefaultTask(void *argument)
{
  /* USER CODE BEGIN StartDefaultTask */
  /* Infinite loop */
  for(;;)
  {
    osDelay(1);
  }
  /* USER CODE END StartDefaultTask */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

/* USER CODE END Application */

