#include "servergc.h"
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

void start_acccepting(int fd)
{
	accepted_socket_t *accepted_socket;
	pthread_t id_receive;
	char *line = NULL;
	size_t linesize = 0;
	ssize_t char_count;

	while (1) {
		accepted_socket = accept_incomming_conn(fd);	
		pthread_create(&id_receive, NULL, receiver, &accepted_socket->fd);
	}

	free(accepted_socket);
}
