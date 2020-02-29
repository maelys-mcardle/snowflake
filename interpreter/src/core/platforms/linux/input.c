#include <stdio.h>
#include <stdlib.h>
#include "../../headers/input.h"

bool get_button(int *button_code)
{
    *button_code = getchar();
    return true;
}

bool get_input(int *string_size, char **string)
{
    size_t max_input_length = MAX_INPUT_LENGTH;
    *string_size = getline(string, &max_input_length, stdin);
    bool is_ok = *string_size > -1 ? true : false;
    return is_ok;
}
