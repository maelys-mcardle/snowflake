#ifndef SNOWFLAKE_BANK_H
#define SNOWFLAKE_BANK_H
#include <stdbool.h>


#define MAX_PARAMETER_SIZE   256

#define TYPE_VARIABLE_STRING "VAR"
#define TYPE_BOOLEAN_STRING  "BLN"
#define TYPE_INTEGER_STRING "INT"
#define TYPE_FLOAT_STRING "FLT"
#define TYPE_STRING_STRING "STR"
#define TYPE_ARRAY_STRING " []"

typedef short BankIdentifier;

typedef struct {
    int count;
    void **items;
} BankArray;

typedef union {
    int integer;
    float floating;
    bool boolean;
    char *string;
    BankArray array;
} BankValue;

typedef enum {
    TYPE_VARIABLE = 10,
    TYPE_BOOLEAN  = 11,
    TYPE_INTEGER  = 12,
    TYPE_FLOAT    = 13,
    TYPE_STRING   = 14,
    TYPE_ARRAY    = 15
} BankType;

typedef struct {
    BankIdentifier identifier;
    BankValue value;
    BankType type;
} Bank;

Bank *new_bank(BankIdentifier identifier);
void free_bank(Bank *bank);
void clear_bank_value(Bank *bank);
void free_array(Bank *bank);
void free_string(Bank *bank);
bool set_bank_boolean(Bank *bank, bool value);
bool set_bank_integer(Bank *bank, int value);
bool set_bank_float(Bank *bank, float value);
bool set_bank_string(Bank *bank, char *value);
bool set_bank_array(Bank *bank, BankArray *value);
bool get_bank_boolean(Bank *bank, bool *ok);
int get_bank_integer(Bank *bank, bool *ok);
float get_bank_float(Bank *bank, bool *ok);
char *get_bank_string(Bank *bank, bool *ok);
BankArray *get_bank_array(Bank *bank, bool *ok);
char *get_bank_as_string(Bank *bank);
bool copy_bank(Bank *destination, Bank *source);
bool convert_bank(Bank *bank, BankType to_type);

#endif