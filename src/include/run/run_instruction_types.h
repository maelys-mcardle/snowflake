#ifndef SNOWFLAKE_RUN_INSTRUCTION_TYPES_H
#define SNOWFLAKE_RUN_INSTRUCTION_TYPES_H
#include <stdbool.h>
#include "core/program.h"
#include "core/instructions.h"

/**
 * Implement VAR instruction.
 * 
 * @param program the snowflake program.
 * @param parameters the parameters for the instruction.
 * @param instruction_pointer the current instruction pointer for the program.
 * @return whether the instruction executed successfully.
 */
bool instruction_variable(Program *program, Parameters *parameters, InstructionPointer *instruction_pointer);

/**
 * Implement BLN instruction.
 * 
 * @param program the snowflake program.
 * @param parameters the parameters for the instruction.
 * @param instruction_pointer the current instruction pointer for the program.
 * @return whether the instruction executed successfully.
 */
bool instruction_boolean(Program *program, Parameters *parameters, InstructionPointer *instruction_pointer);

/**
 * Implement INT instruction.
 * 
 * @param program the snowflake program.
 * @param parameters the parameters for the instruction.
 * @param instruction_pointer the current instruction pointer for the program.
 * @return whether the instruction executed successfully.
 */
bool instruction_integer(Program *program, Parameters *parameters, InstructionPointer *instruction_pointer);

/**
 * Implement FLT instruction.
 * 
 * @param program the snowflake program.
 * @param parameters the parameters for the instruction.
 * @param instruction_pointer the current instruction pointer for the program.
 * @return whether the instruction executed successfully.
 */
bool instruction_float(Program *program, Parameters *parameters, InstructionPointer *instruction_pointer);

/**
 * Implement STR instruction.
 * 
 * @param program the snowflake program.
 * @param parameters the parameters for the instruction.
 * @param instruction_pointer the current instruction pointer for the program.
 * @return whether the instruction executed successfully.
 */
bool instruction_string(Program *program, Parameters *parameters, InstructionPointer *instruction_pointer);

/**
 * Implement [] instruction.
 * 
 * @param program the snowflake program.
 * @param parameters the parameters for the instruction.
 * @param instruction_pointer the current instruction pointer for the program.
 * @return whether the instruction executed successfully.
 */
bool instruction_array(Program *program, Parameters *parameters, InstructionPointer *instruction_pointer);

#endif