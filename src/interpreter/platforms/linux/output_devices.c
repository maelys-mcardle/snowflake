#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include "platforms/output_devices.h"

/**
 * Initialize the output devices before first-use.
 * 
 * @return whether the output devices were initialized.
 */
bool initialize_output_devices()
{
    // Seed the random number generator with the current time.
    srand(time(NULL));
    return true;
}

/**
 * Send a string to standard output.
 * 
 * @param string the string to send.
 * @return whether the operation was successful.
 */
bool send_to_standard_output(char *string)
{
    if (string != NULL)
    {
        printf("%s\n", string);
    }
    return true;
}

/**
 * Seed the pseudo-random number generator.
 * 
 * @param seed the seed to put in the PRNG.
 * @return whether the operation was successful.
 */
bool send_to_random(int seed)
{
    srand(seed);
    return true;
}