#include <stdlib.h>
#include <string.h>
#include "structures/string.h"

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

/* Discards the comment on the line. 
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

char *concatenate_strings(char *first, char *second, bool separate_with_space)
{
    // Compute the final size of the string.
    int concatenated_size =
        ((first != NULL) ? strlen(first) : 0) +
        ((second != NULL) ? strlen(second) : 0) +
        (separate_with_space ? 1 : 0) + 1;

    // Allocate memory for the string.
    char *output_string = malloc(concatenated_size);

    // Generate the string.
    output_string[0] = CHAR_END_STRING;
    if (first != NULL) strncat(output_string, first, concatenated_size);
    if (first != NULL && separate_with_space) strncat(output_string, " ", concatenated_size);
    if (second != NULL) strncat(output_string, second, concatenated_size);

    // Return generated string.
    return output_string;
}

bool has_period(char *string)
{
    return (string != NULL && strchr(string, '.') != NULL);
}