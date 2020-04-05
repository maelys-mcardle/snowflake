#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <getopt.h>
#include "core/program.h"
#include "parse/parse_snowflake_file.h"
#include "platforms/logging.h"
#include "print/print_program.h"
#include "run/run_program.h"
#include "errors.h"
#include "main.h"

/**
 * Entry-point for CLI front-end to interpreter.
 * 
 * @param argc number of command-line arguments.
 * @param argv command-line arguments.
 * @return error code.
 */
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

/**
 * Parses the command-line arguments to the interpreter.
 * 
 * @param argc number of command-line arguments.
 * @param argv command-line arguments.
 * @param print_code whether the --print flag is set.
 * @param run_code whether the --run flag is set.
 * @param line_numbers whether the --lineno flag is set.
 * @param file_path path to the .sn file.
 * @return whether all arguments were parsed.
 */
bool parse_arguments(int argc, char **argv, bool *print_code, bool *run_code, bool *line_numbers, char **file_path)
{
    static struct option long_options[] =
    {
        {ARGUMENT_DEBUG_LONG,  no_argument, 0, ARGUMENT_DEBUG},
        {ARGUMENT_PRINT_LONG,  no_argument, 0, ARGUMENT_PRINT},
        {ARGUMENT_RUN_LONG,    no_argument, 0, ARGUMENT_RUN},
        {ARGUMENT_LINENO_LONG, no_argument, 0, ARGUMENT_LINENO},
        {0, 0, 0, 0}
    };

    // Parse the options.
    while (optind < argc)
    {
        int option_index = 0;

        int current_option = 
            getopt_long(argc, argv, "dprl", long_options, &option_index);

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

/**
 * Parses, prints, and runs the snowflake file.
 * 
 * @param print_code whether the --print flag is set.
 * @param run_code whether the --run flag is set.
 * @param line_numbers whether the --lineno flag is set.
 * @param snowflake_file path to the .sn file.
 * @return exit code.
 */
int parse_snowflake_file_and_run(bool print_code, bool run_code, bool line_numbers, char *snowflake_file)
{
    // Initialize the program.
    Program *program = new_program();
 
    // Load the snowflake code.
    int return_code = parse_snowflake_file(program, snowflake_file);
    
    // Print out the code.
    if (print_code)
    {
        print_program(program, line_numbers);
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

/**
 * Prints the snowflake program.
 * 
 * @param program the parsed snowflake program.
 * @param line_numbers whether the --lineno flag is set.
 */
void print_program(Program *program, bool show_line_number)
{
    char *program_string = get_printable_program(program, show_line_number);
    if (program_string != NULL)
    {
        printf("%s", program_string);
        free(program_string);
    }
}
