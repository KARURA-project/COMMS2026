#ifndef ROBOMASTER_APP_MSGSTRUCT_H
#define ROBOMASTER_APP_MSGSTRUCT_H

#include "cfe.h"
#include "robomaster_app_msgids.h"

/* Use modern CFE MSG/SB header typedefs */
/* Command packet - common header + CmdCode in command secondary header */
typedef struct {
    CFE_MSG_CommandHeader_t CommandHeader; /**< rief Command header */
    uint8                   CmdPayload;   /* reserved */
} ROBOMASTER_NoArgsCmd_t;

/* Housekeeping telemetry */
typedef struct {
    CFE_MSG_TelemetryHeader_t TelemetryHeader; /**< rief Telemetry header */
    uint8                     CmdCtr;
    uint8                     ErrCtr;
    uint16                    Reserved;
} ROBOMASTER_HkTlm_t;

/* Motor telemetry example (single motor sample) */
typedef struct {
    CFE_MSG_TelemetryHeader_t TelemetryHeader; /**< rief Telemetry header */
    uint8                     MotorID;
    float                     Voltage;
    float                     Current;
    float                     RPM;
    int16                     TempC;
    uint8                     Status;
} ROBOMASTER_MotorTlm_t;

#endif /* ROBOMASTER_APP_MSGSTRUCT_H */
