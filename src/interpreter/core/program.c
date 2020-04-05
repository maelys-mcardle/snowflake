#include <stdlib.h>
#include "platforms/logging.h"
#include "errors.h"
#include "core/program.h"

/**
 * Creates a new program and allocates memory.
 *
 * @return the initialized program.
 */
Program *new_program()
{
    Program *program = (Program *) malloc(sizeof(Program));
    if (program != NULL)
    {
        program->instructions = new_instruction_array();
        program->banks = new_bank_array();
    }
    else
    {
        log_error(ERROR_MESG_COULD_NOT_ALLOCATE_MEMORY);
    }

    return program;
}

/**
 * Free the allocated data for the program.
 * 
 * @param program the program to free. 
 */
void free_program(Program *program)
{
    if (program != NULL)
    {
        log_debug("Freeing all program instructions.\n");
        free_array(program->instructions);

        log_debug("Freeing all program banks.\n");
        free_array(program->banks);

        log_debug("Freeing program.\n");
        free(program);
    }
}


/** 
 * Creates a new instruction array.
 * 
 * @return the new instruction array.
 */
Array *new_instruction_array()
{
    Array *instruction_array = new_array();

    if (instruction_array != NULL)
    {
        instruction_array->free_array_item_function = free_instruction_array_item;
    }
    
    return instruction_array;
}

/**
 * Free the instruction contained in the array item.
 * 
 * @param instruction instruction contained in the array item.
 */
void free_instruction_array_item(ArrayItem *instruction)
{
    free_instruction((Instruction *) instruction);
}

/**
 * Fetches the total number of instructions in the program.
 * 
 * @param program program containing the instructions.
 * @return the number of instructions.
 */
InstructionCount get_instruction_count(Program *program)
{
    return get_array_count(program->instructions);
}

/**
 * Gets the instruction at the specified instruction pointer.
 * 
 * @param program containing the instructions.
 * @param instruction_pointer the instruction pointer to the instruction.
 * @return the instruction at the specified instruction pointer.
 */
Instruction *get_instruction(Program *program, InstructionPointer instruction_pointer)
{
    Instruction *instruction = (Instruction *) get_array_item(program->instructions, instruction_pointer);
    return instruction;
}

/** 
 * Adds an instruction to the program.
 * 
 * @param program the program to append the instruction to.
 * @param instruction the instruction to append.
 * @return True if the instruction was added, false if not.
 */
bool append_instruction_to_program(Program *program, Instruction *instruction)
{
    return append_array(program->instructions, instruction);
}

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
bool set_program_bank(Program *program, Bank *new_bank)
{
    // Get the existing index of the bank, if it's set.
    bool bank_exists = false;
    BankIndex bank_index = get_program_bank_index(program, new_bank->identifier, &bank_exists);

    if (!bank_exists) 
    {
        // Bank index doesn't exist. Append it.
        log_debug("Adding Bank %02i to program at Bank Index %i.\n", new_bank->identifier, bank_index);
        return append_bank_to_program(program, new_bank);
    }
    else
    {
        // Bank index already exists. Delete old. Replace with new.
        Bank *old_bank = (Bank *) remove_array_item(program->banks, bank_index);

        // If both banks are pointing to the same memory location, don't free it.
        if (old_bank != new_bank) {
            free_bank(old_bank);
        }
        
        // Indicate that the bank is being replaced.
        log_debug("Replacing Bank %02i in program at Bank Index %i.\n", new_bank->identifier, bank_index);
        return insert_array_item(program->banks, (ArrayItem *) new_bank, bank_index);
    }
}

/**
 * Removes a bank with the specified identifier from the program.
 * 
 * @param program program to remove the bank from.
 * @param identifier identifier of the bank to remove.
 * @return whether the operation was successful.
 */
bool remove_program_bank(Program *program, Identifier identifier)
{
    Bank *bank = remove_program_bank_without_freeing(program, identifier);
    if (bank != NULL) free(bank);
    return true;
}

/**
 * Removes a bank with the specified identifier from the program.
 * It does not unallocate the memory associated with the bank.
 * 
 * @param program program to remove the bank from.
 * @param identifier identifier of the bank to remove.
 * @return the bank that was removed.
 */
Bank *remove_program_bank_without_freeing(Program *program, Identifier identifier)
{
    // Get the existing index of the bank, if it's set.
    bool bank_exists = false;
    BankIndex bank_index = get_program_bank_index(program, identifier, &bank_exists);

    if (!bank_exists) 
    {
        // Bank index doesn't exist. Nothing to delete.
        return NULL;
    }
    else
    {
        // Bank index exists. Delete bank.
        Bank *bank = (Bank *) remove_array_item(program->banks, bank_index);
        return bank;
    }
}

/**
 * Retrieves the bank based on the identifier stored in the parameter.
 * 
 * @param program program to get the bank from.
 * @param parameter the parameter containing the identifier.
 * @return the bank that was retrieved from the program.
 */
Bank *get_bank_from_parameter(Program *program, ParameterValue *parameter)
{
    Identifier target_identifier = parameter->identifier;
    return get_program_bank(program, target_identifier);
}

/**
 * Retrieves the bank based on the identifier.
 * 
 * @param program program to get the bank from.
 * @param identifier the identifier for the bank.
 * @return the bank that was retrieved from the program.
 */
Bank *get_program_bank(Program *program, Identifier identifier)
{
    bool bank_exists = false;
    BankIndex index = get_program_bank_index(program, identifier, &bank_exists);
    if (bank_exists) {
        return (Bank *) get_array_item(program->banks, index);
    }
    return NULL;
}

/**
 * Gets the index in the banks of the bank with the target identifier.
 *
 * @param program the program that has the index.
 * @param target_identifier identifier of the bank in the program.
 * @param target_exists whether the specified bank was found in the program.
 * @return the index of the bank in the array of banks of the program.
 */
BankIndex get_program_bank_index(Program *program, Identifier target_identifier, bool *target_exists)
{
    if (program->banks != NULL)
    {
        for (BankIndex i = 0; i < get_array_count(program->banks); i++)
        {
            Bank *bank = (Bank *) get_array_item(program->banks, i);
            if (bank->identifier == target_identifier) {
                *target_exists = true;
                return i;
            }
        }
    }

    *target_exists = false;
    return 0;
}

/**
 * Appends the bank to the program bank array.
 * 
 * @param program the program to append the bank to.
 * @param bank the bank to add to the program.
 * @return whether the operation was successful.
 */
bool append_bank_to_program(Program *program, Bank *bank)
{
    return append_array(program->banks, (ArrayItem *) bank);
}

/**
 * Creates a new bank. It's identifier is taken from the parameter.
 * 
 * @param parameter parameter that specifies the bank identifier.
 * @return the new bank.
 */
Bank *new_bank_from_parameter(ParameterValue *parameter)
{
    Identifier identifier = parameter->identifier;
    Bank *bank = new_bank(identifier);
    return bank;
}

/**
 * Fetches a bank from the program with the specified identifier.
 * If the bank doesn't exist, it creates it.
 * 
 * @param program program containing the bank.
 * @param parameter parameter specifying the bank identifier.
 */
Bank *get_or_new_bank_from_parameter(Program *program, ParameterValue *parameter)
{
    Bank *bank = get_bank_from_parameter(program, parameter);
    if (bank == NULL)
    {
        bank = new_bank_from_parameter(parameter);
        if (!append_bank_to_program(program, bank))
        {
            free_bank(bank);
        }
    }

    return bank;
}

/**
 * Retrieves the device type from the parameter.
 * 
 * @param parameters the parameters specifying the device type.
 * @return the device type.
 */
Device get_device_from_parameter(Parameters *parameters)
{
    Device device = parameters->first.identifier;
    return device;
}

/**
 * Retrieves the type type from the parameter.
 * 
 * @param parameters the parameters specifying the type type.
 * @return the type type.
 */
BankType get_type_from_parameter(Parameters *parameters)
{
    BankType type = parameters->first.identifier;
    return type;
}

/**
 * Increments the instruction pointer.
 * 
 * @param instruction_pointer the instruction pointer to modify.
 */
void increment_instruction(InstructionPointer *instruction_pointer)
{
    *instruction_pointer += 1;
}

/**
 * Increments the instruction pointer by two.
 * 
 * @param instruction_pointer the instruction pointer to modify.
 */
void skip_next_instruction(InstructionPointer *instruction_pointer)
{
    *instruction_pointer += 2;
}

/**
 * Sets the instruction pointer to a new value.
 * 
 * @param instruction_pointer the instruction pointer to modify.
 * @param new_location new address for the instruction pointer.
 */
void go_to_instruction(InstructionPointer *instruction_pointer, InstructionPointer new_location)
{
    *instruction_pointer = new_location;
}

