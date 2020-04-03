#include <stdlib.h>
#include "platforms/output_devices.h"
#include "platforms/input_devices.h"
#include "platforms/logging.h"
#include "errors.h"
#include "run/run_instruction_io.h"

bool instruction_output(Program *program, Parameters *parameters, InstructionPointer *instruction_pointer)
{
    Bank *bank = get_bank_from_parameter(program, &(parameters->second));
    Device device = get_device_from_parameter(parameters);
    bool instruction_ok = false;

    if (bank != NULL)
    {
        char *bank_string_value;
        int bank_integer_value;
        switch (device)
        {
            case DEVICE_OUT:
                bank_string_value = get_bank_as_string(bank);
                log_debug("Sending Bank %02i (value: '%s') to Device %02i\n", bank->identifier, bank_string_value, device);
                instruction_ok = send_to_standard_output(bank_string_value);
                if (bank_string_value != NULL) free(bank_string_value);
                break;
            case DEVICE_IN:
                log_error(ERROR_MESG_DEVICE_NOT_SUPPORTED_FOR_OUTPUT, device);
                instruction_ok = false;
                break;
            case DEVICE_BTN:
                log_error(ERROR_MESG_DEVICE_NOT_SUPPORTED_FOR_OUTPUT, device);
                instruction_ok = false;
                break;
            case DEVICE_RND:
                bank_integer_value = get_bank_as_integer(bank);
                log_debug("Sending Bank %02i (value: '%i') to Device %02i\n", bank->identifier, bank_integer_value, device);
                instruction_ok = send_to_random(bank_integer_value);
                break;
            default:
                log_error(ERROR_MESG_UNRECOGNIZED_DEVICE, device);
                instruction_ok = false;
                break;
        }  
    }
    
    increment_instruction(instruction_pointer);
    return instruction_ok;
}

bool instruction_input(Program *program, Parameters *parameters, InstructionPointer *instruction_pointer)
{
    // Get the bank. If it doesn't exist, create it.
    Bank *bank = get_or_new_bank_from_parameter(program, &(parameters->second));

    // Get the device.
    Device device = get_device_from_parameter(parameters);
    bool instruction_ok = false;

    // Get the input.
    if (bank != NULL)
    {
        char *string = NULL;
        int string_size = 0;
        int button_code = 0;
        int random_number = 0;

        log_debug("Receiving from Device %02i into Bank %02i\n", device, bank->identifier);

        switch (device)
        {
            case DEVICE_OUT:
                log_error(ERROR_MESG_DEVICE_NOT_SUPPORTED_FOR_INPUT, device);
                instruction_ok = false;
                break;
            case DEVICE_IN:
                instruction_ok = receive_from_standard_input(&string_size, &string);
                if (instruction_ok)
                {
                    log_debug("Setting '%s' to Bank %02i\n", string, bank->identifier);
                    set_bank_string(bank, string);
                }
                break;
            case DEVICE_BTN:
                instruction_ok = receive_from_button(&button_code);
                log_debug("Setting '%i' to Bank %02i\n", button_code, bank->identifier);
                set_bank_integer(bank, button_code);
                break;
            case DEVICE_RND:
                instruction_ok = receive_from_random(&random_number);
                log_debug("Setting '%i' to Bank %02i\n", random_number, bank->identifier);
                set_bank_integer(bank, random_number);
                break;
            default:
                log_error(ERROR_MESG_UNRECOGNIZED_DEVICE, device);
                instruction_ok = false;
                break;
        }
    }
    
    increment_instruction(instruction_pointer);
    return instruction_ok;
}