#include "servergc.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>

void *receiver(void *arg) {
  accepted_socket_t *client = (accepted_socket_t *)arg;
  char *buffer;
  ssize_t recv_stat;

  buffer = malloc(1024 * sizeof(char));
  if (buffer == NULL) {
    perror("Unable to create socket");
    return NULL;
  }

  while (1) {
    recv_stat = recv(client->fd, buffer, 1024, 0);
    if (recv_stat <= 0 || server_signal == 0) {
      break;
    }
    broadcast(client->fd, buffer);
    memset(buffer, 0, 1024);
  }

  free(client);
  free(buffer);
  return NULL;
}

void broadcast(int sender, const char *message) {
  int i;

  for (i = 0; i < no_of_clients; i++) {
    if (accepted_clients[i]->fd != sender) {
      send(accepted_clients[i]->fd, message, strlen(message), 0);
    }
  }
}
