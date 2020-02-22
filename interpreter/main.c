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

/* Starting point of the program. */
int main (int argc, char **argv) 
{
  // Load arguments.
  bool print_code = false;
  char *file_path = NULL;
  parse_arguments(argc, argv, &print_code, &file_path);

  // Initialize the program.
  Program *program = new_program();
 
  // Load the snowflake code.
  int return_code = parse_snowflake_file(program, file_path);
  
  // Print out the code.
  if (print_code)
  {
    print_program(program);
  }
  
  // Free the memory allocated to the program.
  free_program(program);

  // Exit with the return code supplied by processing
  // the snowflake file.
  return return_code;
}

void parse_arguments(int argc, char **argv, bool *print_code, char **file_path)
{
  int current_option;
  static struct option long_options[] =
  {
    {"file", required_argument, 0, 'f'},
    {"debug", no_argument, 0, 'd'},
    {"print-code", no_argument, 0, 'p'},
    {0, 0, 0, 0}
  };

  while (1)
    {
      int option_index = 0;

      current_option = getopt_long (argc, argv, "abc:d:f:",
                       long_options, &option_index);

      // End of options.
      if (current_option == -1)
        break;

      switch (current_option)
      {
        case 'd':
          enable_debug_mode();
          break;
        
        case 'p':
          *print_code = true;
          break;
        
        case 'f':
          *file_path = optarg;
          break;

        case '?':
          break;
      }    

    }
}
