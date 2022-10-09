#include <stdlib.h>
#include "argolib.h"
#include "customscheduler.h"
// GLOBAL CONSTANTS
#define DEFAULT_NUM_XSTREAMS 4

// GLOBAL DECLERATIONS
ABT_xstream *xstreams;
ABT_pool *pools;
ABT_sched *scheds;

// TODO_DOCUMENTATION
void argolib_init(int argc, char **argv) {
    int i, j;
    int num_xstreams = DEFAULT_NUM_XSTREAMS;

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
    fptr(args);
}

// TODO_DOCUMENTATION
Task_handle *argolib_fork(fork_t fptr, void *args) {
    int rank;
    ABT_xstream_self_rank(&rank);
    ABT_pool target_pool = pools[rank];

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
