#include "../socketgc.h"
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

void *receiver(void *arg)
{
  int client_fd = *((int *)arg);
  char buffer[1024];
  ssize_t datareceived;

  while (1) {
    datareceived = recv(client_fd, buffer, 1024, 0);

    if (datareceived  > 0) {
      buffer[datareceived] = 0;
      printf("%d: %s\n", client_fd, buffer);
    }

    if (datareceived == 0) {
      break;
    }
  }

  close(client_fd);
  return (NULL);
}

void receiver_sthread(acceptedsocket_s *client_socket)
{
  pthread_t id;

  pthread_create(&id, NULL, receiver, &client_socket->file_desc);
}
