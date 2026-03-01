#include "robomaster_app.h"
#include <string.h>

/* Minimal driver stub. Replace with real transport (serial/CAN/UDP) code. */
int RM_Init(const char *device, int baud) {
    (void)device; (void)baud;
    /* No-op for scaffold */
    return 0; /* success */
}

int RM_Poll(void) {
    /* Return 0 if no data, 1 if data available (scaffold: no data) */
    return 0;
}

int RM_ReadSample(ROBOMASTER_MotorTlm_t *out) {
    if (!out) return -1;
    /* Scaffold: indicate no data available */
    return -1;
}

void RM_Close(void) {
    /* No-op */
}
