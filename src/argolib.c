#include <stdlib.h>
#include "argolib.h"
#include "customscheduler.h"
// GLOBAL CONSTANTS
#define DEFAULT_NUM_XSTREAMS 13

// GLOBAL DECLERATIONS
ABT_xstream *xstreams;
ABT_pool *pools;
ABT_sched *scheds;
pool_stat *stats;
int *total_threads;
// TODO_DOCUMENTATION
void argolib_init(int argc, char **argv) {
    int i, j;
    int num_xstreams = DEFAULT_NUM_XSTREAMS;
    stats = (pool_stat*) malloc(num_xstreams*sizeof(pool_stat));
    total_threads = (int*)malloc(num_xstreams*sizeof(int));
    for (int i = 0;i<num_xstreams;i++){
        (stats[i]).pop = 0;
        (stats[i]).push = 0;
        (stats[i]).steal = 0;
        (stats[i]).total = 0;
        total_threads[i] = 0;

    }

    /* Allocate memory. */
    xstreams = (ABT_xstream *) malloc(sizeof(ABT_xstream) * num_xstreams);
    pools = (ABT_pool *) malloc(sizeof(ABT_pool) * num_xstreams);
    scheds = (ABT_sched *) malloc(sizeof(ABT_sched) * num_xstreams);

    /* Initialize Argobots. */
    ABT_init(argc, argv);


    /* Create pools. */
    create_pools(num_xstreams,pools);

    /* Create schedulers. */
    create_scheds(num_xstreams,pools,scheds);
    
    

    /* Set up a primary execution stream. */
    ABT_xstream_self(&xstreams[0]);
    ABT_xstream_set_main_sched(xstreams[0], scheds[0]);

    /* Create secondary execution streams. */
    for (i = 1; i < num_xstreams; i++) {
        ABT_xstream_create(scheds[i], &xstreams[i]);
    }
    

}

// TODO_DOCUMENTATION
void argolib_finalize() {
    int i;
    for (i = 1; i < DEFAULT_NUM_XSTREAMS; i++) {
        ABT_xstream_join(xstreams[i]);
        ABT_xstream_free(&xstreams[i]);
    }

    ABT_finalize();

    free(xstreams);
    free(pools);
    free(scheds);
}

// TODO_DOCUMENTATION
void argolib_kernel(fork_t fptr, void *args) {
    double t1 = ABT_get_wtime();
    fptr(args);
    double t2 = ABT_get_wtime();
    int total_push =0;
    int all_threads =0;
    for(int i=0;i<DEFAULT_NUM_XSTREAMS;i++){
        printf("Num pops:%d on stream:%d\n",(stats[i]).pop,i);
        printf("Num push:%d on stream:%d\n",(stats[i]).push,i);
        printf("Num steals:%d on stream:%d\n",(stats[i]).steal,i);
        // printf("%d\n",(stats[i]).total,i);
        total_push += stats[i].push;
        all_threads += total_threads[i];
    }
    printf("Total Push:%d\n",total_push);
    printf("Total threads:%d\n",all_threads);
    printf("elapsed time: %.6f",t2-t1);
    free(stats);
}

// TODO_DOCUMENTATION
Task_handle *argolib_fork(fork_t fptr, void *args) {
    int rank;
    ABT_xstream_self_rank(&rank);
    ABT_pool target_pool = pools[rank];
    total_threads[rank] +=1;
    Task_handle task;
    ABT_thread_create(target_pool, fptr, args, ABT_THREAD_ATTR_NULL, &task);

    Task_handle *task_ptr = (Task_handle *) malloc(sizeof(Task_handle));
    *task_ptr = task;
    return task_ptr;
}


// TODO_DOCUMENTATION
void argolib_join(Task_handle **tasks, int size) {
    for (int i = 0; i < size; ++i) {
        ABT_thread_free(tasks[i]);
    }
}
