#ifndef __CUST_SCHED_H__
#define __CUST_SCHED_H__
#include "schedutils.h"
void create_pools(int num_xstreams,ABT_pool *pools);
void create_scheds(int num_xstreams,ABT_pool *pools,ABT_sched *scheds);

#endif