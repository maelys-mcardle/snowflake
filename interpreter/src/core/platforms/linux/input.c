#include <stdio.h>
#include <stdlib.h>
#include "../../headers/input.h"
#include "../../headers/output.h"
#include "../../headers/string.h"

bool get_button(int *button_code)
{
    log_debug("Waiting for button press...\n");
    *button_code = getchar();
    return true;
}

bool get_input(int *string_size, char **string)
{
    log_debug("Waiting for input...\n");
    size_t max_input_length = MAX_INPUT_LENGTH;
    *string_size = getline(string, &max_input_length, stdin);
    bool is_ok = *string_size > -1 ? true : false;

    if (is_ok)
    {
        strip_end_whitespace(*string, *string_size);
    }

    return is_ok;
}
