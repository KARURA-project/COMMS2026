#include "cfe.h"
#include "robomaster_app.h"
#include "robomaster_app_msg.h"
#include "robomaster_app_events.h"
#include "robomaster_driver.h"

ROBOMASTER_AppData_t ROBOMASTER_AppData;

/* Process a received command message (modern CFE API) */
void ROBOMASTER_ProcessCommand(const CFE_SB_Buffer_t *SBBufPtr) {
    CFE_MSG_FcnCode_t CmdCode = 0;
    CFE_MSG_GetFcnCode(&SBBufPtr->Msg, &CmdCode);

    switch (CmdCode) {
        case ROBOMASTER_APP_NOOP_CC:
            ROBOMASTER_AppData.MsgCount++;
            CFE_EVS_SendEvent(ROBOMASTER_APP_NOOP_INF_EID, CFE_EVS_EventType_INFORMATION,
                              "ROBOMASTER NOOP received");
            break;
        case ROBOMASTER_APP_RESET_COUNTERS_CC:
            ROBOMASTER_AppData.MsgCount = 0;
            ROBOMASTER_AppData.ErrorCount = 0;
            CFE_EVS_SendEvent(ROBOMASTER_APP_INIT_INF_EID, CFE_EVS_EventType_INFORMATION,
                              "ROBOMASTER Reset counters");
            break;
        case ROBOMASTER_APP_EXIT_CC:
            ROBOMASTER_AppData.RunStatus = CFE_ES_RunStatus_APP_EXIT;
            CFE_EVS_SendEvent(ROBOMASTER_APP_EXIT_INF_EID, CFE_EVS_EventType_INFORMATION,
                              "ROBOMASTER Exit command received");
            break;
        default:
            ROBOMASTER_AppData.ErrorCount++;
            CFE_EVS_SendEvent(ROBOMASTER_APP_CMD_ERR_EID, CFE_EVS_EventType_ERROR,
                              "ROBOMASTER invalid cmd code: %d", (int)CmdCode);
            break;
    }
}

/* Send housekeeping telemetry using modern CFE MSG/SB APIs */
void ROBOMASTER_SendHk(void) {
    ROBOMASTER_HkTlm_t Hk;
    memset(&Hk, 0, sizeof(Hk));
    CFE_MSG_Init(CFE_MSG_PTR(Hk.TelemetryHeader), CFE_SB_ValueToMsgId(ROBOMASTER_APP_HK_TLM_MID), sizeof(Hk));
    Hk.CmdCtr = (uint8)ROBOMASTER_AppData.MsgCount;
    Hk.ErrCtr = (uint8)ROBOMASTER_AppData.ErrorCount;
    CFE_SB_TimeStampMsg(CFE_MSG_PTR(Hk.TelemetryHeader));
    CFE_SB_TransmitMsg(CFE_MSG_PTR(Hk.TelemetryHeader), true);
}

void ROBOMASTER_AppMain(void) {
    CFE_SB_Buffer_t *SBBufPtr = NULL;
    CFE_Status_t status;
    CFE_SB_MsgId_t MsgId = CFE_SB_INVALID_MSG_ID;

    ROBOMASTER_AppData.RunStatus = CFE_ES_RunStatus_APP_RUN;

    /* App registration is handled by the framework; just register for events */
    CFE_EVS_Register(NULL, 0, CFE_EVS_EventFilter_BINARY);

    CFE_SB_CreatePipe(&ROBOMASTER_AppData.CmdPipe, 4, "ROBOMASTER_CMD_PIPE");
    CFE_SB_Subscribe(CFE_SB_ValueToMsgId(ROBOMASTER_APP_CMD_MID), ROBOMASTER_AppData.CmdPipe);
    CFE_SB_Subscribe(CFE_SB_ValueToMsgId(ROBOMASTER_APP_SEND_HK_MID), ROBOMASTER_AppData.CmdPipe);

    CFE_EVS_SendEvent(ROBOMASTER_APP_INIT_INF_EID, CFE_EVS_EventType_INFORMATION,
                      "ROBOMASTER App Initialized");

    while (CFE_ES_RunLoop(&ROBOMASTER_AppData.RunStatus) == true) {
        /* Pend on receipt of command packet */
        status = CFE_SB_ReceiveBuffer(&SBBufPtr, ROBOMASTER_AppData.CmdPipe, CFE_SB_PEND_FOREVER);

        if (status == CFE_SUCCESS && SBBufPtr != NULL) {
            CFE_MSG_GetMsgId(&SBBufPtr->Msg, &MsgId);
            switch (CFE_SB_MsgIdToValue(MsgId)) {
                case ROBOMASTER_APP_SEND_HK_MID:
                    ROBOMASTER_SendHk();
                    break;
                case ROBOMASTER_APP_CMD_MID:
                    ROBOMASTER_ProcessCommand(SBBufPtr);
                    break;
                default:
                    CFE_EVS_SendEvent(ROBOMASTER_APP_PIPE_ERR_EID, CFE_EVS_EventType_ERROR,
                                      "ROBOMASTER Received unexpected MsgId: 0x%X", (unsigned int)CFE_SB_MsgIdToValue(MsgId));
                    break;
            }
        } else {
            CFE_EVS_SendEvent(ROBOMASTER_APP_PIPE_ERR_EID, CFE_EVS_EventType_ERROR,
                              "ROBOMASTER pipe read error: 0x%08X", (unsigned int)status);
        }

        /* Poll driver (non-blocking) */
        if (RM_Poll()) {
            ROBOMASTER_MotorTlm_t sample;
            if (RM_ReadSample(&sample) == 0) {
                /* Timestamp and send motor telemetry */
                CFE_MSG_Init(CFE_MSG_PTR(sample.TelemetryHeader), CFE_SB_ValueToMsgId(ROBOMASTER_MOTOR_TLM_MID), sizeof(sample));
                CFE_SB_TimeStampMsg(CFE_MSG_PTR(sample.TelemetryHeader));
                CFE_SB_TransmitMsg(CFE_MSG_PTR(sample.TelemetryHeader), true);
            }
        }
    }

    RM_Close();

    /* Exit the app */
    CFE_ES_ExitApp(ROBOMASTER_AppData.RunStatus);
}
