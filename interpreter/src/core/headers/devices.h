#ifndef SNOWFLAKE_DEVICES_H
#define SNOWFLAKE_DEVICES_H
#include <stdbool.h>

#define DEVICE_OUT_STRING "OUT"
#define DEVICE_IN_STRING  " IN"
#define DEVICE_PRT_STRING "PRT"
#define DEVICE_BTN_STRING "BTN"

typedef enum {
    DEVICE_OUT = 00,
    DEVICE_IN  = 01,
    DEVICE_PRT = 02,
    DEVICE_BTN = 03
} Device;

bool send_to_device(Device device, char *string);

#endif
