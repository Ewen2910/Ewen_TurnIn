#include "data.h"

bool littleEndian() {
    unsigned int i = 1;
    char *c = (char*)&i;
    if (*c) {
        return true;
    }
    else
        return false;
}

Data *makeData(void *dat, int bytes){
    Data *d = malloc(sizeof(Data));
     d->arr = malloc(sizeof(int) * bytes);
    d->arr = dat;
    d->bytes = bytes;
    return d;
}

void *writeData(Data *d) {
    void * res = malloc(sizeof(void) * d->bytes);
    memcpy(res, d->arr, sizeof(d->bytes));
    return res;
}
    //Allocates a buffer with the exact size of the Data and then copies the data being pointed to by the Data struct into the buffer along with the size of the buffer. Returns a pointer to the buffer.

Data *readData(void *buffer) {
    Data *d = malloc(sizeof(Data));

    int size = 0;
    memcpy(&size, buffer, sizeof(int));
    d->bytes = size;

    d->arr = calloc(1, size);
    memcpy(d->arr, buffer + sizeof(int), size);
    return d;
}
	//Declares a Data struct. Reads from buffer created with the writeData function. First it reads size from the buffer (and copies it into the Data struct’s bytes field) so that it knows how much data is in the buffer. Then it reads that much data from the buffer and copies it into the Data struct’s arr field.

void freeData(Data *d){
    free(d->arr);
    free(d);
}
//Free the allocated array in d and also d itself.