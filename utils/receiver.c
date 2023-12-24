#include "../socketgc.h"
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <pthread.h>

void *receiver(void *arg)
{
  int client_fd = *((int *)arg);
  char buffer[1024];
  ssize_t datareceived;

  while (1)
  {
    datareceived = recv(client_fd, buffer, 1024, 0);

    if (datareceived > 0)
    {
      buffer[datareceived] = 0;
      broadcast(buffer, client_fd);
    }

    if (datareceived <= 0)
    {
      break;
    }
  }

  close(client_fd);
  return (NULL);
}

void receiver_sthread(acceptedsocket_s *client_socket)
{
  int status;
  pthread_t id;

  status = pthread_create(&id, NULL, receiver, &client_socket->file_desc);
  if (status != 0) {
    perror("Error creating receiver thread: %d\n");
    free(client_socket);
    return;
  }
}

void broadcast(char *buffer, int fd)
{
  int i, status;
  for (i = 0; i < list_count; i++)
  {
    if (accepted_list[i]->file_desc != fd) {
      send(accepted_list[i]->file_desc, buffer, strlen(buffer), 0);
    }
  }
}
