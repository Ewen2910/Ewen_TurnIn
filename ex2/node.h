#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include<stdbool.h>
#include <sys/types.h>
#include <fcntl.h>
#include <curses.h>
#include <termios.h>
#include <pthread.h>


void runNode(void (*processData)(void*, bool), void (*welcome)(void), void (*parse)(char*), char *ip){
    pthread_t input;
    pthread_t server;
    pthread_t client;
    pthread_create(&input, NULL, foo, &j);
}
    This is the main function of your code. It will start and handle the 3 threads for input, server, and client. It takes 3 arguments that are all function pointers (this will become clear why later). processData will be called on any information received from a remote server or remote client. welcome will be called when you know your server has been set up properly. parse will be called on any user input coming from that thread.
	This function will have references to the local server and clients. So it will handle taking information from them and chaining it along to remote servers and clients.

void *runServer(void *buff);
	This function will run the server. It will handle a BuffLock to lock up the shared buffer and copy to it what is received from the server. The BuffLock is used to shre data between this thread and the node thread.

void *runClient(void *buff);
	This function will run the client. It will handle a BuffLock to lock up the shared buffer and copy to it what is received from the server. The BuffLock is used to shre data between this thread and the node thread.

void processString(void* buff, bool onServer);
	This function will take Data from the network (either server or client) unpack it and display the text inside with appropriate tag based on the value of onServer. 
Example – string: “fishy tacos”, onServer: false - output: [client] fishy tacos
Example – string: “fishy tacos”, onServer: true - output: [server] fishy tacos

void sendInput(char *buff);
	This function takes in the whatever data is on buff (received from user input) and if there is a local server running it send it to its remote clients, if there is a local client connected to a remote server it sends it to that server
 
void welcomeText();
	This function sets up welcomeMessage and welcomeSize. welcomeMessage will be a Data struct with a string in arr, written into a buffer. welcomeSize will be the size of that buffer.