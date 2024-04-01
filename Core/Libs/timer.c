#include "timer.h"

RTC_HandleTypeDef hrtc2;

void timer_init(void){
	  hrtc2.Instance = RTC;
	  hrtc2.Init.HourFormat = RTC_HOURFORMAT_24;
	  hrtc2.Init.AsynchPrediv = 127;
	  hrtc2.Init.SynchPrediv = 255;
	  hrtc2.Init.OutPut = RTC_OUTPUT_DISABLE;
	  hrtc2.Init.OutPutPolarity = RTC_OUTPUT_POLARITY_HIGH;
	  hrtc2.Init.OutPutType = RTC_OUTPUT_TYPE_OPENDRAIN;
	  if (HAL_RTC_Init(&hrtc2) != HAL_OK)
	  {
	    Error_Handler();
	  }
}

uint8_t timer_get(time_handle_t *p_time_handle) {
    RTC_DateTypeDef sDate;
    RTC_TimeTypeDef sTime;
    HAL_RTC_GetTime(&hrtc2, &sTime, RTC_FORMAT_BIN);
    HAL_RTC_GetDate(&hrtc2, &sDate, RTC_FORMAT_BIN);

    // Check if the time values have changed
    if (p_time_handle->hours != sTime.Hours || p_time_handle->minutes != sTime.Minutes || p_time_handle->seconds != sTime.Seconds) {
    	p_time_handle->hours = sTime.Hours;
    	p_time_handle->minutes = sTime.Minutes;
    	p_time_handle->seconds = sTime.Seconds;
        return 1; // Time values changed
    } else {
        return 0; // Time values not changed
    }
}
