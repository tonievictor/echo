#ifndef SOCKET_GCH
#define SOCKET_GCH

#include <netinet/in.h>

typedef struct acceptedsocket_t {
  int file_desc;
  struct sockaddr_in address;
  int error;
  int status;
} acceptedsocket_s;

int createipv4socket(void);
struct sockaddr_in *createIpv4Address(int port, char* ip);
acceptedsocket_s *acceptConnection(int server_socker_fd);
void *receiver(void *arg);
void start_accepting_conn(int server_socket_fd);
void receiver_sthread(acceptedsocket_s *client);

#endif /* SOCKET_GCH */
