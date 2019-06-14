#include "pthread.h"
#include <condition_variable>
#include <mutex>
#include <thread>


int pthread_cond_broadcast(pthread_cond_t* cond) {
    static_cast<std::condition_variable*>(*cond)->notify_all();
    return 0;
}

int pthread_cond_destroy(pthread_cond_t* cond) {
    delete static_cast<std::condition_variable*>(*cond);
    *cond = nullptr;
    return 0;
}

int pthread_cond_init(pthread_cond_t* cond, const pthread_condattr_t*) {
    *cond = new std::condition_variable();
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

int pthread_create(pthread_t* thread, const pthread_attr_t*, voidp_voidp_func executee, void* arg) {
    *thread = new std::thread(executee, arg);
    return 0;
}

void pthread_exit(void*) {
    // It might be enough to do nothing here
    // considering Kvazaar's current use of pthread_exit
}

int pthread_join(pthread_t thread, void**) {
    std::thread* real_thread = static_cast<std::thread*>(thread);
    real_thread->join();
    delete real_thread;
    return 0;
}

int pthread_mutex_destroy(pthread_mutex_t* mutex) {
    delete static_cast<std::mutex*>(*mutex);
    *mutex = nullptr;
    return 0;
}

int pthread_mutex_init(pthread_mutex_t* mutex, const pthread_mutexattr_t*) {
    *mutex = new std::mutex();
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
