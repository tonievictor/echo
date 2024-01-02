#ifndef SERVERGC_H
#define SERVERGC_H

#include <netinet/in.h>
typedef struct accepted_socket_s {
	int fd;
	struct sockaddr_in address;
} accepted_socket_t;

struct accepted_socket_s *accept_incomming_conn(int server_fd);
void *receiver(void *client_fd);
void start_acccepting(int fd);

#endif /* SERVERGC_H */
