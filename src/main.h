#ifndef SNOWFLAKE_MAIN_H
#define SNOWFLAKE_MAIN_H

// Arguments that can be passed to the command-line application.
#define ARGUMENT_DEBUG_LONG "debug"
#define ARGUMENT_DEBUG 'd'
#define ARGUMENT_PRINT_LONG "print"
#define ARGUMENT_PRINT 'p'
#define ARGUMENT_RUN_LONG "run"
#define ARGUMENT_RUN 'r'
#define ARGUMENT_LINENO_LONG "lineno"
#define ARGUMENT_LINENO 'l'
#define ARGUMENT_UNKNOWN '?'

/**
 * Entry-point for CLI front-end to interpreter.
 * 
 * @param argc number of command-line arguments.
 * @param argv command-line arguments.
 * @return error code.
 */
int main (int argc, char **argv);

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
bool parse_arguments(int argc, char **argv, bool *print_code, bool *run_code, bool *line_numbers, char **file_path);

/**
 * Parses, prints, and runs the snowflake file.
 * 
 * @param print_code whether the --print flag is set.
 * @param run_code whether the --run flag is set.
 * @param line_numbers whether the --lineno flag is set.
 * @param snowflake_file path to the .sn file.
 * @return exit code.
 */
int parse_snowflake_file_and_run(bool print_code, bool run_code, bool line_numbers, char *snowflake_file);

/**
 * Prints the snowflake program.
 * 
 * @param program the parsed snowflake program.
 * @param line_numbers whether the --lineno flag is set.
 */
void print_program(Program *program, bool show_line_number);

#endif
