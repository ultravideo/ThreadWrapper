
#include "threads.h"
#include <iostream>
#include <string>
#include <thread>


void* f(void* a) {
    int i = *(int*)a;
    while (i) {
        std::cout << std::string(std::to_string(i--) + '\n');
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }
    return nullptr;
}

int main(int argc, char** argv) {
    pthread_t t1, t2, t3;
    int i1 = 3, i2 = 4, i3 = 2;
    pthread_create(&t1, nullptr, f, &i1);
    pthread_create(&t2, nullptr, f, &i2);
    pthread_create(&t3, nullptr, f, &i3);
    pthread_join(t2, nullptr);
    std::cout << "f exit" << std::endl;
    return 0;
}
