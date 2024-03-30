#ifndef TRANSMIT_DATA_H
#define TRANSMIT_DATA_H

#include "main.h"

void transmit_data(UART_HandleTypeDef *huart, const char *str, int num, const char *lineEnding);

#endif /* TRANSMIT_DATA_H */
