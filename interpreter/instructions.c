#include "instructions.h"


InstructionInfo get_instruction_info(char instruction)
{  
  switch (instruction) {
    case 00:
        return {
            "###",
            INSTRUCTION_TYPE_LABEL,
            INSTRUCTION_TYPE_NONE
        };
    case 01:
      copy_mnemonic(instruction_string, "   ");
      break;
    case 02:
      copy_mnemonic(instruction_string, " <<");
      break;
    case 03:
      copy_mnemonic(instruction_string, " >>");
      break;
    case 04:
      copy_mnemonic(instruction_string, "  =");
      break;
    case 05:
      copy_mnemonic(instruction_string, "DEL");
      break;
    case 06:
      copy_mnemonic(instruction_string, "TYP");
      break;
    case 10:
      copy_mnemonic(instruction_string, "VAR");
      break;
    case 11:
      copy_mnemonic(instruction_string, "BLN");
      break;
    case 12:
      copy_mnemonic(instruction_string, "INT");
      break;
    case 13:
      copy_mnemonic(instruction_string, "FLT");
      break;
    case 14:
      copy_mnemonic(instruction_string, "STR");
      break;
    case 15:
      copy_mnemonic(instruction_string, " []");
      break;
    case 20:
    case 21:
      copy_mnemonic(instruction_string, " ->");
      break;
    case 22:
      copy_mnemonic(instruction_string, "IF=");
      break;
    case 23:
      copy_mnemonic(instruction_string, "IF!");
      break;
    case 23:
      copy_mnemonic(instruction_string, "IF>");
      break;
    case 24:
      copy_mnemonic(instruction_string, "IF<");
      break;
    case 30:
      copy_mnemonic(instruction_string, "  +");
      break;
    case 31:
      copy_mnemonic(instruction_string, "  -");
      break;
    case 32:
      copy_mnemonic(instruction_string, "  *");
      break;
    case 33:
      copy_mnemonic(instruction_string, "  /");
      break;
    case 34:
      copy_mnemonic(instruction_string, " **");
      break;
    case 40:
      copy_mnemonic(instruction_string, "  !");
      break;
    case 41:
      copy_mnemonic(instruction_string, "  &");
      break;
    case 42:
      copy_mnemonic(instruction_string, "  |");
      break;
    case 43:
      copy_mnemonic(instruction_string, "  ^");
      break;
    case 50:
      copy_mnemonic(instruction_string, "+[]");
      break;
    case 51:
      copy_mnemonic(instruction_string, "[]+");
      break;
    case 52:
      copy_mnemonic(instruction_string, "?[]");
      break;
    case 53:
      copy_mnemonic(instruction_string, "[]?");
      break;
    case 54:
      copy_mnemonic(instruction_string, "-[]");
      break;
    case 55:
      copy_mnemonic(instruction_string, "[]-");
      break;
    case 56:
      copy_mnemonic(instruction_string, "[>]");
      break;
    case 57:
      copy_mnemonic(instruction_string, "[<]");
      break;
    case 58:
      copy_mnemonic(instruction_string, "[#]");
      break;
    default:
      // No instruction exists.
      return false;
  }
  
  // Instruction exists.
  return true;
}