#ifndef SNOWFLAKE_BANK_H
#define SNOWFLAKE_BANK_H
#include <stdbool.h>
#include "parameters.h"
#include "array.h"

// Maximum size of a bank parameter.
#define MAX_PARAMETER_SIZE 256

// Bank value types.
#define TYPE_VARIABLE_STRING "VAR"
#define TYPE_BOOLEAN_STRING  "BLN"
#define TYPE_INTEGER_STRING "INT"
#define TYPE_FLOAT_STRING "FLT"
#define TYPE_STRING_STRING "STR"
#define TYPE_ARRAY_STRING " []"

/**
 * Union for the bank value.
 */
typedef union {
    int integer;
    float floating;
    bool boolean;
    char *string;
    Array *array;
} BankValue;

/**
 * Enum for the bank value's type.
 */
typedef enum {
    TYPE_UNDEFINED = 0,
    TYPE_VARIABLE  = 10,
    TYPE_BOOLEAN   = 11,
    TYPE_INTEGER   = 12,
    TYPE_FLOAT     = 13,
    TYPE_STRING    = 14,
    TYPE_ARRAY     = 15
} BankType;

/**
 * Struct for a bank.
 */
typedef struct {
    Identifier identifier;
    BankValue value;
    BankType type;
} Bank;

/**
 * Creates a new bank.
 * 
 * @param identifier unique identifier for the bank.
 * @return allocated bank.
 */
Bank *new_bank(Identifier identifier);

/**
 * Frees the allocated bank.
 * 
 * @param bank to free.
 */
void free_bank(Bank *bank);

/**
 * Clears the value of a bank.
 * 
 * @param bank bank to clear.
 */
void clear_bank_value(Bank *bank);

/**
 * Frees an array stored in a bank.
 * 
 * @param bank bank containing the array.
 */
void free_bank_array(Bank *bank);

/**
 * Frees a string stored in a bank.
 * 
 * @param bank bank containing the string.
 */
void free_string(Bank *bank);

/**
 * Copies the bank.
 * 
 * @param destination where to copy the bank to.
 * @param source where to copy the bank from.
 * @return whether the operation was successful.
 */
bool copy_bank(Bank *destination, Bank *source);

/**
 * Converts bank to the specified type.
 * 
 * @param bank bank to convert.
 * @param to_type the type to convert the bank value to.
 * @return whether the operation was successful.
 */
bool convert_bank(Bank *bank, BankType to_type);

/**
 * Sets the bank as a boolean.
 * 
 * @param bank bank to set.
 * @param value value to assign.
 * @return whether the operation was successful.
 */
bool set_bank_boolean(Bank *bank, bool value);

/**
 * Sets the bank as an integer.
 * 
 * @param bank bank to set.
 * @param value value to assign.
 * @return whether the operation was successful.
 */
bool set_bank_integer(Bank *bank, int value);

/**
 * Sets the bank as a floating point value.
 * 
 * @param bank bank to set.
 * @param value value to assign.
 * @return whether the operation was successful.
 */
bool set_bank_float(Bank *bank, float value);

/**
 * Sets the bank as a string.
 * 
 * @param bank bank to set.
 * @param value value to assign.
 * @return whether the operation was successful.
 */
bool set_bank_string(Bank *bank, char *value);

/**
 * Sets the bank as an array.
 * 
 * @param bank bank to set.
 * @param value value to assign.
 * @return whether the operation was successful.
 */
bool set_bank_array(Bank *bank, Array *value);

/**
 * Sets the bank as an empty array.
 * 
 * @param bank bank to set.
 * @return whether the operation was successful.
 */
bool set_empty_bank_array(Bank *bank);

/**
 * Gets the bank value as a boolean.
 * The bank itself must be a boolean.
 * 
 * @param bank bank to get value from.
 * @param ok whether the value was obtained.
 * @return the interpreted value.
 */
bool get_bank_boolean(Bank *bank, bool *ok);

/**
 * Gets the bank value as an integer.
 * The bank itself must be a integer.
 * 
 * @param bank bank to get value from.
 * @param ok whether the value was obtained.
 * @return the interpreted value.
 */
int get_bank_integer(Bank *bank, bool *ok);

/**
 * Gets the bank value as a float.
 * The bank itself must be a float.
 * 
 * @param bank bank to get value from.
 * @param ok whether the value was obtained.
 * @return the interpreted value.
 */
float get_bank_float(Bank *bank, bool *ok);

/**
 * Gets the bank value as a string.
 * The bank itself must be a string.
 * 
 * @param bank bank to get value from.
 * @param ok whether the value was obtained.
 * @return the interpreted value.
 */
char *get_bank_string(Bank *bank, bool *ok);

/**
 * Gets the bank value as an array.
 * The bank itself must be an array.
 * 
 * @param bank bank to get value from.
 * @param ok whether the value was obtained.
 * @return the interpreted value.
 */
Array *get_bank_array(Bank *bank, bool *ok);

/**
 * Interprets the bank value as a boolean.
 * The bank itself can contain any value.
 * 
 * @param bank bank to get value from.
 * @return the interpreted value.
 */
bool get_bank_as_boolean(Bank *bank);

/**
 * Interprets the bank value as an integer.
 * The bank itself can contain any value.
 * 
 * @param bank bank to get value from.
 * @return the interpreted value.
 */
int get_bank_as_integer(Bank *bank);

/**
 * Interprets the bank value as a float.
 * The bank itself can contain any value.
 * 
 * @param bank bank to get value from.
 * @return the interpreted value.
 */
float get_bank_as_float(Bank *bank);

/**
 * Interprets the bank value as a string.
 * The bank itself can contain any value.
 * 
 * @param bank bank to get value from.
 * @return the interpreted value.
 */
char *get_bank_as_string(Bank *bank);

/**
 * Creates a new array specific to banks.
 * 
 * @return array formatted for banks.
 */
Array *new_bank_array();

/**
 * Copies a bank in an array.
 * 
 * @param source_item item to copy from.
 * @return copy of item.
 */
ArrayItem *copy_bank_array_item(ArrayItem *source_item);

/**
 * Frees a bank in an array.
 * 
 * @param bank bank item to free.
 */
void free_bank_array_item(ArrayItem *bank);

#endif