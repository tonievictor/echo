#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#define MAX_BUF_SIZE 1024
pthread_mutex_t lock;

int main(int argc, char **argv) {
  int fd, port;
  struct sockaddr_in *address;
  char *line = NULL;
  size_t n;
  ssize_t char_count;
  char buffer[MAX_BUF_SIZE];

  if (argc != 3) {
    printf("Usage %s <port> <username>\n", argv[0]);
    return EXIT_FAILURE;
  }
  port = atoi(argv[1]);
  if (port == 0) {
    printf("invalid port provided: %s\n", argv[1]);
    return EXIT_FAILURE;
  }

  fd = socket(AF_INET, SOCK_STREAM, 0);
  address = malloc(sizeof(struct sockaddr_in *));
  if (address == NULL) {
    perror("could not allocate memory for the server addr");
    close(fd);
    return EXIT_FAILURE;
  }
  address->sin_family = AF_INET;
  address->sin_port = htons(port);
  address->sin_addr.s_addr = inet_addr("127.0.0.1");

  if (connect(fd, (struct sockaddr *)address, sizeof(struct sockaddr)) == -1) {
    perror("could not establish a connection to the server");
    free(address);
    close(fd);
    return EXIT_FAILURE;
  }

  while (1) {
    char_count = getline(&line, &n, stdin);
    if (char_count == -1) {
      perror("ERROR: could not read user input");
      free(line);
      free(address);
      close(fd);
      return EXIT_FAILURE;
    }

    if (strcmp(line, "exit\n") == 0)
      break;

    if (send(fd, line, char_count, 0) == -1) {
      perror("ERROR: could not send message");
      free(line);
      free(address);
      close(fd);
      return EXIT_FAILURE;
    }
    if (recv(fd, buffer, MAX_BUF_SIZE, 0) == -1) {
      perror("ERROR: could not send message");
      continue;
    }
    printf("%s", buffer);
    memset(buffer, 0, MAX_BUF_SIZE * sizeof(char));
  }

  free(address);
  close(fd);
  free(line);
  return EXIT_SUCCESS;
}
