#ifndef STATS_H
#define STATS_H

#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <math.h>

#include "main.h"
#include "median_filter.h"

#define TX_BUFFER_SIZE 127

typedef struct {
    float min;
    float max;
    float median;
    float sd;
} stats_handle_t;

uint8_t stats_find(const float data[], uint8_t, stats_handle_t*);

#endif /* STATS_H */
