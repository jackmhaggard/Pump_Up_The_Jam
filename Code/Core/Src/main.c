/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2026 STMicroelectronics.
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
#include "button.h"
#include "mosfet.h"


volatile Notes_Struct Notes;
/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

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
static void MX_GPIO_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{

  /* USER CODE BEGIN 1 */

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
  /* USER CODE BEGIN 2 */
  Reset_Pins();
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
	  //Basic test funciton of a C major Triad
	  //Comment out if not testing code
	  //Arpeggio();
	  //Chromatic();
	  getButtonState();
	  //polling of the GPIO pins to see what notes to activate
	  Polling();
	  Update();
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

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE3);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 8;
  RCC_OscInitStruct.PLL.PLLN = 50;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV4;
  RCC_OscInitStruct.PLL.PLLQ = 7;
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
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV8;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV4;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
/* USER CODE BEGIN MX_GPIO_Init_1 */
/* USER CODE END MX_GPIO_Init_1 */

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOF_CLK_ENABLE();
  //__HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOG_CLK_ENABLE();
  __HAL_RCC_GPIOE_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  GPIOF->MODER |= (0b01 << 10);
  GPIOF->MODER |= (0b01 << 6);
  GPIOF->MODER |= (0b01 << 2);

  GPIOC->MODER |= (0b01 << 30);
  GPIOC->MODER |= (0b01 << 26);

  GPIOE->MODER |= (0b01 << 10);
  GPIOE->MODER |= (0b01 << 6);
  GPIOE->MODER |= (0b01 << 2);

  GPIOB->MODER |= (0b01 << 18);
  GPIOB->MODER |= (0b01 << 14);
  GPIOB->MODER |= (0b01 << 10);
  GPIOB->MODER |= (0b01 << 6);

  //keyboard inputs
  GPIOF->MODER &= ~(0b00 << 8);
  GPIOF->MODER &= ~(0b00 << 4);
  GPIOF->MODER &= ~(0b00 << 0);

  GPIOE->MODER &= ~(0b00 << 12);

  GPIOB->MODER &= ~(0b00 << 16);

  GPIOG->MODER &= ~(0b00 << 22);
  GPIOG->MODER &= ~(0b00 << 18);

  GPIOD->MODER &= ~(0b00 << 14);
  GPIOD->MODER &= ~(0b00 << 10);
  GPIOD->MODER &= ~(0b00 << 6);
  GPIOD->MODER &= ~(0b00 << 2);

  GPIOC->MODER &= ~(0b00 << 20);

  //button pull up configuration
  GPIOF->PUPDR &= ~(0b01 << 8);
  GPIOF->PUPDR &= ~(0b01 << 4);
  GPIOF->PUPDR &= ~(0b01 << 0);

  GPIOE->PUPDR &= ~(0b01 << 12);

  GPIOB->PUPDR &= ~(0b01 << 16);

  GPIOG->PUPDR &= ~(0b01 << 22);
  GPIOG->PUPDR &= ~(0b01 << 18);

  GPIOD->PUPDR &= ~(0b01 << 14);
  GPIOD->PUPDR &= ~(0b01 << 10);
  GPIOD->PUPDR &= ~(0b01 << 6);
  GPIOD->PUPDR &= ~(0b01 << 2);

  GPIOC->PUPDR &= ~(0b01 << 20);


/* USER CODE BEGIN MX_GPIO_Init_2 */
/* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */


void Update(void){
	if(!Notes.C){
		GPIOF->BSRR |= C_OUT;
	}
	else{
		GPIOF->BSRR |= (C_OUT << 16);
	}
	if(!Notes.Cs){
		GPIOF->BSRR |= Cs_OUT;
	}
	else{
		GPIOF->BSRR |= (Cs_OUT <<16);
	}
	if(!Notes.D){
		GPIOF->BSRR |= D_OUT;
	}
	else{
		GPIOF->BSRR |= (D_OUT << 16);
	}
	if(!Notes.Ds){
		GPIOC->BSRR |= Ds_OUT;
	}
	else{
		GPIOC->BSRR |= (Ds_OUT << 16);
	}
	if(!Notes.E){
		GPIOC->BSRR |= E_OUT;
	}
	else{
		GPIOC->BSRR |= (E_OUT << 16);
	}
	if(!Notes.F){
		GPIOE->BSRR |= F_OUT;
	}
	else{
		GPIOE->BSRR |= (F_OUT << 16);
	}
	if(!Notes.Fs){
		GPIOE->BSRR |= Fs_OUT;
	}
	else{
		GPIOE->BSRR |= (Fs_OUT << 16);
	}
	if(!Notes.G){
		GPIOE->BSRR |= G_OUT;
	}
	else{
		GPIOE->BSRR |= (G_OUT << 16);
	}
	if(!Notes.Gs){
		GPIOB->BSRR |= Gs_OUT;
	}
	else{
		GPIOB->BSRR |= (Gs_OUT << 16);
	}
	if(!Notes.A){
		GPIOB->BSRR |= A_OUT;
	}
	else{
		GPIOB->BSRR |= (A_OUT << 16);
	}
	if(!Notes.As){
		GPIOB->BSRR |= As_OUT;
	}
	else{
		GPIOB->BSRR |= (As_OUT << 16);
	}
	if(!Notes.B){
		GPIOB->BSRR |= B_OUT;
	}
	else{
		GPIOB->BSRR |= (B_OUT << 16);
	}


}
void Reset_Pins(void){
	GPIOF->BSRR |= C_OUT;
	GPIOF->BSRR |= Cs_OUT;
	GPIOF->BSRR |= D_OUT;
	GPIOC->BSRR |= Ds_OUT;
	GPIOC->BSRR |= E_OUT;
	GPIOE->BSRR |= F_OUT;
	GPIOE->BSRR |= Fs_OUT;
	GPIOE->BSRR |= G_OUT;
	GPIOB->BSRR |= Gs_OUT;
	GPIOB->BSRR |= A_OUT;
	GPIOB->BSRR |= As_OUT;
	GPIOB->BSRR |= B_OUT;
}


void Arpeggio(void){
	GPIOF->BSRR |= (C_OUT << 16);
	HAL_Delay(3000);
	GPIOF->BSRR |= C_OUT;
	GPIOC->BSRR |= (E_OUT <<16);

	HAL_Delay(3000);
	GPIOC->BSRR |= E_OUT;
	GPIOE->BSRR |= (G_OUT << 16);



	HAL_Delay(3000);

	GPIOF->BSRR |= C_OUT;
	GPIOC->BSRR |= E_OUT;
	GPIOE->BSRR |= G_OUT;

}




void Polling(void){
	  if (GPIOF->IDR & (1 << 4)) {
	      // Logic HIGH (1)
		  Notes.C = 0;
	  } else {
	      // Logic LOW (0)
		  Notes.C = 1;
	  }
	  if (GPIOF->IDR & (1 << 2)) {
	      // Logic HIGH (1)
		  Notes.Cs = 0;
	  } else {
	      // Logic LOW (0)
		  Notes.Cs = 1;
	  }
	  if (GPIOF->IDR & (1 << 0)) {
	      // Logic HIGH (1)
		  Notes.D = 0;
	  } else {
	      // Logic LOW (0)
		  Notes.D = 1;
	  }
	  if (GPIOE->IDR & (1 << 6)) {
	      // Logic HIGH (1)
		  Notes.Ds = 0;
	  } else {
	      // Logic LOW (0)
		  Notes.Ds = 1;
	  }
	  if (GPIOB->IDR & (1 << 8)) {
	      // Logic HIGH (1)
		  Notes.E = 0;
	  } else {
	      // Logic LOW (0)
		  Notes.E = 1;
	  }
	  if (GPIOG->IDR & (1 << 11)) {
	      // Logic HIGH (1)
		  Notes.F = 0;
	  } else {
	      // Logic LOW (0)
		  Notes.F = 1;
	  }
	  if (GPIOG->IDR & (1 << 9)) {
	      // Logic HIGH (1)
		  Notes.Fs = 0;
	  } else {
	      // Logic LOW (0)
		  Notes.Fs = 1;
	  }
	  if (GPIOD->IDR & (1 << 7)) {
	      // Logic HIGH (1)
		  Notes.G = 0;
	  } else {
	      // Logic LOW (0)
		  Notes.G = 1;
	  }
	  if (GPIOD->IDR & (1 << 5)) {
	      // Logic HIGH (1)
		  Notes.Gs = 0;
	  } else {
	      // Logic LOW (0)
		  Notes.Gs = 1;
	  }
	  if (GPIOD->IDR & (1 << 3)) {
	      // Logic HIGH (1)
		  Notes.A = 0;
	  } else {
	      // Logic LOW (0)
		  Notes.A = 1;
	  }
	  if (GPIOD->IDR & (1 << 1)) {
	      // Logic HIGH (1)
		  Notes.As = 0;
	  } else {
	      // Logic LOW (0)
		  Notes.As = 1;
	  }
	  if (GPIOC->IDR & (1 << 10)) {
	      // Logic HIGH (1)
		  Notes.B = 0;
	  } else {
	      // Logic LOW (0)
		  Notes.B = 1;
	  }
}

void getButtonState(){
 	uint32_t state = HAL_GPIO_ReadPin(GPIOA, BUTTON_PIN);
	if(state == 1){
		Reset_Pins();
	}
}

void Button_Init(void){
	GPIO_InitTypeDef* button = {0};
	__HAL_RCC_GPIOA_CLK_ENABLE();
	button->Pin = GPIO_PIN_0;
	button->Mode = GPIO_MODE_INPUT;

	HAL_GPIO_Init(GPIOA, button);


}

void Chromatic(void){
	GPIOF->BSRR |= (C_OUT << 16);
	HAL_Delay(1000);
	GPIOF->BSRR |= C_OUT;
	GPIOF->BSRR |= (Cs_OUT <<16);

	HAL_Delay(1000);
	GPIOF->BSRR |= Cs_OUT;
	GPIOF->BSRR |= (D_OUT <<16);

	HAL_Delay(1000);
	GPIOF->BSRR |= D_OUT;
	GPIOC->BSRR |= (Ds_OUT << 16);

	HAL_Delay(1000);
	GPIOC->BSRR |= Ds_OUT;
	GPIOC->BSRR |= (E_OUT << 16);

	HAL_Delay(1000);
	GPIOC->BSRR |= E_OUT;
	GPIOE->BSRR |= (F_OUT << 16);

	HAL_Delay(1000);
	GPIOE->BSRR |= F_OUT;
	GPIOE->BSRR |= (Fs_OUT << 16);

	HAL_Delay(1000);
	GPIOE->BSRR |= Fs_OUT;
	GPIOE->BSRR |= (G_OUT << 16);

	HAL_Delay(1000);
	GPIOE->BSRR |= G_OUT;
	GPIOB->BSRR |= (Gs_OUT << 16);

	HAL_Delay(1000);
	GPIOB->BSRR |= Gs_OUT;
	GPIOB->BSRR |= (A_OUT << 16);

	HAL_Delay(1000);
	GPIOB->BSRR |= A_OUT;
	GPIOB->BSRR |= (As_OUT << 16);

	HAL_Delay(1000);
	GPIOB->BSRR |= As_OUT;
	GPIOB->BSRR |= (B_OUT << 16);

	HAL_Delay(1000);
	GPIOB->BSRR |= B_OUT;
	HAL_Delay(1000);


}

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
