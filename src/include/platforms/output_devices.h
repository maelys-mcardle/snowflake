#ifndef SNOWFLAKE_OUTPUT_DEVICES_H
#define SNOWFLAKE_OUTPUT_DEVICES_H

#include <stdio.h>
#include <stdarg.h>
#include <stdbool.h>

/**
 * Initialize the output devices before first-use.
 * 
 * @return whether the output devices were initialized.
 */
bool initialize_output_devices();

/**
 * Send a string to standard output.
 * 
 * @param string the string to send.
 * @return whether the operation was successful.
 */
bool send_to_standard_output(char *string);

/**
 * Seed the pseudo-random number generator.
 * 
 * @param seed the seed to put in the PRNG.
 * @return whether the operation was successful.
 */
bool send_to_random(int seed);

#endif
