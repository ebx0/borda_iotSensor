#include "median_filter.h"

//ChatGPT
int compareFloats(const void *a, const void *b) {
    // Comparison function used by qsort
    float floatA = *((float*)a);
    float floatB = *((float*)b);

    if (floatA < floatB) return -1;
    if (floatA > floatB) return 1;
    return 0;
}

//ChatGPT
float findMedian(float array[], uint8_t array_size) {
    // Sort the array using built-in qsort function
    qsort(array, array_size, sizeof(float), compareFloats);

    // If the size of the array is odd, return the middle element
    if (array_size % 2 != 0) {
        return array[array_size / 2];
    }
    // If the size of the array is even, return the average of the two middle elements
    else {
        float middle1 = array[array_size / 2 - 1];
        float middle2 = array[array_size / 2];
        return (middle1 + middle2) / 2.0;
    }
}

float filter_sensor_value(buf_handle_t *p_handle, float value) {
    if (p_handle->size >= p_handle->capacity) {
        buffer_extract(p_handle);
    }
    p_handle->buffer[p_handle->head] = value;
    p_handle->head = (p_handle->head + 1) % p_handle->capacity;
    p_handle->size++;

    float temp_filtered[p_handle->capacity];

    for (int i = 0; i < p_handle->size; i++) {
        int n = p_handle->head-1-i;
        if (n < 0){ // Error handling when index is negative
            n = p_handle->size-i;
        }
        temp_filtered[i] = p_handle->buffer[n];
    }
    float temp_return = findMedian(temp_filtered, p_handle->size);

    return temp_return;
}
