#include <stdio.h>
#include <stdlib.h>
#include "headers/parse_snowflake_file.h"
#include "headers/parse_snowflake_line.h"
#include "headers/errors.h"
#include "headers/output.h"

/* Process a snowflake file. */
int parse_snowflake_file(Program *program, const char *filename)
{
    int max_line_length = MAX_LINE_LENGTH;
    char line[max_line_length];
    FILE* file = fopen(filename, "r");

    // Try to open the file.
    // Return on error.
    if (file == NULL) {
        log_error(ERROR_MESG_COULD_NOT_OPEN_FILE, filename);
        return ERROR_CODE_COULD_NOT_OPEN_FILE;
    }

    // Parse the file line by line.
    int line_number = 1;
    int instructions_parsed = 0;
    while (fgets(line, max_line_length, file)) {
        log_debug("[Line %02i] %s\n", line_number, line);
        bool has_instruction = parse_line(program, line, max_line_length);
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
