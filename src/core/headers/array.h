#ifndef SNOWFLAKE_ARRAY_H
#define SNOWFLAKE_ARRAY_H
#include <stdbool.h>

typedef unsigned int ArrayIndex;

typedef struct {
    ArrayIndex count;
    void **items;
} Array;

Array *new_array();
void free_array(Array *array);
ArrayIndex get_array_count(Array *array);
Array *copy_array(Array *source);

#endif