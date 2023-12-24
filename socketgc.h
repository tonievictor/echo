#ifndef SOCKET_GCH
#define SOCKET_GCH

#include <netinet/in.h>

typedef struct acceptedsocket_t
{
  int file_desc;
  struct sockaddr_in address;
} acceptedsocket_s;

extern struct acceptedsocket_t *accepted_list[10];
extern int list_count;

int createipv4socket(void);
struct sockaddr_in *createIpv4Address(int port, char *ip);
acceptedsocket_s *acceptConnection(int server_socker_fd);
void *receiver(void *arg);
void *subscriber(void *arg);
void start_accepting_conn(int server_socket_fd);
void receiver_sthread(acceptedsocket_s *client);
void subscribeer_thread(int *fd);
void broadcast(char *buffer, int fd);

#endif /* SOCKET_GCH */
