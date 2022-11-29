#include "client.h"

extern Client *c;

Client *connectAsClient(char *ip) {
	Client *c = malloc(sizeof(Client));
	struct sockaddr_in servAddr;
  
    servAddr.sin_family = INADDR_ANY;
    servAddr.sin_port = htons(5050); // use some unused port number
    servAddr.sin_addr.s_addr = inet_addr(ip);

	c->sock = socket(AF_INET, SOCK_STREAM, 0);
	c->tv.tv_sec = 0;
    c->tv.tv_usec = 0;
	
	if (connect(c->sock, (struct sockaddr*)&servAddr,sizeof(servAddr)) != 0) {
		printf("error\n");
		return NULL;
	}
	return c;
}

int receiveData(Client *c, char *buffer) {
    fd_set reader;
    ssize_t r = 0;
    int activity = 0;

    FD_ZERO(&reader);
    FD_SET(c->sock, &reader);
    activity = select(c->sock + 1, &reader, NULL, NULL, &c->tv);
    if (activity < 0)
        return -1;
    if (c->sock > 0 && FD_ISSET(c->sock, &reader)) {
        r = read(c->sock, buffer, BUFF);
        if (r == -1) {
            return -1;
        }
        buffer[r] = '\0';
    }
    return r;
}
