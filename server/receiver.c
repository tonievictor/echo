#include "servergc.h"

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
    memset(buffer, 0, strlen(buffer));
  }

  close(client->fd);
  client = NULL;
  free(buffer);
  return NULL;
}

void broadcast(int sender, char *message) {
  int i;

  for (i = 0; i < no_of_clients; i++) {
    if (accepted_clients[i]->fd != sender && accepted_clients[i] != NULL) {
      pthread_mutex_lock(&mutex);
      send(accepted_clients[i]->fd, message, strlen(message), 0);
      pthread_mutex_unlock(&mutex);
    }
  }
}
