#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include "headers/main.h"
#include "headers/errors.h"
#include "headers/parse_snowflake_file.h"

/* Starting point of the program. */
int main (int argc, char **argv) 
{
  // Check that the user supplied a file path
  // to open.
  if (argc < 2) {
    printf(ERROR_MESG_NO_FILE_SPECIFIED);
    return ERROR_CODE_NO_FILE_SPECIFIED;
  }

  SnowflakeProgram program;

  // Initialize the program.
  initialize_program(&program);
  int return_code = process_snowflake_file(&program, argv[1]);
  free_program(&program);

  // Exit with the return code supplied by processing
  // the snowflake file.
  return return_code;
}

/* Initialize the Program. */
void initialize_program(SnowflakeProgram *program)
{
  program->labels.count = 0;
  program->banks.count = 0;
  program->instructions.count = 0;
}

/* Free the allocated data for the program. */
void free_program(SnowflakeProgram *program)
{
  return;
}
