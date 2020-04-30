#include <stdlib.h>
#include <string.h>
#include "core/array.h"
#include "core/string.h"
#include "core/type_conversion.h"
#include "platforms/logging.h"
#include "errors.h"
#include "core/bank.h"

/**
 * Creates a new bank.
 * 
 * @param identifier unique identifier for the bank.
 * @return allocated bank.
 */
Bank *new_bank(Identifier identifier)
{
    Bank *bank = (Bank *) malloc(sizeof(Bank));
    if (bank != NULL)
    {
        bank->identifier = identifier;
        bank->type = TYPE_UNDEFINED;
    }
    else
    {
        log_error(ERROR_MESG_COULD_NOT_ALLOCATE_MEMORY);
    }
    return bank;
}

/**
 * Frees the allocated bank.
 * 
 * @param bank to free.
 */
void free_bank(Bank *bank)
{
    if (bank != NULL)
    {
        log_debug("Freeing Bank %02i.\n", ((Bank *) bank)->identifier);
        free_string(bank);
        free_bank_array(bank);
        free(bank);
    }
}

/**
 * Frees an array stored in a bank.
 * 
 * @param bank bank containing the array.
 */
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

/**
 * Frees a string stored in a bank.
 * 
 * @param bank bank containing the string.
 */
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

/**
 * Clears the value of a bank.
 * 
 * @param bank bank to clear.
 */
void clear_bank_value(Bank *bank)
{
    free_string(bank);
    free_bank_array(bank);
    bank->type = TYPE_UNDEFINED;
}

/**
 * Sets the bank as a boolean.
 * 
 * @param bank bank to set.
 * @param value value to assign.
 * @return whether the operation was successful.
 */
bool set_bank_boolean(Bank *bank, bool value)
{
    log_debug("Set boolean for Bank %02i.\n", bank->identifier);
    clear_bank_value(bank);
    bank->type = TYPE_BOOLEAN;
    bank->value.boolean = value;
    return true;
}

/**
 * Sets the bank as an integer.
 * 
 * @param bank bank to set.
 * @param value value to assign.
 * @return whether the operation was successful.
 */
bool set_bank_integer(Bank *bank, int value)
{
    log_debug("Set integer for Bank %02i.\n", bank->identifier);
    clear_bank_value(bank);
    bank->type = TYPE_INTEGER;
    bank->value.integer = value;
    return true;
}

/**
 * Sets the bank as a floating point value.
 * 
 * @param bank bank to set.
 * @param value value to assign.
 * @return whether the operation was successful.
 */
bool set_bank_float(Bank *bank, float value)
{
    log_debug("Set float for Bank %02i.\n", bank->identifier);
    clear_bank_value(bank);
    bank->type = TYPE_FLOAT;
    bank->value.floating = value;
    return true;
}

/**
 * Sets the bank as a string.
 * 
 * @param bank bank to set.
 * @param value value to assign.
 * @return whether the operation was successful.
 */
bool set_bank_string(Bank *bank, char *value)
{
    log_debug("Set string for Bank %02i.\n", bank->identifier);
    clear_bank_value(bank);
    bank->type = TYPE_STRING;
    bank->value.string = new_string(value);
    return true;
}

/**
 * Sets the bank as an array.
 * 
 * @param bank bank to set.
 * @param value value to assign.
 * @return whether the operation was successful.
 */
bool set_bank_array(Bank *bank, Array *value)
{
    log_debug("Set array for Bank %02i.\n", bank->identifier);
    clear_bank_value(bank);
    bank->type = TYPE_ARRAY;
    bank->value.array = copy_array(value);
    return true;
}

/**
 * Sets the bank as an empty array.
 * 
 * @param bank bank to set.
 * @return whether the operation was successful.
 */
bool set_empty_bank_array(Bank *bank)
{
    log_debug("Set array for Bank %02i.\n", bank->identifier);
    clear_bank_value(bank);
    bank->type = TYPE_ARRAY;
    bank->value.array = new_bank_array();
    return true;
}
/**
 * Interprets the bank value as a boolean.
 * The bank itself can contain any value.
 * 
 * @param bank bank to get value from.
 * @return the interpreted value.
 */
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

/**
 * Interprets the bank value as an integer.
 * The bank itself can contain any value.
 * 
 * @param bank bank to get value from.
 * @return the interpreted value.
 */
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

/**
 * Interprets the bank value as a float.
 * The bank itself can contain any value.
 * 
 * @param bank bank to get value from.
 * @return the interpreted value.
 */
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

/**
 * Interprets the bank value as a string.
 * The bank itself can contain any value.
 * 
 * @param bank bank to get value from.
 * @return the interpreted value.
 */
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

/**
 * Interprets the bank value as an array.
 * The bank itself can contain any value.
 * 
 * @param bank bank to get value from.
 * @return the interpreted value.
 */
Array *get_bank_as_array(Bank *bank)
{
    if (bank != NULL && bank->type == TYPE_ARRAY)
    {
        log_debug("Read array from Bank %02i.\n", bank->identifier);
        return bank->value.array;
    }

    return NULL;
}

/**
 * Converts bank to the specified type.
 * 
 * @param bank bank to convert.
 * @param to_type the type to convert the bank value to.
 * @return whether the operation was successful.
 */
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

/**
 * Copies the bank.
 * 
 * @param destination where to copy the bank to.
 * @param source where to copy the bank from.
 * @return whether the operation was successful.
 */
bool copy_bank(Bank *destination, Bank *source)
{
    bool set_bank_ok = false;
    clear_bank_value(destination);

    log_debug("Copying from Bank %02i to Bank %02i.\n", 
        source->identifier, destination->identifier);
        
    if (source->type == TYPE_INTEGER)
    {
        int source_value = get_bank_as_integer(source);
        set_bank_ok = set_bank_integer(destination, source_value);
    }
    else if (source->type == TYPE_BOOLEAN)
    {
        bool source_value = get_bank_as_boolean(source);
        set_bank_ok = set_bank_boolean(destination, source_value);
    }
    else if (source->type == TYPE_FLOAT)
    {
        float source_value = get_bank_as_float(source);
        set_bank_ok = set_bank_float(destination, source_value);
    }
    else if (source->type == TYPE_STRING)
    {
        char *source_value = get_bank_as_string(source);
        set_bank_ok = set_bank_string(destination, source_value);
    }
    else if (source->type == TYPE_ARRAY)
    {
        Array *source_value = get_bank_as_array(source);
        set_bank_ok = set_bank_array(destination, source_value);
    }

    return set_bank_ok;
}

/**
 * Creates a new array specific to banks.
 * 
 * @return array formatted for banks.
 */
Array *new_bank_array()
{
    Array *array = new_array();

    if (array != NULL)
    {
        array->free_array_item_function = free_bank_array_item;
        array->copy_array_item_function = copy_bank_array_item;
    }
    
    return array;
}

/**
 * Copies a bank in an array.
 * 
 * @param source_item item to copy from.
 * @return copy of item.
 */
ArrayItem *copy_bank_array_item(ArrayItem *source_item)
{
    Bank *destination = new_bank(0);
    copy_bank(destination, (Bank *) source_item);
    return destination;
}

/**
 * Frees a bank in an array.
 * 
 * @param bank bank item to free.
 */
void free_bank_array_item(ArrayItem *bank)
{
    free_bank((Bank *) bank);
}
