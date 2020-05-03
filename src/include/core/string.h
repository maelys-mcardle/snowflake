#ifndef SNOWFLAKE_STRING_H
#define SNOWFLAKE_STRING_H

#include <stdbool.h>
#define CHAR_COMMENT ';'
#define CHAR_NEWLINE '\n'
#define CHAR_SPACE ' '
#define CHAR_TAB '\t'
#define CHAR_END_STRING '\0'

/**
 * Allocates memory for a string.
 * 
 * @param original_string string to store in the allocated memory.
 * @return the allocated string.
 */
char *new_string(char *original_string);

/**
 * Appends a string to another string.
 * Memory is reallocated to fit the combined string.
 * 
 * @param full_text the main text that will be appended.
 * @param to_append the string that will be appended.
 * @return the combined text.
 */
char *append_string(char *full_text, char *to_append);

/**
 * Join two strings together.
 * 
 * @param left_string the left string to join.
 * @param right_string the right string to join.
 * @return the joined strings.
 */
char *join_strings(char *left_string, char *right_string);

/**
 * Identifies whether the character is whitespace.
 * 
 * @param character character to identify.
 * @return whether the character is whitespace.
 */
bool is_whitespace(char character);

/**
 * Identifies whether the character is the end of a string.
 * 
 * @param character character to identify.
 * @return whether the character is the end of a string.
 */
bool is_string_end(char character);

/**
 * Strip the whitespace at the end of the string.
 * 
 * @param string string to edit.
 * @param max_string_length maximum length of the string.
 * @return whether whitespace was removed.
 */
bool strip_end_whitespace(char *string, int max_string_length);

/**
 * Discards the comment on the line. 
 * 
 * @param line line potentially containing the comment.
 * @param max_line_length maximum length of the line.
 * @return true if comment was removed, false otherwise.
 */
bool strip_comment(char *line, int max_line_length);

/**
 * Identifies whether the string contains a period.
 * 
 * @param string the string that potentially contains a period.
 * @return whether the string contained a period.
 */
bool has_period(char *string);

#endif