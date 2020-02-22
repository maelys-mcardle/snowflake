#ifndef SNOWFLAKE_BANK_H
#define SNOWFLAKE_BANK_H
#include <stdbool.h>
#include "instructions.h"

typedef union {
    int integer;
    float floating;
    bool boolean;
    char *string;
    void *array;
} BankValue;

typedef enum {
    TYPE_VARIABLE=10,
    TYPE_BOOLEAN=11,
    TYPE_INTEGER=12,
    TYPE_FLOAT=13,
    TYPE_STRING=14,
    TYPE_ARRAY=15
} BankType;

typedef struct {
    short identifier;
    BankValue value;
    BankType type;
} Bank;

#endif