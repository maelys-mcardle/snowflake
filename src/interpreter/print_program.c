#include <stdlib.h>
#include <math.h>
#include "platforms/logging.h"
#include "core/devices.h"
#include "core/array.h"
#include "core/string.h"
#include "print/print_instruction.h"
#include "print_program.h"

/** 
 * Gets the entire stringified Snowflake program.
 *
 * @param program the program to print out.
 * @param show_line_number whether to show line numbers.
 * @return the stringified Snowflake program.
 */
char *get_printable_program(Program *program, bool show_line_number)
{
    log_debug("Printing program...\n");
    char *program_string = NULL;

    if (program != NULL && 
        program->instructions != NULL)
    {
        InstructionCount total_instructions = get_instruction_count(program);
        char *line_number_format = (show_line_number) ?
            get_printable_line_number_format(total_instructions):
            NULL;

        for (InstructionPointer i = 0; i < total_instructions; i++)
        {
            char *instruction_line = get_printable_instruction_line(program, i, line_number_format);
            if (instruction_line != NULL)
            {
                program_string = append_string(program_string, instruction_line);
                free(instruction_line);
            }
        }

        if (line_number_format != NULL)
        {
            free(line_number_format);
        }
    }

    return program_string; 
}

/**
 * Gets the stringified instruction with optional line number.
 * 
 * @param program the snowflake program.
 * @param instruction_pointer the instruction pointer to get the instruction from.
 * @param line_number_format the format for displaying the line number.
 * @return the stringified instruction.
 */
char *get_printable_instruction_line(Program *program, InstructionPointer instruction_pointer, char *line_number_format)
{
    char *line = new_string("");
    if (line_number_format != NULL)
    {
        char *line_number_string = get_printable_line_number(line_number_format, instruction_pointer);
        if (line_number_string != NULL)
        {
            line = append_string(line, line_number_string);
            free(line_number_string);
        }
    }

    Instruction *instruction = get_instruction(program, instruction_pointer);
    char *instruction_string = get_printable_instruction(program, instruction);
    if (instruction_string != NULL)
    {
        line = append_string(line, instruction_string);
        free(instruction_string);
    }

    return append_string(line, "\n");
}

/**
 * Gets the stringified line number.
 * 
 * @param string_format format for displaying the line number.
 * @param current_line current line index.
 * @return stringified line number.
 */
char *get_printable_line_number(char *string_format, InstructionCount current_line)
{
    if (string_format == NULL)
    {
        return NULL;
    }

    char line_number[MAX_CHARACTERS_FOR_SHORT_INT + 2];
    snprintf(line_number, sizeof(line_number), string_format, current_line + 1);
    return new_string(line_number);
}

/**
 * Gets the format for printing the line number.
 * 
 * It calculates how many leading zeroes to show in the line number,
 * so that the width of the line number is constant throughout displaying
 * all of the program code. So a thousand-line program would have three
 * leading zeroes.
 * 
 * @param total_lines the total number of lines for the program.
 * @return the printf-compatible string format for the line number.
 */
char *get_printable_line_number_format(InstructionCount total_lines)
{
    unsigned int digits_wide = 1;
    char string_format[MAX_CHARACTERS_FOR_SHORT_INT + 2];

    while (total_lines + 1 > pow(10, digits_wide))
    {
        digits_wide++; 
    }
    
    snprintf(string_format, sizeof(string_format), "%%0%ii ", digits_wide);
    return new_string(string_format);
}
