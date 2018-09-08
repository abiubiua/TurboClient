//
//  tcpclient.c
//  TurboClient
//
//  Created by luobiao on 2018/9/8.
//  Copyright © 2018年 luobiao. All rights reserved.
//

#include "tcpclient.h"
#include <netdb.h>
#include <string.h>
#include <netinet/in.h>
#include <errno.h>
#include <arpa/inet.h>

typedef struct ClientSocket {
    int fd;
    
} ClientSocket;

int StartTCPClient(const char *ip, int port)
{
    if (!ip || strlen(ip) <= 0) return 0;
    int error = 0;
    struct addrinfo hint;
    struct addrinfo *result;
    bzero(&hint, sizeof(hint));
    hint.ai_family = AF_UNSPEC;
    hint.ai_socktype = SOCK_STREAM;
    hint.ai_flags = AI_DEFAULT;
    if ((error = getaddrinfo(ip, "http", &hint, &result)) != 0) {
        return error;
    }
    int fd = socket(AF_INET, SOCK_STREAM, 0);
   
    struct addrinfo *item = result;
    int connected = 0;
    while (item) {
        struct sockaddr *addr = item->ai_addr;
        socklen_t len = item->ai_addrlen;
        if (addr->sa_family == AF_INET) {
            struct sockaddr_in *v4addr = (struct sockaddr_in*)addr;
            char buf[128] = {0};
            v4addr->sin_port = htons(port);
            printf("try connect ip=%s port=%d\n", inet_ntop(addr->sa_family, &v4addr->sin_addr, buf, sizeof(buf)), port);
            
            if ((error = connect(fd, addr, len)) != 0) {
                printf("connect failed %d errno %d\n", error, errno);
                close(fd);
                connected = 0;
                item = item->ai_next;
                continue;
            }
            struct sockaddr_in localaddr;
            socklen_t localaddrlen = sizeof(localaddr);
            getsockname(fd, &localaddr, &localaddrlen);
            printf("local ip %s port %d\n", inet_ntop(localaddr.sin_family, &localaddr.sin_addr, buf, sizeof(buf)), ntohs(localaddr.sin_port));

        } else if (addr->sa_family == AF_INET6) {
            struct sockaddr_in6 *v6addr = (struct sockaddr_in6*)addr;
            v6addr->sin6_port = HTONS(port);
        }
        
        printf("client connected!\n");
        
        connected = 1;
        break;
    }
    freeaddrinfo(result);
    return 0;
}

int StopTCPClient()
{
    return 0;
}
