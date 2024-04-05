#include "circular_buffer.h"

// init the buffer
uint8_t buffer_init(buf_handle_t *p_handle) {
    p_handle->head = 0;
    p_handle->tail = 0;
    p_handle->size = 0;
    p_handle->capacity = CIRCULAR_BUFFER_SIZE;
    return 0;
}

// insert a new value into buffer
uint8_t buffer_insert(buf_handle_t *p_handle, float value) {
    p_handle->array[p_handle->head] = value;
    p_handle->head = (p_handle->head + 1) % p_handle->capacity;
    p_handle->size++;
    return 0;
}

// extracts the last value of buffer,
uint8_t buffer_extract(buf_handle_t *p_handle) {
    p_handle->tail = (p_handle->tail + 1) % p_handle->capacity;
    p_handle->size--;
    return 0;
}

// removes oldest n item from buffer
uint8_t buffer_clear(buf_handle_t *p_handle, uint8_t num) {
    if (num == 0 || num > p_handle->size) {
    	num = p_handle->size;
    }
    for (uint8_t i = 0; i < num; i++) {
        buffer_extract(p_handle);
    }
    return 0;
}

// enters new values, when overflow occurs, discard the oldest data.
uint8_t buffer_enter_value(buf_handle_t *p_handle, float value) {
    if (p_handle->size >= p_handle->capacity) {
        buffer_extract(p_handle);
    }
    buffer_insert(p_handle, value);
    return 0;
}

// Gets and extracts the last value of buffer
uint8_t buffer_get_value(buf_handle_t *p_handle, float *p_sensor_data) {
    if (p_handle == NULL || p_sensor_data == NULL)
        return -2;
    if (p_handle->size == 0)
        return -1;

    *p_sensor_data = p_handle->array[p_handle->tail];
    buffer_extract(p_handle);
    return 0;
}
