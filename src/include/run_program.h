#ifndef SNOWFLAKE_RUN_PROGRAM_H
#define SNOWFLAKE_RUN_PROGRAM_H
#include <stdbool.h>
#include "core/program.h"
#include "core/instructions.h"

/**
 * Typedef for the function that will execute an instruction.
 */
typedef bool (*InstructionFunction)(Program *, Parameters *, InstructionPointer *);

/**
 * Executes the snowflake program.
 * 
 * @param program the snowflake program to execute.
 */
int run_program(Program *program);

/**
 * Executes an individual instruction.
 * 
 * @param program the snowflake program.
 * @param instruction the instruction to execute.
 * @param instruction_pointer the current instruction pointer.
 * @return whether the instruction executed successfully.
 */
bool run_instruction(Program *program, Instruction *instruction, InstructionPointer *instruction_pointer);

#endif