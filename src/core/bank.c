#include <stdlib.h>
#include <string.h>
#include "headers/bank.h"
#include "headers/output.h"
#include "headers/errors.h"
#include "headers/type_conversion.h"

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
    log_debug("Set boolean for Bank %02i.\n", bank->identifier);
    clear_bank_value(bank);
    bank->type = TYPE_BOOLEAN;
    bank->value.boolean = value;
    return true;
}

bool set_bank_integer(Bank *bank, int value)
{
    log_debug("Set integer for Bank %02i.\n", bank->identifier);
    clear_bank_value(bank);
    bank->type = TYPE_INTEGER;
    bank->value.integer = value;
    return true;
}

bool set_bank_float(Bank *bank, float value)
{
    log_debug("Set float for Bank %02i.\n", bank->identifier);
    clear_bank_value(bank);
    bank->type = TYPE_FLOAT;
    bank->value.floating = value;
    return true;
}

bool set_bank_string(Bank *bank, char *value)
{
    log_debug("Set string for Bank %02i.\n", bank->identifier);
    clear_bank_value(bank);
    bank->type = TYPE_STRING;
    size_t string_length = strlen(value);
    bank->value.string = malloc(string_length + 1);
    strncpy(bank->value.string, value, string_length + 1);
    return true;
}

bool set_empty_bank_array(Bank *bank)
{
    log_debug("Set array for Bank %02i.\n", bank->identifier);
    clear_bank_value(bank);
    bank->type = TYPE_ARRAY;
    bank->value.array.count = 0;
    bank->value.array.items = NULL;
    return true;
}

bool set_bank_array(Bank *bank, BankArray *value)
{
    log_debug("Set array for Bank %02i.\n", bank->identifier);
    clear_bank_value(bank);
    bank->type = TYPE_ARRAY;
    bank->value.array.count = value->count;
    bank->value.array.items = NULL;
    return true;
}

bool convert_bank(Bank *bank, BankType to_type)
{
    bool convert_ok = false;
    BankType from_type = bank->type;

    bool as_boolean;
    int as_integer;
    float as_float;
    int max_string_size = MAX_PARAMETER_SIZE;
    char as_string[max_string_size];

    log_debug("Converting Bank %02i", bank->identifier);
    if (from_type == TYPE_BOOLEAN)
    {
        log_debug(" from boolean");
        switch (to_type)
        {
            case TYPE_BOOLEAN:
                log_debug(" to boolean\n");
                break;
            case TYPE_INTEGER:
                log_debug(" to integer\n");
                as_integer = bank->value.boolean ? 1 : 0;
                convert_ok = set_bank_integer(bank, as_integer);
                break;
            case TYPE_FLOAT:
                log_debug(" to float\n");
                as_float = bank->value.boolean ? 1. : 0.;
                convert_ok = set_bank_float(bank, as_float);
                break;
            case TYPE_STRING:
                log_debug(" to string\n");
                convert_ok = set_bank_string(bank, 
                    bank->value.boolean ? "1" : "0");
                break;
            case TYPE_ARRAY:
                log_debug(" to array\n");
                convert_ok = set_empty_bank_array(bank);
                break;
            default:
                log_debug(" to unknown\n");
                convert_ok = false;
        }
    }
    else if (from_type == TYPE_INTEGER)
    {
        log_debug(" from integer");
        switch (to_type)
        {
            case TYPE_BOOLEAN:
                log_debug(" to boolean\n");
                as_boolean = bank->value.integer > 0;
                convert_ok = set_bank_boolean(bank, as_boolean);
                break;
            case TYPE_INTEGER:
                log_debug(" to integer\n");
                break;
            case TYPE_FLOAT:
                log_debug(" to float\n");
                as_float = bank->value.integer;
                convert_ok = set_bank_float(bank, as_float);
                break;
            case TYPE_STRING:
                log_debug(" to string\n");
                snprintf(as_string, max_string_size, "%i", bank->value.integer);
                convert_ok = set_bank_string(bank, as_string);
                break;
            case TYPE_ARRAY:
                log_debug(" to array\n");
                convert_ok = set_empty_bank_array(bank);
                break;
            default:
                log_debug(" to unknown\n");
                convert_ok = false;
        }
    }
    else if (from_type == TYPE_FLOAT)
    {
        log_debug(" from float");
        switch (to_type)
        {
            case TYPE_BOOLEAN:
                log_debug(" to boolean\n");
                as_boolean = bank->value.floating > 0;
                convert_ok = set_bank_boolean(bank, as_boolean);
                break;
            case TYPE_INTEGER:
                log_debug(" to integer\n");
                as_integer = bank->value.floating;
                convert_ok = set_bank_integer(bank, as_integer);
                break;
            case TYPE_FLOAT:
                log_debug(" to float\n");
                break;
            case TYPE_STRING:
                log_debug(" to string\n");
                snprintf(as_string, max_string_size, "%f", bank->value.floating);
                convert_ok = set_bank_string(bank, as_string);
                break;
            case TYPE_ARRAY:
                log_debug(" to array\n");
                convert_ok = set_empty_bank_array(bank);
                break;
            default:
                log_debug(" to unknown\n");
                convert_ok = false;
        }
    }
    else if (from_type == TYPE_STRING)
    {
        log_debug(" from string");
        switch (to_type)
        {
            case TYPE_BOOLEAN:
                log_debug(" to boolean\n");
                as_boolean = string_to_boolean(bank->value.string, &convert_ok);
                convert_ok = set_bank_boolean(bank, as_boolean);
                break;
            case TYPE_INTEGER:
                log_debug(" to integer\n");
                as_integer = string_to_integer(bank->value.string, &convert_ok);
                convert_ok = set_bank_integer(bank, as_integer);
                break;
            case TYPE_FLOAT:
                log_debug(" to float\n");
                as_float = string_to_float(bank->value.string, &convert_ok);
                convert_ok = set_bank_float(bank, as_float);
                break;
            case TYPE_STRING:
                log_debug(" to string\n");
                break;
            case TYPE_ARRAY:
                log_debug(" to array\n");
                convert_ok = set_empty_bank_array(bank);
                break;
            default:
                log_debug(" to unknown\n");
                convert_ok = false;
        }
    }
    else if (from_type == TYPE_ARRAY)
    {
        log_debug(" from array");
        switch (to_type)
        {
            case TYPE_BOOLEAN:
                log_debug(" to boolean\n");
                as_boolean = bank->value.array.count > 0;
                convert_ok = set_bank_boolean(bank, as_boolean);
                break;
            case TYPE_INTEGER:
                log_debug(" to integer\n");
                as_integer = bank->value.array.count;
                convert_ok = set_bank_integer(bank, as_integer);
                break;
            case TYPE_FLOAT:
                log_debug(" to float\n");
                as_float = bank->value.array.count;
                convert_ok = set_bank_float(bank, as_float);
                break;
            case TYPE_STRING:
                log_debug(" to string\n");
                convert_ok = set_bank_string(bank, "");
                break;
            case TYPE_ARRAY:
                log_debug(" to array\n");
                convert_ok = set_empty_bank_array(bank);
                break;
            default:
                log_debug(" to unknown\n");
                convert_ok = false;
        }
    }
    else
    {
        log_debug(" from unallocated bank");
        switch (to_type)
        {
            case TYPE_BOOLEAN:
                log_debug(" to boolean\n");
                convert_ok = set_bank_boolean(bank, false);
                break;
            case TYPE_INTEGER:
                log_debug(" to integer\n");
                convert_ok = set_bank_integer(bank, 0);
                break;
            case TYPE_FLOAT:
                log_debug(" to float\n");
                convert_ok = set_bank_float(bank, 0.);
                break;
            case TYPE_STRING:
                log_debug(" to string\n");
                convert_ok = set_bank_string(bank, "");
                break;
            case TYPE_ARRAY:
                log_debug(" to array\n");
                break;
            default:
                log_debug(" to unknown\n");
                convert_ok = false;
        }
    }
    

    return convert_ok;
}

bool copy_bank(Bank *destination, Bank *source)
{
    bool source_ok = false;
    bool destination_ok = false;
    clear_bank_value(destination);

    log_debug("Copying from Bank %02i to Bank %02i.\n", 
        source->identifier, destination->identifier);
        
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
        log_debug("Read boolean from Bank %02i.\n", bank->identifier);
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
        log_debug("Read integer from Bank %02i.\n", bank->identifier);
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
        log_debug("Read string from Bank %02i.\n", bank->identifier);
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
        log_debug("Read array from Bank %02i.\n", bank->identifier);
        *ok = true;
        return &bank->value.array;
    }

    *ok = false;
    return NULL;
}
