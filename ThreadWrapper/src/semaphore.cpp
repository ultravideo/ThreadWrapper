#include "semaphore.h"
#include <condition_variable>
#include <mutex>


class Semaphore {
public:

    Semaphore(int value):
        val_(value) {
    }

    void post() {
        std::unique_lock<std::mutex> lck(mtx_);
        if (++val_ <= 0) {
            cvar_.notify_one();
        }
    }

    void wait() {
        std::unique_lock<std::mutex> lck(mtx_);
        if (--val_ < 0) {
            cvar_.wait(lck);
        }
    }


private:

    int val_;
    std::condition_variable cvar_;
    std::mutex mtx_;

};  // class Semaphore


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
    static_cast<Semaphore*>(*sem)->post();
    return 0;
}

int sem_wait(sem_t* sem) {
    static_cast<Semaphore*>(*sem)->wait();
    return 0;
}
