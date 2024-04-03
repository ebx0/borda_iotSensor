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

uint8_t filter_sensor_value(buf_handle_t *p_buffer_handle, float value, float *filtered_value) {

    if (p_buffer_handle->size >= p_buffer_handle->capacity) {
        buffer_extract(p_buffer_handle);
    }
    p_buffer_handle->array[p_buffer_handle->head] = value;
    p_buffer_handle->head = (p_buffer_handle->head + 1) % p_buffer_handle->capacity;
    p_buffer_handle->size++;

    float temp_buffer[p_buffer_handle->capacity];

    /* ??? */
    uint8_t window_size = MOV_WINDOW_SIZE; // ??? Really strange but my threads wont work when I took this variable as function argument.
    window_size = (window_size * 2) - 1; // ??? I really don't know why. but the window works correctly with this equation

    if (p_buffer_handle->size < window_size) {
    	window_size = p_buffer_handle->size;
    }

    for (int i = 0; i < window_size; i++) { // Create a temporary buffer with window size to find its median
        int n = p_buffer_handle->head-1-i;
        if (n < 0){ // Error handling when index is negative
            n = p_buffer_handle->size-i;
        }
        temp_buffer[i] = p_buffer_handle->array[n];
    }

    *filtered_value = findMedian(temp_buffer, window_size);
    return 0;
}
