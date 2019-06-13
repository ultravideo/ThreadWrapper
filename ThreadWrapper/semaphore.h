#pragma once

#ifdef __cplusplus
extern "C" {
#endif

typedef void* sem_t;

int sem_destroy(sem_t* sem);
// pshared is always 0 in Kvazaar on w32.
int sem_init(sem_t* sem, int /*pshared*/, unsigned int value);
int sem_post(sem_t* sem);
int sem_wait(sem_t* sem);

#ifdef __cplusplus
}
#endif
