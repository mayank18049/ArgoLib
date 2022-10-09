#include <stdio.h>
#include <stdlib.h>
#include "argolib.h"

typedef struct {
    int n;
    int ret;
} fib_arg_t;


void fib(void *arg) {
    int n = ((fib_arg_t *) arg)->n;
    int *p_ret = &((fib_arg_t *) arg)->ret;

    if (n <= 1) {
        *p_ret = 1;
    } else {
        fib_arg_t child1_arg = {n - 1, 0};
        fib_arg_t child2_arg = {n - 2, 0};

        /* Calculate fib(n - 1). */
        Task_handle *task = argolib_fork(fib, &child1_arg);

        /* Calculate fib(n - 2).  We do not create another ULT. */
        fib(&child2_arg);

        Task_handle **tasks = (Task_handle **) malloc(sizeof(Task_handle*));
        tasks[0] = task;
        argolib_join(tasks, 1);

        *p_ret = child1_arg.ret + child2_arg.ret;
    }
}


int main(int argc, char **argv) {
    argolib_init(argc, argv);

    fib_arg_t arg = {10, 0};
    argolib_kernel(fib, &arg);
    printf("fib(10) = %d\n", arg.ret);

    argolib_finalize();

    return 0;
}
