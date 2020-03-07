#include <stdlib.h>
#include <string.h>
#include "headers/bank.h"
#include "headers/output.h"
#include "headers/errors.h"

Bank *new_bank(BankIdentifier identifier)
{
    Bank *bank = (Bank *) malloc(sizeof(Bank));
    if (bank != NULL)
    {
        bank->identifier = identifier;
        bank->type = TYPE_VARIABLE;
    }
    else
    {
        log_error(ERROR_MESG_COULD_NOT_ALLOCATE_MEMORY);
    }
    return bank;
}

void free_bank(Bank *bank)
{
    if (bank != NULL)
    {
        free_string(bank);
        free_array(bank);
        free(bank);
    }
}

void free_array(Bank *bank)
{
    if (bank != NULL &&
        bank->type == TYPE_ARRAY &&
        bank->value.array.items != NULL)
    {
        free(bank->value.array.items);
        bank->value.array.items = NULL;
        bank->value.array.count = 0;
    }
}

void free_string(Bank *bank)
{
    if (bank != NULL &&
        bank->type == TYPE_STRING &&
        bank->value.string != NULL)
    {
        free(bank->value.string);
        bank->value.string = NULL;
    }
}

void clear_bank_value(Bank *bank)
{
    free_string(bank);
    free_array(bank);
    bank->type = TYPE_VARIABLE;
}

bool set_bank_boolean(Bank *bank, bool value)
{
    clear_bank_value(bank);
    bank->type = TYPE_BOOLEAN;
    bank->value.boolean = value;
    return true;
}

bool set_bank_integer(Bank *bank, int value)
{
    clear_bank_value(bank);
    bank->type = TYPE_INTEGER;
    bank->value.integer = value;
    return true;
}

bool set_bank_float(Bank *bank, float value)
{
    clear_bank_value(bank);
    bank->type = TYPE_FLOAT;
    bank->value.floating = value;
    return true;
}

bool set_bank_string(Bank *bank, char *value)
{
    clear_bank_value(bank);
    bank->type = TYPE_STRING;
    size_t string_length = strlen(value);
    bank->value.string = malloc(string_length + 1);
    strncpy(bank->value.string, value, string_length + 1);
    return true;
}

bool set_bank_array(Bank *bank, BankArray *value)
{
    clear_bank_value(bank);
    bank->type = TYPE_ARRAY;
    bank->value.array.count = value->count;
    bank->value.array.items = NULL;
    return true;
}

bool copy_bank(Bank *destination, Bank *source)
{
    bool source_ok = false;
    bool destination_ok = false;
    clear_bank_value(destination);
    destination->type = source->type;

    if (source->type == TYPE_INTEGER)
    {
        int source_value = get_bank_integer(source, &source_ok);
        destination_ok = set_bank_integer(destination, source_value);
    }
    else if (source->type == TYPE_BOOLEAN)
    {
        bool source_value = get_bank_boolean(source, &source_ok);
        destination_ok = set_bank_boolean(destination, source_value);
    }
    else if (source->type == TYPE_FLOAT)
    {
        float source_value = get_bank_float(source, &source_ok);
        destination_ok = set_bank_float(destination, source_value);
    }
    else if (source->type == TYPE_STRING)
    {
        char *source_value = get_bank_string(source, &source_ok);
        destination_ok = set_bank_string(destination, source_value);
    }
    else if (source->type == TYPE_ARRAY)
    {
        BankArray *source_value = get_bank_array(source, &source_ok);
        destination_ok = set_bank_array(destination, source_value);
    }

    return source_ok && destination_ok;
}

char *get_bank_as_string(Bank *bank)
{
    char *output_string = NULL;
    bool read_bank_value = false;

    if (bank != NULL)
    {
        int output_string_size = MAX_PARAMETER_SIZE;
        output_string = malloc(output_string_size);
        int actual_size = 0;

        if (output_string == NULL)
        {
            log_error(ERROR_MESG_COULD_NOT_ALLOCATE_MEMORY);
        }
        else
        {
            if (bank->type == TYPE_INTEGER)
            {
                actual_size = snprintf(output_string, output_string_size, 
                    "%i", get_bank_integer(bank, &read_bank_value));
            }
            else if (bank->type == TYPE_BOOLEAN)
            {
                actual_size = snprintf(output_string, output_string_size, 
                    "%s", get_bank_boolean(bank, &read_bank_value) ? "true" : "false");
            }
            else if (bank->type == TYPE_FLOAT)
            {
                actual_size = snprintf(output_string, output_string_size, 
                    "%f", get_bank_float(bank, &read_bank_value));
            }
            else if (bank->type == TYPE_STRING)
            {
                actual_size = snprintf(output_string, output_string_size, 
                    "%s", get_bank_string(bank, &read_bank_value));
            }
            else if (bank->type == TYPE_ARRAY)
            {
                actual_size = snprintf(output_string, output_string_size, 
                    "(Array)");
            }

            output_string = realloc(output_string, actual_size);
        }
    }

    return output_string;
}

bool get_bank_boolean(Bank *bank, bool *ok)
{
    if (bank != NULL && bank->type == TYPE_BOOLEAN)
    {
        *ok = true;
        return bank->value.boolean;
    }

    *ok = false;
    return false;
}

int get_bank_integer(Bank *bank, bool *ok)
{
    if (bank != NULL && bank->type == TYPE_INTEGER)
    {
        *ok = true;
        return bank->value.integer;
    }

    *ok = false;
    return 0;
}

float get_bank_float(Bank *bank, bool *ok)
{
    if (bank != NULL && bank->type == TYPE_FLOAT)
    {
        *ok = true;
        return bank->value.floating;
    }

    *ok = false;
    return 0.0;
}

char *get_bank_string(Bank *bank, bool *ok)
{
    if (bank != NULL && bank->type == TYPE_STRING)
    {
        *ok = true;
        return bank->value.string;
    }

    *ok = false;
    return NULL;
}

BankArray *get_bank_array(Bank *bank, bool *ok)
{
    if (bank != NULL && bank->type == TYPE_ARRAY)
    {
        *ok = true;
        return &bank->value.array;
    }

    *ok = false;
    return NULL;
}
