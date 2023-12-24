#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>

int createipv4socket(void)
{
  int socket_fd;

  socket_fd = socket(AF_INET, SOCK_STREAM, 0);

  if (socket_fd < 0) {
    perror("Error creating IPv4 socket");
    exit(errno);
  }

  return (socket_fd);
}
