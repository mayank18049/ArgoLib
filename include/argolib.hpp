#ifndef __ARGOLIB_H__
#define __ARGOLIB_H__
#include <abt.h>

namespace argolib{
typedef ABT_thread Task_handle;
typedef void (*fork_t)(void* args);
/**
* C++ equivalent of the argolib_init API.
*/
void init(int argc, char **argv);
/**
* C++ equivalent of the argolib_finalize API.
*/
void finalize();
// TODO FIGURE OUT LAMBDAS
/**
* C++ equivalent of the argolib_kernel API. User lambda passed instead of function pointer and args.
*/
// void kernel(T &&lambda);
/**
* C++ equivalent of the argolib_fork API. User lambda passed instead of function pointer and args.
*/
// Task_handle* fork(T &&lambda);
/**
* C++ equivalent of the argolib_join API.
* All the task handles are passed as comma separated list. The three dots “...” represents variable
* number of arguments.
*/
// void join(T... handles);
} //end namespace argolib
#endif