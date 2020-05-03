#ifndef SNOWFLAKE_RUN_INSTRUCTION_BASIC_H
#define SNOWFLAKE_RUN_INSTRUCTION_BASIC_H
#include <stdbool.h>
#include "core/program.h"
#include "core/instructions.h"

/**
 * Implement no-op instructions (eg. !!!, ###).
 * 
 * @param program the snowflake program.
 * @param parameters the parameters for the instruction.
 * @param instruction_pointer the current instruction pointer for the program.
 * @return whether the instruction executed successfully.
 */
bool instruction_noop(Program *program, Parameters *parameters, InstructionPointer *instruction_pointer);

/**
 * Implement DEL instruction.
 * 
 * @param program the snowflake program.
 * @param parameters the parameters for the instruction.
 * @param instruction_pointer the current instruction pointer for the program.
 * @return whether the instruction executed successfully.
 */
bool instruction_delete(Program *program, Parameters *parameters, InstructionPointer *instruction_pointer);

/**
 * Implement TYP instruction.
 * 
 * @param program the snowflake program.
 * @param parameters the parameters for the instruction.
 * @param instruction_pointer the current instruction pointer for the program.
 * @return whether the instruction executed successfully.
 */
bool instruction_type(Program *program, Parameters *parameters, InstructionPointer *instruction_pointer);

/**
 * Implement = instruction.
 * 
 * @param program the snowflake program.
 * @param parameters the parameters for the instruction.
 * @param instruction_pointer the current instruction pointer for the program.
 * @return whether the instruction executed successfully.
 */
bool instruction_copy(Program *program, Parameters *parameters, InstructionPointer *instruction_pointer);

/**
 * Implement TO instruction.
 * 
 * @param program the snowflake program.
 * @param parameters the parameters for the instruction.
 * @param instruction_pointer the current instruction pointer for the program.
 * @return whether the instruction executed successfully.
 */
bool instruction_convert(Program *program, Parameters *parameters, InstructionPointer *instruction_pointer);

/**
 * Implement LEN instruction.
 * 
 * @param program the snowflake program.
 * @param parameters the parameters for the instruction.
 * @param instruction_pointer the current instruction pointer for the program.
 * @return whether the instruction executed successfully.
 */
bool instruction_length(Program *program, Parameters *parameters, InstructionPointer *instruction_pointer);

#endif