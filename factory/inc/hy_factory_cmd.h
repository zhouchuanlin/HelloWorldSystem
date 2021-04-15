#ifndef HY_FACTORY_CMD_H
#define HY_FACTORY_CMD_H

enum {
    CMD_OK,
    CMD_ERR,
};

typedef struct {
    char *cmd;
    int (*cmd_handle)(char *, char *);
} FACTORY_CMD_T;

int factory_cmd_get_version(char *req, char *rsp);

static const FACTORY_CMD_T FACTORY_CMDS[] = {
        {"AT+MCUVER?", factory_cmd_get_version},
};

#endif //HY_FACTORY_CMD_H
