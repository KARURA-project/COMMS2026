#ifndef ROBOMASTER_APP_H
#define ROBOMASTER_APP_H

#include "cfe.h"
#include "robomaster_app_msg.h"

#define ROBOMASTER_APP_NAME "robomaster_app"

typedef struct {
    CFE_SB_PipeId_t CmdPipe;
    uint32          RunStatus;
    uint32          MsgCount;
    uint32          ErrorCount;
} ROBOMASTER_AppData_t;

extern ROBOMASTER_AppData_t ROBOMASTER_AppData;

#endif /* ROBOMASTER_APP_H */
