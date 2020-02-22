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

typedef struct {
    short identifier;
    BankValue value;
} Bank;

#endif