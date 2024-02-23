#include "servergc.h"
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

accepted_socket_t *accepted_clients[10] = {NULL};
int no_of_clients = 0;

void *start_acccepting(void *fd) {
  accepted_socket_t *accepted_socket = NULL;
  pthread_t id;
  int server_fd = *(int *)fd;

  while (server_signal == 1) {
    accepted_socket = accept_incomming_conn(server_fd);
    if (accepted_socket != NULL) {
      accepted_clients[no_of_clients] = accepted_socket;
      no_of_clients++;
      pthread_create(&id, NULL, receiver, accepted_socket);
      continue;
    }
  }

  pthread_join(id, NULL);
  return (NULL);
}
