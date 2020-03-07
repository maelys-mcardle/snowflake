#ifndef SNOWFLAKE_PROGRAM_H
#define SNOWFLAKE_PROGRAM_H
#include <stdbool.h>
#include "instructions.h"
#include "bank.h"

typedef struct {
    int count;
    Bank **banks;
} ProgramBanks;

typedef struct {
    int count;
    Instruction **instructions;
} ProgramInstructions;

typedef struct {
    ProgramBanks banks;
    ProgramInstructions instructions;
} Program;

Program *new_program();
void free_program(Program *program);
bool append_instruction_to_program(Program *program, Instruction *instruction);
bool append_bank_to_program(Program *program, Bank *bank);
bool set_program_bank(Program *program, Bank *bank);
bool resize_bank_array(Program *program, int new_count);
int get_program_bank_index(Program *program, BankIdentifier identifier);
bool remove_program_bank(Program *program, BankIdentifier identifier);
Bank *get_program_bank(Program *program, BankIdentifier identifier);
Bank *get_bank_from_first_parameter(Program *program, Instruction *instruction);
Bank *get_bank_from_second_parameter(Program *program, Instruction *instruction);
Bank *new_bank_from_first_parameter(Instruction *instruction);
Bank *new_bank_from_second_parameter(Instruction *instruction);
Bank *get_or_new_bank_from_first_parameter(Program *program, Instruction *instruction);
Bank *get_or_new_bank_from_second_parameter(Program *program, Instruction *instruction);

#endif
