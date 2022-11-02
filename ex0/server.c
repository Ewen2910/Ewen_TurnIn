#include "server.h"

extern void *welcomeMessage;
extern int welcomeSize;
extern Server *s;

Server* setUpServerConnections() {
	printf("Start\n");

	Server *s = malloc(sizeof(Server));

	s->addr.sin_addr.s_addr = INADDR_ANY;
	s->addr.sin_family = AF_INET;
    s->addr.sin_port = htons(5004);
    s->sock = socket(AF_INET, SOCK_STREAM, 0);
	bind(s->sock, (struct sockaddr*)&s->addr, sizeof(s->addr));
    listen(s->sock, 0);
	printf("Listening for incoming connections\n");
	s->clientSocks = malloc(sizeof(int) * 11);

	int y = 0;
    for (; y != 9; y++) {
        s->clientSocks[y] = 0;
    }
    s->clientSocks[y+1] = -1;
	return s;
}

void closeServer(Server *s) {
    if (s->clientSocks != NULL) {
        for (int i = 0; i < s->maxClients; i++) {
            if (s->clientSocks[i] != 0) {
                close(s->clientSocks[i]);
            }
        }
        free(s->clientSocks);
    }
    close(s->sock);
    free(s);
}

int serverSendReceive(Server *s, void *buffer) {

	int client = accept(s->sock, (struct sockaddr *)NULL, NULL);

	int i = 0;
    for (; i <= 10; i++) {
        if (s->clientSocks[i] == 0) {
            s->clientSocks[i] = client;
            break;
        }
    }
	
	dprintf(client, "hell0");
	printf("Client has connected\n");

	return client;
}
