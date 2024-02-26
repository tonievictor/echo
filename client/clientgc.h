#ifndef CLIENT_H
#define CLIENT_H

#include <netinet/in.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

void *subscribe(void *arg);
char *str_cat(char *username, char *message);

extern int client_signal;
extern pthread_mutex_t mutex;
#endif // !CLIENT_H
