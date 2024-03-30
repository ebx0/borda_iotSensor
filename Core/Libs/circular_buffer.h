#ifndef CIRCULAR_H
#define CIRCULAR_H

#include <stdint.h>
#include <stddef.h>

#define CIRCULAR_BUFFER_SIZE 32

typedef struct {
    float buffer[CIRCULAR_BUFFER_SIZE];
    uint32_t head;
    uint32_t tail;
    uint32_t size;
    uint32_t capacity;
} buf_handle_t;


void buffer_init(buf_handle_t *p_handle);
uint8_t buffer_insert(buf_handle_t *p_handle, float value);
uint8_t buffer_extract(buf_handle_t *p_handle);
uint8_t buffer_enter_value(buf_handle_t *p_handle, float value);
uint8_t bufferPrint(buf_handle_t *p_handle);
uint8_t buffer_get_value(buf_handle_t *p_handle, float *p_sensor_data);

#endif /* CIRCULAR_H */
