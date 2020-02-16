#ifndef LOAD_INSTRUCTIONS_H
#define LOAD_INSTRUCTIONS_H

typedef enum {
    INSTRUCTION_TYPE_NONE,
    INSTRUCTION_TYPE_LABEL,
    INSTRUCTION_TYPE_BANK,
    INSTRUCTION_TYPE_LITERAL
} InstructionType;

typedef struct {
    char mnemonic[3];
    InstructionType first_parameter;
    InstructionType second_parameter;
} InstructionInfo;

#endif