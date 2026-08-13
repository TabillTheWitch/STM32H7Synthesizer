#pragma once
#include "stm32h7xx_hal.h"

namespace Composition::Initialization::MX_Initialization
{
	/**
	  * @brief I2S1 Initialization Function
	  * @param None
	  * @retval None
	  */
	bool MX_I2S_Init(I2S_HandleTypeDef& hsai_BlockA1)
	{

	  /* USER CODE BEGIN I2S1_Init 0 */

	  /* USER CODE END I2S1_Init 0 */

	  /* USER CODE BEGIN I2S1_Init 1 */

	  /* USER CODE END I2S1_Init 1 */
		hsai_BlockA1.Instance = SPI1;
		hsai_BlockA1.Init.Mode = I2S_MODE_MASTER_TX;
		hsai_BlockA1.Init.Standard = I2S_STANDARD_PHILIPS;
		hsai_BlockA1.Init.DataFormat = I2S_DATAFORMAT_16B;
		hsai_BlockA1.Init.MCLKOutput = I2S_MCLKOUTPUT_DISABLE;
		hsai_BlockA1.Init.AudioFreq = I2S_AUDIOFREQ_48K;
		hsai_BlockA1.Init.CPOL = I2S_CPOL_LOW;
		hsai_BlockA1.Init.FirstBit = I2S_FIRSTBIT_MSB;
		hsai_BlockA1.Init.WSInversion = I2S_WS_INVERSION_DISABLE;
		hsai_BlockA1.Init.Data24BitAlignment = I2S_DATA_24BIT_ALIGNMENT_RIGHT;
		hsai_BlockA1.Init.MasterKeepIOState = I2S_MASTER_KEEP_IO_STATE_DISABLE;
	  if (HAL_I2S_Init(&hsai_BlockA1) != HAL_OK)
	  {
	    return false;
	  }
	  /* USER CODE BEGIN I2S1_Init 2 */
	  return true;
	  /* USER CODE END I2S1_Init 2 */

	}
	/**
	  * @brief USART3 Initialization Function
	  * @param None
	  * @retval None
	  */
	bool MX_USART3_UART_Init(UART_HandleTypeDef& huart3)
	{

	  /* USER CODE BEGIN USART3_Init 0 */

	  /* USER CODE END USART3_Init 0 */

	  /* USER CODE BEGIN USART3_Init 1 */

	  /* USER CODE END USART3_Init 1 */
	  huart3.Instance = USART3;
	  huart3.Init.BaudRate = 38400;
	  huart3.Init.WordLength = UART_WORDLENGTH_8B;
	  huart3.Init.StopBits = UART_STOPBITS_1;
	  huart3.Init.Parity = UART_PARITY_NONE;
	  huart3.Init.Mode = UART_MODE_TX_RX;
	  huart3.Init.HwFlowCtl = UART_HWCONTROL_NONE;
	  huart3.Init.OverSampling = UART_OVERSAMPLING_16;
	  huart3.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
	  huart3.Init.ClockPrescaler = UART_PRESCALER_DIV1;
	  huart3.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
	  if (HAL_UART_Init(&huart3) != HAL_OK)
	  {
		  return false;
	  }
	  if (HAL_UARTEx_SetTxFifoThreshold(&huart3, UART_TXFIFO_THRESHOLD_1_8) != HAL_OK)
	  {
		  return false;
	  }
	  if (HAL_UARTEx_SetRxFifoThreshold(&huart3, UART_RXFIFO_THRESHOLD_1_8) != HAL_OK)
	  {
		  return false;
	  }
	  if (HAL_UARTEx_DisableFifoMode(&huart3) != HAL_OK)
	  {
		  return false;
	  }
	  /* USER CODE BEGIN USART3_Init 2 */
	  return true;
	  /* USER CODE END USART3_Init 2 */

	}

	/**
	  * @brief GPIO Initialization Function
	  * @param None
	  * @retval None
	  */
	void MX_GPIO_Init(void)
	{
	  GPIO_InitTypeDef GPIO_InitStruct = {0};
	  /* USER CODE BEGIN MX_GPIO_Init_1 */

	  /* USER CODE END MX_GPIO_Init_1 */

	  /* GPIO Ports Clock Enable */
	  __HAL_RCC_GPIOC_CLK_ENABLE();
	  __HAL_RCC_GPIOA_CLK_ENABLE();
	  __HAL_RCC_GPIOB_CLK_ENABLE();
	  __HAL_RCC_GPIOD_CLK_ENABLE();
	  __HAL_RCC_GPIOG_CLK_ENABLE();

	  /*Configure GPIO pins : PC1 PC4 PC5 */
	  GPIO_InitStruct.Pin = GPIO_PIN_1|GPIO_PIN_4|GPIO_PIN_5;
	  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
	  GPIO_InitStruct.Pull = GPIO_NOPULL;
	  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	  GPIO_InitStruct.Alternate = GPIO_AF11_ETH;
	  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

	  /*Configure GPIO pins : PA1 PA2 PA7 */
	  GPIO_InitStruct.Pin = GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_7;
	  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
	  GPIO_InitStruct.Pull = GPIO_NOPULL;
	  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	  GPIO_InitStruct.Alternate = GPIO_AF11_ETH;
	  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

	  /*Configure GPIO pin : PB13 */
	  GPIO_InitStruct.Pin = GPIO_PIN_13;
	  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
	  GPIO_InitStruct.Pull = GPIO_NOPULL;
	  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	  GPIO_InitStruct.Alternate = GPIO_AF11_ETH;
	  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

	  /*Configure GPIO pins : PA8 PA11 PA12 */
	  GPIO_InitStruct.Pin = GPIO_PIN_8|GPIO_PIN_11|GPIO_PIN_12;
	  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
	  GPIO_InitStruct.Pull = GPIO_NOPULL;
	  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	  GPIO_InitStruct.Alternate = GPIO_AF10_OTG1_FS;
	  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

	  /*Configure GPIO pins : PG11 PG13 */
	  GPIO_InitStruct.Pin = GPIO_PIN_11|GPIO_PIN_13;
	  // Ethernetを使用しないので設定不要
	  //GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
	  //GPIO_InitStruct.Pull = GPIO_NOPULL;
	  //GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	  //GPIO_InitStruct.Alternate = GPIO_AF11_ETH;
	  HAL_GPIO_Init(GPIOG, &GPIO_InitStruct);

	  /* USER CODE BEGIN MX_GPIO_Init_2 */

	  /* USER CODE END MX_GPIO_Init_2 */
	}

	/**
	  * Enable DMA controller clock
	  */
	void MX_DMA_Init(void)
	{

	  /* DMA controller clock enable */
	  __HAL_RCC_DMA1_CLK_ENABLE();

	  /* DMA interrupt init */
	  /* DMA1_Stream0_IRQn interrupt configuration */
	  HAL_NVIC_SetPriority(DMA1_Stream0_IRQn, 5, 0);
	  HAL_NVIC_EnableIRQ(DMA1_Stream0_IRQn);

	}


}
