#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <stdbool.h>
#include <curses.h>
#include <termios.h>
#include <pthread.h>

typedef struct Data {
    int bytes;
    void *arr;
} Data;

extern bool runningMainThread;
bool runningMainThread = true;

bool littleEndian();

Data *makeData(void *dat, int bytes);

void *writeData(Data *d);

Data *readData(void *buffer);

void freeData(Data *d);


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

// typedef struct Data {
// 	int bytes;
// 	void *arr;
// } Data;

// extern bool runningMainThread;

// bool littleEndian();
// 	// return true if your computer is little endian and false if it is big endian.

// Data *makeData(void *dat, int bytes);
// 	// Takes in pointer to data and an amount of bytes that are in the data. It creates Data *d and allocates d->arr to the size of bytes and then copies the data from dat into d→arr.

// void *writeData(Data *d);
// 	// Allocates a buffer with the exact size of the Data and then copies the data being pointed to by the Data struct into the buffer along with the size of the buffer. Returns a pointer to the buffer.

// Data *readData(void *buffer);
// 	// Declares a Data struct. Reads from buffer created with the writeData function. First it reads size from the buffer (and copies it into the Data struct’s bytes field) so that it knows how much data is in the buffer. Then it reads that much data from the buffer and copies it into the Data struct’s arr field.

// void freeData(Data *d);
// 	// Free the allocated array in d and also d itself.