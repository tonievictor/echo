#include "servergc.h"
#include <stdio.h>
#include <stdlib.h>

struct accepted_socket_s *accept_incomming_conn(int server_fd)
{
	accepted_socket_t *accepted_socket;
	struct sockaddr_in client_address;
	int	client_fd;
	socklen_t client_addr_size;

	accepted_socket = malloc(sizeof(accepted_socket_t));
	if (accepted_socket == NULL) {
		perror("Unable to allocate memory for the accepted_socket");
		return (NULL);
	}

	client_addr_size = sizeof(client_address);
	client_fd = accept(server_fd, (struct sockaddr *)&client_address, &client_addr_size);
	if (client_fd < 0) {
		perror("Unable to accept incoming connection");
		return (NULL);
	}

	accepted_socket->fd = client_fd;
	accepted_socket->address = client_address;

	return (accepted_socket);
}
