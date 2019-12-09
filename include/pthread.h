/*
Copyright 2019 Tampere University

Permission to use, copy, modify, and/or distribute this software for
any purpose with or without fee is hereby granted, provided that the
above copyright notice and this permission notice appear in all copies.

THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
*/

#pragma once


#ifdef __cplusplus
extern "C" {
#endif

typedef void* pthread_t;
typedef void pthread_attr_t;
typedef void* pthread_cond_t;
typedef void pthread_condattr_t;
typedef void* pthread_mutex_t;
typedef void pthread_mutexattr_t;
typedef void* pthread_rwlock_t;
typedef void pthread_rwlockattr_t;
typedef void*(voidp_voidp_func)(void*);
typedef void(void_voidp_func)(void*);

// Parameters whose names have been commented away have not been implemented,
// as Kvazaar has no use for them.
// Returning of possible error values has not been implemented, all return 0.

int pthread_create(pthread_t* thread, const pthread_attr_t* /*attr*/, voidp_voidp_func fun, void* arg);
void pthread_exit(void* /*retval*/);
pthread_t pthread_self();
int pthread_join(pthread_t thread, void** /*retval*/);

int pthread_cond_init(pthread_cond_t* cond, const pthread_condattr_t* /*attr*/);
int pthread_cond_destroy(pthread_cond_t* cond);
int pthread_cond_broadcast(pthread_cond_t* cond);
int pthread_cond_signal(pthread_cond_t* cond);
int pthread_cond_wait(pthread_cond_t* cond, pthread_mutex_t* mutex);

int pthread_mutex_init(pthread_mutex_t* mutex, const pthread_mutexattr_t* /*attr*/);
int pthread_mutex_destroy(pthread_mutex_t* mutex);
int pthread_mutex_lock(pthread_mutex_t* mutex);
int pthread_mutex_unlock(pthread_mutex_t* mutex);

int pthread_rwlock_init(pthread_rwlock_t* lock, const pthread_rwlockattr_t* /*attr*/);
int pthread_rwlock_destroy(pthread_rwlock_t* rwlock);
int pthread_rwlock_rdlock(pthread_rwlock_t* rwlock);
int pthread_rwlock_wrlock(pthread_rwlock_t* rwlock);
int pthread_rwlock_unlock(pthread_rwlock_t* rwlock);

#ifdef __cplusplus
}
#endif
