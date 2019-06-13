#include "semaphore.h"
#include <condition_variable>
#include <mutex>


class Semaphore {
public:

    Semaphore(int threads):
        capacity_(threads) {
    }

    virtual ~Semaphore() {
        release();
    }
    
    void release(){
        std::unique_lock<std::mutex> lock(mutex_);
        if (waiting_threads_ == 0) {
            return;
        }

        releasing_threads_ = true;
        cvar_.notify_all();
        cvar_.wait(lock, [&] { return !releasing_threads_; });
    }

    void wait() {
        // Wait if threads from last round are still being released
        std::unique_lock<std::mutex> lock(mutex_);
        cvar_.wait(lock, [&] { return !releasing_threads_; });

        // Wait until all threads are waiting
        if (++waiting_threads_ < capacity_) {
            cvar_.wait(lock, [&] { return releasing_threads_; });

        } else {
            release();
        }

        // Wake up sleeping threads
        releasing_threads_ = --waiting_threads_;
        cvar_.notify_all();
    }


private:

    bool releasing_threads_ = false;
    int waiting_threads_ = 0;
    int capacity_;
    std::condition_variable cvar_;
    std::mutex mutex_;       

};  // class Barrier


int sem_destroy(sem_t* sem) {
    delete static_cast<Semaphore*>(*sem);
    *sem = nullptr;
    return 0;
}

int sem_init(sem_t* sem, int, unsigned int value) {
    *sem = new Semaphore(value);
    return 0;
}

int sem_post(sem_t* sem) {
    static_cast<Semaphore*>(*sem)->release();
    return 0;
}

int sem_wait(sem_t* sem) {
    static_cast<Semaphore*>(*sem)->wait();
    return 0;
}
