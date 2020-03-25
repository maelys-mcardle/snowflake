#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include "platforms/output_devices.h"

bool initialize_output_devices()
{
    // Seed the random number generator.
    srand(time(NULL));
    return true;
}

bool send_to_standard_output(char *string)
{
    if (string != NULL)
    {
        printf("%s\n", string);
    }
    return true;
}

bool send_to_random(int seed)
{
    srand(seed);
    return true;
}