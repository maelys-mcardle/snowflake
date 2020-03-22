#include <stdio.h>
#include <stdlib.h>
#include "platforms/input_devices.h"
#include "platforms/logging.h"
#include "structures/string.h"

bool initialize_input()
{
    return true;
}

bool receive_from_standard_input(int *string_size, char **string)
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

bool receive_from_button(int *button_code)
{
    log_debug("Waiting for button press...\n");
    *button_code = getchar();
    return true;
}

bool receive_from_random(int *random_number)
{
    log_debug("Getting random value...\n");
    *random_number = rand();
    return true;
}