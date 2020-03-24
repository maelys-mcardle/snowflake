#ifndef SNOWFLAKE_ARRAY_H
#define SNOWFLAKE_ARRAY_H
#include <stdbool.h>

typedef unsigned int ArrayIndex;
typedef ArrayIndex ArrayCount;
typedef void ArrayItem;
typedef void (*FreeArrayItemFunction)(ArrayItem *array_item);
typedef ArrayItem *(*CopyArrayItemFunction)(ArrayItem *source_item);

typedef struct {
    ArrayCount count;
    ArrayItem **items;
    FreeArrayItemFunction free_array_item_function;
    CopyArrayItemFunction copy_array_item_function;
} Array;

Array *new_array();
void free_array(Array *array);
void free_array_item(ArrayItem *item);

bool resize_array(Array *array, ArrayCount new_count);
ArrayCount get_array_count(Array *array);

Array *copy_array(Array *source);
bool copy_array_items(Array *destination, Array *source);
ArrayItem *copy_array_item(ArrayItem *source_item);

bool prepend_array(Array *array, ArrayItem *item);
bool append_array(Array *array, ArrayItem *item);
bool insert_array_item(Array *array, ArrayItem *item, ArrayIndex index);

ArrayItem *get_array_first(Array *array);
ArrayItem *get_array_last(Array *array);
ArrayItem *get_array_item(Array *array, ArrayIndex index);
ArrayItem *remove_array_first(Array *array);
ArrayItem *remove_array_last(Array *array);
ArrayItem *remove_array_item(Array *array, ArrayIndex index);
bool shift_array_index(Array *array, ArrayIndex from_index, ArrayIndex to_index);

#endif
