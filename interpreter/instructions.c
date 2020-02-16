#include "headers/instructions.h"

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
      info.parameters.second = PARAMETER_LITERAL | PARAMETER_OPTIONAL;
      break;
    case 11:
      info.mnemonic[0] = 'B';
      info.mnemonic[1] = 'L';
      info.mnemonic[2] = 'N';
      info.parameters.first = PARAMETER_BANK;
      info.parameters.second = PARAMETER_LITERAL | PARAMETER_OPTIONAL;
      break;
    case 12:
      info.mnemonic[0] = 'I';
      info.mnemonic[1] = 'N';
      info.mnemonic[2] = 'T';
      info.parameters.first = PARAMETER_BANK;
      info.parameters.second = PARAMETER_LITERAL | PARAMETER_OPTIONAL;
      break;
    case 13:
      info.mnemonic[0] = 'F';
      info.mnemonic[1] = 'L';
      info.mnemonic[2] = 'T';
      info.parameters.first = PARAMETER_BANK;
      info.parameters.second = PARAMETER_LITERAL | PARAMETER_OPTIONAL;
      break;
    case 14:
      info.mnemonic[0] = 'S';
      info.mnemonic[1] = 'T';
      info.mnemonic[2] = 'R';
      info.parameters.first = PARAMETER_BANK;
      info.parameters.second = PARAMETER_LITERAL | PARAMETER_OPTIONAL;
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