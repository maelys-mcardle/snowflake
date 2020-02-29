#include "headers/devices.h"
#include "headers/errors.h"
#include "headers/output.h"

bool send_to_device(Device device, char *string)
{
    log_debug("Sending '%s' to Device %02i\n", string, device);

    bool ok = false;
    switch (device)
    {
        case DEVICE_OUT:
            send_to_output(string);
            ok = true;
            break;
        case DEVICE_IN:
            log_error(ERROR_MESG_DEVICE_NOT_SUPPORTED_FOR_OUTPUT, device);
            ok = false;
            break;
        case DEVICE_PRT:
            send_to_output(string);
            ok = true;
            break;
        case DEVICE_BTN:
            log_error(ERROR_MESG_DEVICE_NOT_SUPPORTED_FOR_OUTPUT, device);
            ok = false;
            break;
        default:
            log_error(ERROR_MESG_UNRECOGNIZED_DEVICE, device);
            ok = false;
            break;
    }

    return ok;
}

char *receive_from_device(Device device, bool *ok)
{
    log_debug("Listening to Device %02i\n", device);
    return NULL;
}