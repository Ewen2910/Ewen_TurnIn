#include <pthread.h>
#include <stdbool.h>

typedef struct BuffLock {
	pthread_mutex_t *lock;
    void *buffer;
}
BuffLock;

BuffLock *makeBuffLock();

void freeBuffLock(BuffLock *bl);

void *inputThread(void *buffer);