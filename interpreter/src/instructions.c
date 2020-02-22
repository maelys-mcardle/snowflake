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

InstructionInfo get_instruction_info(short instruction, bool *exists)
{
    InstructionInfo info;

    switch (instruction) {
        case INSTRUCTION_COMMENT:
            info.mnemonic[0] = '!';
            info.mnemonic[1] = '!';
            info.mnemonic[2] = '!';
            info.parameters.first = PARAMETER_LITERAL | PARAMETER_OPTIONAL;
            info.parameters.second = PARAMETER_NONE;
            break;
        case INSTRUCTION_LABEL:
            info.mnemonic[0] = '#';
            info.mnemonic[1] = '#';
            info.mnemonic[2] = '#';
            info.parameters.first = PARAMETER_LABEL;
            info.parameters.second = PARAMETER_LITERAL | PARAMETER_OPTIONAL;
            break;
        case INSTRUCTION_NAME_BANK:
            info.mnemonic[0] = ' ';
            info.mnemonic[1] = ' ';
            info.mnemonic[2] = ' ';
            info.parameters.first = PARAMETER_BANK;
            info.parameters.second = PARAMETER_LITERAL;
            break;
        case INSTRUCTION_OUTPUT:
            info.mnemonic[0] = ' ';
            info.mnemonic[1] = '<';
            info.mnemonic[2] = '<';
            info.parameters.first = PARAMETER_DEVICE;
            info.parameters.second = PARAMETER_BANK;
            break;
        case INSTRUCTION_INPUT:
            info.mnemonic[0] = ' ';
            info.mnemonic[1] = '>';
            info.mnemonic[2] = '>';
            info.parameters.first = PARAMETER_DEVICE;
            info.parameters.second = PARAMETER_BANK;
            break;
        case INSTRUCTION_COPY:
            info.mnemonic[0] = 'D';
            info.mnemonic[1] = 'E';
            info.mnemonic[2] = 'L';
            info.parameters.first = PARAMETER_BANK;
            info.parameters.second = PARAMETER_NONE;
            break;
        case INSTRUCTION_TYPE:
            info.mnemonic[0] = 'T';
            info.mnemonic[1] = 'Y';
            info.mnemonic[2] = 'P';
            info.parameters.first = PARAMETER_BANK;
            info.parameters.second = PARAMETER_BANK;
            break;
        case INSTRUCTION_VARIABLE:
            info.mnemonic[0] = 'V';
            info.mnemonic[1] = 'A';
            info.mnemonic[2] = 'R';
            info.parameters.first = PARAMETER_BANK;
            info.parameters.second = PARAMETER_LITERAL;
            break;
        case INSTRUCTION_BOOLEAN:
            info.mnemonic[0] = 'B';
            info.mnemonic[1] = 'L';
            info.mnemonic[2] = 'N';
            info.parameters.first = PARAMETER_BANK;
            info.parameters.second = PARAMETER_LITERAL;
            break;
        case INSTRUCTION_INTEGER:
            info.mnemonic[0] = 'I';
            info.mnemonic[1] = 'N';
            info.mnemonic[2] = 'T';
            info.parameters.first = PARAMETER_BANK;
            info.parameters.second = PARAMETER_LITERAL;
            break;
        case INSTRUCTION_FLOAT:
            info.mnemonic[0] = 'F';
            info.mnemonic[1] = 'L';
            info.mnemonic[2] = 'T';
            info.parameters.first = PARAMETER_BANK;
            info.parameters.second = PARAMETER_LITERAL;
            break;
        case INSTRUCTION_STRING:
            info.mnemonic[0] = 'S';
            info.mnemonic[1] = 'T';
            info.mnemonic[2] = 'R';
            info.parameters.first = PARAMETER_BANK;
            info.parameters.second = PARAMETER_LITERAL;
            break;
        case INSTRUCTION_ARRAY:
            info.mnemonic[0] = ' ';
            info.mnemonic[1] = '[';
            info.mnemonic[2] = ']';
            info.parameters.first = PARAMETER_BANK;
            info.parameters.second = PARAMETER_NONE;
            break;
        case INSTRUCTION_JUMP_LABEL:
            info.mnemonic[0] = ' ';
            info.mnemonic[1] = '-';
            info.mnemonic[2] = '>';
            info.parameters.first = PARAMETER_LABEL;
            info.parameters.second = PARAMETER_NONE;
            break;
        case INSTRUCTION_JUMP_BANK:
            info.mnemonic[0] = ' ';
            info.mnemonic[1] = '-';
            info.mnemonic[2] = '>';
            info.parameters.first = PARAMETER_BANK;
            info.parameters.second = PARAMETER_NONE;
            break;
        case INSTRUCTION_IF_EQUAL:
            info.mnemonic[0] = 'I';
            info.mnemonic[1] = 'F';
            info.mnemonic[2] = '=';
            info.parameters.first = PARAMETER_BANK;
            info.parameters.second = PARAMETER_BANK;
            break;
        case INSTRUCTION_IF_NOT_EQUAL:
            info.mnemonic[0] = 'I';
            info.mnemonic[1] = 'F';
            info.mnemonic[2] = '!';
            info.parameters.first = PARAMETER_BANK;
            info.parameters.second = PARAMETER_BANK;
            break;
        case INSTRUCTION_IF_GREATER_THAN:
            info.mnemonic[0] = 'I';
            info.mnemonic[1] = 'F';
            info.mnemonic[2] = '>';
            info.parameters.first = PARAMETER_BANK;
            info.parameters.second = PARAMETER_BANK;
            break;
        case INSTRUCTION_IF_LESSER_THAN:
            info.mnemonic[0] = 'I';
            info.mnemonic[1] = 'F';
            info.mnemonic[2] = '<';
            info.parameters.first = PARAMETER_BANK;
            info.parameters.second = PARAMETER_BANK;
            break;
        case INSTRUCTION_ADD:
            info.mnemonic[0] = ' ';
            info.mnemonic[1] = ' ';
            info.mnemonic[2] = '+';
            info.parameters.first = PARAMETER_BANK;
            info.parameters.second = PARAMETER_BANK;
            break;
        case INSTRUCTION_SUBTRACT:
            info.mnemonic[0] = ' ';
            info.mnemonic[1] = ' ';
            info.mnemonic[2] = '-';
            info.parameters.first = PARAMETER_BANK;
            info.parameters.second = PARAMETER_BANK;
            break;
        case INSTRUCTION_MULTIPLY:
            info.mnemonic[0] = ' ';
            info.mnemonic[1] = ' ';
            info.mnemonic[2] = '*';
            info.parameters.first = PARAMETER_BANK;
            info.parameters.second = PARAMETER_BANK;
            break;
        case INSTRUCTION_DIVIDE:
            info.mnemonic[0] = ' ';
            info.mnemonic[1] = ' ';
            info.mnemonic[2] = '/';
            info.parameters.first = PARAMETER_BANK;
            info.parameters.second = PARAMETER_BANK;
            break;
        case INSTRUCTION_POWER:
            info.mnemonic[0] = ' ';
            info.mnemonic[1] = '*';
            info.mnemonic[2] = '*';
            info.parameters.first = PARAMETER_BANK;
            info.parameters.second = PARAMETER_BANK;
            break;
        case INSTRUCTION_NOT:
            info.mnemonic[0] = ' ';
            info.mnemonic[1] = ' ';
            info.mnemonic[2] = '!';
            info.parameters.first = PARAMETER_BANK;
            info.parameters.second = PARAMETER_NONE;
            break;
        case INSTRUCTION_AND:
            info.mnemonic[0] = ' ';
            info.mnemonic[1] = ' ';
            info.mnemonic[2] = '&';
            info.parameters.first = PARAMETER_BANK;
            info.parameters.second = PARAMETER_BANK;
            break;
        case INSTRUCTION_OR:
            info.mnemonic[0] = ' ';
            info.mnemonic[1] = ' ';
            info.mnemonic[2] = '|';
            info.parameters.first = PARAMETER_BANK;
            info.parameters.second = PARAMETER_BANK;
            break;
        case INSTRUCTION_XOR:
            info.mnemonic[0] = ' ';
            info.mnemonic[1] = ' ';
            info.mnemonic[2] = '^';
            info.parameters.first = PARAMETER_BANK;
            info.parameters.second = PARAMETER_BANK;
            break;
        case INSTRUCTION_ARRAY_SIZE:
            info.mnemonic[0] = '[';
            info.mnemonic[1] = '#';
            info.mnemonic[2] = ']';
            info.parameters.first = PARAMETER_BANK;
            info.parameters.second = PARAMETER_BANK;
            break;
        case INSTRUCTION_PREPEND_ARRAY:
            info.mnemonic[0] = '+';
            info.mnemonic[1] = '[';
            info.mnemonic[2] = ']';
            info.parameters.first = PARAMETER_BANK;
            info.parameters.second = PARAMETER_BANK;
            break;
        case INSTRUCTION_APPEND_ARRAY:
            info.mnemonic[0] = '[';
            info.mnemonic[1] = ']';
            info.mnemonic[2] = '+';
            info.parameters.first = PARAMETER_BANK;
            info.parameters.second = PARAMETER_BANK;
            break;
        case INSTRUCTION_GET_FIRST:
            info.mnemonic[0] = '?';
            info.mnemonic[1] = '[';
            info.mnemonic[2] = ']';
            info.parameters.first = PARAMETER_BANK;
            info.parameters.second = PARAMETER_BANK;
            break;
        case INSTRUCTION_GET_LAST:
            info.mnemonic[0] = '[';
            info.mnemonic[1] = ']';
            info.mnemonic[2] = '?';
            info.parameters.first = PARAMETER_BANK;
            info.parameters.second = PARAMETER_BANK;
            break;
        case INSTRUCTION_REMOVE_FIRST:
            info.mnemonic[0] = '-';
            info.mnemonic[1] = '[';
            info.mnemonic[2] = ']';
            info.parameters.first = PARAMETER_BANK;
            info.parameters.second = PARAMETER_BANK;
            break;
        case INSTRUCTION_REMOVE_LAST:
            info.mnemonic[0] = '[';
            info.mnemonic[1] = ']';
            info.mnemonic[2] = '-';
            info.parameters.first = PARAMETER_BANK;
            info.parameters.second = PARAMETER_BANK;
            break;
        case INSTRUCTION_MOVE_TO_INDEX:
            info.mnemonic[0] = '[';
            info.mnemonic[1] = '>';
            info.mnemonic[2] = ']';
            info.parameters.first = PARAMETER_BANK;
            info.parameters.second = PARAMETER_BANK;
            break;
        case INSTRUCTION_MOVE_TO_FIRST:
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

