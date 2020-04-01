#include <stdlib.h>
#include "run_instruction_logic.h"
#include "platforms/logging.h"

bool instruction_not(Program *program, Parameters *parameters, InstructionPointer *instruction_pointer)
{
    Bank *parameter = get_bank_from_parameter(program, &(parameters->first));
    bool instruction_ok = false;

    if (parameter != NULL)
    {
        log_debug("Logical NOT of Bank %02i.\n", 
            parameter->identifier);

        switch (parameter->type)
        {
            case TYPE_INTEGER:
                log_debug("Doing integer logical NOT.\n");
                instruction_ok = 
                    set_bank_integer(parameter, 
                        ~get_bank_as_integer(parameter));
                break;
            case TYPE_BOOLEAN: 
                log_debug("Doing boolean logical NOT.\n");
                 instruction_ok = 
                    set_bank_boolean(parameter, 
                        !get_bank_as_boolean(parameter));
                break;
            default:
                log_debug("Ignoring logical NOT - it's for an unsupported type.\n");
                instruction_ok = false;
                break;
        }
    }

    increment_instruction(instruction_pointer);
    return instruction_ok;
}

bool instruction_and(Program *program, Parameters *parameters, InstructionPointer *instruction_pointer)
{
    Bank *left_parameter = get_bank_from_parameter(program, &(parameters->first));
    Bank *right_parameter = get_bank_from_parameter(program, &(parameters->second));
    bool instruction_ok = false;

    if (left_parameter != NULL && right_parameter != NULL)
    {
        log_debug("Logical AND of Bank %02i with Bank %02i.\n", 
            left_parameter->identifier, right_parameter->identifier);

        switch (left_parameter->type)
        {
            case TYPE_INTEGER:
                log_debug("Doing integer logical AND.\n");
                instruction_ok = 
                    set_bank_integer(left_parameter, 
                        get_bank_as_integer(left_parameter) &
                        get_bank_as_integer(right_parameter));
                break;
            case TYPE_BOOLEAN: 
                log_debug("Doing boolean logical AND.\n");
                 instruction_ok = 
                    set_bank_boolean(left_parameter, 
                        get_bank_as_boolean(left_parameter) &
                        get_bank_as_boolean(right_parameter));
                break;
            default:
                log_debug("Ignoring logical AND - it's for an unsupported type.\n");
                instruction_ok = false;
                break;
        }
    }

    increment_instruction(instruction_pointer);
    return instruction_ok;
}

bool instruction_or(Program *program, Parameters *parameters, InstructionPointer *instruction_pointer)
{
    Bank *left_parameter = get_bank_from_parameter(program, &(parameters->first));
    Bank *right_parameter = get_bank_from_parameter(program, &(parameters->second));
    bool instruction_ok = false;

    if (left_parameter != NULL && right_parameter != NULL)
    {
        log_debug("Logical OR of Bank %02i with Bank %02i.\n", 
            left_parameter->identifier, right_parameter->identifier);

        switch (left_parameter->type)
        {
            case TYPE_INTEGER:
                log_debug("Doing integer logical OR.\n");
                instruction_ok = 
                    set_bank_integer(left_parameter, 
                        get_bank_as_integer(left_parameter) |
                        get_bank_as_integer(right_parameter));
                break;
            case TYPE_BOOLEAN: 
                log_debug("Doing boolean logical OR.\n");
                 instruction_ok = 
                    set_bank_boolean(left_parameter, 
                        get_bank_as_boolean(left_parameter) |
                        get_bank_as_boolean(right_parameter));
                break;
            default:
                log_debug("Ignoring logical OR - it's for an unsupported type.\n");
                instruction_ok = false;
                break;
        }
    }

    increment_instruction(instruction_pointer);
    return instruction_ok;
}

bool instruction_xor(Program *program, Parameters *parameters, InstructionPointer *instruction_pointer)
{
    Bank *left_parameter = get_bank_from_parameter(program, &(parameters->first));
    Bank *right_parameter = get_bank_from_parameter(program, &(parameters->second));
    bool instruction_ok = false;

    if (left_parameter != NULL && right_parameter != NULL)
    {
        log_debug("Logical XOR of Bank %02i with Bank %02i.\n", 
            left_parameter->identifier, right_parameter->identifier);

        switch (left_parameter->type)
        {
            case TYPE_INTEGER:
                log_debug("Doing integer logical XOR.\n");
                instruction_ok = 
                    set_bank_integer(left_parameter, 
                        get_bank_as_integer(left_parameter) ^
                        get_bank_as_integer(right_parameter));
                break;
            case TYPE_BOOLEAN: 
                log_debug("Doing boolean logical XOR.\n");
                 instruction_ok = 
                    set_bank_boolean(left_parameter, 
                        get_bank_as_boolean(left_parameter) ^
                        get_bank_as_boolean(right_parameter));
                break;
            default:
                log_debug("Ignoring logical XOR - it's for an unsupported type.\n");
                instruction_ok = false;
                break;
        }
    }

    increment_instruction(instruction_pointer);
    return instruction_ok;
}