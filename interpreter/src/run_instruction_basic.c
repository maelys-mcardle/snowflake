#include <stdlib.h>
#include "headers/run_instruction_basic.h"
#include "headers/bank.h"
#include "headers/output.h"
#include "headers/devices.h"

bool instruction_output(Program *program, Instruction *instruction, int *instruction_pointer)
{
    Bank *bank = get_program_bank_from_first_parameter(program, instruction);
    
    if (bank != NULL)
    {
        if (bank->type == TYPE_INTEGER)
        {
            print("%i\n", bank->value.integer);
        }
        else if (bank->type == TYPE_BOOLEAN)
        {
            print("%s\n", bank->value.boolean ? "true" : "false");
        }
        else if (bank->type == TYPE_FLOAT)
        {
            print("%f\n", bank->value.floating);
        }
        else if (bank->type == TYPE_STRING)
        {
            print("%s\n", bank->value.string);
        }
        else if (bank->type == TYPE_ARRAY)
        {
            print("(Array)\n");
        }
    }
    
    *instruction_pointer += 1;
    return true;
}