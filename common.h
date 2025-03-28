#ifndef LECTORE8_COMMON_H
#define LECTORE8_COMMON_H

#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdint.h>
#include <stdlib.h>
#include <time.h>

#define SERVER_PORT 60002
#define BUFFER_SIZE 256
void print_sockaddr(const struct sockaddr_in* addr) {
    printf("%d.%d.%d.%d:%d", 
           (int)(addr->sin_addr.s_addr & 0xFF),
           (int)((addr->sin_addr.s_addr >> 8) & 0xFF),
           (int)((addr->sin_addr.s_addr >> 16) & 0xFF),
           (int)((addr->sin_addr.s_addr >> 24) & 0xFF),
           ntohs(addr->sin_port));
}

int make_socket(int type) {
    int sock = socket(AF_INET, type, 0);
    if (sock < 0) {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }
    return sock;
}

struct sockaddr_in local_addr(unsigned short port) {
	struct sockaddr_in addr;
	memset(&addr, 0, sizeof(addr));
	addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK); // 127.0.0.1
	addr.sin_port = htons(port);
	addr.sin_family = AF_INET;
	return addr;
}
#endif
