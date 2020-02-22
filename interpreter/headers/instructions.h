#ifndef SNOWFLAKE_INSTRUCTIONS_H
#define SNOWFLAKE_INSTRUCTIONS_H
#include <stdbool.h>

#define MAX_INSTRUCTION_SIZE 3
#define MAX_PARAMETER_SIZE 256
#define MAX_LABEL_SIZE 4
#define MAX_BANK_SIZE 4
#define MAX_DEVICE_SIZE 4
#define MAX_LITERAL_SIZE 256

#define INSTRUCTION_COMMENT 00
#define INSTRUCTION_LABEL 01
#define INSTRUCTION_NAME_BANK 02

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
    int instruction;
    InstructionInfo info;
    Parameters parameters;
} Instruction;

Instruction *new_instruction();
void free_instruction(Instruction *instruction);
void free_parameter(ParameterType type, ParameterValue value);
InstructionInfo get_instruction_info(int instruction, bool *exists);

#endif
