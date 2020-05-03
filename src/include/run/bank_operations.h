#ifndef SNOWFLAKE_BANK_OPERATIONS_H
#define SNOWFLAKE_BANK_OPERATIONS_H
#include <stdbool.h>
#include "core/program.h"
#include "core/instructions.h"

// Decorator function for a bank operation involving a single bank.
typedef bool (*SingleBankOperation)(Bank *, char *);

// Decorator function for a bank operation involving two banks.
typedef bool (*DualBankOperation)(Bank *, Bank *, char *);

/**
 * Executes a function that requires a single defined bank.
 * 
 * @param program the full snowflake program.
 * @param parameters parameters for the instruction being executed.
 * @param instruction_pointer the current instruction pointer.
 * @param operation_function the function to execute.
 * @param operation_name the name for the operation, used for logging.
 * @return whether the operation was successful.
 */
bool single_bank_operation(Program *program, Parameters *parameters, InstructionPointer *instruction_pointer, 
    SingleBankOperation operation_function, char *operation_name);

/**
 * Executes a function that requires a two defined banks.
 * 
 * @param program the full snowflake program.
 * @param parameters parameters for the instruction being executed.
 * @param instruction_pointer the current instruction pointer.
 * @param operation_function the function to execute.
 * @param operation_name the name for the operation, used for logging.
 * @return whether the operation was successful.
 */
bool dual_bank_operation(Program *program, Parameters *parameters, InstructionPointer *instruction_pointer, 
    DualBankOperation operation_function, char *operation_name);

/**
 * Perform addition using the bank values.
 * 
 * @param first_bank the first bank.
 * @param second_bank the second bank.
 * @param operation_name the name of the operation (for logging).
 * @return whether the operation was successful.
 */
bool bank_operation_addition(Bank *first_bank, Bank *second_bank, char *operation_name);

/**
 * Perform subtraction using the bank values.
 * 
 * @param first_bank the first bank.
 * @param second_bank the second bank.
 * @param operation_name the name of the operation (for logging).
 * @return whether the operation was successful.
 */
bool bank_operation_subtraction(Bank *first_bank, Bank *second_bank, char *operation_name);

/**
 * Perform multiplication using the bank values.
 * 
 * @param first_bank the first bank.
 * @param second_bank the second bank.
 * @param operation_name the name of the operation (for logging).
 * @return whether the operation was successful.
 */
bool bank_operation_multiplication(Bank *first_bank, Bank *second_bank, char *operation_name);

/**
 * Perform division using the bank values.
 * 
 * @param first_bank the first bank.
 * @param second_bank the second bank.
 * @param operation_name the name of the operation (for logging).
 * @return whether the operation was successful.
 */
bool bank_operation_division(Bank *first_bank, Bank *second_bank, char *operation_name);

/**
 * Perform modulo using the bank values.
 * 
 * @param first_bank the first bank.
 * @param second_bank the second bank.
 * @param operation_name the name of the operation (for logging).
 * @return whether the operation was successful.
 */
bool bank_operation_modulo(Bank *first_bank, Bank *second_bank, char *operation_name);

/**
 * Perform exponential using the bank values.
 * 
 * @param first_bank the first bank.
 * @param second_bank the second bank.
 * @param operation_name the name of the operation (for logging).
 * @return whether the operation was successful.
 */
bool bank_operation_power(Bank *first_bank, Bank *second_bank, char *operation_name);

/**
 * Perform square root using the bank value.
 * 
 * @param bank the first bank.
 * @param operation_name the name of the operation (for logging).
 * @return whether the operation was successful.
 */
bool bank_operation_square_root(Bank *bank, char *operation_name);

/**
 * Perform logical NOT using the bank value.
 * 
 * @param bank the first bank.
 * @param operation_name the name of the operation (for logging).
 * @return whether the operation was successful.
 */
bool bank_operation_not(Bank *bank, char *operation_name);

/**
 * Perform logical AND using the bank values.
 * 
 * @param first_bank the first bank.
 * @param second_bank the second bank.
 * @param operation_name the name of the operation (for logging).
 * @return whether the operation was successful.
 */
bool bank_operation_and(Bank *first_bank, Bank *second_bank, char *operation_name);

/**
 * Perform logical OR using the bank values.
 * 
 * @param first_bank the first bank.
 * @param second_bank the second bank.
 * @param operation_name the name of the operation (for logging).
 * @return whether the operation was successful.
 */
bool bank_operation_or(Bank *first_bank, Bank *second_bank, char *operation_name);

/**
 * Perform logical XOR using the bank values.
 * 
 * @param first_bank the first bank.
 * @param second_bank the second bank.
 * @param operation_name the name of the operation (for logging).
 * @return whether the operation was successful.
 */
bool bank_operation_xor(Bank *first_bank, Bank *second_bank, char *operation_name);

#endif