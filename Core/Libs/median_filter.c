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
    //qsort(array, array_size, sizeof(float), compareFloats);

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

float filter_sensor_value(sensor_handle_t *p_sensor_handle, float value) {
    if (p_sensor_handle->buff_raw.size >= p_sensor_handle->buff_raw.capacity) {
        buffer_extract(&p_sensor_handle->buff_raw);
    }
    p_sensor_handle->buff_raw.array[p_sensor_handle->buff_raw.head] = value;
    p_sensor_handle->buff_raw.head = (p_sensor_handle->buff_raw.head + 1) % p_sensor_handle->buff_raw.capacity;
    p_sensor_handle->buff_raw.size++;

    float temp_filtered[p_sensor_handle->buff_raw.capacity];

    /* ??? */
    uint8_t window_size = MOV_WINDOW_SIZE; // ??? Really strange but my threads wont work when I took this variable as function argument.
    window_size = (window_size * 2) - 1; // ??? I really don't know why. but the window works correctly with this equation

    if (p_sensor_handle->buff_raw.size < window_size) {
    	window_size = p_sensor_handle->buff_raw.size;
    }

    for (int i = 0; i < window_size; i++) {
        int n = p_sensor_handle->buff_raw.head-1-i;
        if (n < 0){ // Error handling when index is negative
            n = p_sensor_handle->buff_raw.size-i;
        }
        temp_filtered[i] = p_sensor_handle->buff_raw.array[n];
    }

    float filtered_value = value;
    //filtered_value = findMedian(temp_filtered, window_size);
    return filtered_value;
}
