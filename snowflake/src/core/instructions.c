#include <stdlib.h>
#include "headers/instructions.h"
#include "headers/output.h"

Instruction *new_instruction()
{
    Instruction *instruction = (Instruction *) malloc(sizeof(Instruction));
    return instruction;
}

void free_instruction(Instruction *instruction)
{
    if (instruction != NULL)
    {
        free_parameter(
            instruction->info.parameters.first, 
            instruction->parameters.first);

        free_parameter(
            instruction->info.parameters.second, 
            instruction->parameters.second);

        free(instruction);
    }
}

void free_parameter(ParameterType type, ParameterValue value)
{
    ParameterType type_without_flags = type & PARAMETER_WITHOUT_FLAGS;
    if (type_without_flags == PARAMETER_LITERAL &&
        value.string != NULL)
    {
      free(value.string);
      value.string = NULL;
    }
}

ParameterType get_parameter_type(ParameterType type)
{
    return (type & PARAMETER_WITHOUT_FLAGS);
}

bool is_parameter_optional(ParameterType type)
{
    return ((type & PARAMETER_OPTIONAL) == PARAMETER_OPTIONAL);
}

bool is_parameter_none(ParameterType type)
{
    return (type == PARAMETER_NONE);
}

Device get_device_from_instruction(Instruction *instruction)
{
    Device device = instruction->parameters.first.integer;
    return device;
}

InstructionInfo get_instruction_info(InstructionCode instruction, bool *exists)
{
    InstructionInfo info;

    switch (instruction) {
        case INSTRUCTION_COMMENT:
            set_mnemonic(&info, "!!!");
            info.parameters.first = PARAMETER_LITERAL | PARAMETER_OPTIONAL;
            info.parameters.second = PARAMETER_NONE;
            break;
        case INSTRUCTION_LABEL:
            set_mnemonic(&info, "###");
            info.parameters.first = PARAMETER_LABEL;
            info.parameters.second = PARAMETER_LITERAL | PARAMETER_OPTIONAL;
            break;
        case INSTRUCTION_NAME_BANK:
            set_mnemonic(&info, "   ");
            info.parameters.first = PARAMETER_BANK;
            info.parameters.second = PARAMETER_LITERAL;
            break;
        case INSTRUCTION_OUTPUT:
            set_mnemonic(&info, " <<");
            info.parameters.first = PARAMETER_DEVICE;
            info.parameters.second = PARAMETER_BANK;
            break;
        case INSTRUCTION_INPUT:
            set_mnemonic(&info, " >>");
            info.parameters.first = PARAMETER_DEVICE;
            info.parameters.second = PARAMETER_BANK;
            break;
        case INSTRUCTION_COPY:
            set_mnemonic(&info, "  =");
            info.parameters.first = PARAMETER_BANK;
            info.parameters.second = PARAMETER_BANK;
            break;
        case INSTRUCTION_DELETE:
            set_mnemonic(&info, "DEL");
            info.parameters.first = PARAMETER_BANK;
            info.parameters.second = PARAMETER_NONE;
            break;
        case INSTRUCTION_TYPE:
            set_mnemonic(&info, "TYP");
            info.parameters.first = PARAMETER_BANK;
            info.parameters.second = PARAMETER_BANK;
            break;
        case INSTRUCTION_VARIABLE:
            set_mnemonic(&info, "VAR");
            info.parameters.first = PARAMETER_BANK;
            info.parameters.second = PARAMETER_LITERAL;
            break;
        case INSTRUCTION_BOOLEAN:
            set_mnemonic(&info, "BLN");
            info.parameters.first = PARAMETER_BANK;
            info.parameters.second = PARAMETER_LITERAL;
            break;
        case INSTRUCTION_INTEGER:
            set_mnemonic(&info, "INT");
            info.parameters.first = PARAMETER_BANK;
            info.parameters.second = PARAMETER_LITERAL;
            break;
        case INSTRUCTION_FLOAT:
            set_mnemonic(&info, "FLT");
            info.parameters.first = PARAMETER_BANK;
            info.parameters.second = PARAMETER_LITERAL;
            break;
        case INSTRUCTION_STRING:
            set_mnemonic(&info, "STR");
            info.parameters.first = PARAMETER_BANK;
            info.parameters.second = PARAMETER_LITERAL;
            break;
        case INSTRUCTION_ARRAY:
            set_mnemonic(&info, " []");
            info.parameters.first = PARAMETER_BANK;
            info.parameters.second = PARAMETER_NONE;
            break;
        case INSTRUCTION_JUMP_LABEL:
            set_mnemonic(&info, " ->");
            info.parameters.first = PARAMETER_LABEL;
            info.parameters.second = PARAMETER_NONE;
            break;
        case INSTRUCTION_JUMP_BANK:
            set_mnemonic(&info, " ->");
            info.parameters.first = PARAMETER_BANK;
            info.parameters.second = PARAMETER_NONE;
            break;
        case INSTRUCTION_IF_EQUAL:
            set_mnemonic(&info, "IF=");
            info.parameters.first = PARAMETER_BANK;
            info.parameters.second = PARAMETER_BANK;
            break;
        case INSTRUCTION_IF_NOT_EQUAL:
            set_mnemonic(&info, "IF!");
            info.parameters.first = PARAMETER_BANK;
            info.parameters.second = PARAMETER_BANK;
            break;
        case INSTRUCTION_IF_GREATER_THAN:
            set_mnemonic(&info, "IF>");
            info.parameters.first = PARAMETER_BANK;
            info.parameters.second = PARAMETER_BANK;
            break;
        case INSTRUCTION_IF_LESSER_THAN:
            set_mnemonic(&info, "IF<");
            info.parameters.first = PARAMETER_BANK;
            info.parameters.second = PARAMETER_BANK;
            break;
        case INSTRUCTION_ADD:
            set_mnemonic(&info, "  +");
            info.parameters.first = PARAMETER_BANK;
            info.parameters.second = PARAMETER_BANK;
            break;
        case INSTRUCTION_SUBTRACT:
            set_mnemonic(&info, "  -");
            info.parameters.first = PARAMETER_BANK;
            info.parameters.second = PARAMETER_BANK;
            break;
        case INSTRUCTION_MULTIPLY:
            set_mnemonic(&info, "  *");
            info.parameters.first = PARAMETER_BANK;
            info.parameters.second = PARAMETER_BANK;
            break;
        case INSTRUCTION_DIVIDE:
            set_mnemonic(&info, "  /");
            info.parameters.first = PARAMETER_BANK;
            info.parameters.second = PARAMETER_BANK;
            break;
        case INSTRUCTION_POWER:
            set_mnemonic(&info, " **");
            info.parameters.first = PARAMETER_BANK;
            info.parameters.second = PARAMETER_BANK;
            break;
        case INSTRUCTION_NOT:
            set_mnemonic(&info, "  !");
            info.parameters.first = PARAMETER_BANK;
            info.parameters.second = PARAMETER_NONE;
            break;
        case INSTRUCTION_AND:
            set_mnemonic(&info, "  &");
            info.parameters.first = PARAMETER_BANK;
            info.parameters.second = PARAMETER_BANK;
            break;
        case INSTRUCTION_OR:
            set_mnemonic(&info, "  |");
            info.parameters.first = PARAMETER_BANK;
            info.parameters.second = PARAMETER_BANK;
            break;
        case INSTRUCTION_XOR:
            set_mnemonic(&info, "  ^");
            info.parameters.first = PARAMETER_BANK;
            info.parameters.second = PARAMETER_BANK;
            break;
        case INSTRUCTION_ARRAY_SIZE:
            set_mnemonic(&info, "[#]");
            info.parameters.first = PARAMETER_BANK;
            info.parameters.second = PARAMETER_BANK;
            break;
        case INSTRUCTION_PREPEND_ARRAY:
            set_mnemonic(&info, " +[]");
            info.parameters.first = PARAMETER_BANK;
            info.parameters.second = PARAMETER_BANK;
            break;
        case INSTRUCTION_APPEND_ARRAY:
            set_mnemonic(&info, "[]+");
            info.parameters.first = PARAMETER_BANK;
            info.parameters.second = PARAMETER_BANK;
            break;
        case INSTRUCTION_GET_FIRST:
            set_mnemonic(&info, "?[]");
            info.parameters.first = PARAMETER_BANK;
            info.parameters.second = PARAMETER_BANK;
            break;
        case INSTRUCTION_GET_LAST:
            set_mnemonic(&info, "[]?");
            info.parameters.first = PARAMETER_BANK;
            info.parameters.second = PARAMETER_BANK;
            break;
        case INSTRUCTION_REMOVE_FIRST:
            set_mnemonic(&info, "-[]");
            info.parameters.first = PARAMETER_BANK;
            info.parameters.second = PARAMETER_BANK;
            break;
        case INSTRUCTION_REMOVE_LAST:
            set_mnemonic(&info, "[]-");
            info.parameters.first = PARAMETER_BANK;
            info.parameters.second = PARAMETER_BANK;
            break;
        case INSTRUCTION_MOVE_TO_INDEX:
            set_mnemonic(&info, "[>]");
            info.parameters.first = PARAMETER_BANK;
            info.parameters.second = PARAMETER_BANK;
            break;
        case INSTRUCTION_MOVE_TO_FIRST:
            set_mnemonic(&info, "[<]");
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

void set_mnemonic(InstructionInfo *info, char *mnemonic)
{
    info->mnemonic[0] = mnemonic[0];
    info->mnemonic[1] = mnemonic[1];
    info->mnemonic[2] = mnemonic[2];
}