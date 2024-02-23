#include "servergc.h"
#include <stdio.h>
#include <stdlib.h>

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
    printf("%s\n", buffer);
  }

  free(client);
  free(buffer);
  return NULL;
}
