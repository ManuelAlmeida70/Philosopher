#include "philo.h"

void *safe_malloc(size_t bytes)
{
    void *ret;
    
    ret = malloc(bytes);
    if (ret == NULL)
        error_exit("Error withr the malloc");
    return (ret);
}

static void handle_mutex_error(int status, t_opcode opcode)
{
    if (status == 0)
        return ;
    if (EINVAL == status && (INIT == opcode || UNLOCK == opcode))
        error_exit("The value specified by mutex is invalid.");
    else if (EINVAL == status && INIT == opcode)
        error_exit("The value specified by attr is invalid.");
    else if (EDEADLK == status)
        error_exit("A deadlock would occur if the thread blocked waitin for mutex.");
    else if (EPERM == status)
        error_exit("The current thread does not hold a lock mutex.");
    else if (ENOMEM == status)
        error_exit("The process cannot allocate enough memory to create another mutex.");
    else if (EBUSY == status)
        error_exit("Mutex is locked");
}

void safe_mutex_handle(pthread_mutex_t *mutex, t_opcode opcode)
{
    if (LOCK == opcode)
        handle_mutex_error(pthread_mutex_lock(mutex), opcode);
    else if (UNLOCK == opcode)
        handle_mutex_error(pthread_mutex_unlock(mutex), opcode);
    else if (INIT == opcode)
        handle_mutex_error(pthread_mutex_init(mutex, NULL), opcode);
    else if (DESTROY == opcode)
        handle_mutex_error(pthread_mutex_destroy(mutex), opcode);
    else
        error_exit("Wrong opcode for mutex handle");
}