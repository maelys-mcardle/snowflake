#ifndef SNOWFLAKE_PRINT_INSTRUCTION_H
#define SNOWFLAKE_PRINT_INSTRUCTION_H
#include <stdbool.h>
#include "core/program.h"
#include "core/instructions.h"

// Maximum length for an short integer.
#define MAX_CHARACTERS_FOR_SHORT_INT 12

/** 
 * Gets a Snowflake instruction with parameters as a string.
 *
 * @param program the entire program.
 * @param instruction the instruction to display. 
 */
char *get_printable_instruction(Program *program, Instruction *instruction);

/**
 * Gets a parameter as a string, if one is defined.
 * 
 * @param program the snowflake program.
 * @param current_instruction the code for the current instruction.
 * @param type the parameter type.
 * @param value the parameter value.
 * @return True if a parameter is defined; false if not.
 */
char *get_printable_parameter(Program *program, InstructionCode current_instruction, ParameterType type, ParameterValue value);

/**
 * Get the stringified identifier.
 * 
 * These identifiers can be labels, banks, etc. If an instruction was used to name
 * these identifiers, it tries to locate it so that what's displayed is this name.
 * If the identifier (eg. label, bank) was never given a name, then it's numeric
 * value is displayed.
 * 
 * @param program the snowflake program.
 * @param current_instruction the code for the current instruction.
 * @param naming_instruction the code for the instruction that names this identifier.
 * @param target_identifier the identifier defined by the naming instruction.
 * @param format the format to display the identifier.
 * @return the stringified identifier.
 */
char *get_printable_identifier(Program *program, InstructionCode current_instruction, InstructionCode naming_instruction, int target_identifier, char *format);

/** 
 * Gets the stringified device, if one is defined.
 * 
 * @param device the device type.
 * @return The stringified device.
 */
char *get_printable_device(int device);

/** 
 * Gets the stringified type, if one is defined.
 * 
 * @param type the type type.
 * @return The stringified type.
 */
char *get_printable_type(int type);

/**
 * Locates the name for the target identifier in the program.
 * 
 * @param program the program.
 * @param naming_instruction the instruction that assigns a name to the identifier.
 * @param target_identifier the identifier to look for that might have been given a name.
 * @return the name for the parameter. NULL if no name was found.
 */
char *get_name(Program *program, InstructionCode naming_instruction, int target_identifier);

#endif