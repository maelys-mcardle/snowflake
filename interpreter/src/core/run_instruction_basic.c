#include <stdlib.h>
#include "headers/run_instruction_basic.h"
#include "headers/bank.h"
#include "headers/output.h"
#include "headers/input.h"
#include "headers/devices.h"
#include "headers/errors.h"

bool instruction_output(Program *program, Instruction *instruction, int *instruction_pointer)
{
    Bank *bank = get_program_bank_from_second_parameter(program, instruction);
    char *bank_string_value = get_bank_as_string(bank);
    Device device = get_device_from_instruction(instruction);
    bool instruction_ok = false;

    if (bank_string_value != NULL)
    {
        instruction_ok = send_to_device(device, bank_string_value);
        free(bank_string_value);
    }
    else
    {
        instruction_ok = send_to_device(device, "(Empty)");
    }
    
    *instruction_pointer += 1;
    return instruction_ok;
}

bool instruction_input(Program *program, Instruction *instruction, int *instruction_pointer)
{
    Bank *bank = get_program_bank_from_second_parameter(program, instruction);
    Device device = get_device_from_instruction(instruction);
    bool instruction_ok = false;

    if (bank == NULL)
    {
        bank = new_bank_from_second_parameter(instruction);
    }

    if (bank != NULL)
    {
        char *string = NULL;
        int string_size = 0;
        int button_code = 0;

        log_debug("Receiving from Device %02i\n", device);

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
                    set_bank_string(bank, string);
                }
                break;
            case DEVICE_PRT:
                log_error(ERROR_MESG_DEVICE_NOT_SUPPORTED_FOR_INPUT, device);
                instruction_ok = false;
                break;
            case DEVICE_BTN:
                instruction_ok = get_button(&button_code);
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