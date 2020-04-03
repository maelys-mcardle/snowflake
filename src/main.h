#ifndef SNOWFLAKE_MAIN_H
#define SNOWFLAKE_MAIN_H

#define ARGUMENT_DEBUG_FULL "debug"
#define ARGUMENT_DEBUG 'd'
#define ARGUMENT_PRINT_FULL "print"
#define ARGUMENT_PRINT 'p'
#define ARGUMENT_RUN_FULL "run"
#define ARGUMENT_RUN 'r'
#define ARGUMENT_LINENO_FULL "lineno"
#define ARGUMENT_LINENO 'l'
#define ARGUMENT_UNKNOWN '?'

bool parse_arguments(int argc, char **argv, bool *print_code, bool *run_code, bool *line_numbers, char **file_path);
int parse_snowflake_file_and_run(bool print_code, bool run_code, bool line_numbers, char *snowflake_file);
void print_program(Program *program, bool show_line_number);

#endif
