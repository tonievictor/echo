#include "clientgc.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>

void *subscribe(void *arg) {
  int fd = *(int *)arg;
  char *buffer;
  ssize_t recv_stat;

  buffer = malloc(1024 * sizeof(char));
  if (buffer == NULL) {
  }

  while (1) {
    pthread_mutex_lock(&mutex);
    recv_stat = recv(fd, buffer, 1024, 0);
    if (recv_stat <= 0 || client_signal == 0) {
      break;
    }

    printf("%s\n", buffer);
    memset(buffer, 0, strlen(buffer));

    pthread_mutex_unlock(&mutex);
  }

  free(buffer);
  return (NULL);
}
