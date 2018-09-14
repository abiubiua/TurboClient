//
//  main.c
//  TurboClient
//
//  Created by luobiao on 2018/9/8.
//  Copyright © 2018年 luobiao. All rights reserved.
//

#include <stdio.h>
#include "tcpclient.h"
#include "udpclient.h"

int main(int argc, const char * argv[]) {
    // insert code here...
    const char *tmp = "123456";
    int len = strlen("123456");
    int sizeoflen = sizeof("123456");
    printf("strlen=%d sizeof=%d\n", len, sizeoflen);
    StartUDPClient("10.116.34.147", 5200);
    return 0;
}
