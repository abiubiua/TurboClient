//
//  main.c
//  TurboClient
//
//  Created by luobiao on 2018/9/8.
//  Copyright © 2018年 luobiao. All rights reserved.
//

#include <stdio.h>
#include "tcpclient.h"

int main(int argc, const char * argv[]) {
    // insert code here...
    StartTCPClient("10.116.34.147", 5200);
    return 0;
}
