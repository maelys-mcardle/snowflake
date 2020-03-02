#ifndef SNOWFLAKE_INSTRUCTIONS_H
#define SNOWFLAKE_INSTRUCTIONS_H
#include <stdbool.h>
#include "devices.h"

#define MAX_INSTRUCTION_SIZE 3
#define MAX_PARAMETER_SIZE   256

typedef enum {
    INSTRUCTION_COMMENT    = 00,
    INSTRUCTION_LABEL      = 01,
    INSTRUCTION_NAME_BANK  = 02,
    INSTRUCTION_OUTPUT     = 03,
    INSTRUCTION_INPUT      = 04,
    INSTRUCTION_COPY       = 05,
    INSTRUCTION_DELETE     = 06,
    INSTRUCTION_TYPE       = 07,
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
    INSTRUCTION_ADD        = 30,
    INSTRUCTION_SUBTRACT   = 31,
    INSTRUCTION_MULTIPLY   = 32,
    INSTRUCTION_DIVIDE     = 33,
    INSTRUCTION_POWER      = 34,
    INSTRUCTION_NOT        = 40,
    INSTRUCTION_AND        = 41,
    INSTRUCTION_OR         = 42,
    INSTRUCTION_XOR        = 43,
    INSTRUCTION_ARRAY_SIZE    = 50,
    INSTRUCTION_PREPEND_ARRAY = 51,
    INSTRUCTION_APPEND_ARRAY  = 52,
    INSTRUCTION_GET_FIRST     = 53,
    INSTRUCTION_GET_LAST      = 54,
    INSTRUCTION_REMOVE_FIRST  = 55,
    INSTRUCTION_REMOVE_LAST   = 56,
    INSTRUCTION_MOVE_TO_INDEX = 57,
    INSTRUCTION_MOVE_TO_FIRST = 58
} InstructionCode;

typedef enum {
    PARAMETER_NONE = 0,
    PARAMETER_LABEL,
    PARAMETER_BANK,
    PARAMETER_DEVICE,
    PARAMETER_LITERAL,
    PARAMETER_OPTIONAL = 0b1000000,
    PARAMETER_WITHOUT_FLAGS = 0b0111111
} ParameterType;

typedef struct {
    ParameterType first;
    ParameterType second;
} ParameterInfo;

typedef struct {
    char mnemonic[3];
    ParameterInfo parameters;
} InstructionInfo;

typedef union {
    int integer;
    char *string;
} ParameterValue;

typedef struct {
    ParameterValue first;
    ParameterValue second;
} Parameters;

typedef struct {
    InstructionCode instruction;
    InstructionInfo info;
    Parameters parameters;
} Instruction;

Instruction *new_instruction();
void free_instruction(Instruction *instruction);
void free_parameter(ParameterType type, ParameterValue value);
ParameterType get_parameter_type(ParameterType type);
bool is_parameter_optional(ParameterType type);
bool is_parameter_none(ParameterType type);
InstructionInfo get_instruction_info(InstructionCode instruction, bool *exists);
Device get_device_from_instruction(Instruction *instruction);
void set_mnemonic(InstructionInfo *info, char *mnemonic);

#endif