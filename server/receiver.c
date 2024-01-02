#include "servergc.h"
#include <stdio.h>
#include <stdlib.h>

void *receiver(void *arg)
{
	int client_fd = *(int*)arg;
	char *buffer;
	ssize_t recv_stat;

	buffer = malloc(1024 * sizeof(char));
	if (buffer == NULL) {
		perror("Unable to create socket");
		return NULL;
	}

	while (1) {
		recv_stat = recv(client_fd, buffer, 1024, 0);
		if (recv_stat <= 0) {
			printf("wagwan\n");
			break;
		}
		printf("%s\n", buffer);
	}
	
	free(buffer);
	return NULL;
}
