#include "sensors.h"

uint8_t sensor_init(sensor_handle_t *p_sensor_handle, uint8_t id){
	p_sensor_handle->id = id;
	buffer_init(&p_sensor_handle->buff_raw);
	buffer_init(&p_sensor_handle->buff);

	return 0;
}
