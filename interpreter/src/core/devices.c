#include "headers/devices.h"
#include "headers/errors.h"
#include "headers/output.h"
#include "headers/input.h"

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

bool receive_from_device(Device device, int *string_size, char **string)
{
    log_debug("Listening to Device %02i\n", device);
    bool ok = false;

    switch (device)
    {
        case DEVICE_OUT:
            log_error(ERROR_MESG_DEVICE_NOT_SUPPORTED_FOR_INPUT, device);
            ok = false;
            break;
        case DEVICE_IN:
            ok = get_input(string_size, string);
            break;
        case DEVICE_PRT:
            log_error(ERROR_MESG_DEVICE_NOT_SUPPORTED_FOR_INPUT, device);
            ok = false;
            break;
        case DEVICE_BTN:
            ok = get_button(string_size, string);
            break;
        default:
            log_error(ERROR_MESG_UNRECOGNIZED_DEVICE, device);
            ok = false;
            break;
    }

    return ok;
}