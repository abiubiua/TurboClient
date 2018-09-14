//
//  udpclient.c
//  TurboClient
//
//  Created by luobiao on 12/9/2018.
//  Copyright © 2018 luobiao. All rights reserved.
//

#include "udpclient.h"
#include "log.h"
#include "commoninclude.h"

static const char *TAG = "udpclient";

void StartUDPClient(const char *ip, int port)
{
    LOGD(TAG, "create udp socket");
    int erro = 0;
    int udpsock = socket(AF_INET, SOCK_DGRAM, 0);
    if (udpsock <= 0) {
        LOGE(TAG, "create udp socket error %d errno %d", udpsock, errno);
        return;
    }
    struct addrinfo *resultaddr = NULL;
//    EAI_FAIL
    struct addrinfo hint;
    bzero(&hint, sizeof(hint));
    hint.ai_family = AF_UNSPEC;
    hint.ai_socktype = SOCK_DGRAM;
    hint.ai_flags = AI_DEFAULT;
    if ((erro =  getaddrinfo(ip, "http", &hint, &resultaddr)) != 0) {
        LOGE(TAG, "getaddrinfo error %d errno %d", erro, errno);
        return;
    }
    struct sockaddr *remoteaddr = NULL;
    struct addrinfo *itemaddr = resultaddr;
    while (itemaddr) {
        struct sockaddr *addr = itemaddr->ai_addr;
        socklen_t addrlen = addr->sa_len;
        if (addr->sa_family == AF_INET) {
            struct sockaddr_in *v4addr = (struct sockaddr_in*)addr;
            v4addr->sin_port = htons(port);
            char ipbuf[128] = {0};
            LOGI(TAG, "try udp connect v4 ip %s port %d", inet_ntop(AF_INET, &v4addr->sin_addr, ipbuf, sizeof(ipbuf)), ntohs(v4addr->sin_port));
        } else if (addr->sa_family == AF_INET6) {
            struct sockaddr_in6 *v6addr = (struct sockaddr_in6*)addr;
            v6addr->sin6_port = htons(port);
            char ipbuf[128] = {0};
            LOGI(TAG, "try udp connect v6 ip %s port %d", inet_ntop(AF_INET6, &v6addr->sin6_addr, ipbuf, sizeof(ipbuf)), ntohs(v6addr->sin6_port));
        }
        if ((erro = connect(udpsock, addr, addrlen)) != 0) {
            LOGE(TAG, "udp connect error %d errno %d", erro, errno);
            continue;
        }
        if (addr->sa_family == AF_INET) {
            struct sockaddr_in *v4addr = malloc(sizeof(struct sockaddr_in));
            memcpy(v4addr, addr, addrlen);
            remoteaddr = (struct sockaddr*)v4addr;
        } else if (addr->sa_family == AF_INET6) {
            struct sockaddr_in6 *v6addr = malloc(sizeof(struct sockaddr_in6));
            memcpy(v6addr, addr, addrlen);
            remoteaddr = (struct sockaddr*)v6addr;
        }
        break;
    }
    char sendbuf[1024] = {0};
    sendbuf[0] = '1';
    char recvbuf[1024] = {0};
    while (1) {
        erro = send(udpsock, sendbuf, sizeof(sendbuf), 0);
        if (erro <= 0) {
            LOGE(TAG, "send to error %d errno %d", erro, errno);
        }
        int recvcnt = recv(udpsock, recvbuf, sizeof(recvbuf), 0);
        if (recvcnt <= 0) {
            LOGE(TAG, "recv error %d errno %d", recvcnt, errno);
        } else {
            LOGD(TAG, "recv cnt %d:%s", recvcnt, recvbuf);
        }
        usleep(1000*1000);
    }
    

    
}

void StopUDPClient()
{
    
}
