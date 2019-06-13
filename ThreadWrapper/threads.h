#pragma once

#ifndef __cplusplus
extern "C" {
#endif

using pthread_cond_t = void*;
using pthread_mutex_t = void*;
using pthread_t = void*;
using voidp_voidp_func = void*(*)(void*);

using placeholder = void;
using pthread_attr_t = placeholder;
using pthread_condattr_t = placeholder;
using pthread_mutexattr_t = placeholder;

// Parameter names that have been commented away do nothing,
// as they are always null when the functions are used in Kvazaar.

int pthread_cond_broadcast(pthread_cond_t* cond);
int pthread_cond_destroy(pthread_cond_t* cond);
int pthread_cond_init(pthread_cond_t* cond, const pthread_condattr_t* /*attr*/);
int pthread_cond_signal(pthread_cond_t* cond);
int pthread_cond_wait(pthread_cond_t* cond, pthread_mutex_t* mutex);

int pthread_create(pthread_t* thread, const pthread_attr_t* /*attr*/, voidp_voidp_func executee, void* arg);
void pthread_exit(void* /*value_ptr*/);
int pthread_join(pthread_t thread, void** /*value_ptr*/);

int pthread_mutex_destroy(pthread_mutex_t* mutex);
int pthread_mutex_init(pthread_mutex_t* mutex, const pthread_mutexattr_t* /*attr*/);
int pthread_mutex_lock(pthread_mutex_t* mutex);
int pthread_mutex_unlock(pthread_mutex_t* mutex);

#ifndef __cplusplus
}
#endif
