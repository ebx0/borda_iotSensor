#include "sensors.h"

// Initializes a sensor handle struct.
uint8_t sensor_init(sensor_handle_t *p_sensor_handle, uint8_t address, const char *name){
    p_sensor_handle->addr = address;
    p_sensor_handle->raw = 0.0f;
    p_sensor_handle->filtered = 0.0f;
    buffer_init(&p_sensor_handle->buff_raw);
    buffer_init(&p_sensor_handle->buff);
    snprintf(p_sensor_handle->sensor_name, sizeof(p_sensor_handle->sensor_name), "%s", name);

    return 0;
}

// CHATGPT:
// Function to generate a random float value within a specified range (To mock sensor values)
float generateRandomFloat(float min, float max) {
    float scale = rand() / (float)RAND_MAX; // Generate a random float between 0 and 1
    return min + scale * (max - min); // Scale the random value to the desired range
}

// Reads the sensor data and stores in .raw variable
uint8_t sensor_read(sensor_handle_t *p_sensor_handle){
	if (p_sensor_handle->addr == LIGHT) {
		p_sensor_handle->raw = generateRandomFloat(150, 200);
	}
	else if (p_sensor_handle->addr == TEMP) {
		p_sensor_handle->raw = generateRandomFloat(18, 22);
	}
	else if (p_sensor_handle->addr == CO2) {
			p_sensor_handle->raw = generateRandomFloat(1000, 4000);
	}

	return 0;
}
