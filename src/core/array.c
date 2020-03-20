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
            array->free_array_item_function(array->items[index]);
        }
        free(array);
    }
}

void free_array_item(ArrayItem item)
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
        destination->items = copy_array_items(source);
        destination->count = (destination->items == NULL) ? 0 : source->count;
    }
    return destination;
}

ArrayItem *copy_array_items(Array *source)
{
    if (source->count == 0)
    {
        return NULL;
    }

    ArrayItem *items = malloc(sizeof(ArrayItem) * source->count);
    if (items != NULL)
    {
        for (ArrayIndex index = 0; index < source->count; index++)
        {
            items[index] = 
                source->copy_array_item_function(
                    source->items[index]);
        }
    }
    else
    {
        log_error(ERROR_MESG_COULD_NOT_ALLOCATE_MEMORY);
    }
    
    return items;
}

ArrayItem copy_array_item(ArrayItem source_item)
{
    log_debug("Call to copy item at %p.\n", source_item);
    return source_item;
}

ArrayCount get_array_count(Array *array)
{
    return (array != NULL) ? array->count : 0;
}

bool push(Array *array, ArrayItem *item)
{
    // Unused parameters. This is done to suppress compiler warnings.
    (void)(array);
    (void)(item);

    return true;
}

bool pop(Array *array, ArrayItem *item)
{
    // Unused parameters. This is done to suppress compiler warnings.
    (void)(array);
    (void)(item);

    return true;
}

bool unshift(Array *array, ArrayItem *item)
{
    // Unused parameters. This is done to suppress compiler warnings.
    (void)(array);
    (void)(item);

    return true;
}

bool shift(Array *array, ArrayItem *item)
{
    // Unused parameters. This is done to suppress compiler warnings.
    (void)(array);
    (void)(item);

    return true;
}

bool swap_index_items(Array *array, ArrayIndex first_index, ArrayIndex second_index)
{
    // Unused parameters. This is done to suppress compiler warnings.
    (void)(array);
    (void)(first_index);
    (void)(second_index);

    return true;
}
