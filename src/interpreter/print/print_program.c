#include <stdlib.h>
#include <math.h>
#include "platforms/logging.h"
#include "core/devices.h"
#include "core/array.h"
#include "core/string.h"
#include "print/print_program.h"
#include "print/print_instruction.h"

/* Prints an entire Snowflake program. */
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

char *get_printable_line_number_format(InstructionCount total_lines)
{
    unsigned int digits_wide = 1;
    char string_format[MAX_IDENTIFIER_SIZE + 2];

    while (total_lines + 1 > pow(10, digits_wide))
    {
        digits_wide++; 
    }
    
    snprintf(string_format, sizeof(string_format), "%%0%ii ", digits_wide);
    return new_string(string_format);
}

char *get_printable_line_number(char *string_format, InstructionCount current_line)
{
    if (string_format == NULL)
    {
        return NULL;
    }

    char line_number[MAX_IDENTIFIER_SIZE + 2];
    snprintf(line_number, sizeof(line_number), string_format, current_line + 1);
    return new_string(line_number);
}

