#ifndef SNOWFLAKE_BANK_OPERATIONS_H
#define SNOWFLAKE_BANK_OPERATIONS_H
#include <stdbool.h>
#include "core/program.h"
#include "core/instructions.h"

typedef bool (*SingleBankOperation)(Bank *, char *);
typedef bool (*DualBankOperation)(Bank *, Bank *, char *);

bool single_bank_operation(Program *program, Parameters *parameters, InstructionPointer *instruction_pointer, 
    SingleBankOperation operation_function, char *operation_name);
bool dual_bank_operation(Program *program, Parameters *parameters, InstructionPointer *instruction_pointer, 
    DualBankOperation operation_function, char *operation_name);

bool bank_operation_addition(Bank *first_bank, Bank *second_bank, char *operation_name);
bool bank_operation_subtraction(Bank *first_bank, Bank *second_bank, char *operation_name);
bool bank_operation_multiplication(Bank *first_bank, Bank *second_bank, char *operation_name);
bool bank_operation_division(Bank *first_bank, Bank *second_bank, char *operation_name);
bool bank_operation_modulo(Bank *first_bank, Bank *second_bank, char *operation_name);
bool bank_operation_power(Bank *first_bank, Bank *second_bank, char *operation_name);
bool bank_operation_square_root(Bank *bank, char *operation_name);

bool bank_operation_not(Bank *bank, char *operation_name);
bool bank_operation_and(Bank *first_bank, Bank *second_bank, char *operation_name);
bool bank_operation_or(Bank *first_bank, Bank *second_bank, char *operation_name);
bool bank_operation_xor(Bank *first_bank, Bank *second_bank, char *operation_name);

char *join_strings(char *left_string, char *right_string);

#endif