#ifndef SNOWFLAKE_ARRAY_H
#define SNOWFLAKE_ARRAY_H
#include <stdbool.h>

typedef unsigned int ArrayCount;

typedef struct {
    ArrayCount count;
    void **items;
} Array;

#endif