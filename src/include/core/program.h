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

/**
 * Stores an entire Snowflake program.
 */
typedef struct {
    Array *banks;
    Array *instructions;
} Program;

/**
 * Creates a new program and allocates memory.
 *
 * @return the initialized program.
 */
Program *new_program();

/**
 * Free the allocated data for the program.
 * 
 * @param program the program to free. 
 */
void free_program(Program *program);

/** 
 * Creates a new instruction array.
 * 
 * @return the new instruction array.
 */
Array *new_instruction_array();

/**
 * Free the instruction contained in the array item.
 * 
 * @param instruction instruction contained in the array item.
 */
void free_instruction_array_item(ArrayItem *instruction);

/**
 * Fetches the total number of instructions in the program.
 * 
 * @param program program containing the instructions.
 * @return the number of instructions.
 */
InstructionCount get_instruction_count(Program *program);

/**
 * Gets the instruction at the specified instruction pointer.
 * 
 * @param program containing the instructions.
 * @param instruction_pointer the instruction pointer to the instruction.
 * @return the instruction at the specified instruction pointer.
 */
Instruction *get_instruction(Program *program, InstructionPointer instruction_pointer);

/** 
 * Adds an instruction to the program.
 * 
 * @param program the program to append the instruction to.
 * @param instruction the instruction to append.
 * @return True if the instruction was added, false if not.
 */
bool append_instruction_to_program(Program *program, Instruction *instruction);

/**
 * Appends the bank to the program bank array.
 * 
 * @param program the program to append the bank to.
 * @param bank the bank to add to the program.
 * @return whether the operation was successful.
 */
bool append_bank_to_program(Program *program, Bank *bank);

/**
 * Adds or replaces a bank to the program.
 * 
 * If there's no bank with the same identifier in the program, it adds it.
 * If there's a bank with the same identifier in the program, it replaces it.
 *
 * @param program the program to add/replace the bank for.
 * @param new_bank the bank to set in the program.
 * @return whether the operation was successful.
 */
bool set_program_bank(Program *program, Bank *bank);

/**
 * Gets the index in the banks of the bank with the target identifier.
 *
 * @param program the program that has the index.
 * @param target_identifier identifier of the bank in the program.
 * @param target_exists whether the specified bank was found in the program.
 * @return the index of the bank in the array of banks of the program.
 */
BankIndex get_program_bank_index(Program *program, Identifier identifier, bool *bank_exists);

/**
 * Removes a bank with the specified identifier from the program.
 * 
 * @param program program to remove the bank from.
 * @param identifier identifier of the bank to remove.
 * @return whether the operation was successful.
 */
bool remove_program_bank(Program *program, Identifier identifier);

/**
 * Removes a bank with the specified identifier from the program.
 * It does not unallocate the memory associated with the bank.
 * 
 * @param program program to remove the bank from.
 * @param identifier identifier of the bank to remove.
 * @return the bank that was removed.
 */
Bank *remove_program_bank_without_freeing(Program *program, Identifier identifier);

/**
 * Retrieves the bank based on the identifier.
 * 
 * @param program program to get the bank from.
 * @param identifier the identifier for the bank.
 * @return the bank that was retrieved from the program.
 */
Bank *get_program_bank(Program *program, Identifier identifier);

/**
 * Retrieves the bank based on the identifier stored in the parameter.
 * 
 * @param program program to get the bank from.
 * @param parameter the parameter containing the identifier.
 * @return the bank that was retrieved from the program.
 */
Bank *get_bank_from_parameter(Program *program, ParameterValue *parameter);

/**
 * Creates a new bank. It's identifier is taken from the parameter.
 * 
 * @param parameter parameter that specifies the bank identifier.
 * @return the new bank.
 */
Bank *new_bank_from_parameter(ParameterValue *parameter);

/**
 * Fetches a bank from the program with the specified identifier.
 * If the bank doesn't exist, it creates it.
 * 
 * @param program program containing the bank.
 * @param parameter parameter specifying the bank identifier.
 */
Bank *get_or_new_bank_from_parameter(Program *program, ParameterValue *parameter);

/**
 * Retrieves the device type from the parameter.
 * 
 * @param parameters the parameters specifying the device type.
 * @return the device type.
 */
Device get_device_from_parameter(Parameters *parameters);

/**
 * Retrieves the type type from the parameter.
 * 
 * @param parameters the parameters specifying the type type.
 * @return the type type.
 */
BankType get_type_from_parameter(Parameters *parameters);

/**
 * Increments the instruction pointer.
 * 
 * @param instruction_pointer the instruction pointer to modify.
 */
void increment_instruction(InstructionPointer *instruction_pointer);

/**
 * Increments the instruction pointer by two.
 * 
 * @param instruction_pointer the instruction pointer to modify.
 */
void skip_next_instruction(InstructionPointer *instruction_pointer);

/**
 * Sets the instruction pointer to a new value.
 * 
 * @param instruction_pointer the instruction pointer to modify.
 * @param new_location new address for the instruction pointer.
 */
void go_to_instruction(InstructionPointer *instruction_pointer, InstructionPointer new_location);

#endif
