#ifndef SNOWFLAKE_INPUT_DEVICES_H
#define SNOWFLAKE_INPUT_DEVICES_H

#include <stdbool.h>
#define MAX_INPUT_LENGTH 255

/**
 * Initialize the input devices before first-use.
 * 
 * @return whether the input devices were initialized.
 */
bool initialize_input_devices();

/**
 * Get input from the standard input.
 * 
 * @param string the string that was retrieved.
 * @param string_size how many bytes were received.
 * @return whether data was received.
 */
bool receive_from_standard_input(char **string, int *string_size);

/**
 * Receive the button pressed.
 * 
 * @param button_code the unique ID of the button pressed.
 * @return whether the button was pressed.
 */
bool receive_from_button(int *button_code);

/**
 * Receive a random number.
 * 
 * @param random_number the random number.
 * @return whether a random number was received.
 */
bool receive_from_random(int *random_number);

#endif
