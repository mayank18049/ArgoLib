#ifndef __CUST_SCHED_H__
#define __CUST_SCHED_H__
#include "abt.h"
#include <stdlib.h>
#include <pthread.h>
typedef struct {
    uint32_t push;
    uint32_t pop;
    uint32_t steal;
    uint32_t total;
} pool_stat;


void create_pools(int num_xstreams,ABT_pool *pools);
void create_scheds(int num_xstreams,ABT_pool *pools,ABT_sched *scheds);

#endif