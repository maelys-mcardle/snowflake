#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include "snowflake.h"
#include "load_program.h"

/* Starting point of the program. */
int main (int argc, char **argv) 
{
  // Check that the user supplied a file path
  // to open.
  if (argc < 2) {
    printf(ERROR_MESG_NO_FILE_SPECIFIED);
    return ERROR_CODE_NO_FILE_SPECIFIED;
  }

  // Exit with the return code supplied by processing
  // the snowflake file.
  return process_snowflake_file(argv[1]);
}

/* Process a snowflake file. */
int process_snowflake_file(const char *filename)
{
  char line[MAX_LINE_LENGTH];
  SnowflakeProgram program;
  FILE* file = fopen(filename, "r");

  // Try to open the file.
  // Return on error.
  if (file == NULL) {
    printf(ERROR_MESG_COULD_NOT_OPEN_FILE);
    return ERROR_CODE_COULD_NOT_OPEN_FILE;
  }

  // Initialize the program.
  initialize_program(&program);

  // Parse the file line by line.
  while (fgets(line, MAX_LINE_LENGTH, file)) {
    load_line_into_program(&program, line, MAX_LINE_LENGTH);
  }

  // Free the program, close the file, and 
  // denote success.
  free_program(&program);
  fclose(file);
  return SUCCESS;
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
