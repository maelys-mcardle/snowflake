#ifndef STRUCTURES_H
#define STRUCTURES_H

typedef union {
    bool b;
    int i;
    float f;
    char *string;
    void *array;
} SnowflakeValue;

typedef enum {
    TYPE_BOOL,
    TYPE_INT,
    TYPE_FLOAT,
    TYPE_STRING,
    TYPE_ARRAY
} SnowflakeType;

typedef struct {
    SnowflakeValue value;
    SnowflakeType type;
} SnowflakeVariable;

typedef struct {
    char instruction;
    SnowflakeVariable *first;
    SnowflakeVariable *second;
} SnowflakeInstruction;

typedef struct {
    int count;
    SnowflakeInstruction *instructions;
} SnowflakeInstructionList;

typedef struct {
    SnowflakeVariable variable;
    void *next;
} VariableArrayItem;

typedef struct {
    int count;
    VariableArrayItem *items;
} VariableArray;

typedef struct {
    int index;
    int value;
    void *next;
} SnowflakeIdentifier;

typedef struct {
    int count;
    SnowflakeIdentifier *identifier;
} SnowflakeIdentifierList;

typedef struct {
    SnowflakeIdentifierList labels;
    SnowflakeIdentifierList banks;
    SnowflakeInstructionList instructions;
} SnowflakeProgram;

#endif