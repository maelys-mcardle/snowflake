#ifndef SNOWFLAKE_ARRAY_H
#define SNOWFLAKE_ARRAY_H
#include <stdbool.h>

// Array structures and typedefs.
typedef unsigned int ArrayIndex;
typedef ArrayIndex ArrayCount;
typedef void ArrayItem;
typedef void (*FreeArrayItemFunction)(ArrayItem *array_item);
typedef ArrayItem *(*CopyArrayItemFunction)(ArrayItem *source_item);

/**
 * Struct that contains an array.
 */
typedef struct {
    ArrayCount count;
    ArrayItem **items;
    FreeArrayItemFunction free_array_item_function;
    CopyArrayItemFunction copy_array_item_function;
} Array;

/**
 * Creates a new array.
 * 
 * @return allocated array.
 */
Array *new_array();

/**
 * Frees an allocated array.
 * 
 * @param array array to free.
 */
void free_array(Array *array);

/**
 * Default implementation of the function to free an array item.
 * This is a no-op.
 * 
 * @param item array item to free.
 */
void free_array_item(ArrayItem *item);

/**
 * Resizes the array so it can fit the new size.
 * 
 * @param array array to resize.
 * @param new_count new size of array.
 * @return whether the operation was successful.
 */
bool resize_array(Array *array, ArrayCount new_count);

/**
 * Get the size of the array.
 * 
 * @param array array to get the size of.
 * @return size of the array.
 */
ArrayCount get_array_count(Array *array);

/**
 * Copies an array.
 * 
 * @param source original array to copy.
 * @return copy of array.
 */
Array *copy_array(Array *source);

/**
 * Copies all the items of one array into another.
 * 
 * @param destination where to copy the items to.
 * @param source where to copy the items from.
 * @return whether the operation was successful.
 */
bool copy_array_items(Array *destination, Array *source);

/**
 * Default implementation of the function to copy an array item.
 * This is a no-op.
 * 
 * @param item array item to copy.
 * @return copy of the array item.
 */
ArrayItem *copy_array_item(ArrayItem *source_item);

/**
 * Prepend an item to the array.
 * 
 * @param array array to modify.
 * @param item item to prepend.
 * @return whether the operation was successful.
 */
bool prepend_array(Array *array, ArrayItem *item);

/**
 * Append an item to the array.
 * 
 * @param array array to modify.
 * @param item item to append.
 * @return whether the operation was successful.
 */
bool append_array(Array *array, ArrayItem *item);

/**
 * Insert the specified item into an array.
 * 
 * @param array array to insert the item into.
 * @param item the item to insert in the array.
 * @param index_to_insert the index to insert the item at.
 * @return whether the operation was successful.
 */
bool insert_array_item(Array *array, ArrayItem *item, ArrayIndex index);

/**
 * Fetch the first item of an array.
 * 
 * @param array array to get the item from.
 * @return the first item of the array.
 */
ArrayItem *get_array_first(Array *array);

/**
 * Fetch the last item of an array.
 * 
 * @param array array to get the item from.
 * @return the last item of the array.
 */
ArrayItem *get_array_last(Array *array);

/**
 * Fetch the specified item of an array.
 * 
 * @param array array to get the item from.
 * @param index_to_get index of the item in the array.
 * @return the item from the array.
 */
ArrayItem *get_array_item(Array *array, ArrayIndex index);

/**
 * Removes the first item of an array.
 * 
 * @param array array to get the item from.
 * @return the first item of the array.
 */
ArrayItem *remove_array_first(Array *array);

/**
 * Removes the last item of an array.
 * 
 * @param array array to get the item from.
 * @return the last item of the array.
 */
ArrayItem *remove_array_last(Array *array);

/**
 * Remove the specified item of an array.
 * 
 * @param array array to remove the item from.=
 * @param index_to_remove the index to remove the item from.
 * @return the item that was removed.
 */
ArrayItem *remove_array_item(Array *array, ArrayIndex index);

#endif
