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
#define INSTRUCTION_OUTPUT 03
#define INSTRUCTION_INPUT 04
#define INSTRUCTION_COPY 05
#define INSTRUCTION_TYPE 06
#define INSTRUCTION_VARIABLE 10
#define INSTRUCTION_BOOLEAN 11
#define INSTRUCTION_INTEGER 12
#define INSTRUCTION_FLOAT 13
#define INSTRUCTION_STRING 14
#define INSTRUCTION_ARRAY 15
#define INSTRUCTION_JUMP_LABEL 20
#define INSTRUCTION_JUMP_BANK 21
#define INSTRUCTION_IF_EQUAL 22
#define INSTRUCTION_IF_NOT_EQUAL 23
#define INSTRUCTION_IF_GREATER_THAN 24
#define INSTRUCTION_IF_LESSER_THAN 25
#define INSTRUCTION_ADD 30
#define INSTRUCTION_SUBTRACT 31
#define INSTRUCTION_MULTIPLY 32
#define INSTRUCTION_DIVIDE 33
#define INSTRUCTION_POWER 34
#define INSTRUCTION_NOT 40
#define INSTRUCTION_AND 41
#define INSTRUCTION_OR 42
#define INSTRUCTION_XOR 43
#define INSTRUCTION_ARRAY_SIZE 50
#define INSTRUCTION_PREPEND_ARRAY 51
#define INSTRUCTION_APPEND_ARRAY 52
#define INSTRUCTION_GET_FIRST 53
#define INSTRUCTION_GET_LAST 54
#define INSTRUCTION_REMOVE_FIRST 55
#define INSTRUCTION_REMOVE_LAST 56
#define INSTRUCTION_MOVE_TO_INDEX 57
#define INSTRUCTION_MOVE_TO_FIRST 58

#define DEVICE_OUT 00
#define DEVICE_IN 01
#define DEVICE_PRT 02
#define DEVICE_BTN 03

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
    short instruction;
    InstructionInfo info;
    Parameters parameters;
} Instruction;

Instruction *new_instruction();
void free_instruction(Instruction *instruction);
void free_parameter(ParameterType type, ParameterValue value);
InstructionInfo get_instruction_info(short instruction, bool *exists);

#endif
