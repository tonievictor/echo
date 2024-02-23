#ifndef SERVERGC_H
#define SERVERGC_H

#include <netinet/in.h>
typedef struct accepted_socket_s {
  int fd;
  struct sockaddr_in address;
} accepted_socket_t;

struct accepted_socket_s *accept_incomming_conn(int server_fd);
void *receiver(void *client_fd);
void *start_acccepting(void *fd);
void broadcast(int sender, const char *message);

extern int server_signal;
extern accepted_socket_t *accepted_clients[10];
extern int no_of_clients;

#endif /* SERVERGC_H */
