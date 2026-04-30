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
  //The following 3 function initialize and prepare the LCD for operation
  LTCD__Init();
  LTCD_Layer_Init(0);
  LCD_Clear(0,LCD_COLOR_WHITE);
  //visualDemo();
  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
	  //Basic test funciton of a C major Triad
	  //Comment out if not testing code
	  //Arpeggio();
	  //testing function of more notes
	  //Chromatic();
	  //checks and resets the notes being played based on the button input on the STM board
	  getButtonState();
	  //polling of the GPIO pins to see what notes to activate
	  Polling();
	  //updates the mosfet gates
	  Update();
	  //updates the LCD
	  LCD_Update();
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
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOG_CLK_ENABLE();
  __HAL_RCC_GPIOE_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();

  /*Configure Mosfet controlling GPIO Pins */
  GPIOF->MODER |= (0b01 << 10);
  GPIOF->MODER |= (0b01 << 6);
  GPIOF->MODER |= (0b01 << 2);

  GPIOC->MODER |= (0b01 << 30);
  GPIOC->MODER |= (0b01 << 26);

  GPIOE->MODER |= (0b01 << 10);
  GPIOE->MODER |= (0b01 << 6);
  GPIOE->MODER |= (0b01 << 2);

  GPIOD->MODER |= (0b01 << 0);
  GPIOB->MODER |= (0b01 << 14);
  GPIOB->MODER |= (0b01 << 10);
  GPIOB->MODER |= (0b01 << 6);

  //keyboard inputs
  GPIOF->MODER &= ~(0b00 << 8);
  GPIOF->MODER &= ~(0b00 << 4);
  GPIOF->MODER &= ~(0b00 << 0);

  GPIOE->MODER &= ~(0b00 << 12);

  GPIOE->MODER &= ~(0b00 << 0);

  GPIOG->MODER &= ~(0b00 << 26);
  GPIOG->MODER &= ~(0b00 << 18);

  GPIOD->MODER &= ~(0b00 << 14);
  GPIOC->MODER &= ~(0b00 << 16);
  GPIOA->MODER &= ~(0b00 << 20);
  GPIOD->MODER &= ~(0b00 << 2);

  GPIOA->MODER &= ~(0b00 << 28);

  //button pull up configuration
  GPIOF->PUPDR &= ~(0b01 << 8);
  GPIOF->PUPDR &= ~(0b01 << 4);
  GPIOF->PUPDR &= ~(0b01 << 0);

  GPIOE->PUPDR &= ~(0b01 << 12);

  GPIOE->PUPDR &= ~(0b01 << 0);

  GPIOG->PUPDR &= ~(0b01 << 26);
  GPIOG->PUPDR &= ~(0b01 << 18);

  GPIOD->PUPDR &= ~(0b01 << 14);
  GPIOC->PUPDR &= ~(0b01 << 16);
  GPIOA->PUPDR &= ~(0b01 << 20);
  GPIOD->PUPDR &= ~(0b01 << 2);

  GPIOA->PUPDR &= ~(0b01 << 28);


/* USER CODE BEGIN MX_GPIO_Init_2 */
/* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function updates the LCD to display which note(s) is/are currently being played.
  * @retval None
  */

void LCD_Update(void){
	LCD_Clear(0,LCD_COLOR_WHITE);
	LCD_SetTextColor(LCD_COLOR_BLACK);
	LCD_SetFont(&Font16x24);
	if(Notes.C){
		LCD_DisplayChar(10, 160, 'C');
	}

	if(Notes.Cs){
		LCD_DisplayChar(20, 140, 'C');
		LCD_DisplayChar(35, 140, '#');
	}

	if(Notes.D){
		LCD_DisplayChar(45, 160, 'D');
	}

	if(Notes.Ds){
		LCD_DisplayChar(55, 140, 'D');
		LCD_DisplayChar(70, 140, '#');
	}

	if(Notes.E){
		LCD_DisplayChar(80, 160, 'E');
	}

	if(Notes.F){
		LCD_DisplayChar(95, 160, 'F');

	}

	if(Notes.Fs){
		LCD_DisplayChar(105, 140, 'F');
		LCD_DisplayChar(120, 140, '#');
	}

	if(Notes.G){
		LCD_DisplayChar(130, 160, 'G');

	}

	if(Notes.Gs){
		LCD_DisplayChar(140, 140, 'G');
		LCD_DisplayChar(155, 140, '#');
	}

	if(Notes.A){
		LCD_DisplayChar(165, 160, 'A');
	}

	if(Notes.As){
		LCD_DisplayChar(175, 140, 'A');
		LCD_DisplayChar(190, 140, '#');

	}

	if(Notes.B){
		LCD_DisplayChar(200, 160, 'B');

	}

}

/**
  * @brief  This function updates the mosfet controlling GPIO pins to control which note(s) is/are played
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
		GPIOD->BSRR |= Gs_OUT;
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

/**
  * @brief  This function resets the notes to all be off in the event that a weird logic state is captured
  * @retval None
  */
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

/**
  * @brief  This function plays a C major triad for testing purposes.
  * @retval None
  */
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



/**
  * @brief  This function checks the logic level of each of the 12 button inputs
  * @retval None
  */
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
	  if (GPIOE->IDR & (1 << 0)) {
	      // Logic HIGH (1)
		  Notes.E = 0;
	  } else {
	      // Logic LOW (0)
		  Notes.E = 1;
	  }
	  if (GPIOG->IDR & (1 << 13)) {
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
	  if (GPIOC->IDR & (1 << 8)) {
	      // Logic HIGH (1)
		  Notes.Gs = 0;
	  } else {
	      // Logic LOW (0)
		  Notes.Gs = 1;
	  }
	  if (GPIOA->IDR & (1 << 10)) {
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
	  if (GPIOA->IDR & (1 << 14)) {
	      // Logic HIGH (1)
		  Notes.B = 0;
	  } else {
	      // Logic LOW (0)
		  Notes.B = 1;
	  }
}

/**
  * @brief  This function checks the reset button and calls the associated function if needed.
  * @retval None
  */
void getButtonState(){
 	uint32_t state = HAL_GPIO_ReadPin(GPIOA, BUTTON_PIN);
	if(state == 1){
		Reset_Pins();
	}
}

/**
  * @brief  This function initializes the button
  * @retval None
  */
void Button_Init(void){
	GPIO_InitTypeDef* button = {0};
	__HAL_RCC_GPIOA_CLK_ENABLE();
	button->Pin = GPIO_PIN_0;
	button->Mode = GPIO_MODE_INPUT;

	HAL_GPIO_Init(GPIOA, button);


}

/**
  * @brief  This function plays all 12 notes in a chromatic scale for testing purposes.
  * @retval None
  */
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
