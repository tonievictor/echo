#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * createipv4address - creates an ipv4 address struct.
 * @port: the port number for the address.
 * @ip: A string representing the IPv4 address.
 *
 * Return: A pointer to the created sockaddr_in struct,
 * or null is an erro is encountered, this err is printed
 * to stderr.
*/
struct sockaddr_in *createipv4address(int port, char *ip)
{
	struct sockaddr_in *address;

	address = malloc(sizeof(struct sockaddr_in));

	if (address == NULL) {
		perror("Unable to allocate memory for address struct");
		return (NULL);
	}

	address->sin_port = htons(port);
	address->sin_family = AF_INET;
	if (strlen(ip) == 0) {
		address->sin_addr.s_addr = INADDR_ANY;
	} else {
		inet_pton(AF_INET, ip, &address->sin_addr.s_addr);
	}

	return (address);
}
