#ifndef SNOWFLAKE_ARRAY_H
#define SNOWFLAKE_ARRAY_H
#include <stdbool.h>

typedef unsigned int ArrayIndex;

typedef struct {
    ArrayIndex count;
    void **items;
} Array;

#endif