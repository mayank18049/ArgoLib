#ifdef __cplusplus
extern "C"{
#endif 

#include "abt.h"

#include <stdbool.h>

typedef ABT_thread Task_handle;
typedef void (*fork_t)(void* args);
/**
* Initializes the ArgoLib runtime, and it should be the first thing to call in the user main.
* Arguments “argc” and “argv” are the ones passed in the call to user main method.
*/
void argolib_init(int argc, char **argv);
/**
* Finalize the ArgoLib runtime, and performs the cleanup.
*/
void argolib_finalize();
/**
* User can use this API to launch the top-level computation kernel. This API
* gathers statistics for the parallel execution and reports after the completion
* of the computation kernel. Some of the statistics are: execution time, total
* tasks created, etc. This top-level kernel would actually be launching the recursive tasks.
*/
void argolib_kernel(fork_t fptr, void* args);
/**
* Creates an Argobot ULT that would execute a user method with the specified argument.
* It returns a pointer to the task handle that would be used for joining this ULT.
*/
Task_handle* argolib_fork(fork_t fptr, void* args);
/**
* Used for joining one more ULTs using the corresponding task handles. In case of more than one
* task handles, user can pass an array of Task_handle*. The parameter “size” is the array size.
*/
void argolib_join(Task_handle** list, int size);

#ifdef __cplusplus
}
#endif