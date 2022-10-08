#include <stdlib.h>
#include <argolib.h>
// GLOBAL CONSTANTS
#define DEFAULT_NUM_XSTREAMS 1
// GLOBAL DECLERATIONS
ABT_xstream *xstreams;
ABT_pool *pools;
ABT_sched *scheds;
ABT_thread *top_thread;

// TODO_DOCUMENTATION
void argolib_init(int argc, char **argv){
    int i,j;
    int num_xstreams = DEFAULT_NUM_XSTREAMS;
    xstreams = (ABT_xstream *)malloc(sizeof(ABT_xstream) * num_xstreams);
    pools = (ABT_pool *)malloc(sizeof(ABT_pool) * num_xstreams);
    scheds = (ABT_sched *)malloc(sizeof(ABT_sched) * num_xstreams);
    ABT_init(argc, argv);
    
    for(i = 0;i<num_xstreams;i++){
        ABT_pool_create_basic(ABT_POOL_RANDWS, ABT_POOL_ACCESS_MPMC, ABT_TRUE, &pools[i]);
    }

    for (i = 0; i < num_xstreams; i++) {
        ABT_pool *tmp = (ABT_pool *)malloc(sizeof(ABT_pool) * num_xstreams);
        for (j = 0; j < num_xstreams; j++) {
            tmp[j] = pools[(i + j) % num_xstreams];
        }
        ABT_sched_create_basic(ABT_SCHED_RANDWS, num_xstreams, tmp,
                               ABT_SCHED_CONFIG_NULL, &scheds[i]);
        free(tmp);
    }
    ABT_xstream_self(&xstreams[0]);
    ABT_xstream_set_main_sched(xstreams[0], scheds[0]);
    for (i = 1; i < num_xstreams; i++) {
        ABT_xstream_create(scheds[i], &xstreams[i]);
    }

}
// TODO_DOCUMENTATION
void argolib_finalize(){
    ABT_thread_join(top_thread);
    ABT_thread_free(top_thread);
    free(top_thread);
    ABT_finalize();
}
// TODO_DOCUMENTATION
void argolib_kernel(fork_t fptr, void* args){
    top_thread = (ABT_thread *)malloc(sizeof(ABT_thread));
    ABT_thread_create(pools[0], fptr, args,
                          ABT_THREAD_ATTR_NULL, top_thread);
}
// TODO_DOCUMENTATION
Task_handle* argolib_fork(fork_t fptr, void* args){
    Task_handle * task;
    task = (ABT_thread *)malloc(sizeof(ABT_thread));
    ABT_thread_create(pools[0], fptr, args,
                          ABT_THREAD_ATTR_NULL, task);
    return task;
}
// TODO_DOCUMENTATION
void argolib_join(Task_handle** list, int size){
    ABT_thread_join_many(list,size);
    for(int i =0;i<size;i++){
        free(list[i]);
    }
}