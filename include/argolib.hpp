#ifndef __ARGOLIB_HPP__
#define __ARGOLIB_HPP__
#include "abt.h"
#include "argolib.h"
#include <functional>
#include <type_traits>

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
void lambda_wrapper(void *arg) {
    T *lambda = static_cast<T* >(arg);
    (*lambda)(); // !!! May cause a worker-swap !!!
    delete lambda;
}
template<typename T>
void kernel(T &&lambda){
    // TODO
    argolib_kernel(lambda_wrapper<T>, new T(lambda));
}

/**
* C++ equivalent of the argolib_fork API. User lambda passed instead of function pointer and args.
*/
template<typename T>
Task_handle* fork(T &&lambda){
    // TODO
    typedef typename std::remove_reference<T>::type U;
    return argolib_fork(lambda_wrapper<U>, new U(lambda));
}
template <typename... Ts>
Task_handle **construct_handles_list(Ts... handles) {
    const size_t n = sizeof...(handles); // parameter pack count
    return new Task_handle*[n+1] { handles..., nullptr };
}
/**
* C++ equivalent of the argolib_join API.
* All the task handles are passed as comma separated list. The three dots “...” represents variable
* number of arguments.
*/
template<typename... T>
void join(T... handles){
    // TODO
    Task_handle ** task_handles = construct_handles_list(handles ...);
    int sz = 0;
    for(int i =0;;i++){
        if(task_handles[i] == nullptr){
            break;
        }
        sz +=1;
    }
    argolib_join(task_handles,sz);
    // delete task_handles;

}

} //end namespace argolib
#endif