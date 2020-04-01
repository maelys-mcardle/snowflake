#include <stdlib.h>
#include "parse_file.h"
#include "parse_instruction.h"
#include "errors.h"
#include "platforms/logging.h"
#include "core/string.h"

/* Process a snowflake file. */
int parse_snowflake_file(Program *program, const char *filename)
{
    // Check that a file name was given.
    if (filename == NULL)
    {
        log_error(ERROR_MESG_NO_FILE_SPECIFIED, filename);
        return ERROR_CODE_NO_FILE_SPECIFIED;
    }

    // Open the file.
    int max_line_length = MAX_LINE_LENGTH;
    char line[max_line_length];
    FILE* file = fopen(filename, "r");

    // Return on error.
    if (file == NULL)
    {
        log_error(ERROR_MESG_COULD_NOT_OPEN_FILE, filename);
        return ERROR_CODE_COULD_NOT_OPEN_FILE;
    }

    // Log.
    log_debug("Reading Snowflake file...\n");

    // Parse the file line by line.
    int line_number = 1;
    int instructions_parsed = 0;
    while (fgets(line, max_line_length, file)) {
        
        // Log the line.
        strip_end_whitespace(line, max_line_length);
        log_debug("[Line %02i] %s\n", line_number, line);

        // Parse the line.
        bool has_instruction = parse_instruction(program, line, max_line_length);
        if (has_instruction) {
            instructions_parsed++;
        }
        line_number++;
    }
    
    // Close the file.
    fclose(file);
    
    // File had no instructions!
    if (instructions_parsed == 0)
    {
        log_error(ERROR_MESG_FILE_HAD_NO_CODE, filename);
        return ERROR_CODE_FILE_HAD_NO_CODE;
    }

    // Denote the success.
    return SUCCESS;
}
