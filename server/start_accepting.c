#include "servergc.h"
#include <pthread.h>

accepted_socket_t *accepted_clients[10] = {NULL};
int no_of_clients = 0;
pthread_mutex_t mutex;

void *start_acccepting(void *fd) {
  accepted_socket_t *accepted_socket = NULL;
  pthread_t id;
  int server_fd = *(int *)fd;
  pthread_mutex_init(&mutex, NULL);

  while (server_signal == 1) {
    accepted_socket = accept_incomming_conn(server_fd);
    if (accepted_socket != NULL) {
      accepted_clients[no_of_clients] = accepted_socket;
      no_of_clients++;
      pthread_create(&id, NULL, receiver, accepted_socket);
    }
    pthread_detach(id);
  }

  pthread_mutex_destroy(&mutex);
  return (NULL);
}
