/**
  ******************************************************************************
  * @file    FreeRTOS/FreeRTOS_ThreadCreation/Src/stm32f4xx_it.c 
  * @author  MCD Application Team
  * @version V1.1.0
  * @date    26-June-2014
  * @brief   Main Interrupt Service Routines.
  *          This file provides template for all exceptions handler and 
  *          peripherals interrupt service routine.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT(c) 2014 STMicroelectronics</center></h2>
  *
  * Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
  * You may not use this file except in compliance with the License.
  * You may obtain a copy of the License at:
  *
  *        http://www.st.com/software_license_agreement_liberty_v2
  *
  * Unless required by applicable law or agreed to in writing, software 
  * distributed under the License is distributed on an "AS IS" BASIS, 
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"
#include "stm32f4xx_it.h"
#include "cmsis_os.h"
#include "FreeRTOS.h"
#include "task.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
extern void xPortSysTickHandler(void);

extern DMA_HandleTypeDef hdma_adc1;
extern DMA_HandleTypeDef hdma_adc2;
extern DMA_HandleTypeDef hdma_dac2;

extern ADC_HandleTypeDef hadc1;
extern ADC_HandleTypeDef hadc2;
extern DAC_HandleTypeDef hdac;

extern SD_HandleTypeDef hsd;
extern DMA_HandleTypeDef hdma_sdiorx;
extern DMA_HandleTypeDef hdma_sdiotx;

extern PCD_HandleTypeDef hpcd_USB_OTG_HS;

/* Private functions ---------------------------------------------------------*/

/******************************************************************************/
/*            Cortex-M4 Processor Exceptions Handlers                         */
/******************************************************************************/

/**
  * @brief  This function handles NMI exception.
  * @param  None
  * @retval None
  */
void NMI_Handler(void)
{
}

/**
  * @brief  This function handles Hard Fault exception.
  * @param  None
  * @retval None
  */
void HardFault_Handler(void)
{
  /* Go to infinite loop when Hard Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Memory Manage exception.
  * @param  None
  * @retval None
  */
void MemManage_Handler(void)
{
  /* Go to infinite loop when Memory Manage exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Bus Fault exception.
  * @param  None
  * @retval None
  */
void BusFault_Handler(void)
{
  /* Go to infinite loop when Bus Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Usage Fault exception.
  * @param  None
  * @retval None
  */
void UsageFault_Handler(void)
{
  /* Go to infinite loop when Usage Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Debug Monitor exception.
  * @param  None
  * @retval None
   */
void DebugMon_Handler(void)
{
}

/**
  * @brief  This function handles SysTick Handler.
  * @param  None
  * @retval None
  */
void SysTick_Handler(void)
{
  if (xTaskGetSchedulerState() != taskSCHEDULER_NOT_STARTED)
  {
    xPortSysTickHandler();
  }
  HAL_IncTick();
}

/******************************************************************************/
/*                 STM32F4xx Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_stm32f4xx.s).                                               */
/******************************************************************************/

/**
  * @brief  This function handles PPP interrupt request.
  * @param  None
  * @retval None
  */
/*void PPP_IRQHandler(void)
{
}*/

void SDIO_IRQHandler(void){
    HAL_SD_IRQHandler(&hsd);
    return;
}

void DMA2_Stream3_IRQHandler(void){
    HAL_DMA_IRQHandler(&hdma_sdiorx);
    return;
}

void DMA2_Stream6_IRQHandler(void){
    HAL_DMA_IRQHandler(&hdma_sdiotx);
    return;
}

/* Double Buffer Swapping Callbacks */
void DMA2_Stream0_IRQHandler(void){
    HAL_DMA_IRQHandler(&hdma_adc1);
    return;
}

void DMA1_Stream6_IRQHandler(void){
    HAL_DMA_IRQHandler(&hdma_dac2);
    return;
}

void OTG_HS_IRQHandler(void)
{
      /* USER CODE BEGIN OTG_HS_IRQn 0 */

      /* USER CODE END OTG_HS_IRQn 0 */
      HAL_PCD_IRQHandler(&hpcd_USB_OTG_HS);
      /* USER CODE BEGIN OTG_HS_IRQn 1 */

      /* USER CODE END OTG_HS_IRQn 1 */

}

void OTG_HS_WKUP_IRQHandler(void)
{
      /* USER CODE BEGIN OTG_HS_WKUP_IRQn 0 */

      /* USER CODE END OTG_HS_WKUP_IRQn 0 */
      HAL_PCD_IRQHandler(&hpcd_USB_OTG_HS);
      /* USER CODE BEGIN OTG_HS_WKUP_IRQn 1 */

      /* USER CODE END OTG_HS_WKUP_IRQn 1 */

}

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
