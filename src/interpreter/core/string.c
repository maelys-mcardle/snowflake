#include <stdlib.h>
#include <string.h>
#include "core/string.h"

/**
 * Allocates memory for a string.
 * 
 * @param original_string string to store in the allocated memory.
 * @return the allocated string.
 */
char *new_string(char *original_string)
{
    return append_string(NULL, original_string);
}

/**
 * Appends a string to another string.
 * Memory is reallocated to fit the combined string.
 * 
 * @param full_text the main text that will be appended.
 * @param to_append the string that will be appended.
 * @return the combined text.
 */
char *append_string(char *full_text, char *to_append)
{
    if (to_append != NULL)
    {
        size_t new_size = 
            ((full_text != NULL) ? strlen(full_text) : 0 ) + 
            strlen(to_append) + 1;
        
        char *appended_full_text = (char *) realloc(full_text, new_size);

        if (appended_full_text != NULL)
        {
            if(full_text != NULL)
            {
                strncat(appended_full_text, to_append, new_size - 1);
                appended_full_text[new_size -1] = CHAR_END_STRING;
                return appended_full_text;
            }
            else
            {
                memcpy(appended_full_text, to_append, new_size - 1);
                appended_full_text[new_size -1] = CHAR_END_STRING;
                return appended_full_text;
            }
        } 
    }

    return full_text;
}

/**
 * Join two strings together.
 * 
 * @param left_string the left string to join.
 * @param right_string the right string to join.
 * @return the joined strings.
 */
char *join_strings(char *left_string, char *right_string)
{
    char *joined_string = new_string("");

    if (left_string != NULL)
    {
        joined_string = append_string(joined_string, left_string);
    }

    if (left_string != NULL && right_string != NULL)
    {
        joined_string = append_string(joined_string, " ");
    }

    if (right_string != NULL)
    {
        joined_string = append_string(joined_string, right_string);
    }

    return joined_string;
}

/**
 * Strip the whitespace at the end of the string.
 * 
 * @param string string to edit.
 * @param max_string_length maximum length of the string.
 * @return whether whitespace was removed.
 */
bool strip_end_whitespace(char *string, int max_string_length)
{
    int index = 0;
    int last_non_whitespace_character = -1;

    // Find the last non-whitespace character.
    for (index = 0; index < max_string_length; index++)
    {
        char character = string[index];
        if (character == CHAR_END_STRING)
        {
            break;
        }
        else if (!is_whitespace(character))
        {
            last_non_whitespace_character = index;
        }
    }

    // Whitespace removed.
    if (last_non_whitespace_character == -1 && max_string_length > 0)
    {
        string[0] = CHAR_END_STRING;
        return true;
    }
    else if (last_non_whitespace_character + 1 < index)
    {
        string[last_non_whitespace_character + 1] = CHAR_END_STRING;
        return true;
    }

    // No whitespace removed.
    return false;
}

/**
 * Identifies whether the character is whitespace.
 * 
 * @param character character to identify.
 * @return whether the character is whitespace.
 */
bool is_whitespace(char character)
{
    switch (character)
    {
        case CHAR_NEWLINE:
        case CHAR_SPACE:
        case CHAR_TAB:
            return true;
        default:
            return false;
    }
}

/**
 * Identifies whether the character is the end of a string.
 * 
 * @param character character to identify.
 * @return whether the character is the end of a string.
 */
bool is_string_end(char character)
{
    switch (character)
    {
        case CHAR_NEWLINE:
        case CHAR_END_STRING:
            return true;
        default:
            return false;
    } 
}

/**
 * Discards the comment on the line. 
 * 
 * @param line line potentially containing the comment.
 * @param max_line_length maximum length of the line.
 * @return true if comment was removed, false otherwise.
 */
bool strip_comment(char *line, int max_line_length)
{
    bool last_char_is_semicolon = false;

    // Remove anything that follows the ";;"
    for (int index = 0; index < max_line_length; index++)
    {
        char character = line[index];

        // Stop at newline or break.
        if (is_string_end(character))
        {
            return false;
        }

        // Second ";" found.
        else if (character == CHAR_COMMENT &&
            last_char_is_semicolon)
        {

            // Set end the line here.
            line[index-1] = CHAR_END_STRING;
            return true;
        }

        // First ";" found.
        else if (character == CHAR_COMMENT)
        {
            last_char_is_semicolon = true;
        }

        // Any other character found.
        else
        {
            last_char_is_semicolon = false;
        }
    }

    return false;
}

/**
 * Identifies whether the string contains a period.
 * 
 * @param string the string that potentially contains a period.
 * @return whether the string contained a period.
 */
bool has_period(char *string)
{
    return (string != NULL && strchr(string, '.') != NULL);
}
