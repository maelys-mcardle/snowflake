#include <stdlib.h>
#include <math.h>
#include "run/bank_operations.h"
#include "errors.h"
#include "core/string.h"
#include "platforms/logging.h"

bool single_bank_operation(Program *program, Parameters *parameters, InstructionPointer *instruction_pointer, 
    SingleBankOperation operation_function, char *operation_name)
{
    Bank *bank = get_bank_from_parameter(program, &(parameters->first));
    bool instruction_ok = false;

    if (bank != NULL)
    {
        log_debug("%s of Bank %02i.\n",
            operation_name, bank->identifier);

        instruction_ok = operation_function(bank, operation_name);
    }
    else
    {
        log_error(ERROR_MESG_IGNORING_OPERATION_BANK_UNDEFINED, 
            operation_name, parameters->first.identifier);
    }

    increment_instruction(instruction_pointer);
    return instruction_ok;
}

bool dual_bank_operation(Program *program, Parameters *parameters, InstructionPointer *instruction_pointer, 
    DualBankOperation operation_function, char *operation_name)
{
    Bank *left_parameter = get_bank_from_parameter(program, &(parameters->first));
    Bank *right_parameter = get_bank_from_parameter(program, &(parameters->second));
    bool instruction_ok = false;

    if (left_parameter != NULL && right_parameter != NULL)
    {
        log_debug("%s of Bank %02i with Bank %02i.\n",
            operation_name, left_parameter->identifier, 
            right_parameter->identifier);

        instruction_ok = operation_function(
            left_parameter, right_parameter, operation_name);
    }
    else if (left_parameter == NULL)
    {
        log_error(ERROR_MESG_IGNORING_OPERATION_BANK_UNDEFINED, 
            operation_name, parameters->first.identifier);
    }
    else if (right_parameter == NULL)
    {
        log_error(ERROR_MESG_IGNORING_OPERATION_BANK_UNDEFINED, 
            operation_name, parameters->second.identifier);
    }

    increment_instruction(instruction_pointer);
    return instruction_ok;
}

bool bank_operation_addition(Bank *first_bank, Bank *second_bank, char *operation_name)
{
    if (first_bank->type == TYPE_INTEGER)
    {
        return set_bank_integer(first_bank, 
            get_bank_as_integer(first_bank) +
            get_bank_as_integer(second_bank));
    }
    else if (first_bank->type == TYPE_FLOAT)
    {
        return set_bank_float(first_bank, 
            get_bank_as_float(first_bank) +
            get_bank_as_float(second_bank));
    }
    else if (first_bank->type == TYPE_STRING)
    {
        char *left_string = get_bank_as_string(first_bank);
        char *right_string = get_bank_as_string(second_bank);
        char *combined_string = join_strings(left_string, right_string);
        bool is_ok = set_bank_string(first_bank, combined_string);
        if (left_string != NULL) free(left_string);
        if (right_string != NULL) free(right_string);
        if (combined_string != NULL) free(combined_string);
        return is_ok;
    }

    log_error(ERROR_MESG_IGNORING_OPERATION_UNSUPPORTED_TYPE,
        operation_name, first_bank->identifier);
    return false;
}

bool bank_operation_subtraction(Bank *first_bank, Bank *second_bank, char *operation_name)
{
    if (first_bank->type == TYPE_INTEGER)
    {
        return set_bank_integer(first_bank, 
            get_bank_as_integer(first_bank) -
            get_bank_as_integer(second_bank));
    }
    else if (first_bank->type == TYPE_FLOAT)
    {
        return set_bank_float(first_bank, 
            get_bank_as_float(first_bank) -
            get_bank_as_float(second_bank));
    }

    log_error(ERROR_MESG_IGNORING_OPERATION_UNSUPPORTED_TYPE,
        operation_name, first_bank->identifier);
    return false;
}

bool bank_operation_multiplication(Bank *first_bank, Bank *second_bank, char *operation_name)
{
    if (first_bank->type == TYPE_INTEGER)
    {
        return set_bank_integer(first_bank, 
            get_bank_as_integer(first_bank) *
            get_bank_as_integer(second_bank));
    }
    else if (first_bank->type == TYPE_FLOAT)
    {
        return set_bank_float(first_bank, 
            get_bank_as_float(first_bank) *
            get_bank_as_float(second_bank));
    }

    log_error(ERROR_MESG_IGNORING_OPERATION_UNSUPPORTED_TYPE,
        operation_name, first_bank->identifier);
    return false;
}

bool bank_operation_division(Bank *first_bank, Bank *second_bank, char *operation_name)
{
    if (first_bank->type == TYPE_INTEGER)
    {
        return set_bank_integer(first_bank, 
            get_bank_as_integer(first_bank) /
            get_bank_as_integer(second_bank));
    }
    else if (first_bank->type == TYPE_FLOAT)
    {
        return set_bank_float(first_bank, 
            get_bank_as_float(first_bank) /
            get_bank_as_float(second_bank));
    }

    log_error(ERROR_MESG_IGNORING_OPERATION_UNSUPPORTED_TYPE,
        operation_name, first_bank->identifier);
    return false;
}

bool bank_operation_modulo(Bank *first_bank, Bank *second_bank, char *operation_name)
{
    if (first_bank->type == TYPE_INTEGER)
    {
        return set_bank_integer(first_bank, 
            get_bank_as_integer(first_bank) %
            get_bank_as_integer(second_bank));
    }
    else if (first_bank->type == TYPE_FLOAT)
    {
        return set_bank_float(first_bank, 
                fmodf(get_bank_as_float(first_bank),
                    get_bank_as_float(second_bank)));
    }

    log_error(ERROR_MESG_IGNORING_OPERATION_UNSUPPORTED_TYPE,
        operation_name, first_bank->identifier);
    return false;
}

bool bank_operation_power(Bank *first_bank, Bank *second_bank, char *operation_name)
{
    if (first_bank->type == TYPE_INTEGER)
    {
        return set_bank_integer(first_bank, 
                powf(
                    get_bank_as_float(first_bank),
                    get_bank_as_float(second_bank)));
    }
    else if (first_bank->type == TYPE_FLOAT)
    {
        return set_bank_float(first_bank, 
                powf(get_bank_as_float(first_bank),
                    get_bank_as_float(second_bank)));
    }

    log_error(ERROR_MESG_IGNORING_OPERATION_UNSUPPORTED_TYPE,
        operation_name, first_bank->identifier);
    return false;
}

bool bank_operation_square_root(Bank *bank, char *operation_name)
{
    if (bank->type == TYPE_INTEGER)
    {
        return set_bank_integer(bank, 
            sqrtf(get_bank_as_float(bank)));
    }
    else if (bank->type == TYPE_FLOAT)
    {
        return set_bank_float(bank, 
            sqrtf(get_bank_as_float(bank)));
    }

    log_error(ERROR_MESG_IGNORING_OPERATION_UNSUPPORTED_TYPE,
        operation_name, bank->identifier);
    return false;
}

bool bank_operation_not(Bank *bank, char *operation_name)
{
    if (bank->type == TYPE_INTEGER)
    {
        return set_bank_integer(bank, 
            ~get_bank_as_integer(bank));
    }
    else if (bank->type == TYPE_BOOLEAN)
    {
        return set_bank_boolean(bank, 
            !get_bank_as_boolean(bank));
    }

    log_error(ERROR_MESG_IGNORING_OPERATION_UNSUPPORTED_TYPE,
        operation_name, bank->identifier);
    return false;
}

bool bank_operation_and(Bank *first_bank, Bank *second_bank, char *operation_name)
{
    if (first_bank->type == TYPE_INTEGER)
    {
        return set_bank_integer(first_bank, 
            get_bank_as_integer(first_bank) &
            get_bank_as_integer(second_bank));
    }
    else if (first_bank->type == TYPE_BOOLEAN)
    {
        return set_bank_boolean(first_bank, 
            get_bank_as_boolean(first_bank) &
            get_bank_as_boolean(second_bank));
    }

    log_error(ERROR_MESG_IGNORING_OPERATION_UNSUPPORTED_TYPE,
        operation_name, first_bank->identifier);
    return false;
}

bool bank_operation_or(Bank *first_bank, Bank *second_bank, char *operation_name)
{
    if (first_bank->type == TYPE_INTEGER)
    {
        return set_bank_integer(first_bank, 
            get_bank_as_integer(first_bank) |
            get_bank_as_integer(second_bank));
    }
    else if (first_bank->type == TYPE_BOOLEAN)
    {
        return set_bank_boolean(first_bank, 
            get_bank_as_boolean(first_bank) |
            get_bank_as_boolean(second_bank));
    }

    log_error(ERROR_MESG_IGNORING_OPERATION_UNSUPPORTED_TYPE,
        operation_name, first_bank->identifier);
    return false;
}

bool bank_operation_xor(Bank *first_bank, Bank *second_bank, char *operation_name)
{
    if (first_bank->type == TYPE_INTEGER)
    {
        return set_bank_integer(first_bank, 
            get_bank_as_integer(first_bank) ^
            get_bank_as_integer(second_bank));
    }
    else if (first_bank->type == TYPE_BOOLEAN)
    {
        return set_bank_boolean(first_bank, 
            get_bank_as_boolean(first_bank) ^
            get_bank_as_boolean(second_bank));
    }

    log_error(ERROR_MESG_IGNORING_OPERATION_UNSUPPORTED_TYPE,
        operation_name, first_bank->identifier);
    return false;
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