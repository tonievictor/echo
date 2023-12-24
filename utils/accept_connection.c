#include "../socketgc.h"
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <unistd.h>

acceptedsocket_s *acceptConnection(int server_socket_fd)
{
  acceptedsocket_s *accepted_socket;
  int client_fd;
  struct sockaddr_in *client_add;
  socklen_t client_addsize;
  int status = 0;

  accepted_socket = malloc(sizeof(acceptedsocket_s));
  if (accepted_socket == NULL) {
    perror("Memory allocation failed. Exiting.\n");
    exit(errno);
  }
  client_addsize = sizeof(*client_add);
  client_fd = accept(server_socket_fd, (struct sockaddr *)client_add, &client_addsize);

  if (client_fd < 0) {
    perror("Error accepting connections");
    shutdown(client_fd, SHUT_RDWR);
    close(client_fd);
    free(accepted_socket);
  }

  accepted_socket->address = *client_add;
  accepted_socket->file_desc = client_fd;

  return accepted_socket;
}
