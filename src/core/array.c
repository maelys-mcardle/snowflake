#include <stdlib.h>
#include "headers/array.h"
#include "headers/errors.h"
#include "headers/logging.h"

Array *new_array()
{
    log_debug("Creating new array.\n");
    Array *array = malloc(sizeof(Array));
    if (array != NULL)
    {
        array->count = 0;
        array->items = NULL;
        array->free_array_item_function = free_array_item;
        array->copy_array_item_function = copy_array_item;
    }
    else
    {
        log_error(ERROR_MESG_COULD_NOT_ALLOCATE_MEMORY);
    }
    return array;
}

void free_array(Array *array)
{
    log_debug("Free array.");
    if (array != NULL)
    {
        for (ArrayIndex index = 0; index < array->count; index++)
        {
            log_debug("Free array item %i of %i.\n", index, array->count);
            ArrayItem *item = array->items[index];
            array->free_array_item_function(item);
        }
        free(array);
    }
}

void free_array_item(ArrayItem *item)
{
    log_debug("Call to free item at %p.\n", item);
}

Array *copy_array(Array *source)
{
    Array *destination = new_array();
    if (destination != NULL)
    {
        destination->copy_array_item_function = source->copy_array_item_function;
        destination->free_array_item_function = source->free_array_item_function;
        copy_array_items(destination, source);
    }
    return destination;
}

bool resize_array(Array *array, ArrayCount new_count)
{
    ArrayItem **new_items = realloc(array->items, sizeof(ArrayItem *) * new_count);
    if (new_items != NULL)
    {
        array->items = new_items;
        array->count = new_count;
        return true;
    }
    else
    {
        log_error(ERROR_MESG_COULD_NOT_ALLOCATE_MEMORY);
        return false;
    }
}

bool copy_array_items(Array *destination, Array *source)
{
    if (source->count == 0)
    {
        return NULL;
    }

    bool ok = resize_array(destination, source->count);
    if (ok)
    {
        for (ArrayIndex index = 0; index < source->count; index++)
        {
            destination->items[index] = 
                source->copy_array_item_function(
                    source->items[index]);
        }
    }
    
    return ok;
}

ArrayItem *copy_array_item(ArrayItem *source_item)
{
    log_debug("Call to copy item at %p.\n", source_item);
    return source_item;
}

ArrayCount get_array_count(Array *array)
{
    return (array != NULL) ? array->count : 0;
}

bool insert_array_first(Array *array, ArrayItem *item)
{
    return insert_array_item(array, item, 0);
}

bool insert_array_last(Array *array, ArrayItem *item)
{
    return insert_array_item(array, item, array->count);
}

ArrayItem *remove_array_first(Array *array)
{
    return remove_array_item(array, 0);
}

ArrayItem *remove_array_last(Array *array)
{
    return remove_array_item(array, array->count);
}

/* Add an element to the index of an array. */
bool insert_array_item(Array *array, ArrayItem *item, ArrayIndex index_to_insert)
{
    // Resize the array to fit the new item.
    bool resize_ok = resize_array(array, array->count + 1);
    if (!resize_ok)
    {
        return false;
    }

    // Shift all the items by one above the index to insert.
    for (ArrayIndex index = index_to_insert + 1; index < array->count; index++)
    {
        array->items[index] = array->items[index - 1];
    }

    // Insert the item at the index. If it's at a value
    // that is bigger than the array, add it to the end.
    if (index_to_insert < array->count)
    {
        array->items[index_to_insert] = item;
    }
    else
    {
        array->items[array->count - 1] = item;
    }

    return true;
}

/* Remove element at the index of an array. */
ArrayItem *remove_array_item(Array *array, ArrayIndex index_to_remove)
{
    // Obtaining value that doesn't exist.
    if (index_to_remove >= array->count)
    {
        return NULL;
    }

    // Get the item.
    ArrayItem *item = array->items[index_to_remove];

    // Shift all the items by one above the index to insert.
    for (ArrayIndex index = index_to_remove; index < array->count - 1; index++)
    {
        array->items[index] = array->items[index + 1];
    }

    // Resize the array down.
    resize_array(array, array->count - 1);

    return item;
}

bool swap_index_items(Array *array, ArrayIndex first_index, ArrayIndex second_index)
{
    log_debug("Swapping index items %i and %i.\n", first_index, second_index);
    if (array != NULL)
    {
        if (first_index < array->count &&
            second_index < array->count)
        {
            ArrayItem *first_item = array->items[first_index];
            ArrayItem *second_item = array->items[second_index];
            array->items[first_index] = second_item;
            array->items[second_index] = first_item;
            return true;
        }
    }

    return false;
}
