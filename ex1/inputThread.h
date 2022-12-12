#include "data.c"

typedef struct BuffLock {
    pthread_mutex_t *lock;
    void *buffer;
} BuffLock;

BuffLock *makeBuffLock();

void freeBuffLock(BuffLock *bl);

void *flipEndian(void *buff, int size);

void *inputThread(void *buffer);



// #include <stdio.h>
// #include <stdlib.h>
// #include <unistd.h>
// #include <errno.h>
// #include <string.h>
// #include <stdbool.h>
// #include <curses.h>
// #include <termios.h>
// #include <pthread.h>
// #include <time.h>
// #include "data.c"

// typedef struct BuffLock {
//     pthread_mutex_t *lock;
//     void *buffer;
// } BuffLock;

// BuffLock *makeBuffLock();

// void freeBuffLock(BuffLock *bl);

// void *flipEndian(void *buff, int size);

// void *inputThread(void *buffer);

// void *flipEndian(void *buff, int size);

// void *inputThread(void *buffer);
