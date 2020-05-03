#ifndef SNOWFLAKE_RUN_INSTRUCTION_ARRAY_H
#define SNOWFLAKE_RUN_INSTRUCTION_ARRAY_H
#include <stdbool.h>
#include "core/program.h"
#include "core/instructions.h"

/**
 * Tracks whether the first array item, last item, or one at index.
 */
typedef enum {
    FIRST,
    LAST,
    INDEX
} ArrayPosition;

/**
 * Implement +[] instruction.
 * 
 * @param program the snowflake program.
 * @param parameters the parameters for the instruction.
 * @param instruction_pointer the current instruction pointer for the program.
 * @return whether the instruction executed successfully.
 */
bool instruction_bank_to_first(Program *program, Parameters *parameters, InstructionPointer *instruction_pointer);

/**
 * Implement []+ instruction.
 * 
 * @param program the snowflake program.
 * @param parameters the parameters for the instruction.
 * @param instruction_pointer the current instruction pointer for the program.
 * @return whether the instruction executed successfully.
 */
bool instruction_bank_to_last(Program *program, Parameters *parameters, InstructionPointer *instruction_pointer);

/**
 * Implement -[] instruction.
 * 
 * @param program the snowflake program.
 * @param parameters the parameters for the instruction.
 * @param instruction_pointer the current instruction pointer for the program.
 * @return whether the instruction executed successfully.
 */
bool instruction_first_to_bank(Program *program, Parameters *parameters, InstructionPointer *instruction_pointer);

/**
 * Implement []- instruction.
 * 
 * @param program the snowflake program.
 * @param parameters the parameters for the instruction.
 * @param instruction_pointer the current instruction pointer for the program.
 * @return whether the instruction executed successfully.
 */
bool instruction_last_to_bank(Program *program, Parameters *parameters, InstructionPointer *instruction_pointer);

/**
 * Implement >[] instruction.
 * 
 * @param program the snowflake program.
 * @param parameters the parameters for the instruction.
 * @param instruction_pointer the current instruction pointer for the program.
 * @return whether the instruction executed successfully.
 */
bool instruction_first_to_index(Program *program, Parameters *parameters, InstructionPointer *instruction_pointer);

/**
 * Implement []< instruction.
 * 
 * @param program the snowflake program.
 * @param parameters the parameters for the instruction.
 * @param instruction_pointer the current instruction pointer for the program.
 * @return whether the instruction executed successfully.
 */
bool instruction_last_to_index(Program *program, Parameters *parameters, InstructionPointer *instruction_pointer);

/**
 * Implement [<] instruction.
 * 
 * @param program the snowflake program.
 * @param parameters the parameters for the instruction.
 * @param instruction_pointer the current instruction pointer for the program.
 * @return whether the instruction executed successfully.
 */
bool instruction_index_to_first(Program *program, Parameters *parameters, InstructionPointer *instruction_pointer);

/**
 * Implement [>] instruction.
 * 
 * @param program the snowflake program.
 * @param parameters the parameters for the instruction.
 * @param instruction_pointer the current instruction pointer for the program.
 * @return whether the instruction executed successfully.
 */
bool instruction_index_to_last(Program *program, Parameters *parameters, InstructionPointer *instruction_pointer);

/**
 * Inserts bank in the array.
 * 
 * @param program snowflake program.
 * @param parameters parameters for the instruction that invoked this.
 * @param position position in the array to insert the bank to.
 * @return whether the operation was successful.
 */
bool bank_to_array(Program *program, Parameters *parameters, ArrayPosition position);

/**
 * Retrieves bank in the array.
 * 
 * @param program snowflake program.
 * @param parameters parameters for the instruction that invoked this.
 * @param position position in the array to retrieve the bank from.
 * @return whether the operation was successful.
 */
bool array_to_bank(Program *program, Parameters *parameters, ArrayPosition position);

/**
 * Shift the position of a bank in the array.
 * 
 * @param program snowflake program.
 * @param parameters parameters for the instruction that invoked this.
 * @param from position in the array that contains the bank.
 * @param to position in the array to move the bank to.
 * @return whether the operation was successful.
 */
bool array_shift_positions(Program *program, Parameters *parameters, ArrayPosition from, ArrayPosition to);

/**
 * Translates a named position (eg. first, last, index) into a numeric index.
 * 
 * @param array the array to get the index from.
 * @param position named position.
 * @param index the numeric index when the named position is INDEX.
 * @return the numeric index for the named position.
 */
ArrayIndex get_array_index_from_position(Array *array, ArrayPosition position, ArrayIndex index);

#endif