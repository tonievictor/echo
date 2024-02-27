#include "servergc.h"
#include <errno.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

accepted_socket_t *accept_incomming_conn(int server_fd) {
  accepted_socket_t *accepted_socket;
  struct sockaddr_in client_address;
  int client_fd;
  socklen_t client_addr_size;

  accepted_socket = malloc(sizeof(accepted_socket_t));
  if (accepted_socket == NULL) {
    perror("Unable to allocate memory for the accepted_socket");
    return (NULL);
  }

  client_addr_size = sizeof(client_address);
  client_fd =
      accept(server_fd, (struct sockaddr *)&client_address, &client_addr_size);
  if (client_fd < 0) {
    if (errno != 22) {
      perror("Unable to accept incoming connection");
    }
    free(accepted_socket);
    return (NULL);
  }

  accepted_socket->fd = client_fd;
  accepted_socket->address = client_address;

  return (accepted_socket);
}
