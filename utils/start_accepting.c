#include "../socketgc.h"
#include <stdio.h>
#include <stdlib.h>

void start_accepting_conn(int server_socket_fd)
{
  acceptedsocket_s *client_socket;
  int i = 0;

  while (1) {
    client_socket = acceptConnection(server_socket_fd);
    receiver_sthread(client_socket);
  }
}
