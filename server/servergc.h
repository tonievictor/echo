#ifndef SERVERGC_H
#define SERVERGC_H

#include <fcntl.h>
#include <netinet/in.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

typedef struct accepted_socket_s {
  int fd;
  struct sockaddr_in address;
} accepted_socket_t;

struct accepted_socket_s *accept_incomming_conn(int server_fd);
void *receiver(void *client_fd);
void *start_acccepting(void *fd);
void broadcast(int sender, char *message);

extern int server_signal;
extern accepted_socket_t *accepted_clients[10];
extern int no_of_clients;
extern pthread_mutex_t mutex;

#endif /* SERVERGC_H */
