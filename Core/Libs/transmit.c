#include "transmit.h"

// Helper function to convert integer to string
static void int_to_string(int num, char *buffer) {
    int i = 0;
    int is_negative = 0;

    // Handle negative numbers
    if (num < 0) {
        is_negative = 1;
        num = -num;
    }

    // Convert each digit to a character and store in reverse order
    do {
        buffer[i++] = num % 10 + '0';
        num /= 10;
    } while (num > 0);

    // Add negative sign if applicable
    if (is_negative) {
        buffer[i++] = '-';
    }

    // Reverse the string
    for (int j = 0; j < i / 2; j++) {
        char temp = buffer[j];
        buffer[j] = buffer[i - j - 1];
        buffer[i - j - 1] = temp;
    }

    // Null-terminate the string
    buffer[i] = '\0';
}

// Helper function to convert floating-point number to string
static void float_to_string(float num, char *buffer) {
    int integer_part = (int)num;
    float fractional_part = num - integer_part;

    // Convert integer part to string
    int_to_string(integer_part, buffer);

    // Find the end of the integer part
    int len = strlen(buffer);

    // Add decimal point
    buffer[len++] = '.';

    // Convert fractional part to string
    if ( fractional_part > 0 ) { // If number is negative, dont write it like -12.-23 just -12.23
    	int_to_string((int)(fractional_part * 100), buffer + len);
    } else {
    	int_to_string((int)(-fractional_part * 100), buffer + len);
    }


}

void transmit_data(UART_HandleTypeDef *huart, const char *str, int num, const char *lineEnding) {
    char buffer[20]; // Buffer to hold the string representation of the integer

    // Convert integer to string
    int_to_string(num, buffer);

    // Concatenate the prefix string, integer string, and line ending
    strcat(buffer, lineEnding);

    // Transmit over UART
    HAL_UART_Transmit(huart, (uint8_t *)str, strlen(str), HAL_MAX_DELAY);
    HAL_UART_Transmit(huart, (uint8_t *)buffer, strlen(buffer), HAL_MAX_DELAY);
}


void transmit_dataf(UART_HandleTypeDef *huart, const char *str, float num, const char *lineEnding) {
    char buffer[20]; // Buffer to hold the string representation of the float

    // Convert float to string
    float_to_string(num, buffer);

    // Concatenate the prefix string, float string, and line ending
    strcat(buffer, lineEnding);

    // Transmit over UART
    HAL_UART_Transmit(huart, (uint8_t *)str, strlen(str), HAL_MAX_DELAY);
    HAL_UART_Transmit(huart, (uint8_t *)buffer, strlen(buffer), HAL_MAX_DELAY);
}

void transmit_stats(UART_HandleTypeDef *huart, sensor_handle_t *p_sensor_handle) {
	float temp_data;
	float temp_data_array[32];
	uint8_t index = 0;

	stats_handle_t stats;

	while (p_sensor_handle->buff.size){
	    buffer_get_value(&p_sensor_handle->buff, &temp_data);
	    temp_data_array[index] = temp_data;
		index++;
	}

	stats_find(temp_data_array, index, &stats);

	transmit_data(huart,"ID=", p_sensor_handle->id, ",");
	transmit_data(huart,"size=", index, ",");
	transmit_dataf(huart,"min=", stats.min, ",");
	transmit_dataf(huart,"med=", stats.median, ",");
	transmit_dataf(huart,"max=", stats.max, ",");
	transmit_dataf(huart,"sd=", stats.sd, "\r\n");
}

void transmit_time(UART_HandleTypeDef *huart, time_handle_t *p_time_handle) {
	timer_get(p_time_handle);

	if (p_time_handle->hours < 10){transmit_data(huart,"(0", p_time_handle->hours, "");}
	else {transmit_data(huart,"(", p_time_handle->hours, "");}

	if (p_time_handle->minutes < 10){transmit_data(huart,":0", p_time_handle->minutes, "");}
	else {transmit_data(huart,":", p_time_handle->minutes, "");}

	if (p_time_handle->seconds < 10){transmit_data(huart,":0", p_time_handle->seconds, ")\r\n");}
	else {transmit_data(huart,":", p_time_handle->seconds, ")\r\n");}
}
