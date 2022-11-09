#include "inputThread.h"

BuffLock *makeBuffLock() {

}
	//create BuffLock struct, allocated buffer to size of BUFF, and initalize lock.

void freeBuffLock(BuffLock *bl) {

}
	//frees allocated memory for buffer and lock as well as the memory for bl.

void *inputThread(void *buffer) {

}
	//Receives a shared buffer with a pthread_mutex_t stored in it.  Pull the pthread_mutex_t out and store it. Test your code to make sure that this lock is properly connected to the pthread_mutex_t being used in main.
	//buffer is shared between this thread and the main thread. In a loop have this function take in user input and stores it in a buffer, when the user hits enter take in the string from the input buffer and copy it into the shared buffer via a Data struct. The main thread should then pick up that there is data in the buffer, and unpack it to display the string the user typed in.
	//If the user hits the escape key have the program end. Hint take in the user input charavter at a time, rather than line by line.