#ifndef MEDIAN_FILTER_H
#define MEDIAN_FILTER_H

#define MOV_WINDOW_SIZE 5

#include <stdint.h>
#include <stddef.h>
#include <math.h>

#include "circular_buffer.h"
#include "sensors.h"
#include "stats.h"
#include "stdlib.h"


int compareFloats(const void *a, const void *b);
float findMedian(float array[], uint8_t);
float filter_sensor_value(sensor_handle_t *p_sensor_handle, float value);

#endif /* MEDIAN_FILTER_H */
