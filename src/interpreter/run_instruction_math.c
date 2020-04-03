#include <stdlib.h>
#include <math.h>
#include "run_instruction_math.h"
#include "core/string.h"
#include "platforms/logging.h"
#include "errors.h"

bool instruction_add(Program *program, Parameters *parameters, InstructionPointer *instruction_pointer)
{
    Bank *left_parameter = get_bank_from_parameter(program, &(parameters->first));
    Bank *right_parameter = get_bank_from_parameter(program, &(parameters->second));
    bool instruction_ok = false;

    if (left_parameter != NULL && right_parameter != NULL)
    {
        char *left_string, *right_string, *combined_string;

        log_debug("Addition of Bank %02i with Bank %02i.\n", 
            left_parameter->identifier, right_parameter->identifier);

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
                combined_string = join_strings(left_string, right_string);
                instruction_ok = set_bank_string(left_parameter, combined_string);
                if (left_string != NULL) free(left_string);
                if (right_string != NULL) free(right_string);
                if (combined_string != NULL) free(combined_string);
                break;
            default:
                log_error(ERROR_MESG_IGNORING_OPERATION_UNSUPPORTED_TYPE,
                    "addition", left_parameter->identifier);
                instruction_ok = false;
                break;
        }
    }
    else if (left_parameter == NULL)
    {
        log_error(ERROR_MESG_IGNORING_OPERATION_BANK_UNDEFINED, 
            "addition", parameters->first.identifier);
    }
    else if (right_parameter == NULL)
    {
        log_error(ERROR_MESG_IGNORING_OPERATION_BANK_UNDEFINED, 
            "addition", parameters->second.identifier);
    }

    increment_instruction(instruction_pointer);
    return instruction_ok;
}

bool instruction_subtract(Program *program, Parameters *parameters, InstructionPointer *instruction_pointer)
{
    Bank *left_parameter = get_bank_from_parameter(program, &(parameters->first));
    Bank *right_parameter = get_bank_from_parameter(program, &(parameters->second));
    bool instruction_ok = false;

    if (left_parameter != NULL && right_parameter != NULL)
    {
        log_debug("Subtraction of Bank %02i with Bank %02i.\n", 
            left_parameter->identifier, right_parameter->identifier);

        switch (left_parameter->type)
        {
            case TYPE_INTEGER:
                log_debug("Doing integer subtraction.\n");
                instruction_ok = 
                    set_bank_integer(left_parameter, 
                        get_bank_as_integer(left_parameter) -
                        get_bank_as_integer(right_parameter));
                break;
            case TYPE_FLOAT: 
                log_debug("Doing float subtraction.\n");
                 instruction_ok = 
                    set_bank_float(left_parameter, 
                        get_bank_as_float(left_parameter) -
                        get_bank_as_float(right_parameter));
                break;
            default:
                log_error(ERROR_MESG_IGNORING_OPERATION_UNSUPPORTED_TYPE,
                    "subtraction", left_parameter->identifier);
                instruction_ok = false;
                break;
        }
    }
    else if (left_parameter == NULL)
    {
        log_error(ERROR_MESG_IGNORING_OPERATION_BANK_UNDEFINED, 
            "subtraction", parameters->first.identifier);
    }
    else if (right_parameter == NULL)
    {
        log_error(ERROR_MESG_IGNORING_OPERATION_BANK_UNDEFINED, 
            "subtraction", parameters->second.identifier);
    }

    increment_instruction(instruction_pointer);
    return instruction_ok;
}

bool instruction_multiply(Program *program, Parameters *parameters, InstructionPointer *instruction_pointer)
{
    Bank *left_parameter = get_bank_from_parameter(program, &(parameters->first));
    Bank *right_parameter = get_bank_from_parameter(program, &(parameters->second));
    bool instruction_ok = false;

    if (left_parameter != NULL && right_parameter != NULL)
    {
        log_debug("Multiplication of Bank %02i with Bank %02i.\n", 
            left_parameter->identifier, right_parameter->identifier);

        switch (left_parameter->type)
        {
            case TYPE_INTEGER:
                log_debug("Doing integer multiplication.\n");
                instruction_ok = 
                    set_bank_integer(left_parameter, 
                        get_bank_as_integer(left_parameter) *
                        get_bank_as_integer(right_parameter));
                break;
            case TYPE_FLOAT: 
                log_debug("Doing float multiplication.\n");
                 instruction_ok = 
                    set_bank_float(left_parameter, 
                        get_bank_as_float(left_parameter) *
                        get_bank_as_float(right_parameter));
                break;
            default:
                log_error(ERROR_MESG_IGNORING_OPERATION_UNSUPPORTED_TYPE,
                    "multiplication", left_parameter->identifier);
                instruction_ok = false;
                break;
        }
    }
    else if (left_parameter == NULL)
    {
        log_error(ERROR_MESG_IGNORING_OPERATION_BANK_UNDEFINED, 
            "multiplication", parameters->first.identifier);
    }
    else if (right_parameter == NULL)
    {
        log_error(ERROR_MESG_IGNORING_OPERATION_BANK_UNDEFINED, 
            "multiplication", parameters->second.identifier);
    }

    increment_instruction(instruction_pointer);
    return instruction_ok;
}

bool instruction_divide(Program *program, Parameters *parameters, InstructionPointer *instruction_pointer)
{
    Bank *left_parameter = get_bank_from_parameter(program, &(parameters->first));
    Bank *right_parameter = get_bank_from_parameter(program, &(parameters->second));
    bool instruction_ok = false;

    if (left_parameter != NULL && right_parameter != NULL)
    {
        log_debug("Division of Bank %02i with Bank %02i.\n", 
            left_parameter->identifier, right_parameter->identifier);

        switch (left_parameter->type)
        {
            case TYPE_INTEGER:
                log_debug("Doing integer division.\n");
                instruction_ok = 
                    set_bank_integer(left_parameter, 
                        get_bank_as_integer(left_parameter) /
                        get_bank_as_integer(right_parameter));
                break;
            case TYPE_FLOAT: 
                log_debug("Doing float division.\n");
                 instruction_ok = 
                    set_bank_float(left_parameter, 
                        get_bank_as_float(left_parameter) /
                        get_bank_as_float(right_parameter));
                break;
            default:
                log_error(ERROR_MESG_IGNORING_OPERATION_UNSUPPORTED_TYPE,
                    "division", left_parameter->identifier);
                instruction_ok = false;
                break;
        }
    }
    else if (left_parameter == NULL)
    {
        log_error(ERROR_MESG_IGNORING_OPERATION_BANK_UNDEFINED, 
            "division", parameters->first.identifier);
    }
    else if (right_parameter == NULL)
    {
        log_error(ERROR_MESG_IGNORING_OPERATION_BANK_UNDEFINED, 
            "division", parameters->second.identifier);
    }

    increment_instruction(instruction_pointer);
    return instruction_ok;
}

bool instruction_modulo(Program *program, Parameters *parameters, InstructionPointer *instruction_pointer)
{
    Bank *left_parameter = get_bank_from_parameter(program, &(parameters->first));
    Bank *right_parameter = get_bank_from_parameter(program, &(parameters->second));
    bool instruction_ok = false;

    if (left_parameter != NULL && right_parameter != NULL)
    {
        log_debug("Modulo of Bank %02i with Bank %02i.\n", 
            left_parameter->identifier, right_parameter->identifier);

        switch (left_parameter->type)
        {
            case TYPE_INTEGER:
                log_debug("Doing integer modulo.\n");
                instruction_ok = 
                    set_bank_integer(left_parameter, 
                        get_bank_as_integer(left_parameter) %
                        get_bank_as_integer(right_parameter));
                break;
            case TYPE_FLOAT: 
                log_debug("Doing float modulo.\n");
                 instruction_ok = 
                    set_bank_float(left_parameter, 
                        fmodf(
                            get_bank_as_float(left_parameter),
                            get_bank_as_float(right_parameter)));
                break;
            default:
                log_error(ERROR_MESG_IGNORING_OPERATION_UNSUPPORTED_TYPE,
                    "modulo", left_parameter->identifier);
                instruction_ok = false;
                break;
        }
    }
    else if (left_parameter == NULL)
    {
        log_error(ERROR_MESG_IGNORING_OPERATION_BANK_UNDEFINED, 
            "modulo", parameters->first.identifier);
    }
    else if (right_parameter == NULL)
    {
        log_error(ERROR_MESG_IGNORING_OPERATION_BANK_UNDEFINED, 
            "modulo", parameters->second.identifier);
    }

    increment_instruction(instruction_pointer);
    return instruction_ok;
}

bool instruction_power(Program *program, Parameters *parameters, InstructionPointer *instruction_pointer)
{
    Bank *left_parameter = get_bank_from_parameter(program, &(parameters->first));
    Bank *right_parameter = get_bank_from_parameter(program, &(parameters->second));
    bool instruction_ok = false;

    if (left_parameter != NULL && right_parameter != NULL)
    {
        log_debug("Power of Bank %02i with Bank %02i.\n", 
            left_parameter->identifier, right_parameter->identifier);

        switch (left_parameter->type)
        {
            case TYPE_INTEGER:
                log_debug("Doing integer power.\n");
                instruction_ok = 
                    set_bank_integer(left_parameter, 
                        powf(
                            get_bank_as_float(left_parameter),
                            get_bank_as_float(right_parameter)));
                break;
            case TYPE_FLOAT: 
                log_debug("Doing float power.\n");
                 instruction_ok = 
                    set_bank_float(left_parameter, 
                        powf(
                            get_bank_as_float(left_parameter),
                            get_bank_as_float(right_parameter)));
                break;
            default:
                log_error(ERROR_MESG_IGNORING_OPERATION_UNSUPPORTED_TYPE,
                    "power", left_parameter->identifier);
                instruction_ok = false;
                break;
        }
    }
    else if (left_parameter == NULL)
    {
        log_error(ERROR_MESG_IGNORING_OPERATION_BANK_UNDEFINED, 
            "power", parameters->first.identifier);
    }
    else if (right_parameter == NULL)
    {
        log_error(ERROR_MESG_IGNORING_OPERATION_BANK_UNDEFINED, 
            "power", parameters->second.identifier);
    }

    increment_instruction(instruction_pointer);
    return instruction_ok;
}

bool instruction_square_root(Program *program, Parameters *parameters, InstructionPointer *instruction_pointer)
{
    Bank *bank = get_bank_from_parameter(program, &(parameters->first));
    bool instruction_ok = false;

    if (bank != NULL)
    {
        log_debug("Square root of Bank %02i.\n", bank->identifier);

        switch (bank->type)
        {
            case TYPE_INTEGER:
                log_debug("Doing integer square root.\n");
                instruction_ok = 
                    set_bank_integer(bank, 
                        sqrtf(get_bank_as_float(bank)));
                break;
            case TYPE_FLOAT: 
                log_debug("Doing float square root.\n");
                 instruction_ok = 
                    set_bank_float(bank, 
                        sqrtf(get_bank_as_float(bank)));
                break;
            default:
                log_error(ERROR_MESG_IGNORING_OPERATION_UNSUPPORTED_TYPE,
                    "square root", bank->identifier);
                instruction_ok = false;
                break;
        }
    }
    else
    {
        log_error(ERROR_MESG_IGNORING_OPERATION_BANK_UNDEFINED, 
            "square root", parameters->first.identifier);
    }

    increment_instruction(instruction_pointer);
    return instruction_ok;
}

bool instruction_increment(Program *program, Parameters *parameters, InstructionPointer *instruction_pointer)
{
    return add_value(program, parameters, instruction_pointer, 1);
}

bool instruction_decrement(Program *program, Parameters *parameters, InstructionPointer *instruction_pointer)
{
    return add_value(program, parameters, instruction_pointer, -1);
}

bool add_value(Program *program, Parameters *parameters, InstructionPointer *instruction_pointer, int value_to_add)
{
    Bank *bank = get_bank_from_parameter(program, &(parameters->first));
    bool instruction_ok = false;

    if (bank != NULL)
    {
        log_debug("Adding %i to Bank %02i.\n", 
            value_to_add, bank->identifier);

        switch (bank->type)
        {
            case TYPE_INTEGER:
                log_debug("Adding %i to integer.\n", value_to_add);
                instruction_ok = 
                    set_bank_integer(bank, 
                        get_bank_as_integer(bank) + value_to_add);
                break;
            case TYPE_FLOAT: 
                log_debug("Adding %i to float.\n", value_to_add);
                 instruction_ok = 
                    set_bank_float(bank, 
                        get_bank_as_float(bank) + value_to_add);
                break;
            default:
                log_error(ERROR_MESG_IGNORING_OPERATION_UNSUPPORTED_TYPE,
                    "increment/decrement", bank->identifier);
                instruction_ok = false;
                break;
        }
    }
    else
    {
        log_error(ERROR_MESG_IGNORING_OPERATION_BANK_UNDEFINED, 
            "increment/decrement", parameters->first.identifier);
    }

    increment_instruction(instruction_pointer);
    return instruction_ok;
}

char *join_strings(char *left_string, char *right_string)
{
    char *joined_string = new_string("");

    if (left_string != NULL)
    {
        joined_string = append_string(joined_string, left_string);
    }

    if (left_string != NULL && right_string != NULL)
    {
        joined_string = append_string(joined_string, " ");
    }

    if (right_string != NULL)
    {
        joined_string = append_string(joined_string, right_string);
    }

    return joined_string;
}