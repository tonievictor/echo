#include "../socketgc.h"
#include "servergc.h"
#include <stdio.h>
#include <unistd.h>

int server_signal = 1;

int main(void) {
  int server_fd, bind_stat, listen_stat;
  struct sockaddr_in *address;
  char *line = NULL;
  size_t linesize = 0;
  ssize_t char_count;
  pthread_t id;

  server_fd = socket(AF_INET, SOCK_STREAM, 0);
  if (server_fd < 0) {
    perror("Unable to create socket");
    return (EXIT_FAILURE);
  }

  address = createipv4address(2000, "");
  bind_stat = bind(server_fd, (struct sockaddr *)address, sizeof(*address));
  if (bind_stat < 0) {
    perror("Unable to bind socket to specified address");
    shutdown(server_fd, SHUT_RDWR);
    free(address);
    return (EXIT_FAILURE);
  }

  listen_stat = listen(server_fd, 10);
  if (listen_stat < 0) {
    perror("Unable to listen for incoming connections");
    shutdown(server_fd, SHUT_RDWR);
    free(address);
    return (EXIT_FAILURE);
  }

  printf("Listening for incoming connections. Type 'exit' to shutdown the "
         "server\n");
  pthread_create(&id, NULL, start_acccepting, &server_fd);

  while (1) {
    char_count = getline(&line, &linesize, stdin);
    if (char_count > 0 || strcmp(line, "exit\n")) {
      server_signal = 0;
      break;
    }
  }

  printf("Gracefully shutting down the server...\n");
  sleep(5);
  shutdown(server_fd, SHUT_RDWR);
  close(server_fd);
  pthread_join(id, NULL);
  free(line);
  free(address);
  printf("Bye...\n");
  return (EXIT_SUCCESS);
}
