#ifndef SNOWFLAKE_RUN_INSTRUCTION_MATH_H
#define SNOWFLAKE_RUN_INSTRUCTION_MATH_H
#include <stdbool.h>
#include "core/program.h"
#include "core/instructions.h"

/**
 * Implement + instruction.
 * 
 * @param program the snowflake program.
 * @param parameters the parameters for the instruction.
 * @param instruction_pointer the current instruction pointer for the program.
 * @return whether the instruction executed successfully.
 */
bool instruction_add(Program *program, Parameters *parameters, InstructionPointer *instruction_pointer);

/**
 * Implement - instruction.
 * 
 * @param program the snowflake program.
 * @param parameters the parameters for the instruction.
 * @param instruction_pointer the current instruction pointer for the program.
 * @return whether the instruction executed successfully.
 */
bool instruction_subtract(Program *program, Parameters *parameters, InstructionPointer *instruction_pointer);

/**
 * Implement * instruction.
 * 
 * @param program the snowflake program.
 * @param parameters the parameters for the instruction.
 * @param instruction_pointer the current instruction pointer for the program.
 * @return whether the instruction executed successfully.
 */
bool instruction_multiply(Program *program, Parameters *parameters, InstructionPointer *instruction_pointer);

/**
 * Implement / instruction.
 * 
 * @param program the snowflake program.
 * @param parameters the parameters for the instruction.
 * @param instruction_pointer the current instruction pointer for the program.
 * @return whether the instruction executed successfully.
 */
bool instruction_divide(Program *program, Parameters *parameters, InstructionPointer *instruction_pointer);

/**
 * Implement % instruction.
 * 
 * @param program the snowflake program.
 * @param parameters the parameters for the instruction.
 * @param instruction_pointer the current instruction pointer for the program.
 * @return whether the instruction executed successfully.
 */
bool instruction_modulo(Program *program, Parameters *parameters, InstructionPointer *instruction_pointer);

/**
 * Implement ** instruction.
 * 
 * @param program the snowflake program.
 * @param parameters the parameters for the instruction.
 * @param instruction_pointer the current instruction pointer for the program.
 * @return whether the instruction executed successfully.
 */
bool instruction_power(Program *program, Parameters *parameters, InstructionPointer *instruction_pointer);

/**
 * Implement SQR instruction.
 * 
 * @param program the snowflake program.
 * @param parameters the parameters for the instruction.
 * @param instruction_pointer the current instruction pointer for the program.
 * @return whether the instruction executed successfully.
 */
bool instruction_square_root(Program *program, Parameters *parameters, InstructionPointer *instruction_pointer);

/**
 * Implement +1 instruction.
 * 
 * @param program the snowflake program.
 * @param parameters the parameters for the instruction.
 * @param instruction_pointer the current instruction pointer for the program.
 * @return whether the instruction executed successfully.
 */
bool instruction_increment(Program *program, Parameters *parameters, InstructionPointer *instruction_pointer);

/**
 * Implement -1 instruction.
 * 
 * @param program the snowflake program.
 * @param parameters the parameters for the instruction.
 * @param instruction_pointer the current instruction pointer for the program.
 * @return whether the instruction executed successfully.
 */
bool instruction_decrement(Program *program, Parameters *parameters, InstructionPointer *instruction_pointer);

/**
 * Adds a value to a bank containing a numeric value.
 * 
 * @param program the snowflake program.
 * @param parameters the parameters for the instruction.
 * @param instruction_pointer the current instruction pointer for the program.
 * @param value_to_add the integer value to add to the numeric value contained in the bank.
 * @return whether the instruction executed successfully.
 */
bool add_value(Program *program, Parameters *parameters, InstructionPointer *instruction_pointer, int value_to_add);

#endif