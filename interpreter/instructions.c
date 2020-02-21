#include <stdlib.h>
#include "headers/instructions.h"

Instruction *new_instruction()
{
  Instruction *instruction = (Instruction *) malloc(sizeof(Instruction));
  return instruction;
}

void free_instruction(Instruction *instruction)
{
  if (instruction != NULL)
  {
    //TODO: Free parameter.
    free(instruction);
  }
}

InstructionInfo get_instruction_info(int instruction, bool *exists)
{  
  InstructionInfo info;

  switch (instruction) {
    case 00:
      info.mnemonic[0] = '!';
      info.mnemonic[1] = '!';
      info.mnemonic[2] = '!';
      info.parameters.first = PARAMETER_LITERAL | PARAMETER_OPTIONAL;
      info.parameters.second = PARAMETER_NONE;
      break;
    case 01:
      info.mnemonic[0] = '#';
      info.mnemonic[1] = '#';
      info.mnemonic[2] = '#';
      info.parameters.first = PARAMETER_LABEL;
      info.parameters.second = PARAMETER_LITERAL | PARAMETER_OPTIONAL;
      break;
    case 02:
      info.mnemonic[0] = ' ';
      info.mnemonic[1] = ' ';
      info.mnemonic[2] = ' ';
      info.parameters.first = PARAMETER_BANK;
      info.parameters.second = PARAMETER_LITERAL;
      break;
    case 03:
      info.mnemonic[0] = ' ';
      info.mnemonic[1] = '<';
      info.mnemonic[2] = '<';
      info.parameters.first = PARAMETER_DEVICE;
      info.parameters.second = PARAMETER_BANK;
      break;
    case 04:
      info.mnemonic[0] = ' ';
      info.mnemonic[1] = '>';
      info.mnemonic[2] = '>';
      info.parameters.first = PARAMETER_DEVICE;
      info.parameters.second = PARAMETER_BANK;
      break;
    case 05:
      info.mnemonic[0] = 'D';
      info.mnemonic[1] = 'E';
      info.mnemonic[2] = 'L';
      info.parameters.first = PARAMETER_BANK;
      info.parameters.second = PARAMETER_NONE;
      break;
    case 06:
      info.mnemonic[0] = 'T';
      info.mnemonic[1] = 'Y';
      info.mnemonic[2] = 'P';
      info.parameters.first = PARAMETER_BANK;
      info.parameters.second = PARAMETER_BANK;
      break;
    case 10:
      info.mnemonic[0] = 'V';
      info.mnemonic[1] = 'A';
      info.mnemonic[2] = 'R';
      info.parameters.first = PARAMETER_BANK;
      info.parameters.second = PARAMETER_LITERAL;
      break;
    case 11:
      info.mnemonic[0] = 'B';
      info.mnemonic[1] = 'L';
      info.mnemonic[2] = 'N';
      info.parameters.first = PARAMETER_BANK;
      info.parameters.second = PARAMETER_LITERAL;
      break;
    case 12:
      info.mnemonic[0] = 'I';
      info.mnemonic[1] = 'N';
      info.mnemonic[2] = 'T';
      info.parameters.first = PARAMETER_BANK;
      info.parameters.second = PARAMETER_LITERAL;
      break;
    case 13:
      info.mnemonic[0] = 'F';
      info.mnemonic[1] = 'L';
      info.mnemonic[2] = 'T';
      info.parameters.first = PARAMETER_BANK;
      info.parameters.second = PARAMETER_LITERAL;
      break;
    case 14:
      info.mnemonic[0] = 'S';
      info.mnemonic[1] = 'T';
      info.mnemonic[2] = 'R';
      info.parameters.first = PARAMETER_BANK;
      info.parameters.second = PARAMETER_LITERAL;
      break;
    case 15:
      info.mnemonic[0] = ' ';
      info.mnemonic[1] = '[';
      info.mnemonic[2] = ']';
      info.parameters.first = PARAMETER_BANK;
      info.parameters.second = PARAMETER_NONE;
      break;
    case 20:
      info.mnemonic[0] = ' ';
      info.mnemonic[1] = '-';
      info.mnemonic[2] = '>';
      info.parameters.first = PARAMETER_LABEL;
      info.parameters.second = PARAMETER_NONE;
      break;
    case 21:
      info.mnemonic[0] = ' ';
      info.mnemonic[1] = '-';
      info.mnemonic[2] = '>';
      info.parameters.first = PARAMETER_BANK;
      info.parameters.second = PARAMETER_NONE;
      break;
    case 22:
      info.mnemonic[0] = 'I';
      info.mnemonic[1] = 'F';
      info.mnemonic[2] = '=';
      info.parameters.first = PARAMETER_BANK;
      info.parameters.second = PARAMETER_BANK;
      break;
    case 23:
      info.mnemonic[0] = 'I';
      info.mnemonic[1] = 'F';
      info.mnemonic[2] = '!';
      info.parameters.first = PARAMETER_BANK;
      info.parameters.second = PARAMETER_BANK;
      break;
    case 24:
      info.mnemonic[0] = 'I';
      info.mnemonic[1] = 'F';
      info.mnemonic[2] = '>';
      info.parameters.first = PARAMETER_BANK;
      info.parameters.second = PARAMETER_BANK;
      break;
    case 25:
      info.mnemonic[0] = 'I';
      info.mnemonic[1] = 'F';
      info.mnemonic[2] = '<';
      info.parameters.first = PARAMETER_BANK;
      info.parameters.second = PARAMETER_BANK;
      break;
    case 30:
      info.mnemonic[0] = ' ';
      info.mnemonic[1] = ' ';
      info.mnemonic[2] = '+';
      info.parameters.first = PARAMETER_BANK;
      info.parameters.second = PARAMETER_BANK;
      break;
    case 31:
      info.mnemonic[0] = ' ';
      info.mnemonic[1] = ' ';
      info.mnemonic[2] = '-';
      info.parameters.first = PARAMETER_BANK;
      info.parameters.second = PARAMETER_BANK;
      break;
    case 32:
      info.mnemonic[0] = ' ';
      info.mnemonic[1] = ' ';
      info.mnemonic[2] = '*';
      info.parameters.first = PARAMETER_BANK;
      info.parameters.second = PARAMETER_BANK;
      break;
    case 33:
      info.mnemonic[0] = ' ';
      info.mnemonic[1] = ' ';
      info.mnemonic[2] = '/';
      info.parameters.first = PARAMETER_BANK;
      info.parameters.second = PARAMETER_BANK;
      break;
    case 34:
      info.mnemonic[0] = ' ';
      info.mnemonic[1] = '*';
      info.mnemonic[2] = '*';
      info.parameters.first = PARAMETER_BANK;
      info.parameters.second = PARAMETER_BANK;
      break;
    case 40:
      info.mnemonic[0] = ' ';
      info.mnemonic[1] = ' ';
      info.mnemonic[2] = '!';
      info.parameters.first = PARAMETER_BANK;
      info.parameters.second = PARAMETER_NONE;
      break;
    case 41:
      info.mnemonic[0] = ' ';
      info.mnemonic[1] = ' ';
      info.mnemonic[2] = '&';
      info.parameters.first = PARAMETER_BANK;
      info.parameters.second = PARAMETER_BANK;
      break;
    case 42:
      info.mnemonic[0] = ' ';
      info.mnemonic[1] = ' ';
      info.mnemonic[2] = '|';
      info.parameters.first = PARAMETER_BANK;
      info.parameters.second = PARAMETER_BANK;
      break;
    case 43:
      info.mnemonic[0] = ' ';
      info.mnemonic[1] = ' ';
      info.mnemonic[2] = '^';
      info.parameters.first = PARAMETER_BANK;
      info.parameters.second = PARAMETER_BANK;
      break;
    case 50:
      info.mnemonic[0] = '[';
      info.mnemonic[1] = '#';
      info.mnemonic[2] = ']';
      info.parameters.first = PARAMETER_BANK;
      info.parameters.second = PARAMETER_BANK;
      break;
    case 51:
      info.mnemonic[0] = '+';
      info.mnemonic[1] = '[';
      info.mnemonic[2] = ']';
      info.parameters.first = PARAMETER_BANK;
      info.parameters.second = PARAMETER_BANK;
      break;
    case 52:
      info.mnemonic[0] = '[';
      info.mnemonic[1] = ']';
      info.mnemonic[2] = '+';
      info.parameters.first = PARAMETER_BANK;
      info.parameters.second = PARAMETER_BANK;
      break;
    case 53:
      info.mnemonic[0] = '?';
      info.mnemonic[1] = '[';
      info.mnemonic[2] = ']';
      info.parameters.first = PARAMETER_BANK;
      info.parameters.second = PARAMETER_BANK;
      break;
    case 54:
      info.mnemonic[0] = '[';
      info.mnemonic[1] = ']';
      info.mnemonic[2] = '?';
      info.parameters.first = PARAMETER_BANK;
      info.parameters.second = PARAMETER_BANK;
      break;
    case 55:
      info.mnemonic[0] = '-';
      info.mnemonic[1] = '[';
      info.mnemonic[2] = ']';
      info.parameters.first = PARAMETER_BANK;
      info.parameters.second = PARAMETER_BANK;
      break;
    case 56:
      info.mnemonic[0] = '[';
      info.mnemonic[1] = ']';
      info.mnemonic[2] = '-';
      info.parameters.first = PARAMETER_BANK;
      info.parameters.second = PARAMETER_BANK;
      break;
    case 57:
      info.mnemonic[0] = '[';
      info.mnemonic[1] = '>';
      info.mnemonic[2] = ']';
      info.parameters.first = PARAMETER_BANK;
      info.parameters.second = PARAMETER_BANK;
      break;
    case 58:
      info.mnemonic[0] = '[';
      info.mnemonic[1] = '<';
      info.mnemonic[2] = ']';
      info.parameters.first = PARAMETER_BANK;
      info.parameters.second = PARAMETER_BANK;
      break;
    default:
      // No instruction exists.
      *exists = false;
      return info;
  }
  
  // Instruction exists.
  *exists = true;
  return info;
}


/* Prints a line of Snowflake. */
void print_instruction(Instruction *instruction)
{
    // Print mnemonic.
    print("%c%c%c ",
        instruction->info.mnemonic[0],
        instruction->info.mnemonic[1],
        instruction->info.mnemonic[2]);

    // Print first parameter.
    bool has_parameter = print_parameter(
        instruction->info.parameters.first, 
        instruction->parameters.first);

    // Print the space that separates the parameter.
    if (has_parameter)
    {
        print(" ");
    }

    // Print second parameter.
    print_parameter(
        instruction->info.parameters.second, 
        instruction->parameters.second);

    // Print end of line.
    print("\n");
}

/* Prints a parameter, if one is defined.
 * @return True if a parameter is defined; false if not.
 */
bool print_parameter(ParameterType type, ParameterValue value)
{
    ParameterType type_without_flags = type & PARAMETER_WITHOUT_FLAGS;
    switch (type_without_flags)
    {
        case PARAMETER_NONE:
            return false;
        case PARAMETER_BANK:
            print("@%02i", value.integer);
            return true;
        case PARAMETER_LABEL:
            print(":%02i", value.integer);
            return true;
        case PARAMETER_DEVICE:
            return print_device(value.integer);
        case PARAMETER_LITERAL:
            print("%s", value.string);
            return true;
        default:
            return false;
    }
}

/* Prints a device, if one is defined.
 * @return True if a device is defined; false if not.
 */
bool print_device(int device)
{
    switch (device)
    {
        case 0:
            print("OUT");
            return true;
        case 1:
            print(" IN");
            return true;
        case 2:
            print("PRT");
            return true;
        case 3:
            print("BTN");
            return true;
        default:
            return false;
    }
}
