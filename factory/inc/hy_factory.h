#ifndef HY_FACTORY_H
#define HY_FACTORY_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <sl_udelay.h>
#include "types.h"
#include "hy_factory_cmd.h"

#define FACTORY_BUF_SIZE 1024
#define FACTORY_REQ_SIZE 1024
#define FACTORY_RSP_SIZE 1024
#define FACTORY_MODE_FLAG "AT+FACTTEST"

typedef struct {
    u8 buf[FACTORY_BUF_SIZE];
    u16 len;
} FACTORY_IN_T;

bool Factory_WaitingToEnter();
void Factory_Process();
void Factory_OnUartEvent(u8 byte);

#endif
