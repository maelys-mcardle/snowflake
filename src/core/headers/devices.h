#ifndef SNOWFLAKE_DEVICES_H
#define SNOWFLAKE_DEVICES_H
#include <stdbool.h>

#define DEVICE_OUT_STRING "OUT"
#define DEVICE_IN_STRING  " IN"
#define DEVICE_BTN_STRING "BTN"

typedef enum {
    DEVICE_OUT = 0,
    DEVICE_IN  = 1,
    DEVICE_BTN = 2
} Device;

bool send_to_device(Device device, char *string);

#endif
