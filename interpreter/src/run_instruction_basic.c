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

    if (bank_string_value != NULL)
    {
        send_to_device(device, bank_string_value);
        free(bank_string_value);
    }
    
    *instruction_pointer += 1;
    return true;
}