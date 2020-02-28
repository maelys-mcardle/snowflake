#include <stdlib.h>
#include <string.h>
#include "headers/bank.h"
#include "headers/output.h"
#include "headers/errors.h"

Bank *new_bank(short identifier)
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

bool set_bank_array(Bank *bank)
{
    clear_bank_value(bank);
    bank->type = TYPE_ARRAY;
    bank->value.array.count = 0;
    bank->value.array.items = NULL;
    return true;
}
