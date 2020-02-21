#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include "headers/main.h"
#include "headers/errors.h"
#include "headers/parse_snowflake_file.h"
#include "headers/program.h"
#include "headers/output.h"

/* Starting point of the program. */
int main (int argc, char **argv) 
{
  // Check that the user supplied a file path
  // to open.
  if (argc < 2) {
    log_error(ERROR_MESG_NO_FILE_SPECIFIED);
    return ERROR_CODE_NO_FILE_SPECIFIED;
  }

  // Initialize the program.
  Program *program = new_program();
 
  // Load the snowflake code.
  int return_code = parse_snowflake_file(program, argv[1]);
  
  // Print out the code.
  print_snowflake_program(program);
  
  // Free the memory allocated to the program.
  free_program(program);

  // Exit with the return code supplied by processing
  // the snowflake file.
  return return_code;
}
