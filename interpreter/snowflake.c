#include <stdio.h>
#include <string.h>
#include "snowflake.h"

/* Starting point of the program. */
int main () 
{
  // Header.
  printf("SNOWFLAKE INTERPRETER\n"
        "======================\n");

  // Run the interpeter loop.
  run_interpreter_loop();

  // Exit without error.
  return(0);
}

/* The main REPL loop. */
void run_interpreter_loop()
{
  printf("> ");
  char instruction = get_instruction();
}

/* Returns the instruction code. */
char get_instruction()
{
  // When reading instruction:
  //  * Everything before the subsequent space or newline is part of the instruction
  //  * Instructions are made up of one or two digits
  char instruction[2];
  char input_character;
  instruction[0] = getchar();
  instruction[1] = getchar();
}

void instruction_mnemonic(char instruction, char *mnemonic)
{  
  switch (instruction) {
    case 00:
      copy_mnemonic(mnemonic, "###");
      break;
    default:
      copy_mnemonic(mnemonic, "   ");
      break;
  }
}

void copy_mnemonic(char *output, char *input)
{
  int mnemonic_length = 3;
  strncpy(output, input, mnemonic_length);
}
