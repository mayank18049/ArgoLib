#ifndef __ARGOLIB_HPP__
#define __ARGOLIB_HPP__
#include "abt.h"
#include "argolib.h"

namespace argolib{
typedef ABT_thread Task_handle;
typedef void (*fork_t)(void* args);
/**
* C++ equivalent of the argolib_init API.
*/
void init(int argc, char **argv){
    argolib_init(argc,argv);
}
/**
* C++ equivalent of the argolib_finalize API.
*/
void finalize(){
    argolib_finalize();
}
// TODO FIGURE OUT LAMBDAS
/**
* C++ equivalent of the argolib_kernel API. User lambda passed instead of function pointer and args.
*/
template<typename T>
void kernel(T &&lambda){
    // TODO
};
/**
* C++ equivalent of the argolib_fork API. User lambda passed instead of function pointer and args.
*/
template<typename T>
Task_handle* fork(T &&lambda){
    // TODO
}
/**
* C++ equivalent of the argolib_join API.
* All the task handles are passed as comma separated list. The three dots “...” represents variable
* number of arguments.
*/
template<typename... T>
void join(T... handles){
    // TODO
}
} //end namespace argolib
#endif