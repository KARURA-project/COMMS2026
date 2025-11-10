#ifndef ROBOMASTER_DRIVER_H
#define ROBOMASTER_DRIVER_H

#include "robomaster_app_msg.h"

int RM_Init(const char *device, int baud);
int RM_Poll(void);
int RM_ReadSample(ROBOMASTER_MotorTlm_t *out);
void RM_Close(void);

#endif /* ROBOMASTER_DRIVER_H */
