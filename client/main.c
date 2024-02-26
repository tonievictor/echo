#include "../socketgc.h"
#include "clientgc.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>

int client_signal = 1;
pthread_mutex_t mutex;

int main(int argc, char **argv) {
  int fd, conn_result;
  struct sockaddr_in *address;
  char *line = NULL;
  size_t linesize = 0;
  ssize_t char_count, amount_sent;
  char *username, *message;
  pthread_t id;
  pthread_mutex_init(&mutex, NULL);

  if (argc != 2) {
    fprintf(stderr, "Usage: %s <username>\n", argv[0]);
    return EXIT_FAILURE;
  }
  username = strcat(argv[1], ": ");

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
      client_signal = 0;
      break;
    } else {
      line[char_count - 1] = '\0';
      message = malloc((strlen(username) + char_count) * sizeof(char));
      sprintf(message, "%s%s", username, line);
      amount_sent = send(fd, message, strlen(message), 0);
      free(message);
    }
  }

  shutdown(fd, SHUT_RDWR);
  pthread_join(id, NULL);
  pthread_mutex_destroy(&mutex);
  free(address);
  free(line);

  return (EXIT_SUCCESS);
}
