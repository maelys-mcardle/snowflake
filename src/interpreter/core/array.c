#include <stdlib.h>
#include "platforms/logging.h"
#include "errors.h"
#include "core/array.h"

/**
 * Creates a new array.
 * 
 * @return allocated array.
 */
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

/**
 * Frees an allocated array.
 * 
 * @param array array to free.
 */
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

/**
 * Default implementation of the function to free an array item.
 * This is a no-op.
 * 
 * @param item array item to free.
 */
void free_array_item(ArrayItem *item)
{
    (void)(item);
}

/**
 * Copies an array.
 * 
 * @param source original array to copy.
 * @return copy of array.
 */
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

/**
 * Resizes the array so it can fit the new size.
 * 
 * @param array array to resize.
 * @param new_count new size of array.
 * @return whether the operation was successful.
 */
bool resize_array(Array *array, ArrayCount new_count)
{
    log_debug("Resizing array to %i items.\n", new_count);

    if (array == NULL)
    {
        log_error(ERROR_MESG_ARRAY_IS_NULL);
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

/**
 * Copies all the items of one array into another.
 * 
 * @param destination where to copy the items to.
 * @param source where to copy the items from.
 * @return whether the operation was successful.
 */
bool copy_array_items(Array *destination, Array *source)
{
    if (source == NULL || destination == NULL)
    {
        log_error(ERROR_MESG_ARRAY_IS_NULL);
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

/**
 * Default implementation of the function to copy an array item.
 * This is a no-op.
 * 
 * @param item array item to copy.
 * @return copy of the array item.
 */
ArrayItem *copy_array_item(ArrayItem *source_item)
{
    return source_item;
}

/**
 * Get the size of the array.
 * 
 * @param array array to get the size of.
 * @return size of the array.
 */
ArrayCount get_array_count(Array *array)
{
    return (array != NULL) ? array->count : 0;
}

/**
 * Prepend an item to the array.
 * 
 * @param array array to modify.
 * @param item item to prepend.
 * @return whether the operation was successful.
 */
bool prepend_array(Array *array, ArrayItem *item)
{
    log_debug("Inserting item at start of array.\n");
    return insert_array_item(array, item, 0);
}

/**
 * Append an item to the array.
 * 
 * @param array array to modify.
 * @param item item to append.
 * @return whether the operation was successful.
 */
bool append_array(Array *array, ArrayItem *item)
{
    log_debug("Inserting item at end of array.\n");
    return insert_array_item(array, item, array->count);
}

/**
 * Removes the first item of an array.
 * 
 * @param array array to get the item from.
 * @return the first item of the array.
 */
ArrayItem *remove_array_first(Array *array)
{
    log_debug("Removing item at start of array.\n");
    return remove_array_item(array, 0);
}

/**
 * Removes the last item of an array.
 * 
 * @param array array to get the item from.
 * @return the last item of the array.
 */
ArrayItem *remove_array_last(Array *array)
{
    log_debug("Removing item at end of array.\n");
    return remove_array_item(array, array->count - 1);
}

/**
 * Fetch the first item of an array.
 * 
 * @param array array to get the item from.
 * @return the first item of the array.
 */
ArrayItem *get_array_first(Array *array)
{
    log_debug("Get item at start of array.\n");
    return get_array_item(array, 0);
}

/**
 * Fetch the last item of an array.
 * 
 * @param array array to get the item from.
 * @return the last item of the array.
 */
ArrayItem *get_array_last(Array *array)
{
    log_debug("Get item at end of array.\n");
    return get_array_item(array, array->count - 1);
}

/**
 * Fetch the specified item of an array.
 * 
 * @param array array to get the item from.
 * @param index_to_get index of the item in the array.
 * @return the item from the array.
 */
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

/**
 * Insert the specified item into an array.
 * 
 * @param array array to insert the item into.
 * @param item the item to insert in the array.
 * @param index_to_insert the index to insert the item at.
 * @return whether the operation was successful.
 */
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

/**
 * Remove the specified item of an array.
 * 
 * @param array array to remove the item from.=
 * @param index_to_remove the index to remove the item from.
 * @return the item that was removed.
 */
ArrayItem *remove_array_item(Array *array, ArrayIndex index_to_remove)
{
    log_debug("Removing item at position %i of array.\n", index_to_remove);
    if (array == NULL)
    {
        log_error(ERROR_MESG_ARRAY_IS_NULL);
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
