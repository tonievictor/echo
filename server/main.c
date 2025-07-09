#include "server.h"

#define PORT 2000
#define BUF_SIZE 1024

typedef struct sockaddr_in Addr;

int main(void) {
  int sfd = socket(AF_INET, SOCK_STREAM, 0);
  if (sfd < 0) {
    perror("could not create a new socket");
    return EXIT_FAILURE;
  }

  Addr *address = malloc(sizeof(Addr));
  if (address == NULL) {
    perror("Unable to allocate memory for address struct");
    return EXIT_FAILURE;
  }
  address->sin_family = AF_INET;
  address->sin_port = htons(PORT);
  address->sin_addr.s_addr = inet_addr("127.0.0.1");

  if (bind(sfd, (struct sockaddr *)address, sizeof(*address)) == -1) {
    char errmsg[50];
    sprintf(errmsg, "unable to listen on server port %d", PORT);
    perror(errmsg);
    free(address);
    return EXIT_FAILURE;
  }

  if (listen(sfd, 10) == -1) {
    perror("unable to listen on server port 2000");
    free(address);
    return EXIT_FAILURE;
  };

  printf("Listening for incoming connections on port %d \n", PORT);

  while (1) {
    int *peer = malloc(sizeof(int));
    *peer = accept(sfd, NULL, 0);
    if (*peer == -1) {
      perror("ERROR: could not accept conn");
      free(peer);
      continue;
    }
    pthread_t tid;
    pthread_create(&tid, NULL, handle_connection, peer);
    pthread_detach(tid);
  }

  shutdown(sfd, SHUT_RDWR);
  free(address);
  return EXIT_SUCCESS;
}

void *handle_connection(void *arg) {
  int peer = *(int *)arg;
  free(arg);
  char buffer[BUF_SIZE];

  while (1) {
    int n = recv(peer, buffer, BUF_SIZE, 0);

    if (n == 0) {
      break;
    }

    if (n == -1) {
      perror("could not read from client");
      break;
    }

    if (send(peer, buffer, strlen(buffer), 0) == -1)
      perror("could not send to client");
    memset(buffer, 0, BUF_SIZE * sizeof(char));
  }

  close(peer);
  return NULL;
}
