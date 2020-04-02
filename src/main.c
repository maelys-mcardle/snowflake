#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <getopt.h>
#include "core/program.h"
#include "platforms/logging.h"
#include "parse_file.h"
#include "print_program.h"
#include "errors.h"
#include "run_program.h"
#include "main.h"

/* Starting point of the program. */
int main (int argc, char **argv) 
{
    bool no_unrecognized_arguments = false;
    bool print_code = false;
    bool run_code = false;
    bool line_numbers = false;
    char *file_path = NULL;

    // Parse command-line arguments.
    no_unrecognized_arguments = parse_arguments(argc, argv, 
        &print_code, &run_code, &line_numbers, &file_path);

    // Abort if there was an unrecognized argument.
    if (!no_unrecognized_arguments)
    {
        log_error(ERROR_MESG_UNRECOGNIZED_ARGUMENT);
        return ERROR_CODE_UNRECOGNIZED_ARGUMENT;
    }

    // Abort if no action was selected.
    if (!print_code && !run_code)
    {
        log_error(ERROR_MESG_NO_ACTION_SELECTED);
        return ERROR_CODE_NO_ACTION_SELECTED;
    }

    // Parse the snowflake file and do the action(s).
    return parse_snowflake_file_and_run(print_code, run_code, line_numbers, file_path);
}

int parse_snowflake_file_and_run(bool print_code, bool run_code, bool line_numbers, char *snowflake_file)
{
    // Initialize the program.
    Program *program = new_program();
 
    // Load the snowflake code.
    int return_code = parse_snowflake_file(program, snowflake_file);
    
    // Print out the code.
    if (print_code)
    {
        print_program(program, line_numbers ? WITH_LINE_NUMBER : WITHOUT_LINE_NUMBER);
    }

    // Execute the code.
    if (run_code)
    {
        run_program(program);
    }
    
    // Free the memory allocated to the program.
    free_program(program);

    // Exit with the return code supplied by processing
    // the snowflake file.
    return return_code;
}

void print_program(Program *program, LineNumbering line_numbering)
{
    char *program_string = get_printable_program(program, line_numbering);
    if (program_string != NULL)
    {
        printf("%s", program_string);
        free(program_string);
    }
}

bool parse_arguments(int argc, char **argv, bool *print_code, bool *run_code, bool *line_numbers, char **file_path)
{
    static struct option long_options[] =
    {
        {ARGUMENT_DEBUG_FULL, no_argument, 0, ARGUMENT_DEBUG},
        {ARGUMENT_PRINT_FULL, no_argument, 0, ARGUMENT_PRINT},
        {ARGUMENT_RUN_FULL, no_argument, 0, ARGUMENT_RUN},
        {ARGUMENT_LINENO_FULL, no_argument, 0, ARGUMENT_LINENO},
        {0, 0, 0, 0}
    };

    // Parse the options.
    while (optind < argc)
    {
        int option_index = 0;

        int current_option = 
            getopt_long (argc, argv, "f:dsr",
            long_options, &option_index);

        // End of options.
        if (current_option == -1)
        {
            break;
        }

        switch (current_option)
        {
            case ARGUMENT_DEBUG:
                enable_debug_mode();
                break;
            
            case ARGUMENT_PRINT:
                *print_code = true;
                break;
            
            case ARGUMENT_RUN:
                *run_code = true;
                break;

            case ARGUMENT_LINENO:
                *line_numbers = true;
                break;

            case ARGUMENT_UNKNOWN:
                // Unknown argument.
                return false;
        }        

    }

    // Positional argument is the file path.
    for (int index = optind; index < argc; index++)
    {
        *file_path = argv[index];
    }

    // No unknown argument.
    return true;
}
