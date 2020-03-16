#include <stdlib.h>
#include <string.h>
#include "headers/string.h"
#include "headers/bank.h"
#include "headers/logging.h"
#include "headers/errors.h"
#include "headers/type_conversion.h"
#include "headers/array.h"

Bank *new_bank(Identifier identifier)
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
        free_bank_array(bank);
        free(bank);
    }
}

void free_bank_array(Bank *bank)
{
    if (bank != NULL &&
        bank->type == TYPE_ARRAY && 
        bank->value.array != NULL)
    {
        free_array(bank->value.array);
        bank->value.array = NULL;
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
    free_bank_array(bank);
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
    bank->value.array = new_array();
    return true;
}

bool set_bank_array(Bank *bank, Array *value)
{
    log_debug("Set array for Bank %02i.\n", bank->identifier);
    clear_bank_value(bank);
    bank->type = TYPE_ARRAY;
    bank->value.array = copy_array(value);
    return true;
}

bool get_bank_as_boolean(Bank *bank)
{
    if (bank == NULL)
    {
        log_debug("Invalid bank - returning default value.\n");
        return false;
    }

    log_debug("Interpreting Bank %02i as a boolean.\n", bank->identifier);

    bool ok = true;
    switch (bank->type)
    {
        case TYPE_BOOLEAN:
            return bank->value.boolean;
        case TYPE_INTEGER:
            return bank->value.integer != 0;
        case TYPE_FLOAT:
            return bank->value.floating != 0;
        case TYPE_STRING:
            return string_to_boolean(bank->value.string, &ok);
        case TYPE_ARRAY:
            return false;
        default:
            return false;
    }
}

int get_bank_as_integer(Bank *bank)
{
    if (bank == NULL)
    {
        log_debug("Invalid bank - returning default value.\n");
        return 0;
    }

    log_debug("Interpreting Bank %02i as an integer.\n", bank->identifier);

    bool ok = true;
    switch (bank->type)
    {
        case TYPE_BOOLEAN:
            return bank->value.boolean ? 1 : 0;
        case TYPE_INTEGER:
            return bank->value.integer;
        case TYPE_FLOAT:
            return bank->value.floating;
        case TYPE_STRING:
            return string_to_integer(bank->value.string, &ok);
        case TYPE_ARRAY:
            return get_array_count(bank->value.array);
        default:
            return 0;
    }
}

float get_bank_as_float(Bank *bank)
{
    if (bank == NULL)
    {
        log_debug("Invalid bank - returning default value.\n");
        return 0.;
    }

    log_debug("Interpreting Bank %02i as a float.\n", bank->identifier);

    bool ok = true;
    switch (bank->type)
    {
        case TYPE_BOOLEAN:
            return bank->value.boolean ? 1. : 0.;
        case TYPE_INTEGER:
            return bank->value.integer;
        case TYPE_FLOAT:
            return bank->value.floating;
        case TYPE_STRING:
            return string_to_float(bank->value.string, &ok);
        case TYPE_ARRAY:
            return get_array_count(bank->value.array);
        default:
            return 0.;
    }
}

char *get_bank_as_string(Bank *bank)
{
    if (bank == NULL)
    {
        log_debug("Invalid bank - returning default value.\n");
        return NULL;
    }

    log_debug("Interpreting Bank %02i as a string.\n", bank->identifier);
    int output_string_size = MAX_PARAMETER_SIZE;
    char *output_string = malloc(output_string_size);
    int actual_size = 0;

    if (output_string == NULL)
    {
        log_error(ERROR_MESG_COULD_NOT_ALLOCATE_MEMORY);
    }
    else
    {
        switch (bank->type)
        {
            case TYPE_BOOLEAN:
                actual_size = snprintf(output_string, output_string_size, 
                    "%i", bank->value.boolean ? 1 : 0);
                break;
            case TYPE_INTEGER:
                actual_size = snprintf(output_string, output_string_size, 
                    "%i", bank->value.integer);
                break;
            case TYPE_FLOAT:
                actual_size = snprintf(output_string, output_string_size, 
                    "%f", bank->value.floating);
                break;
            case TYPE_STRING:
                actual_size = snprintf(output_string, output_string_size, 
                    "%s", bank->value.string);
                break;
            case TYPE_ARRAY:
            default:
                output_string[0] = CHAR_END_STRING;
                actual_size = 1;
                break;
        }

        output_string = realloc(output_string, actual_size);
    }

    return output_string;
}

bool convert_bank(Bank *bank, BankType to_type)
{
    bool convert_ok = false;
    BankType from_type = bank->type;
    bool as_boolean;
    int as_integer;
    float as_float;
    char *as_string = NULL;

    if (to_type == TYPE_BOOLEAN && from_type != TYPE_BOOLEAN)
    {
        log_debug("Converting Bank %02i to boolean.\n", bank->identifier);
        as_boolean = get_bank_as_boolean(bank);
        convert_ok = set_bank_boolean(bank, as_boolean);
    }
    else if (to_type == TYPE_INTEGER && from_type != TYPE_INTEGER)
    {
        log_debug("Converting Bank %02i to integer.\n", bank->identifier);
        as_integer = get_bank_as_integer(bank);
        convert_ok = set_bank_integer(bank, as_integer);
    }
    else if (to_type == TYPE_FLOAT && from_type != TYPE_FLOAT)
    {
        log_debug("Converting Bank %02i to float.\n", bank->identifier);
        as_float = get_bank_as_float(bank);
        convert_ok = set_bank_float(bank, as_float);
    }
    else if (to_type == TYPE_STRING && from_type != TYPE_STRING)
    {
        log_debug("Converting Bank %02i to string.\n", bank->identifier);
        as_string = get_bank_as_string(bank);
        if (as_string != NULL)
        {
            convert_ok = set_bank_string(bank, as_string);
            free(as_string);
        }
    }
    else if (to_type == TYPE_ARRAY && from_type != TYPE_ARRAY)
    {
        log_debug("Converting Bank %02i to array.\n", bank->identifier);
        convert_ok = set_empty_bank_array(bank);
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
        Array *source_value = get_bank_array(source, &source_ok);
        destination_ok = set_bank_array(destination, source_value);
    }

    return source_ok && destination_ok;
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

Array *get_bank_array(Bank *bank, bool *ok)
{
    if (bank != NULL && bank->type == TYPE_ARRAY)
    {
        log_debug("Read array from Bank %02i.\n", bank->identifier);
        *ok = true;
        return bank->value.array;
    }

    *ok = false;
    return NULL;
}
