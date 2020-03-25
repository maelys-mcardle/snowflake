#include <stdlib.h>
#include "structures/array.h"
#include "errors.h"
#include "platforms/logging.h"

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
    if (array != NULL)
    {
        log_debug("Free array of %i items.\n", array->count);
        for (ArrayIndex index = 0; index < array->count; index++)
        {
            log_debug("Free item %i of %i.\n", index + 1, array->count);
            ArrayItem *item = array->items[index];
            array->free_array_item_function(item);
        }
        free(array);
    }
}

void free_array_item(ArrayItem *item)
{
    (void)(item);
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
    log_debug("Resizing array to %i items.\n", new_count);

    if (array == NULL)
    {
        log_debug("Array is NULL, aborting.\n");
        return false;
    }

    if (new_count > 0)
    {
        // New count 
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
    else
    {
        if (array->items != NULL)
        {
            free(array->items);
        }
        array->items = NULL;
        array->count = 0;
        return true;
    }
}

bool copy_array_items(Array *destination, Array *source)
{
    if (source == NULL || destination == NULL)
    {
        log_debug("Array is NULL, aborting.\n");
        return false;
    }
    
    if (source->count == 0)
    {
        destination->count = 0;
        destination->items = NULL;
        return true;
    }

    bool ok = resize_array(destination, source->count);
    if (ok)
    {
        for (ArrayIndex index = 0; index < source->count; index++)
        {    
            log_debug("Copy array item %i of %i.\n", index + 1, source->count);
            destination->items[index] = 
                source->copy_array_item_function(
                    source->items[index]);
        }
    }
    
    return ok;
}

ArrayItem *copy_array_item(ArrayItem *source_item)
{
    return source_item;
}

ArrayCount get_array_count(Array *array)
{
    return (array != NULL) ? array->count : 0;
}

bool prepend_array(Array *array, ArrayItem *item)
{
    log_debug("Inserting item at start of array.\n");
    return insert_array_item(array, item, 0);
}

bool append_array(Array *array, ArrayItem *item)
{
    log_debug("Inserting item at end of array.\n");
    return insert_array_item(array, item, array->count);
}

ArrayItem *remove_array_first(Array *array)
{
    log_debug("Removing item at start of array.\n");
    return remove_array_item(array, 0);
}

ArrayItem *remove_array_last(Array *array)
{
    log_debug("Removing item at end of array.\n");
    return remove_array_item(array, array->count - 1);
}

ArrayItem *get_array_first(Array *array)
{
    log_debug("Get item at start of array.\n");
    return get_array_item(array, 0);
}

ArrayItem *get_array_last(Array *array)
{
    log_debug("Get item at end of array.\n");
    return get_array_item(array, array->count - 1);
}

ArrayItem *get_array_item(Array *array, ArrayIndex index_to_get)
{
    if (index_to_get < array->count)
    {
        return array->items[index_to_get];
    }
    else
    {
        return NULL;
    }
}

/* Add an element to the index of an array. */
bool insert_array_item(Array *array, ArrayItem *item, ArrayIndex index_to_insert)
{
    log_debug("Inserting item at position %i of array.\n", index_to_insert);
    if (array == NULL)
    {
        return false;
    }

    // Resize the array to fit the new item.
    bool resize_ok = resize_array(array, array->count + 1);
    if (!resize_ok)
    {
        return false;
    }

    // Shift all the items by one above the index to insert.
    for (ArrayIndex index = array->count - 1; index > index_to_insert; index--)
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
    log_debug("Removing item at position %i of array.\n", index_to_remove);
    if (array == NULL)
    {
        log_debug("Array is NULL.\n");
        return NULL;
    }

    // Obtaining value that doesn't exist.
    if (index_to_remove >= array->count)
    {
        log_debug("Removing value that doesn't exist.\n");
        return NULL;
    }

    // Get the item.
    ArrayItem *item = array->items[index_to_remove];

    // Shift all the items by one above the index to remove.
    for (ArrayIndex index = index_to_remove; index < array->count - 1; index++)
    {
        array->items[index] = array->items[index + 1];
    }

    // Resize the array down.
    resize_array(array, array->count - 1);

    return item;
}
