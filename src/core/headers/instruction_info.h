#ifndef SNOWFLAKE_INSTRUCTION_INFO_H
#define SNOWFLAKE_INSTRUCTION_INFO_H
#include <stdbool.h>
#include "parameters.h"

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

typedef struct {
    ParameterType first;
    ParameterType second;
} ParameterInfo;

typedef struct {
    char mnemonic[3];
    ParameterInfo parameters;
} InstructionInfo;

InstructionInfo get_instruction_info(InstructionCode instruction, bool *exists);
void set_mnemonic(InstructionInfo *info, char *mnemonic);

#endif
