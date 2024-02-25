#include "../socketgc.h"
#include "clientgc.h"
#include <netinet/in.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

int main(int argc, char **argv) {
  int fd, conn_result;
  struct sockaddr_in *address;
  char *line = NULL;
  size_t linesize = 0, usernamesize, messagesize;
  ssize_t char_count, amount_sent;
  char *username, *message;
  pthread_t id;

  if (argc != 2) {
    fprintf(stderr, "Usage: %s <username>\n", argv[0]);
    return EXIT_FAILURE;
  }
  username = argv[1];
  usernamesize = strlen(username);

  fd = socket(AF_INET, SOCK_STREAM, 0);
  if (fd < 0) {
    perror("Unable to create socket");
    return (EXIT_FAILURE);
  }

  address = createipv4address(2000, "127.0.0.1");
  conn_result = connect(fd, (struct sockaddr *)address, sizeof(*address));
  if (conn_result != 0) {
    perror("Unable to connect to the server");
    close(fd);
    free(address);
    return (EXIT_FAILURE);
  }

  printf("Connected! Type a message and press enter to send, or type 'exit' to "
         "exit.\r\n");

  pthread_create(&id, NULL, subscribe, &fd);
  while (1) {
    char_count = getline(&line, &linesize, stdin);
    if (char_count < 0 || strcmp(line, "exit\n") == 0) {
      break;
    }
    line[char_count - 1] = 0;
    messagesize = usernamesize + (char_count - 1) + 2;
    message = str_cat(username, line);
    amount_sent = send(fd, message, messagesize, 0);
  }

  pthread_join(id, NULL);
  close(fd);
  free(address);
  free(line);
  return (EXIT_SUCCESS);
}

char *str_cat(char *username, char *message) {
  char *res;

  if (username == NULL || message == NULL) {
    return (NULL);
  }

  res = strcat(username, ": ");
  res = strcat(res, message);

  return res;
}
