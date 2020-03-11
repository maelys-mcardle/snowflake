#include <stdlib.h>
#include <math.h>
#include "headers/run_instruction_math.h"
#include "headers/string.h"
#include "headers/output.h"

bool instruction_add(Program *program, Parameters *parameters, int *instruction_pointer)
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
                combined_string = concatenate_strings(left_string, right_string, true);
                instruction_ok = set_bank_string(left_parameter, combined_string);
                if (left_string != NULL) free(left_string);
                if (right_string != NULL) free(right_string);
                if (combined_string != NULL) free(combined_string);
                break;
            default:
                log_debug("Ignoring addition - it's for an unsupported type.\n");
                instruction_ok = false;
                break;
        }
    }

    *instruction_pointer += 1;
    return instruction_ok;
}

bool instruction_subtract(Program *program, Parameters *parameters, int *instruction_pointer)
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
                log_debug("Ignoring subtraction - it's for an unsupported type.\n");
                instruction_ok = false;
                break;
        }
    }

    *instruction_pointer += 1;
    return instruction_ok;
}

bool instruction_multiply(Program *program, Parameters *parameters, int *instruction_pointer)
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
                log_debug("Ignoring multiplication - it's for an unsupported type.\n");
                instruction_ok = false;
                break;
        }
    }

    *instruction_pointer += 1;
    return instruction_ok;
}

bool instruction_divide(Program *program, Parameters *parameters, int *instruction_pointer)
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
                log_debug("Ignoring division - it's for an unsupported type.\n");
                instruction_ok = false;
                break;
        }
    }

    *instruction_pointer += 1;
    return instruction_ok;
}

bool instruction_modulo(Program *program, Parameters *parameters, int *instruction_pointer)
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
                log_debug("Ignoring modulo - it's for an unsupported type.\n");
                instruction_ok = false;
                break;
        }
    }

    *instruction_pointer += 1;
    return instruction_ok;
}

bool instruction_power(Program *program, Parameters *parameters, int *instruction_pointer)
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
                log_debug("Ignoring power - it's for an unsupported type.\n");
                instruction_ok = false;
                break;
        }
    }

    *instruction_pointer += 1;
    return instruction_ok;
}

bool instruction_square_root(Program *program, Parameters *parameters, int *instruction_pointer)
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
                log_debug("Ignoring square root - it's for an unsupported type.\n");
                instruction_ok = false;
                break;
        }
    }

    *instruction_pointer += 1;
    return instruction_ok;
}