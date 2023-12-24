#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include "../socketgc.h"

/**
 * main -
 */
int main(int argc, char **argv)
{
	int socket_fd, conn_result;
	char *line = NULL;
	size_t linesize = 0;
	ssize_t charcount, datasent;
	struct sockaddr_in *address;
  char buffer[1024];

  if (argc != 2) {
    fprintf(stderr, "Enter a username -> Usage: %s <username>\n", argv[0]);
    return (EXIT_FAILURE);
  }

	socket_fd = socket(AF_INET, SOCK_STREAM, 0);
  if (socket_fd < 0) {
    perror("Error creating socket");
    return EXIT_FAILURE;
  }

	address = createIpv4Address(2000, "127.0.0.1");

	conn_result = connect(socket_fd, (struct sockaddr *)address, sizeof(*address));
  if (conn_result < 0) {
    perror("Error connecting to server");
    close(socket_fd);
    free(address);
    return (EXIT_FAILURE);
  }
	printf("Connected! Type a message and press enter to send, or type 'exit' to exit.\r\n");

  subscribeer_thread(&socket_fd);
	while (1)
	{
		charcount = getline(&line, &linesize, stdin);

		if (charcount > 0)
		{
			if (strcmp(line, "exit\n") == 0)
			{
				break;
			}
      sprintf(buffer, "%s: %s", argv[1], line);
			datasent = send(socket_fd, buffer, strlen(buffer), 0);
      if (datasent < 0) {
        perror("Error sending message");
        break;
      }
		}
	}

	close(socket_fd);
	free(line);
  free(address);
	return (EXIT_SUCCESS);
}
