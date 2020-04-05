#include <stdio.h>
#include <stdlib.h>
#include "platforms/input_devices.h"
#include "platforms/logging.h"
#include "core/string.h"

/**
 * Initialize the input devices before first-use.
 * 
 * @return whether the input devices were initialized.
 */
bool initialize_input_devices()
{
    return true;
}

/**
 * Get input from the standard input.
 * 
 * @param string the string that was retrieved.
 * @param string_size how many bytes were received.
 * @return whether data was received.
 */
bool receive_from_standard_input(char **string, int *string_size)
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

/**
 * Receive the button pressed.
 * 
 * @param button_code the unique ID of the button pressed.
 * @return whether the button was pressed.
 */
bool receive_from_button(int *button_code)
{
    log_debug("Waiting for button press...\n");
    *button_code = getchar();
    return true;
}

/**
 * Receive a random number.
 * 
 * @param random_number the random number.
 * @return whether a random number was received.
 */
bool receive_from_random(int *random_number)
{
    log_debug("Getting random value...\n");
    *random_number = rand();
    return true;
}