#include "../socketgc.h"
#include <stdio.h>
#include <stdlib.h>

acceptedsocket_s *acceptConnection(int server_socket_fd)
{
  acceptedsocket_s *accepted_socket;
  int client_fd;
  struct sockaddr_in *client_add;
  socklen_t client_addsize;
  int status = 0;

  accepted_socket = malloc(sizeof(acceptedsocket_s));
  client_addsize = sizeof(*client_add);
  client_fd = accept(server_socket_fd, (struct sockaddr *)client_add, &client_addsize);
  if (client_fd < 0) {
    perror("Well, look what we have here");
  }
  if (client_fd > 0) {
    status = 1;
  }

  accepted_socket->address = *client_add;
  accepted_socket->file_desc = client_fd;
  accepted_socket->status = status;

  if (accepted_socket->status > 0) {
    accepted_socket->error = client_fd;
  }

  return accepted_socket;
}
