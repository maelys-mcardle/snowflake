#include <stdlib.h>
#include "headers/run_instruction_basic.h"
#include "headers/bank.h"
#include "headers/output.h"
#include "headers/devices.h"

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

    char *input = receive_from_device(device, &instruction_ok);

    // Replace contents of target bank with new string.
    // Create bank if it doesn't exist. get_program_bank should create it
    // if it doesn't exist?
    
    *instruction_pointer += 1;
    return instruction_ok;
}