# Enviromental Sensor IoT Device

## Introduction
In the given assignment, the data coming from three sensors must be periodically (1s) received, filtered, and stored in a circular buffer with a microcontroller. After that, the data stored in the buffer will be transmitted over Bluetooth in a longer period (30s). These instructions have been carefully followed to create a project that works.

## Materials
### 2.1 Microcontroller:
For a project like this, the first hardware material I would choose would be a microcontroller. For this project, I chose the STM32 family, which is a microcontroller family with nice libraries such as the HAL library, which I can quickly configure and program via CubeIDE, and which has RTOS support. Since the project requires the production of a prototype, I chose the STM32F407 Discovery board, which is a development board that I already have. In this way, I can quickly build my circuit on the breadboard.

### 2.2 Sensors:
Because of the lack of sensors, I just used 3 fake sensor data with random raw values.

### 2.3 BLE Module:
For transmitting the final sensor data in a given period I used a BLE module called HC-05. It is a cheap BLE module that works over UART and is easy to use. 

## Methods and Libraries
### 3.1 freeRTOS:
Since there is an RTOS expectation in the bonus part, I have included an RTOS library in my project. This will help to run the two main tasks in my project (data receiving and data transmitting) more professionally and in real time. For RTOS, I am using the freeRTOS libraries, which are very commonly used in STM32. This project will be the first project where I use freeRTOS. Previously I was using my own multithread library for PIC microcontrollers.

### 3.2 HAL:
I also used the HAL library for I2C and UART communication of my project.

### 3.3 RTC:
I use an RTC that I configured via CubeMX.

### 3.4 User Defined Libraries:
For the development of the project, I created a lot of small libraries, which made the project more manageable and organized for me. To briefly summarize the libraries, I used:

#### circular_buffer.h/.c
- buf_handle_t: Struct for buffer, includes an array, size, tail, head and capacity elements.
- buffer_init(buf_handle_t): initializes a buffer from buf_handle_t.
- buffer_insert(buf_handle_t*, float): Adds an item to buffer array.
- buffer_extract(buf_handle_t*): Removes last item from buffer.
- buffer_clear(buf_handle_t*, uint8_t): Removes last x items from buffer.
- buffer_enter_value(buf_handle_t*, float): Enters a value, can discard the oldest data.
- buffer_get_value(buf_handle_t*, float*): Gets last value from buffer. 

#### median_filter.h/.c
- compareFloats(const void*, const void*): Compares two variable.
- findMedian(float[], uint8_t): Find medians of an array.
- filter_sensor_value(buf_handle_t*, float, uint8_t, float*): To filter raw array values.

#### sensors.h/.c
- sensor_handle_t: Includes two buffers as raw and filtered, and two values as raw and float.
- sensor_init(sensor_handle_t *p_sensor_handle, uint8_t): Initializes a sensor handle struct.
- sensor_read(sensor_handle_t*): reads the sensor data and stores in .raw variable

#### stats.h/.c
- stats_handle_t: Used only in the stats.c, for clarity and return multiple values from function.
- stats_find(const float[], uint8_t, stats_handle_t*): Finds stats like min or max of sensor struct.

#### timer.h/.c
- time_handle_t: Real time clock struct, includes second, minutes and hours.
- timer_init(): To initialize RTC.
- timer_get(time_handle_t*): Gets lastest RTC data for time_handle_t struct.

#### transmit.h/.c
- transmit_data(…): Special UART fnc to transmit integer variables with a tag and line ending.
- transmit_dataf(…): Special UART fnc to transmit float variables with a tag and line ending.
- transmit_stats(…, sensor_handle_t*): To transmit all of the sensor statistics with one fnc.
- transmit_time(…, time_handle_t*); To transmit real time in UART. With a defined format.

### 3.5 Main Code
In addition to the standard configuration performed with CubeMX, the main points of my program code are as follows:

- The sample rate is defined as 1 Hz, and the broadcast period is set to 30 seconds.
- Two tasks (producer and consumer) were created to execute RTOS operations.
- Mutex; time, and sensor structs were initialized.
- In the main function, created variables were initialized.

#### 3.5.1 Producer Task
Every second, the Producer Task takes the mutex. It runs a loop for each sensor, calls a sensor read function to obtain raw data, filters it, and then stores it into a circular buffer. If overflow occurs, function discard the oldest data.

#### 3.5.2 Consumer Task
During each broadcast period, the Consumer Task takes the mutex. Transmits the current time over UART/BLE. Runs a loop for each sensor, calls the function that finds and transmits the statistics of sensor values from circular buffer.
