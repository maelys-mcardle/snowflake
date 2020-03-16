#include <stdlib.h>
#include "headers/array.h"
#include "headers/errors.h"
#include "headers/logging.h"

Array *new_array()
{
    Array *array = malloc(sizeof(Array));
    if (array != NULL)
    {
        array->count = 0;
        array->items = NULL;
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
        free(array);
    }
}

Array *copy_array(Array *source)
{
    Array *destination = new_array();
    if (destination != NULL)
    {
        destination->count = source->count;
        destination->items = source->items;
    }
    return destination;
}

ArrayIndex get_array_count(Array *array)
{
    return (array != NULL) ? array->count : 0;
}