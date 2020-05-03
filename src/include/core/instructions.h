#ifndef SNOWFLAKE_INSTRUCTIONS_H
#define SNOWFLAKE_INSTRUCTIONS_H
#include <stdbool.h>
#include "devices.h"
#include "parameters.h"
#include "bank.h"

// Max number of digits for an instruction code.
#define MAX_INSTRUCTION_SIZE 3

/**
 * Enum defining all supported instructions and associated op codes.
 */
typedef enum {
    INSTRUCTION_COMMENT         = 0,
    INSTRUCTION_LABEL           = 1,
    INSTRUCTION_NAME_BANK       = 2,
    INSTRUCTION_OUTPUT          = 3,
    INSTRUCTION_INPUT           = 4,
    INSTRUCTION_COPY            = 5,
    INSTRUCTION_CONVERT         = 6,
    INSTRUCTION_TYPE            = 7,
    INSTRUCTION_DELETE          = 8,
    INSTRUCTION_LENGTH          = 9,
    INSTRUCTION_VARIABLE        = 10,
    INSTRUCTION_BOOLEAN         = 11,
    INSTRUCTION_INTEGER         = 12,
    INSTRUCTION_FLOAT           = 13,
    INSTRUCTION_STRING          = 14,
    INSTRUCTION_ARRAY           = 15,
    INSTRUCTION_JUMP_LABEL      = 20,
    INSTRUCTION_JUMP_BANK       = 21,
    INSTRUCTION_IF_EQUAL        = 22,
    INSTRUCTION_IF_NOT_EQUAL    = 23,
    INSTRUCTION_IF_GREATER_THAN = 24,
    INSTRUCTION_IF_LESSER_THAN  = 25,
    INSTRUCTION_ADD             = 30,
    INSTRUCTION_SUBTRACT        = 31,
    INSTRUCTION_MULTIPLY        = 32,
    INSTRUCTION_DIVIDE          = 33,
    INSTRUCTION_MODULO          = 34,
    INSTRUCTION_POWER           = 35,
    INSTRUCTION_SQUARE_ROOT     = 36,
    INSTRUCTION_INCREMENT       = 37,
    INSTRUCTION_DECREMENT       = 38,
    INSTRUCTION_NOT             = 40,
    INSTRUCTION_AND             = 41,
    INSTRUCTION_OR              = 42,
    INSTRUCTION_XOR             = 43,
    INSTRUCTION_BANK_TO_FIRST   = 50,
    INSTRUCTION_BANK_TO_LAST    = 51,
    INSTRUCTION_FIRST_TO_BANK   = 52,
    INSTRUCTION_LAST_TO_BANK    = 53,
    INSTRUCTION_FIRST_TO_INDEX  = 54,
    INSTRUCTION_LAST_TO_INDEX   = 55,
    INSTRUCTION_INDEX_TO_FIRST  = 56,
    INSTRUCTION_INDEX_TO_LAST   = 57,
} InstructionCode;

/**
 * Parameters for an instruction.
 */
typedef struct {
    ParameterValue first;
    ParameterValue second;
} Parameters;

/**
 * A single instruction, with its parameters.
 */
typedef struct {
    InstructionCode instruction;
    Parameters parameters;
} Instruction;

/**
 * Information about instruction parameters.
 */
typedef struct {
    ParameterType first;
    ParameterType second;
} ParameterInfo;

/**
 * Information about a single parameter.
 */
typedef struct {
    char mnemonic[4];
    ParameterInfo parameters;
} InstructionInfo;

/**
 * Creates a new program instruction.
 * 
 * @return the new instruction.
 */
Instruction *new_instruction();

/**
 * Frees the program instruction.
 * 
 * @param instruction instruction to free.
 */
void free_instruction(Instruction *instruction);

/**
 * Retrieves information about a specified instruction.
 * 
 * @param instruction the instruction to get information from.
 * @param exists whether the instruction exists.
 * @return information about the instruction.
 */
InstructionInfo get_instruction_info(InstructionCode instruction, bool *exists);

/**
 * Sets the mnemonic for the instruction.
 * 
 * @param info the instruction information.
 * @param mnemonic the mnemonic to insert into the instruction information.
 */
void set_mnemonic(InstructionInfo *info, char *mnemonic);

#endif
