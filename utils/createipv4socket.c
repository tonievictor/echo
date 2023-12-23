#include <stdio.h>
#include <sys/socket.h>

int createipv4socket(void)
{
  return socket(AF_INET, SOCK_STREAM, 0);
}
