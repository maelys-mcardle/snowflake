#include <stdlib.h>
#include "headers/run_instruction_math.h"
#include "headers/string.h"
#include "headers/output.h"

bool instruction_add(Program *program, Instruction *instruction, int *instruction_pointer)
{
    Bank *left_parameter = get_bank_from_first_parameter(program, instruction);
    Bank *right_parameter = get_bank_from_second_parameter(program, instruction);
    bool instruction_ok = false;

    if (left_parameter != NULL && right_parameter != NULL)
    {
        char *left_string, *right_string, *combined_string;

        log_debug("Adding Bank %02i to Bank %02i.\n", 
            right_parameter->identifier, left_parameter->identifier);

        switch (left_parameter->type)
        {
            case TYPE_INTEGER:
                log_debug("Doing integer addition.\n");
                instruction_ok = 
                    set_bank_integer(left_parameter, 
                        get_bank_as_integer(left_parameter) +
                        get_bank_as_integer(right_parameter));
                break;
            case TYPE_FLOAT: 
                log_debug("Doing float addition.\n");
                 instruction_ok = 
                    set_bank_float(left_parameter, 
                        get_bank_as_float(left_parameter) +
                        get_bank_as_float(right_parameter));
                break;
            case TYPE_STRING:
                log_debug("Doing string concatenation.\n");
                left_string = get_bank_as_string(left_parameter);
                right_string = get_bank_as_string(right_parameter);
                combined_string = concatenate_strings(left_string, right_string, true);
                instruction_ok = set_bank_string(left_parameter, combined_string);
                if (left_string != NULL) free(left_string);
                if (right_string != NULL) free(right_string);
                if (combined_string != NULL) free(combined_string);
                break;
            case TYPE_BOOLEAN:
            case TYPE_ARRAY:
            default:
                log_debug("Ignoring addition - it's for an unsupported type.\n");
                instruction_ok = false;
                break;
        }
    }

    *instruction_pointer += 1;
    return instruction_ok;
}