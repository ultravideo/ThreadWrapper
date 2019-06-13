#pragma once

#ifdef __cplusplus
extern "C" {
#endif

typedef void* pthread_cond_t;
typedef void* pthread_cond_t;
typedef void* pthread_mutex_t;
typedef void* pthread_t;
typedef void*(voidp_voidp_func)(void*);

typedef void pthread_attr_t;
typedef void pthread_condattr_t;
typedef void pthread_mutexattr_t;

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

#ifdef __cplusplus
}
#endif
