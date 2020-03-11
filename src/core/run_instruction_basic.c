#include <stdlib.h>
#include <string.h>
#include "headers/run_instruction_basic.h"
#include "headers/bank.h"
#include "headers/output.h"
#include "headers/input.h"
#include "headers/devices.h"
#include "headers/errors.h"

bool instruction_noop(Program *program, Parameters *parameters, int *instruction_pointer)
{
    // Unused parameters. This is done to suppress compiler warnings.
    (void)(program);
    (void)(parameters);

    // Perform no-op.
    bool instruction_ok = true;
    log_debug("No-op instruction.\n");
    *instruction_pointer += 1;
    return instruction_ok;
}

bool instruction_output(Program *program, Parameters *parameters, int *instruction_pointer)
{
    Bank *bank = get_bank_from_parameter(program, &(parameters->second));
    Device device = get_device_from_parameter(parameters);
    bool instruction_ok = false;

    if (bank != NULL)
    {
        char *bank_string_value = get_bank_as_string(bank);
        log_debug("Sending Bank %02i (value: '%s') to Device %02i\n", bank->identifier, bank_string_value, device);
        instruction_ok = send_to_device(device, bank_string_value);
        free(bank_string_value);
    }
    else
    {
        log_debug("Sending unallocated Bank %02i to Device %02i\n", parameters->second.integer, device);
        instruction_ok = send_to_device(device, "(Empty)");
    }
    
    *instruction_pointer += 1;
    return instruction_ok;
}

bool instruction_input(Program *program, Parameters *parameters, int *instruction_pointer)
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

        log_debug("Receiving from Device %02i into Bank %02i\n", device, bank->identifier);

        switch (device)
        {
            case DEVICE_OUT:
                log_error(ERROR_MESG_DEVICE_NOT_SUPPORTED_FOR_INPUT, device);
                instruction_ok = false;
                break;
            case DEVICE_IN:
                instruction_ok = get_input(&string_size, &string);
                if (instruction_ok)
                {
                    log_debug("Setting '%s' to Bank %02i\n", string, bank->identifier);
                    set_bank_string(bank, string);
                }
                break;
            case DEVICE_BTN:
                instruction_ok = get_button(&button_code);
                log_debug("Setting '%i' to Bank %02i\n", button_code, bank->identifier);
                set_bank_integer(bank, button_code);
                break;
            default:
                log_error(ERROR_MESG_UNRECOGNIZED_DEVICE, device);
                instruction_ok = false;
                break;
        }
    }
    
    *instruction_pointer += 1;
    return instruction_ok;
}

bool instruction_delete(Program *program, Parameters *parameters, int *instruction_pointer)
{
    Bank *bank = get_bank_from_parameter(program, &(parameters->first));
    bool instruction_ok = true;

    if (bank == NULL)
    {
        log_debug("Asked to delete unallocated bank.\n");
    }
    else
    {
        log_debug("Deleting Bank %02i.\n", bank->identifier);
        instruction_ok = remove_program_bank(program, bank->identifier);
    }
    
    *instruction_pointer += 1;
    return instruction_ok;
}

bool instruction_type(Program *program, Parameters *parameters, int *instruction_pointer)
{
    bool instruction_ok = false;

    // Get the banks.
    Bank *bank_to_store_type_in = get_or_new_bank_from_parameter(program, &(parameters->first));
    Bank *bank_with_type_to_get = get_bank_from_parameter(program, &(parameters->second));

    // Bank has a type.
    if (bank_to_store_type_in == NULL)
    {
        log_error(ERROR_MESG_COULD_NOT_ALLOCATE_MEMORY);
        instruction_ok = false;
    }
    else if (bank_with_type_to_get != NULL)
    {
        instruction_ok = set_bank_integer(bank_to_store_type_in, bank_with_type_to_get->type);
    }
    else if (bank_with_type_to_get == NULL)
    {
        instruction_ok = set_bank_integer(bank_to_store_type_in, 0);
    }

    *instruction_pointer += 1;
    return instruction_ok;
}

bool instruction_copy(Program *program, Parameters *parameters, int *instruction_pointer)
{
    bool instruction_ok = false;

    // Get the banks.
    Bank *bank_destination = get_or_new_bank_from_parameter(program, &(parameters->first));
    Bank *bank_source = get_bank_from_parameter(program, &(parameters->second));

    // Bank has a type.
    if (bank_destination == NULL)
    {
        log_error(ERROR_MESG_COULD_NOT_ALLOCATE_MEMORY);
        instruction_ok = false;
    }
    else if (bank_source != NULL)
    {
        log_debug("Copying to Bank %02i.\n", bank_destination->identifier);
        instruction_ok = copy_bank(bank_destination, bank_source);
    }
    else if (bank_source == NULL)
    {
        log_debug("Source bank is unallocated. Deleting Bank %02i.\n", bank_destination->identifier);
        instruction_ok = remove_program_bank(program, bank_destination->identifier);
    }

    *instruction_pointer += 1;
    return instruction_ok; 
}

bool instruction_convert(Program *program, Parameters *parameters, int *instruction_pointer)
{
    bool instruction_ok = false;

    // Get the bank and type to convert to.
    Bank *bank = get_or_new_bank_from_parameter(program, &(parameters->second));
    BankType to_type = get_type_from_parameter(parameters);

    if (bank != NULL)
    {
        log_debug("Converting Bank %02i to type %i.\n", bank->identifier, to_type);
        instruction_ok = convert_bank(bank, to_type);
    }

    *instruction_pointer += 1;
    return instruction_ok;
}


bool instruction_length(Program *program, Parameters *parameters, int *instruction_pointer)
{
    Bank *bank_to_store_length_in = get_or_new_bank_from_parameter(program, &(parameters->first));
    Bank *bank_to_get_length_from = get_bank_from_parameter(program, &(parameters->second));
    bool instruction_ok = false;
    bool parse_ok = true; 

    log_debug("Storing length in Bank %02i.\n",
            bank_to_store_length_in->identifier);

    if (bank_to_get_length_from != NULL &&
        bank_to_get_length_from->type == TYPE_STRING)
    {
        char *string = get_bank_string(bank_to_get_length_from, &parse_ok);
        instruction_ok = 
            set_bank_integer(bank_to_store_length_in, 
                string != NULL ? strlen(string) : 0);
    }
    else if (bank_to_get_length_from != NULL &&
        bank_to_get_length_from->type == TYPE_ARRAY)
    {
        instruction_ok = 
            set_bank_integer(bank_to_store_length_in, 
                get_bank_array(bank_to_get_length_from, &parse_ok)->count);
    }
    else
    {
        instruction_ok = 
            set_bank_integer(bank_to_store_length_in, 0);
    }

    *instruction_pointer += 1;
    return instruction_ok;
}