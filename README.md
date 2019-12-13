ThreadWrapper
=======
Wraps pthread functions so that they actually call C++ standard functions.

Only functions used by Kvazaar, an open-source HEVC encoder, are implemented. 
People are free to contribute if they implement other functions.

Implemented functions:
- pthread_create
- pthread_exit
- pthread_self
- pthread_join
- pthread_key_create
- pthread_key_delete
- pthread_getspecific
- pthread_setspecific
- pthread_cond_init
- pthread_cond_destroy
- pthread_cond_broadcast
- pthread_cond_signal
- pthread_cond_wait
- pthread_mutex_init
- pthread_mutex_destroy
- pthread_mutex_lock
- pthread_mutex_unlock
- pthread_rwlock_init
- pthread_rwlock_destroy
- pthread_rwlock_rdlock
- pthread_rwlock_wrlock
- pthread_rwlock_unlock
- sem_init
- sem_destroy
- sem_post
- sem_wait