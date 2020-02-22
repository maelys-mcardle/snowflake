#ifndef SNOWFLAKE_MAIN_H
#define SNOWFLAKE_MAIN_H

bool parse_arguments(int argc, char **argv, bool *print_code, bool *run_code, char **file_path);
int parse_snowflake_file_and_run(bool print_code, bool run_code, char *snowflake_file);

#endif
