#include "transmit.h"
#include <string.h>

void transmit_data(UART_HandleTypeDef *huart, const char *str, int num, const char *lineEnding) {
    char buffer[20]; // Buffer to hold the string representation of the integer
    int len = 0;
    int temp = num;

    // Handle negative numbers
    if (temp < 0) {
        buffer[len++] = '-';
        temp = -temp;
    }

    // Convert the number to string in reverse order
    do {
        buffer[len++] = (temp % 10) + '0';
        temp /= 10;
    } while (temp > 0);

    // Reverse the string
    for (int i = 0; i < len / 2; i++) {
        char tmp = buffer[i];
        buffer[i] = buffer[len - i - 1];
        buffer[len - i - 1] = tmp;
    }

    // Null-terminate the string
    buffer[len] = '\0';

    // Transmit string over UART
    HAL_UART_Transmit(huart, (uint8_t *)str, strlen(str), HAL_MAX_DELAY);
    // Transmit integer over UART
    HAL_UART_Transmit(huart, (uint8_t *)buffer, len, HAL_MAX_DELAY);
    // Transmit line ending over UART
    HAL_UART_Transmit(huart, (uint8_t *)lineEnding, strlen(lineEnding), HAL_MAX_DELAY);
}
