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
    int_to_string((int)(fractional_part * 100), buffer + len);
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

void transmit_stats(UART_HandleTypeDef *huart, buf_handle_t *p_buf_handle, stats_handle_t *p_stats_handle) {
	stats_find(p_buf_handle->buffer, p_buf_handle->size, p_stats_handle);

	transmit_dataf(huart,"min=", p_stats_handle->min, ",");
	transmit_dataf(huart,"med=", p_stats_handle->median, ",");
	transmit_dataf(huart,"max=", p_stats_handle->max, ",");
	transmit_dataf(huart,"sd=", p_stats_handle->sd, "\r\n");
}
