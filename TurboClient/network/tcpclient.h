//
//  tcpclient.h
//  TurboClient
//
//  Created by luobiao on 2018/9/8.
//  Copyright © 2018年 luobiao. All rights reserved.
//

#ifndef tcpclient_h
#define tcpclient_h

#include <stdio.h>

int StartTCPClient(const char *ip, int port);
int StopTCPClient(void);

#endif /* tcpclient_h */
