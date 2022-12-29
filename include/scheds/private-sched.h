#ifndef __PRIVATE_SCHED_H__
#define __PRIVATE_SCHED_H__
#include "schedutils.h"
#include <stdatomic.h>



void create_pools(int num_xstreams,ABT_pool *pools);
void create_scheds(int num_xstreams,ABT_pool *pools,ABT_sched *scheds);
#endif