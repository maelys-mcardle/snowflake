#include <stdlib.h>
#include "headers/instructions.h"
#include "headers/output.h"
#include "headers/bank.h"

Instruction *new_instruction()
{
    Instruction *instruction = (Instruction *) malloc(sizeof(Instruction));
    return instruction;
}

void free_instruction(Instruction *instruction)
{
    if (instruction != NULL)
    {
        bool instruction_exists = false;
        InstructionInfo info = get_instruction_info(
            instruction->instruction, &instruction_exists);

        if (instruction_exists)
        {
            free_parameter(
                info.parameters.first, 
                instruction->parameters.first);

            free_parameter(
                info.parameters.second, 
                instruction->parameters.second);
        
            free(instruction);
        }
    }
}

void free_parameter(ParameterType type, ParameterValue value)
{
    if (is_parameter_literal(type) &&
        value.string != NULL)
    {
      free(value.string);
      value.string = NULL;
    }
}

bool is_parameter_literal(ParameterType type)
{
    return get_parameter_type_without_flags(type) == PARAMETER_LITERAL;
}

bool is_parameter_bank(ParameterType type)
{
    return get_parameter_type_without_flags(type) == PARAMETER_BANK;
}

bool is_parameter_label(ParameterType type)
{
    return get_parameter_type_without_flags(type) == PARAMETER_LABEL;
}

bool is_parameter_device(ParameterType type)
{
    return get_parameter_type_without_flags(type) == PARAMETER_DEVICE;
}

bool is_parameter_type(ParameterType type)
{
    return get_parameter_type_without_flags(type) == PARAMETER_TYPE;
}

ParameterType get_parameter_type_without_flags(ParameterType type)
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
        case INSTRUCTION_CONVERT:
            set_mnemonic(&info, " TO");
            info.parameters.first = PARAMETER_TYPE;
            info.parameters.second = PARAMETER_BANK;
            break;
        case INSTRUCTION_TYPE:
            set_mnemonic(&info, "TYP");
            info.parameters.first = PARAMETER_BANK;
            info.parameters.second = PARAMETER_BANK;
            break;
        case INSTRUCTION_DELETE:
            set_mnemonic(&info, "DEL");
            info.parameters.first = PARAMETER_BANK;
            info.parameters.second = PARAMETER_NONE;
            break;
        case INSTRUCTION_VARIABLE:
            set_mnemonic(&info, TYPE_VARIABLE_STRING);
            info.parameters.first = PARAMETER_BANK;
            info.parameters.second = PARAMETER_LITERAL;
            break;
        case INSTRUCTION_BOOLEAN:
            set_mnemonic(&info, TYPE_BOOLEAN_STRING);
            info.parameters.first = PARAMETER_BANK;
            info.parameters.second = PARAMETER_LITERAL;
            break;
        case INSTRUCTION_INTEGER:
            set_mnemonic(&info, TYPE_INTEGER_STRING);
            info.parameters.first = PARAMETER_BANK;
            info.parameters.second = PARAMETER_LITERAL;
            break;
        case INSTRUCTION_FLOAT:
            set_mnemonic(&info, TYPE_FLOAT_STRING);
            info.parameters.first = PARAMETER_BANK;
            info.parameters.second = PARAMETER_LITERAL;
            break;
        case INSTRUCTION_STRING:
            set_mnemonic(&info, TYPE_STRING_STRING);
            info.parameters.first = PARAMETER_BANK;
            info.parameters.second = PARAMETER_LITERAL;
            break;
        case INSTRUCTION_ARRAY:
            set_mnemonic(&info, TYPE_ARRAY_STRING);
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