#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include "snowflake.h"
#define INSTRUCTION_LENGTH 256
#define MNEMONIC_LENGTH 3

/*
 * REPL LOGIC 
 */

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
  prog *program = NULL;
  inst *instruction = NULL;
  char stdin_string[INSTRUCTION_LENGTH];
  
  do 
  {
    printf("> ");
    
    if (gets_s(stdin_string, INSTRUCTION_LENGTH) != NULL) {
    
      inst *instruction = parse_instruction(stdin_string);

      append_instruction(program, instruction);

      show_instruction_plaintext(program, instruction);
    }
    
  } while (instruction != NULL);
  
  show_program_plaintext(program);
  
  execute_program(program);
    
  free_program(program);
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

/*
 * EXECUTE INSTRUCTIONS
 */

/*
 * CONVERT TO STRING
 */

bool label_to_string(char label, char *label_string)
{
  return true;
}

bool bank_to_string(char bank, char *bank_string)
{
  return true;
}

bool instruction_to_string(char instruction, char *instruction_string)
{  
  switch (instruction) {
    case 00:
      copy_mnemonic(instruction_string, "###");
      break;
    default:
      // No instruction exists.
      copy_mnemonic(instruction_string, "   ");
      return false;
  }
  
  // Instruction exists.
  return true;
}

void copy_mnemonic(char *output, char *input)
{
  strncpy(output, input, MNEMONIC_LENGTH);
}
