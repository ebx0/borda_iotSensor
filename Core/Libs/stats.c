#include "stats.h"

uint8_t stats_find(const float data[], uint8_t size, stats_handle_t *p_handle) {
	float min = data[0];
	float max = data[0];
	float sum = 0;

	for (int i = 0; i < size; i++) {
		if (data[i] < min)
			min = data[i];
		if (data[i] > max)
			max = data[i];
		sum += data[i];
	}
	float mean = sum / size;

	// Calculating sum of squared differences
	float sumSqDiff = 0;
	for (int i = 0; i < size; i++) {
		float diff = data[i] - mean; // Step 2
		sumSqDiff += diff * diff;    // Step 3-4
	}
	float variance = sumSqDiff / size; // Step 5
	float sd = sqrt(variance);         // Step 6

	float median = findMedian(data, size);

	p_handle->max = max;
	p_handle->min = min;
	p_handle->median = median;
	p_handle->sd = sd;
	return 0;
}

