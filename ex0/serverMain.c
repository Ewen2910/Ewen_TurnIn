
#include "server.c"

int main() {
	int send = 0;
	int welcomeSize = sizeof(int);
	void *welcomeMessage = calloc(welcomeSize, 1);
	memcpy(welcomeMessage, &send, welcomeSize);

	Server *s = setUpServerConnections();
	int max = 5;
	int num = 0;
	if (s > 0) {
		bool runningServer = true;
		char *buffer = (char *)calloc(sizeof(char), BUFF + 1);
		while (runningServer) {
			printf("cc\n");
			int gotData = serverSendReceive(s, buffer);
			if (gotData != 0) {
				printf("received %i\n", *(int*)buffer);
				num += *(int*)buffer;
				if (num >= max) {
					printf("got enough data(%i), exiting now\n", num);
					runningServer = false;
				}
				memset(buffer, 0, BUFF);
				gotData = 0;
			} 
		}
		printf("server ended\n");
		free(buffer);
		closeServer(s);
	}
	free(welcomeMessage);
}
