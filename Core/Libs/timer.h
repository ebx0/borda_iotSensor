#ifndef TIMER_H
#define TIMER_H

#include <stdint.h>
#include "main.h"



typedef struct {
    uint8_t hours;
    uint8_t minutes;
    uint8_t seconds;
} time_handle_t;

uint8_t timer_get(time_handle_t*);

#endif /* TIMER_H */
