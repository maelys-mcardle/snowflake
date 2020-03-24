#ifndef SNOWFLAKE_PROGRAM_H
#define SNOWFLAKE_PROGRAM_H
#include <stdbool.h>
#include "instructions.h"
#include "bank.h"
#include "array.h"

typedef ArrayIndex InstructionPointer;
typedef InstructionPointer InstructionCount;
typedef ArrayIndex BankIndex;
typedef BankIndex BankCount;

typedef struct {
    Array *banks;
    Array *instructions;
} Program;

Program *new_program();
void free_program(Program *program);
bool append_instruction_to_program(Program *program, Instruction *instruction);
bool append_bank_to_program(Program *program, Bank *bank);
bool set_program_bank(Program *program, Bank *bank);
BankIndex get_program_bank_index(Program *program, Identifier identifier, bool *bank_exists);
bool remove_program_bank(Program *program, Identifier identifier);
Bank *remove_program_bank_without_freeing(Program *program, Identifier identifier);
Bank *get_program_bank(Program *program, Identifier identifier);
Bank *get_bank_from_parameter(Program *program, ParameterValue *parameter);
Bank *new_bank_from_parameter(ParameterValue *parameter);
Bank *get_or_new_bank_from_parameter(Program *program, ParameterValue *parameter);
Device get_device_from_parameter(Parameters *parameters);
BankType get_type_from_parameter(Parameters *parameters);
void increment_instruction(InstructionPointer *instruction_pointer);
void skip_next_instruction(InstructionPointer *instruction_pointer);
void go_to_instruction(InstructionPointer *instruction_pointer, InstructionPointer new_location);
InstructionCount get_instruction_count(Program *program);
Instruction *get_instruction(Program *program, InstructionPointer instruction_pointer);

#endif
