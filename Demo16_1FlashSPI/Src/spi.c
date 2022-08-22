/**
  ******************************************************************************
  * File Name          : SPI.c
  * Description        : This file provides code for the configuration
  *                      of the SPI instances.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2022 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "spi.h"

/* USER CODE BEGIN 0 */
#include	"w25flash.h"	//W25Q128驱动程序头文�?
#include	<string.h>		//用到函数strlen()
/* USER CODE END 0 */

SPI_HandleTypeDef hspi1;

/* SPI1 init function */
void MX_SPI1_Init(void)
{

  hspi1.Instance = SPI1;
  hspi1.Init.Mode = SPI_MODE_MASTER;
  hspi1.Init.Direction = SPI_DIRECTION_2LINES;
  hspi1.Init.DataSize = SPI_DATASIZE_8BIT;
  hspi1.Init.CLKPolarity = SPI_POLARITY_HIGH;
  hspi1.Init.CLKPhase = SPI_PHASE_2EDGE;
  hspi1.Init.NSS = SPI_NSS_SOFT;
  hspi1.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_8;
  hspi1.Init.FirstBit = SPI_FIRSTBIT_MSB;
  hspi1.Init.TIMode = SPI_TIMODE_DISABLE;
  hspi1.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
  hspi1.Init.CRCPolynomial = 10;
  if (HAL_SPI_Init(&hspi1) != HAL_OK)
  {
    Error_Handler();
  }

}

void HAL_SPI_MspInit(SPI_HandleTypeDef* spiHandle)
{

  GPIO_InitTypeDef GPIO_InitStruct = {0};
  if(spiHandle->Instance==SPI1)
  {
  /* USER CODE BEGIN SPI1_MspInit 0 */

  /* USER CODE END SPI1_MspInit 0 */
    /* SPI1 clock enable */
    __HAL_RCC_SPI1_CLK_ENABLE();

    __HAL_RCC_GPIOB_CLK_ENABLE();
    /**SPI1 GPIO Configuration
    PB3     ------> SPI1_SCK
    PB4     ------> SPI1_MISO
    PB5     ------> SPI1_MOSI
    */
    GPIO_InitStruct.Pin = GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF5_SPI1;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /* USER CODE BEGIN SPI1_MspInit 1 */

  /* USER CODE END SPI1_MspInit 1 */
  }
}

void HAL_SPI_MspDeInit(SPI_HandleTypeDef* spiHandle)
{

  if(spiHandle->Instance==SPI1)
  {
  /* USER CODE BEGIN SPI1_MspDeInit 0 */

  /* USER CODE END SPI1_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_SPI1_CLK_DISABLE();

    /**SPI1 GPIO Configuration
    PB3     ------> SPI1_SCK
    PB4     ------> SPI1_MISO
    PB5     ------> SPI1_MOSI
    */
    HAL_GPIO_DeInit(GPIOB, GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5);

  /* USER CODE BEGIN SPI1_MspDeInit 1 */

  /* USER CODE END SPI1_MspDeInit 1 */
  }
}

/* USER CODE BEGIN 1 */
//读取DeviceID，状态寄存器 SR1和SR2
void	Flash_TestReadStatus(void)
{
//读DeviceID ,  SR1, SR2
	uint16_t devID=Flash_ReadID();	//读取器件ID
	USB_printf("The ID is %d",devID);
    USB_printf("The chip is: ");
	switch (devID)
	{
	case 0xEF17:
		USB_printf("W25Q128");
		break;
	case 0xC817:
		USB_printf("GD25Q128");
		break;
	case 0x1C17:
		USB_printf("EN25Q128");
		break;
	case 0x2018:
		USB_printf("N25Q128");
		break;
	case 0x2017:
		USB_printf("XM25QH128");
		break;
	case 0xA117:
		USB_printf("FM25Q128");
		break;
	default:
		USB_printf("Unknown type");
	}

	uint8_t SR1=Flash_ReadSR1();	//读寄存器1, SR1=0x00才正�?
	USB_printf("Status Reg1=%d ",SR1);

	uint8_t SR2=Flash_ReadSR2();	//读寄存器2,  SR2=0x00才正�?
	USB_printf("Status Reg2=%d ",SR2);
}


//测试写入Page0 和Page1
// 注意：一个Page写入之前必须是被擦除过的，写入之后就不能再重复写�??
void	Flash_TestWrite(void)
{
	uint8_t		blobkNo=0;
	uint16_t	sectorNo=0;
	uint16_t	pageNo=0;
	uint32_t  	memAddress=0;

	//写入Page 0 两个字符�?
	memAddress=Flash_Addr_byBlockSectorPage(blobkNo, sectorNo,pageNo);	//Page0的地�?
	char	bufStr1[]="Hello from beginning";
	uint16_t	len=1+strlen(bufStr1); 		//包括结束�?'\0'
	Flash_WriteInPage(memAddress, 	  bufStr1, len);   //在Page0的起始位置写入数�?
	USB_printf("Write in Page0:0");
	USB_printf("%s",bufStr1);

	char bufStr2[]="Hello in page";
	len=1+strlen(bufStr2); 		//包括结束�?'\0'
	Flash_WriteInPage(memAddress+100,   bufStr2, len);   //Page0内偏�?100
USB_printf("Write in Page0:100");
	USB_DMA_printf("%s",bufStr2);

//写入Page 1
	uint8_t	bufPage[FLASH_PAGE_SIZE];	//EN25Q_PAGE_SIZE=256
	for (uint16_t i=0;i<FLASH_PAGE_SIZE; i++)
		bufPage[i]=i;		//准备数据
	pageNo=1; 	//Page 1
	memAddress=Flash_Addr_byBlockSectorPage(blobkNo, sectorNo, pageNo);	//page1的地�?
	Flash_WriteInPage(memAddress, bufPage, FLASH_PAGE_SIZE);   //写一个Page
	USB_DMA_printf("Write 0-255 in Page1");
}

//测试读取 Page0 �? Page1的内�?
void	Flash_TestRead(void)
{
	uint8_t		blobkNo=0;
	uint16_t	sectorNo=0;
	uint16_t	pageNo=0;
//读取Page 0
 char		bufStr[50];		//Page0读出的数�?
	uint32_t  memAddress=Flash_Addr_byBlockSectorPage(blobkNo, sectorNo,pageNo);
	Flash_ReadBytes(memAddress, bufStr, 50);	//读取50个字�?
	USB_printf("Read from Page0:0");
	USB_printf("%s",bufStr);	  //自动�?'\0'结束

	Flash_ReadBytes(memAddress+100, bufStr, 50);	//地址偏移100后的50个字字节
	USB_printf("Read from Page0:100");
	USB_printf("%s",bufStr);	  //自动�?'\0'结束

//读取Page 1
	uint8_t	randData=0;
	pageNo=1;
	memAddress=Flash_Addr_byBlockSectorPage(blobkNo, sectorNo,pageNo);

	randData =Flash_ReadOneByte(memAddress+12);		//读取1个字节数据，页内地址偏移12
	USB_printf("Page1[12] =");
	USB_printf("%d",randData);

	randData =Flash_ReadOneByte(memAddress+136);	//页内地址偏移136
	USB_printf("Page1[136] =");
	USB_printf("%d",randData);

	randData =Flash_ReadOneByte(memAddress+210);	//页内地址偏移210
	USB_printf("Page1[210] =");
	USB_printf("%d",randData);
}

/* USER CODE END 1 */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
