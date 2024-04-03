#ifndef MEDIAN_FILTER_H
#define MEDIAN_FILTER_H

#include <stdint.h>
#include <stddef.h>
#include <math.h>

#include "circular_buffer.h"
#include "sensors.h"
#include "stats.h"
#include "stdlib.h"


int compareFloats(const void *a, const void *b);
float findMedian(float array[], uint8_t);
uint8_t filter_sensor_value(buf_handle_t*, float, uint8_t, float*);

#endif /* MEDIAN_FILTER_H */
