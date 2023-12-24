#include "../socketgc.h"
#include <bits/pthreadtypes.h>
#include <errno.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <unistd.h>

struct acceptedsocket_t *accepted_list[10];
int list_count = 0;

void start_accepting_conn(int server_socket_fd)
{
  acceptedsocket_s *client_socket;
  int i = 0;

  while (1)
  {
    client_socket = acceptConnection(server_socket_fd);
    accepted_list[list_count++] = client_socket;
    receiver_sthread(client_socket);
  }
}

void subscribeer_thread(int *fd)
{
  int status;
  pthread_t id;

  status = pthread_create(&id, NULL, subscriber, fd);

  if (status != 0) {
    perror("Error creating subscriber thread: %d\n");
    return;
  }

}

void *subscriber(void *arg)
{
  int fd = *((int *)arg);
  char buffer[1024];
  ssize_t datareceived;

  while (1)
  {
    datareceived = recv(fd, buffer, 1024, 0);

    if (datareceived > 0)
    {
      buffer[datareceived] = 0;
      printf("%s\n", buffer);
    }

    if (datareceived == 0)
    {
      break;
    }
  }

  close(fd);
  return (NULL);
}

