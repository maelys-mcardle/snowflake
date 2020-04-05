#include <stdlib.h>
#include "core/bank.h"
#include "core/string.h"
#include "platforms/logging.h"
#include "core/instructions.h"

/**
 * Creates a new program instruction.
 * 
 * @return the new instruction.
 */
Instruction *new_instruction()
{
    Instruction *instruction = (Instruction *) malloc(sizeof(Instruction));
    return instruction;
}

/**
 * Creates a new program instruction.
 * 
 * @return the new instruction.
 */
void free_instruction(Instruction *instruction)
{
    if (instruction != NULL)
    {
        log_debug("Freeing instruction.\n");
        bool instruction_exists = false;
        InstructionInfo info = get_instruction_info(
            instruction->instruction, &instruction_exists);

        if (instruction_exists)
        {
            free_parameter(
                &(instruction->parameters.first),
                info.parameters.first);

            free_parameter(
                &(instruction->parameters.second),
                info.parameters.second);
        }

        free(instruction);
    }
}

/**
 * Retrieves information about a specified instruction.
 * 
 * @param instruction the instruction to get information from.
 * @param exists whether the instruction exists.
 * @return information about the instruction.
 */
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
        case INSTRUCTION_LENGTH:
            set_mnemonic(&info, "LEN");
            info.parameters.first = PARAMETER_BANK;
            info.parameters.second = PARAMETER_BANK;
            break;
        case INSTRUCTION_DELETE:
            set_mnemonic(&info, "DEL");
            info.parameters.first = PARAMETER_BANK;
            info.parameters.second = PARAMETER_NONE;
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
        case INSTRUCTION_MODULO:
            set_mnemonic(&info, "  %");
            info.parameters.first = PARAMETER_BANK;
            info.parameters.second = PARAMETER_BANK;
            break;        
        case INSTRUCTION_POWER:
            set_mnemonic(&info, " **");
            info.parameters.first = PARAMETER_BANK;
            info.parameters.second = PARAMETER_BANK;
            break;
        case INSTRUCTION_SQUARE_ROOT:
            set_mnemonic(&info, "SQR");
            info.parameters.first = PARAMETER_BANK;
            info.parameters.second = PARAMETER_NONE;
            break;
        case INSTRUCTION_INCREMENT:
            set_mnemonic(&info, " +1");
            info.parameters.first = PARAMETER_BANK;
            info.parameters.second = PARAMETER_NONE;
            break;
        case INSTRUCTION_DECREMENT:
            set_mnemonic(&info, " -1");
            info.parameters.first = PARAMETER_BANK;
            info.parameters.second = PARAMETER_NONE;
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
        case INSTRUCTION_BANK_TO_FIRST:
            set_mnemonic(&info, "+[]");
            info.parameters.first = PARAMETER_BANK;
            info.parameters.second = PARAMETER_BANK;
            break;
        case INSTRUCTION_BANK_TO_LAST:
            set_mnemonic(&info, "[]+");
            info.parameters.first = PARAMETER_BANK;
            info.parameters.second = PARAMETER_BANK;
            break;
        case INSTRUCTION_FIRST_TO_BANK:
            set_mnemonic(&info, "-[]");
            info.parameters.first = PARAMETER_BANK;
            info.parameters.second = PARAMETER_BANK;
            break;
        case INSTRUCTION_LAST_TO_BANK:
            set_mnemonic(&info, "[]-");
            info.parameters.first = PARAMETER_BANK;
            info.parameters.second = PARAMETER_BANK;
            break;
        case INSTRUCTION_FIRST_TO_INDEX:
            set_mnemonic(&info, ">[]");
            info.parameters.first = PARAMETER_BANK;
            info.parameters.second = PARAMETER_BANK;
            break;
        case INSTRUCTION_LAST_TO_INDEX:
            set_mnemonic(&info, "[]<");
            info.parameters.first = PARAMETER_BANK;
            info.parameters.second = PARAMETER_BANK;
            break;
        case INSTRUCTION_INDEX_TO_FIRST:
            set_mnemonic(&info, "[<]");
            info.parameters.first = PARAMETER_BANK;
            info.parameters.second = PARAMETER_BANK;
            break;
        case INSTRUCTION_INDEX_TO_LAST:
            set_mnemonic(&info, "[>]");
            info.parameters.first = PARAMETER_BANK;
            info.parameters.second = PARAMETER_BANK;
            break;
        default:
            // No instruction exists.
            set_mnemonic(&info, "  ");
            info.parameters.first = PARAMETER_NONE;
            info.parameters.second = PARAMETER_NONE;
            *exists = false;
            return info;
    }
    
    // Instruction exists.
    *exists = true;
    return info;
}

/**
 * Sets the mnemonic for the instruction.
 * 
 * @param info the instruction information.
 * @param mnemonic the mnemonic to insert into the instruction information.
 */
void set_mnemonic(InstructionInfo *info, char *mnemonic)
{
    info->mnemonic[0] = mnemonic[0];
    info->mnemonic[1] = mnemonic[1];
    info->mnemonic[2] = mnemonic[2];
    info->mnemonic[3] = CHAR_END_STRING;
}