#ifndef SNOWFLAKE_RUN_INSTRUCTION_BRANCHING_H
#define SNOWFLAKE_RUN_INSTRUCTION_BRANCHING_H
#include <stdbool.h>
#include "core/program.h"
#include "core/instructions.h"

/**
 * Implement -> LABEL instruction.
 * 
 * @param program the snowflake program.
 * @param parameters the parameters for the instruction.
 * @param instruction_pointer the current instruction pointer for the program.
 * @return whether the instruction executed successfully.
 */
bool instruction_jump_label(Program *program, Parameters *parameters, InstructionPointer *instruction_pointer);

/**
 * Implement -> BANK instruction.
 * 
 * @param program the snowflake program.
 * @param parameters the parameters for the instruction.
 * @param instruction_pointer the current instruction pointer for the program.
 * @return whether the instruction executed successfully.
 */
bool instruction_jump_bank(Program *program, Parameters *parameters, InstructionPointer *instruction_pointer);

/**
 * Implement IF= instruction.
 * 
 * @param program the snowflake program.
 * @param parameters the parameters for the instruction.
 * @param instruction_pointer the current instruction pointer for the program.
 * @return whether the instruction executed successfully.
 */
bool instruction_if_equal(Program *program, Parameters *parameters, InstructionPointer *instruction_pointer);

/**
 * Implement IF! instruction.
 * 
 * @param program the snowflake program.
 * @param parameters the parameters for the instruction.
 * @param instruction_pointer the current instruction pointer for the program.
 * @return whether the instruction executed successfully.
 */
bool instruction_if_not_equal(Program *program, Parameters *parameters, InstructionPointer *instruction_pointer);

/**
 * Implement IF> instruction.
 * 
 * @param program the snowflake program.
 * @param parameters the parameters for the instruction.
 * @param instruction_pointer the current instruction pointer for the program.
 * @return whether the instruction executed successfully.
 */
bool instruction_if_greater_than(Program *program, Parameters *parameters, InstructionPointer *instruction_pointer);

/**
 * Implement IF< instruction.
 * 
 * @param program the snowflake program.
 * @param parameters the parameters for the instruction.
 * @param instruction_pointer the current instruction pointer for the program.
 * @return whether the instruction executed successfully.
 */
bool instruction_if_lesser_than(Program *program, Parameters *parameters, InstructionPointer *instruction_pointer);

/**
 * Jump to the instruction pointer associated with a label.
 * 
 * @param program the program containing the label.
 * @param instruction_pointer the current instruction pointer.
 * @param target_label the label to jump to.
 * @return whether the label was located.
 */
bool jump_to_label(Program *program, InstructionPointer *instruction_pointer, int target_label);

/**
 * Get the instruction pointer associated with a label.
 * 
 * @param program the program containing the label.
 * @param target_label the label to get the instruction pointer from.
 * @param target_found whether the label was located.
 * @return the instruction pointer to the label.
 */
InstructionPointer get_label_instruction_pointer(Program *program, int target_label, bool *target_found);

/**
 * Whether the two parameters are equal.
 * 
 * @param program the program.
 * @param parameters the parameters to compare.
 * @return whether the parameters are equal.
 */
bool is_parameters_equal(Program *program, Parameters *parameters);

/**
 * Whether the two strings are equal.
 * 
 * @param first_bank the bank containing the first string.
 * @param second_bank the bank containing the second string.
 * @return whether the strings are equal.
 */
bool is_string_equal(Bank *first_bank, Bank *second_bank);

#endif