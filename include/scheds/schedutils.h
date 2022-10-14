#ifndef __SCHED_UTILS_H__
#define __SCHED_UTILS_H__
#include "abt.h"
#include <stdlib.h>
#include <pthread.h>

typedef struct {
    uint32_t push;
    uint32_t pop;
    uint32_t steal;
    uint32_t total;
} pool_stat;

typedef struct {
    uint event_freq;
} sched_data_t;

#endif