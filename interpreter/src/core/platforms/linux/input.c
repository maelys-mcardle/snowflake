#include <stdio.h>
#include <stdlib.h>
#include "../../headers/input.h"

bool get_button(int *string_size, char **string)
{
    int button = getchar();

    // If ASCII printable characters.
    if (button >= 32 && button <= 127) {
        *string_size = 2;
        *string = realloc(*string, *string_size);
        *string[0] = button & 0xff;
        *string[1] = '\0';
    }

    bool is_ok = true;
    return is_ok;
}

bool get_input(int *string_size, char **string)
{
    size_t max_input_length = MAX_INPUT_LENGTH;
    *string_size = getline(string, &max_input_length, stdin);
    bool is_ok = *string_size > -1 ? true : false;
    return is_ok;
}
