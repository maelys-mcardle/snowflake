#ifndef SNOWFLAKE_DEVICES_H
#define SNOWFLAKE_DEVICES_H
#include <stdbool.h>

// Mnemonics for the input/output devices.
#define DEVICE_OUT_STRING "OUT"
#define DEVICE_IN_STRING  " IN"
#define DEVICE_BTN_STRING "BTN"
#define DEVICE_RND_STRING "RND"

/**
 * Enum for the intput/output devices.
 */
typedef enum {
    DEVICE_OUT = 0,
    DEVICE_IN  = 1,
    DEVICE_BTN = 2,
    DEVICE_RND = 3
} Device;

#endif
