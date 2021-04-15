#include "hy_factory_cmd.h"

int factory_cmd_get_version(char *req, char *rsp) {
    sprintf(rsp, "+MCUVER:%s", "default");
    return CMD_OK;
}
