#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include "snowflake.h"

/* Starting point of the program. */
int main (int argc, char **argv) 
{
  if (argc < 2) {
    printf(ERROR_MESG_NO_FILE_SPECIFIED);
    return ERROR_CODE_NO_FILE_SPECIFIED;
  }

  return process_snowflake_file(argv[1]);
}

/* Process a snowflake file. */
int process_snowflake_file(const char *filename)
{
  char line[MAX_LINE_LENGTH];
  FILE* file = fopen(filename, "r");

  if (file == NULL) {
    printf(ERROR_MESG_COULD_NOT_OPEN_FILE);
    return ERROR_CODE_COULD_NOT_OPEN_FILE;
  }

  while (fgets(line, MAX_LINE_LENGTH, file)) {
    printf("%s", line); 
  }

  fclose(file);
  return SUCCESS;
}

/* The main REPL loop. */
/*
void run_interpreter_loop()
{
  prog *program = NULL;
  inst *instruction = NULL;
  char stdin_string[INSTRUCTION_LENGTH];
  
  do 
  { 
    if (gets_s(stdin_string, INSTRUCTION_LENGTH) != NULL) {
    
      inst *instruction = parse_instruction(stdin_string);

      append_instruction(program, instruction);

      show_instruction_plaintext(program, instruction);
    }
    
  } while (instruction != NULL);
  
  show_program_plaintext(program);
  
  execute_program(program);
    
  free_program(program);
}*/
