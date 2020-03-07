#include <stdlib.h>
#include "headers/run_instruction_basic.h"
#include "headers/bank.h"
#include "headers/output.h"
#include "headers/input.h"
#include "headers/devices.h"
#include "headers/errors.h"

bool instruction_noop(Program *program, Instruction *instruction, int *instruction_pointer)
{
    // Unused parameters. This is done to suppress compiler warnings.
    (void)(program);
    (void)(instruction);

    // Perform no-op.
    bool instruction_ok = true;
    log_debug("No-op instruction.\n");
    *instruction_pointer += 1;
    return instruction_ok;
}

bool instruction_output(Program *program, Instruction *instruction, int *instruction_pointer)
{
    Bank *bank = get_bank_from_second_parameter(program, instruction);
    Device device = get_device_from_instruction(instruction);
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
        log_debug("Sending unallocated Bank %02i to Device %02i\n", instruction->parameters.second.integer, device);
        instruction_ok = send_to_device(device, "(Empty)");
    }
    
    *instruction_pointer += 1;
    return instruction_ok;
}

bool instruction_input(Program *program, Instruction *instruction, int *instruction_pointer)
{
    // Get the bank. If it doesn't exist, create it.
    Bank *bank = get_or_new_bank_from_second_parameter(program, instruction);

    // Get the device.
    Device device = get_device_from_instruction(instruction);
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

bool instruction_delete(Program *program, Instruction *instruction, int *instruction_pointer)
{
    Bank *bank = get_bank_from_first_parameter(program, instruction);
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

bool instruction_type(Program *program, Instruction *instruction, int *instruction_pointer)
{
    bool instruction_ok = false;

    // Get the banks.
    Bank *bank_to_store_type_in = get_or_new_bank_from_first_parameter(program, instruction);
    Bank *bank_with_type_to_get = get_bank_from_second_parameter(program, instruction);

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

bool instruction_copy(Program *program, Instruction *instruction, int *instruction_pointer)
{
    bool instruction_ok = false;

    // Get the banks.
    Bank *bank_destination = get_or_new_bank_from_first_parameter(program, instruction);
    Bank *bank_source = get_bank_from_second_parameter(program, instruction);

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

bool instruction_convert(Program *program, Instruction *instruction, int *instruction_pointer)
{
    bool instruction_ok = false;

    // Get the bank and type to convert to.
    Bank *bank = get_or_new_bank_from_second_parameter(program, instruction);
    BankType to_type = get_type_from_instruction(instruction);

    if (bank != NULL)
    {
        log_debug("Converting Bank %02i to type %i.\n", bank->identifier, to_type);
        instruction_ok = convert_bank(bank, to_type);
    }

    *instruction_pointer += 1;
    return instruction_ok;
}