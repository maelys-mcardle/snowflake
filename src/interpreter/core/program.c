#include <stdlib.h>
#include "core/program.h"
#include "errors.h"
#include "platforms/logging.h"

/* Creates a new program and allocates memory.
 * @return The initialized program.
 */
Program *new_program()
{
    Program *program = (Program *) malloc(sizeof(Program));
    if (program != NULL)
    {
        program->instructions = new_array();
        program->instructions->free_array_item_function = free_instruction;

        program->banks = new_bank_array();
    }
    else
    {
        log_error(ERROR_MESG_COULD_NOT_ALLOCATE_MEMORY);
    }

    return program;
}

/* Free the allocated data for the program. */
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

/* Adds an instruction to the program.
 * @return True if the instruction was added, false if not.
 */
bool append_instruction_to_program(Program *program, Instruction *instruction)
{
    return append_array(program->instructions, instruction);
}

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

bool remove_program_bank(Program *program, Identifier identifier)
{
    Bank *bank = remove_program_bank_without_freeing(program, identifier);
    if (bank != NULL) free(bank);
    return true;
}

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


Bank *get_bank_from_parameter(Program *program, ParameterValue *parameter)
{
    Identifier target_identifier = parameter->identifier;
    return get_program_bank(program, target_identifier);
}

Bank *get_program_bank(Program *program, Identifier identifier)
{
    bool bank_exists = false;
    BankIndex index = get_program_bank_index(program, identifier, &bank_exists);
    if (bank_exists) {
        return (Bank *) get_array_item(program->banks, index);
    }
    return NULL;
}

/* Gets the index in the banks of the bank with the target identifier. */
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

bool append_bank_to_program(Program *program, Bank *bank)
{
    return append_array(program->banks, (ArrayItem *) bank);
}

Bank *new_bank_from_parameter(ParameterValue *parameter)
{
    Identifier identifier = parameter->identifier;
    Bank *bank = new_bank(identifier);
    return bank;
}

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

Device get_device_from_parameter(Parameters *parameters)
{
    Device device = parameters->first.identifier;
    return device;
}

BankType get_type_from_parameter(Parameters *parameters)
{
    BankType type = parameters->first.identifier;
    return type;
}

void increment_instruction(InstructionPointer *instruction_pointer)
{
    *instruction_pointer += 1;
}

void skip_next_instruction(InstructionPointer *instruction_pointer)
{
    *instruction_pointer += 2;
}

void go_to_instruction(InstructionPointer *instruction_pointer, InstructionPointer new_location)
{
    *instruction_pointer = new_location;
}

InstructionCount get_instruction_count(Program *program)
{
    return get_array_count(program->instructions);
}

Instruction *get_instruction(Program *program, InstructionPointer instruction_pointer)
{
    Instruction *instruction = (Instruction *) get_array_item(program->instructions, instruction_pointer);
    return instruction;
}