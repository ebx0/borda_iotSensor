#ifndef LIBS_SENSORS_H_
#define LIBS_SENSORS_H_

#include <stdint.h>
#include "main.h"
#include "circular_buffer.h"
#include "stats.h"

typedef struct {
	uint8_t id; //reserved
	float raw;
	float filtered;
	buf_handle_t buff_raw;
	buf_handle_t buff;
} sensor_handle_t;

uint8_t sensor_init(sensor_handle_t *p_sensor_handle, uint8_t);

#endif /* LIBS_SENSORS_H_ */
