/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
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
#include "main.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <stdbool.h>
#include <string.h>
#include "kernel.h"
#include "task.h"
#include "lcd.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
static void Kernel_init(void);

void User_task0(void);
void User_task1(void);
void User_task2(void);

void HAL_Delay(uint32_t Delay);
/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */
  //JIRA와 github 연동 테스트 1
  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_USART1_UART_Init();
  /* USER CODE BEGIN 2 */
  LL_USART_EnableIT_RXNE(USART1);
  vPrintString("simpleRTOS starting ... \r\n");
  Kernel_init();
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */
static void Kernel_init(void)
{
	uint32_t taskId;

	Kernel_task_init();
	Kernel_event_flag_init();
	Kernel_msgQ_init();

	taskId = Kernel_task_create(User_task0);
	if(NOT_ENOUGH_TASK_NUM == taskId){
		vPrintString("Task0 creation fail \r\n");
	}

	taskId = Kernel_task_create(User_task1);
	if(NOT_ENOUGH_TASK_NUM == taskId){
		vPrintString("Task1 creation fail \r\n");
	}

	taskId = Kernel_task_create(User_task2);
	if(NOT_ENOUGH_TASK_NUM == taskId){
		vPrintString("Task2 creation fail \r\n");
	}

	Kernel_start();
}

void User_task0(void)
{
	vPrintString("User task #0 \r\n");

	uint8_t cmdBuf[16];
	uint32_t cmdBufIdx = 0;
	uint8_t uartch= 0;

	while(true){
		KernelEventFlag_t handle_event = Kernel_wait_events(KernelEventFlag_UartIn);
		switch(handle_event){
		case KernelEventFlag_UartIn:
			//vPrintString("\r\nEvent handled \r\n");
			Kernel_recv_msg(KernelMsgQ_Task0, &uartch, 1);
			if(uartch == '\n'){
				cmdBuf[cmdBufIdx] = '\0';

				//Kernel_send_msg(KernelMsgQ_Task1, &cmdBufIdx, 1);
				//Kernel_send_msg(KernelMsgQ_Task1, cmdBuf, cmdBufIdx);
				//Kernel_send_events(KernelEventFlag_CmdIn);
				while(true){
					Kernel_send_events(KernelEventFlag_CmdIn);
					if(false == Kernel_send_msg(KernelMsgQ_Task1, &cmdBufIdx, 1)){
						Kernel_yield();
					}
					else if(false == Kernel_send_msg(KernelMsgQ_Task1, cmdBuf, cmdBufIdx)){
						uint8_t rollback;
						Kernel_recv_msg(KernelMsgQ_Task1, &rollback, 1);
						Kernel_yield();
					}
					else{
						break;
					}
				}

				cmdBufIdx = 0;
			}
			else{
				cmdBuf[cmdBufIdx] = uartch;
				cmdBufIdx++;
				cmdBufIdx %= 16;
			}
			break;
		case KernelEventFlag_Empty:
			break;
		default:
			break;
		}
		Kernel_yield();
	}
}

void User_task1(void)
{
	vPrintString("User task #1 \r\n");

	DispInit(2, 16);
	DispStr(0, 0, "simpleRTOS      ");
	DispStr(1, 0, "                ");

	uint8_t cmdlen = 0;
	uint8_t cmd[16] = {0};

	while(true){
		KernelEventFlag_t handle_event = Kernel_wait_events(KernelEventFlag_CmdIn);
		switch(handle_event){
		case KernelEventFlag_CmdIn:
			memset(cmd, 0, 16);
			Kernel_recv_msg(KernelMsgQ_Task1, &cmdlen, 1);
			Kernel_recv_msg(KernelMsgQ_Task1, cmd, cmdlen);
			vPrintString("\r\nRecv Cmd : ");
			vPrintString((const char*)cmd);
			DispStr(1, 0, "                ");
			DispStr(1, 0, (char*)cmd);
			break;
		case KernelEventFlag_Empty:
			break;
		default:
			break;
		}
		Kernel_yield();
	}
}

void User_task2(void)
{
	vPrintString("User task #2 \r\n");

	while(true){
		HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_6);
		HAL_Delay(1000);
		//Kernel_yield();
	}
}

void HAL_Delay(uint32_t Delay)
{
  uint32_t tickstart = HAL_GetTick();
  uint32_t wait = Delay;

  /* Add a freq to guarantee minimum wait */
  if (wait < HAL_MAX_DELAY)
  {
    wait += (uint32_t)(uwTickFreq);
  }

  while ((HAL_GetTick() - tickstart) < wait)
  {
	  Kernel_yield();
  }
}
/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
