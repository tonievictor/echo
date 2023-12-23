#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "../socketgc.h"

/**
 * main - 
*/
int main(void)
{
  int socket_fd, conn_result;
  char *line = NULL;
  size_t linesize = 0;
  ssize_t charcount, datasent;
  struct sockaddr_in *address;

  socket_fd = createipv4socket();

  address = createIpv4Address(2000,"127.0.0.1");
  conn_result = connect(socket_fd, (struct sockaddr *)address, sizeof(*address));
  if (conn_result == 0) {
    printf("Connection to the server was successful\n");
  }

  while (1) {
    charcount = getline(&line, &linesize, stdin);

    if (charcount > 0) {
      if (strcmp(line, "exit\n") == 0) {
        break;
      }
      datasent = send(socket_fd, line, charcount, 0);
    }
  }

  close(socket_fd);
  return (EXIT_SUCCESS);
}
