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

#include "pthread.h"
#include <condition_variable>
#include <mutex>
#include <shared_mutex>
#include <thread>
#include <unordered_map>
#include <vector>


static thread_local std::thread* this_thread = nullptr;

static int next_key_ = 0;
static std::vector<pthread_key_t> keys_;
static std::shared_mutex key_mtx_;

thread_local std::unordered_map<pthread_key_t, void*> data_;

struct rw_lock_internal {
    std::shared_mutex* lock;
    bool write_lock;
};


int pthread_create(pthread_t* thread, const pthread_attr_t*, voidp_voidp_func fun, void* arg) {
    std::thread* new_thread = new std::thread();
    *thread = new (new_thread) std::thread([&, fun, arg] {
        this_thread = new_thread;
        fun(arg);
    });
    return 0;
}

void pthread_exit(void*) {
    // It might be enough to do nothing here
    // considering Kvazaar's current use of pthread_exit.
}

pthread_t pthread_self() {
    return this_thread;
}

int pthread_join(pthread_t thread, void**) {
    static_cast<std::thread*>(thread)->join();
    delete static_cast<std::thread*>(thread);
    return 0;
}

int pthread_key_create(pthread_key_t* key, void_voidp_func dtor) {
    // The pthread_key_create() function performs no implicit synchronization.
    // It is the responsibility of the programmer to ensure that it is called
    // exactly once per key before use of the key.      POISTA KUN KAIKKI OK
    std::lock_guard<std::shared_mutex> lock(key_mtx_);
    *key = reinterpret_cast<void*>(next_key_++);
    keys_.push_back(*key);
    return 0;
}

int pthread_key_delete(pthread_key_t key) {

    return 0;
}

void* pthread_getspecific(pthread_key_t key) {
    return nullptr;
}

int pthread_setspecific(pthread_key_t key, const void* value) {
    return 0;
}

int pthread_cond_init(pthread_cond_t* cond, const pthread_condattr_t*) {
    *cond = new std::condition_variable();
    return 0;
}

int pthread_cond_destroy(pthread_cond_t* cond) {
    delete static_cast<std::condition_variable*>(*cond);
    return 0;
}

int pthread_cond_broadcast(pthread_cond_t* cond) {
    static_cast<std::condition_variable*>(*cond)->notify_all();
    return 0;
}

int pthread_cond_signal(pthread_cond_t* cond) {
    static_cast<std::condition_variable*>(*cond)->notify_one();
    return 0;
}

int pthread_cond_wait(pthread_cond_t* cond, pthread_mutex_t* mutex) {
    std::mutex* real_mutex = static_cast<std::mutex*>(*mutex);
    std::unique_lock<std::mutex> lock(*real_mutex, std::adopt_lock);
    static_cast<std::condition_variable*>(*cond)->wait(lock);
    lock.release();
    return 0;
}

int pthread_mutex_init(pthread_mutex_t* mutex, const pthread_mutexattr_t*) {
    *mutex = new std::mutex();
    return 0;
}

int pthread_mutex_destroy(pthread_mutex_t* mutex) {
    delete static_cast<std::mutex*>(*mutex);
    return 0;
}

int pthread_mutex_lock(pthread_mutex_t* mutex) {
    static_cast<std::mutex*>(*mutex)->lock();
    return 0;
}

int pthread_mutex_unlock(pthread_mutex_t* mutex) {
    static_cast<std::mutex*>(*mutex)->unlock();
    return 0;
}

int pthread_rwlock_init(pthread_rwlock_t* lock, const pthread_rwlockattr_t*) {
    *lock = new rw_lock_internal();
    static_cast<rw_lock_internal*>(*lock)->lock = new std::shared_mutex();
    static_cast<rw_lock_internal*>(*lock)->write_lock = false;
    return 0;
}

int pthread_rwlock_destroy(pthread_rwlock_t* rwlock) {
    delete static_cast<rw_lock_internal*>(*rwlock)->lock;
    delete static_cast<rw_lock_internal*>(*rwlock);
    return 0;
}

int pthread_rwlock_rdlock(pthread_rwlock_t* rwlock) {
    static_cast<rw_lock_internal*>(*rwlock)->lock->lock_shared();
    return 0;
}

int pthread_rwlock_wrlock(pthread_rwlock_t* rwlock) {
    static_cast<rw_lock_internal*>(*rwlock)->lock->lock();
    static_cast<rw_lock_internal*>(*rwlock)->write_lock = true;
    return 0;
}

int pthread_rwlock_unlock(pthread_rwlock_t* rwlock) {
    if (static_cast<rw_lock_internal*>(*rwlock)->write_lock) {
        static_cast<rw_lock_internal*>(*rwlock)->write_lock = false;
        static_cast<rw_lock_internal*>(*rwlock)->lock->unlock();
    } else {
        static_cast<rw_lock_internal*>(*rwlock)->lock->unlock_shared();
    }
    return 0;
}
