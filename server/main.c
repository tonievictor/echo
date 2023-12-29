#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <unistd.h>
#include "../socketgc.h"
#include "servergc.h"

/**
 * main - entry point of the server.
 * It initializes a server socket, binds it to a specified address
 * and port, listens for incoming connections, and
 * upon connection, accepts data from the client
 * and prints the received response.
 *
 * Return: 0 on successful execution, otherwise it returns 1.
 *
*/
int main(void)
{
	int server_fd, bind_stat, listen_stat;
	struct sockaddr_in *address;
	accepted_socket_t *accepted_socket;

	server_fd = socket(AF_INET, SOCK_STREAM, 0);
	if (server_fd < 0) {
		perror("Unable to create socket");
		return (EXIT_FAILURE);
	}

	address = createipv4address(2000, "");
	bind_stat = bind(server_fd, (struct sockaddr *)address, sizeof(*address));
	if (bind_stat < 0) {
		perror("Unable to bind socket to specified address");
		shutdown(server_fd, SHUT_RDWR);
		free(address);
		return (EXIT_FAILURE);
	}

	listen_stat = listen(server_fd, 10);
	if (listen_stat < 0) {
		perror("Unable to listen for incoming connections");
		shutdown(server_fd, SHUT_RDWR);
		free(address);
		return (EXIT_FAILURE);
	}

	printf("Listening for incoming connections\n");

	accepted_socket = accept_incomming_conn(server_fd);
	receiver(accepted_socket->fd);

	shutdown(server_fd, SHUT_RDWR);
	free(address);
	free(accepted_socket);
	return (EXIT_SUCCESS);
}
