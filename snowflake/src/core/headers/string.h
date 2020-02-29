#ifndef SNOWFLAKE_STRING_H
#define SNOWFLAKE_STRING_H

#include <stdbool.h>
#define CHAR_COMMENT ';'
#define CHAR_NEWLINE '\n'
#define CHAR_SPACE ' '
#define CHAR_TAB '\t'
#define CHAR_END_STRING '\0'

bool is_whitespace(char character);
bool is_string_end(char character);
bool strip_end_whitespace(char *string, int max_string_length);
bool strip_comment(char *line, int max_line_length);

#endif