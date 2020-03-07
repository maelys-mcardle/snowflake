#ifndef SNOWFLAKE_INSTRUCTIONS_H
#define SNOWFLAKE_INSTRUCTIONS_H
#include <stdbool.h>
#include "devices.h"
#include "parameters.h"
#include "bank.h"

#define MAX_INSTRUCTION_SIZE 3

typedef enum {
    INSTRUCTION_COMMENT    = 0,
    INSTRUCTION_LABEL      = 1,
    INSTRUCTION_NAME_BANK  = 2,
    INSTRUCTION_OUTPUT     = 3,
    INSTRUCTION_INPUT      = 4,
    INSTRUCTION_COPY       = 5,
    INSTRUCTION_CONVERT    = 6,
    INSTRUCTION_TYPE       = 7,
    INSTRUCTION_DELETE     = 8,
    INSTRUCTION_VARIABLE   = 10,
    INSTRUCTION_BOOLEAN    = 11,
    INSTRUCTION_INTEGER    = 12,
    INSTRUCTION_FLOAT      = 13,
    INSTRUCTION_STRING     = 14,
    INSTRUCTION_ARRAY      = 15,
    INSTRUCTION_JUMP_LABEL = 20,
    INSTRUCTION_JUMP_BANK  = 21,
    INSTRUCTION_IF_EQUAL   = 22,
    INSTRUCTION_IF_NOT_EQUAL    = 23,
    INSTRUCTION_IF_GREATER_THAN = 24,
    INSTRUCTION_IF_LESSER_THAN  = 25,
    INSTRUCTION_ADD             = 30,
    INSTRUCTION_SUBTRACT        = 31,
    INSTRUCTION_MULTIPLY        = 32,
    INSTRUCTION_DIVIDE          = 33,
    INSTRUCTION_POWER           = 34,
    INSTRUCTION_NOT             = 40,
    INSTRUCTION_AND             = 41,
    INSTRUCTION_OR              = 42,
    INSTRUCTION_XOR             = 43,
    INSTRUCTION_ARRAY_SIZE      = 50,
    INSTRUCTION_PREPEND_ARRAY   = 51,
    INSTRUCTION_APPEND_ARRAY    = 52,
    INSTRUCTION_GET_FIRST       = 53,
    INSTRUCTION_GET_LAST        = 54,
    INSTRUCTION_REMOVE_FIRST    = 55,
    INSTRUCTION_REMOVE_LAST     = 56,
    INSTRUCTION_MOVE_TO_INDEX   = 57,
    INSTRUCTION_MOVE_TO_FIRST   = 58
} InstructionCode;

typedef struct {
    ParameterType first;
    ParameterType second;
} ParameterInfo;

typedef struct {
    char mnemonic[3];
    ParameterInfo parameters;
} InstructionInfo;

typedef struct {
    ParameterValue first;
    ParameterValue second;
} Parameters;

typedef struct {
    InstructionCode instruction;
    Parameters parameters;
} Instruction;

Instruction *new_instruction();
void free_instruction(Instruction *instruction);
InstructionInfo get_instruction_info(InstructionCode instruction, bool *exists);
Device get_device_from_instruction(Instruction *instruction);
BankType get_type_from_instruction(Instruction *instruction);
void set_mnemonic(InstructionInfo *info, char *mnemonic);

#endif
