#ifndef LOAD_INSTRUCTIONS_H
#define LOAD_INSTRUCTIONS_H
#include <stdbool.h>

typedef enum {
    PARAMETER_NONE,
    PARAMETER_LABEL,
    PARAMETER_BANK,
    PARAMETER_LITERAL,
    PARAMETER_OPTIONAL = 0b10000
} ParameterType;

typedef struct {
    ParameterType first;
    ParameterType second;
} Parameters;

typedef struct {
    char mnemonic[3];
    Parameters parameters;
} InstructionInfo;

#endif