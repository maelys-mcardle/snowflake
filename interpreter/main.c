#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <getopt.h>
#include "headers/main.h"
#include "headers/errors.h"
#include "headers/parse_snowflake_file.h"
#include "headers/program.h"
#include "headers/output.h"
#include "headers/print_program.h"
#include "headers/run_program.h"

/* Starting point of the program. */
int main (int argc, char **argv) 
{
  bool no_unrecognized_arguments = false;
  bool print_code = false;
  bool run_code = false;
  char *file_path = NULL;

  // Parse command-line arguments.
  no_unrecognized_arguments = parse_arguments(argc, argv, &print_code, &run_code, &file_path);

  // Abort if there was an unrecognized argument.
  if (!no_unrecognized_arguments)
  {
    log_error(ERROR_MESG_UNRECOGNIZED_ARGUMENT);
    return ERROR_CODE_UNRECOGNIZED_ARGUMENT;
  }

  if (!print_code && !run_code)
  {
    log_error(ERROR_MESG_NO_ACTION_SELECTED);
    return ERROR_CODE_NO_ACTION_SELECTED;
  }

  // Initialize the program.
  Program *program = new_program();
 
  // Load the snowflake code.
  int return_code = parse_snowflake_file(program, file_path);
  
  // Print out the code.
  if (print_code)
  {
    print_program(program);
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

bool parse_arguments(int argc, char **argv, bool *print_code, bool *run_code, char **file_path)
{
  int current_option;
  static struct option long_options[] =
  {
    {"file", required_argument, 0, 'f'},
    {"debug", no_argument, 0, 'd'},
    {"show-code", no_argument, 0, 's'},
    {"run", no_argument, 0, 'r'},
    {0, 0, 0, 0}
  };

  while (1)
    {
      int option_index = 0;

      current_option = getopt_long (argc, argv, "f:dsr",
                       long_options, &option_index);

      // End of options.
      if (current_option == -1)
        break;

      switch (current_option)
      {
        case 'd':
          enable_debug_mode();
          break;
        
        case 's':
          *print_code = true;
          break;
        
        case 'f':
          *file_path = optarg;
          break;

        case 'r':
          *run_code = true;
          break;

        case '?':
          return false;
      }    

    }

    return true;
}
