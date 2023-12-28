#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <unistd.h>
#include "../socketgc.h"

/**
 * main - entry point of the server.
 * It initializes a server socket, binds it to a specified address
 * and port, listens for incoming connections, and
 * upon connection, accepts data from the client
 * and prints the received response.
 * Return: 0 on successful execution, otherwise it returns 1.
 *
*/
int main(void)
{
	int server_fd, bind_stat, listen_stat;
	int	client_fd;
	socklen_t client_addr_size;
	char *buffer;
	struct sockaddr_in *address;
	struct sockaddr_in client_address;

	server_fd = socket(AF_INET, SOCK_STREAM, 0);
	if (server_fd < 0) {
		perror("Unable to create socket");
		return (EXIT_FAILURE);
	}

	buffer = malloc(1024 * sizeof(char));

	address = createipv4address(2000, "");
	bind_stat = bind(server_fd, (struct sockaddr *)address, sizeof(*address));
	if (bind_stat < 0) {
		perror("Unable to bind socket to specified address");
		shutdown(server_fd, SHUT_RDWR);
		free(address);
		free(buffer);
		return (EXIT_FAILURE);
	}

	listen_stat = listen(server_fd, 10);
	if (listen_stat < 0) {
		perror("Unable to listen for incoming connections");
		shutdown(server_fd, SHUT_RDWR);
		free(address);
		free(buffer);
		return (EXIT_FAILURE);
	}
	printf("Listening for incoming connections\n");

	client_addr_size = sizeof(client_address);
	client_fd = accept(server_fd, (struct sockaddr *)&client_address, &client_addr_size);
	if (client_fd < 0) {
		perror("Unable to accept incoming connection");
		shutdown(server_fd, SHUT_RDWR);
		free(address);
		free(buffer);
		return (EXIT_FAILURE);
	}

	recv(client_fd, buffer, 1024, 0);
	printf("%s\n", buffer);

	shutdown(server_fd, SHUT_RDWR);
	free(address);
	free(buffer);
	return (EXIT_SUCCESS);
}
