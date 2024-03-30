#ifndef TRANSMIT_H
#define TRANSMIT_H

#include <string.h>
#include <stdio.h>

#include "main.h"
#include "stats.h"
#include "circular_buffer.h"

void transmit_data(UART_HandleTypeDef *huart, const char *str, int num, const char *lineEnding);
void transmit_dataf(UART_HandleTypeDef *huart, const char *str, float num, const char *lineEnding);
void transmit_stats(UART_HandleTypeDef *huart, buf_handle_t *p_bhandle, stats_handle_t *p_shandle);

#endif /* TRANSMIT_H */
