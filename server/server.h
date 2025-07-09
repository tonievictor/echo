#ifndef SERVER_H
#define SERVER_H

#include <arpa/inet.h>
#include <pthread.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

void *handle_connection(void *arg);
void broadcast(char *message, int sender);
void *server(void *arg);

#endif // SERVER_H
