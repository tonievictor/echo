#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#define PORT 2000
int main(void) {
  struct sockaddr_in *address;
  int peer, fd;

  fd = socket(AF_INET, SOCK_STREAM, 0);
  if (fd < 0) {
    perror("could not create a new socket");
    return EXIT_FAILURE;
  }

  address = malloc(sizeof(struct sockaddr_in));
  if (address == NULL) {
    perror("Unable to allocate memory for address struct");
    return EXIT_FAILURE;
  }
  address->sin_family = AF_INET;
  address->sin_port = htons(PORT);
  address->sin_addr.s_addr = inet_addr("127.0.0.1");

  if (bind(fd, (struct sockaddr *)address, sizeof(*address)) == -1) {
    char errmsg[50];
    sprintf(errmsg, "unable to listen on server port %d", PORT);
    perror(errmsg);
    free(address);
    return EXIT_FAILURE;
  }

  if (listen(fd, 10) == -1) {
    perror("unable to listen on server port 2000");
    free(address);
    return EXIT_FAILURE;
  };

  printf("Listening for incoming connections on port %d \n", PORT);

  peer = accept(fd, NULL, 0);
  if (peer == -1) {
    perror("unable to listen on server port whatever");
    free(address);
    return EXIT_FAILURE;
  }

  shutdown(fd, SHUT_RDWR);
  free(address);
  return EXIT_SUCCESS;
}
