#include "../socketgc.h"
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <unistd.h>

int main(void)
{
	int socket_fd;
	int listenstat, bindstat;
	struct sockaddr_in *server_add;

	socket_fd = createipv4socket();
	server_add = createIpv4Address(2000, "");

	bindstat = bind(socket_fd, (struct sockaddr *)server_add, sizeof(*server_add));
	if (bindstat == 0)
	{
		printf("Ready to accept incoming connections...\n");
	}

	listenstat = listen(socket_fd, 10);

	start_accepting_conn(socket_fd);

	shutdown(socket_fd, SHUT_RDWR);
	return EXIT_SUCCESS;
}
