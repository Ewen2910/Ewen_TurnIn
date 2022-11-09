#include "client.h"

extern Client *c;

Client *connectAsClient(char *ip) {
	Client *c = malloc(sizeof(Client));
	struct sockaddr_in servAddr;
  
    servAddr.sin_family = INADDR_ANY;
    servAddr.sin_port = htons(8080); // use some unused port number
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

int receiveData(Client *c, void *buffer) {
	return 0;
}
