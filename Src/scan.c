
/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"
#include "main.h"
#include "scan.h"
#include "tim.h"

float frequency_scan_start = 43.3 ;  //单位：khz
float frequency_scan_stop  = 96.6 ;  //单位：khz
float frequency_scan_add   = 0.4  ;  //单位：khz

uint32_t frequency_scan_start_transfer;
uint32_t frequency_scan_stop_transfer;
uint32_t frequency_scan_add_transfer;

uint32_t tim1_arr;

/* USER CODE BEGIN Includes */
uint16_t frequency_value;   
uint8_t  frequency_scan_state;

//frequency_scan_state=0x00    初始化扫频状态，未开始扫频
//frequency_scan_state=0x01    正常扫频状态
//frequency_scan_state=0x02    扫频完成
//frequency_scan_state=0x03    扫频出错

void scan_frequency(void)
{
	frequency_scan_state = 0;
	frequency_scan_start_transfer = (uint32_t)(frequency_scan_start* 10);
	frequency_scan_stop_transfer  = (uint32_t)(frequency_scan_stop * 10);
	frequency_scan_add_transfer   = (uint32_t)(frequency_scan_add  * 10);
	for (frequency_value=frequency_scan_start_transfer;;)
	{
		tim1_arr = 240000 / frequency_value;
		TIM1->ARR = tim1_arr;
		htim1.Instance->CCR1 = tim1_arr / 2;
		HAL_TIM_Base_Start_IT(&htim1);
		HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_1);
		HAL_Delay(50);
		frequency_value += frequency_scan_add_transfer;//

		if (frequency_value > frequency_scan_stop_transfer)//
		{
			frequency_scan_state = 0x02;//
		}

		if (frequency_scan_state == 0x02)
			return;

	}

}



/* USER CODE END Includes */







