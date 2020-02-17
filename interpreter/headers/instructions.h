#ifndef LOAD_INSTRUCTIONS_H
#define LOAD_INSTRUCTIONS_H
#include <stdbool.h>

typedef enum {
    PARAMETER_NONE,
    PARAMETER_LABEL,
    PARAMETER_BANK,
    PARAMETER_DEVICE,
    PARAMETER_LITERAL,
    PARAMETER_OPTIONAL = 0b10000
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
    int i;
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

InstructionInfo get_instruction_info(int instruction, bool *exists);

#endif