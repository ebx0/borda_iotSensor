#ifndef LIBS_SENSORS_H_
#define LIBS_SENSORS_H_

#include <stdint.h>
#include <stdio.h>
#include "main.h"
#include "circular_buffer.h"
#include "stats.h"


typedef struct {
	uint8_t addr;
	char sensor_name[20];
	float raw;
	float filtered;
	buf_handle_t buff_raw;
	buf_handle_t buff;
} sensor_handle_t;

typedef enum {
    LIGHT,
    TEMP,
    CO2,
	LAST_SENSOR
} sensor_t;

uint8_t sensor_init(sensor_handle_t*, uint8_t, const char*);
uint8_t sensor_read(sensor_handle_t*);

#endif /* LIBS_SENSORS_H_ */
