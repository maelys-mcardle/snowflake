#ifndef SNOWFLAKE_RUN_INSTRUCTION_IO_H
#define SNOWFLAKE_RUN_INSTRUCTION_IO_H
#include <stdbool.h>
#include "core/program.h"
#include "core/instructions.h"

/**
 * Implement << instruction.
 * 
 * @param program the snowflake program.
 * @param parameters the parameters for the instruction.
 * @param instruction_pointer the current instruction pointer for the program.
 * @return whether the instruction executed successfully.
 */
bool instruction_output(Program *program, Parameters *parameters, InstructionPointer *instruction_pointer);

/**
 * Implement >> instruction.
 * 
 * @param program the snowflake program.
 * @param parameters the parameters for the instruction.
 * @param instruction_pointer the current instruction pointer for the program.
 * @return whether the instruction executed successfully.
 */
bool instruction_input(Program *program, Parameters *parameters, InstructionPointer *instruction_pointer);

#endif