#include "lexer.h"
#include "runtime.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *
remove_trivial_chars (const char *buffer, u64 *len)
{
    u64 buffer_len = strlen (buffer);
    u64 index = 0;
    char *tmp = xcalloc (buffer_len + 1, sizeof (char));
    bool isQuoted = false, commented = false;

    for (u64 i = 0; i < buffer_len; i++)
    {
        if (!commented && !isQuoted && buffer[ i ] == '#')
        {
            commented = true;
        }
        if (!commented)
        {
            if (buffer[ i ] == '"')
            {
                isQuoted = !isQuoted;
            }
            if (buffer[ i ] != '\t' && buffer[ i ] != '\n'
                && buffer[ i ] != ' ')
            {
                tmp[ index++ ] = buffer[ i ];
            }
            else if (buffer[ i ] == ' ' && isQuoted)
                tmp[ index++ ] = buffer[ i ];
        }
        else if (buffer[ i ] == '\n')
            commented = false;
    }

    *len = index + 1;
    return tmp;
}

void
lexer_add (lexer_result_t *result, char *str, lexer_type type)
{
    if (result->entries != NULL)
        result->entries = xreallocarray (result->entries, result->count + 1,
                                         sizeof (lexer_entry_t));
    else
        result->entries = xcalloc (1, sizeof (lexer_entry_t));

    lexer_entry_t *current = &result->entries[ result->count++ ];
    current->content = str;
    current->type = type;
}

lexer_result_t *
lexer (const char *buffer_input)
{
    lexer_result_t *result = lexer_tokenize (buffer_input);
    if (lexer_check (result))
        return result;
    return NULL;
}

lexer_result_t *
lexer_tokenize (const char *buffer_input)
{
    lexer_result_t *result = xcalloc (1, sizeof (lexer_result_t));
    u64 len = 0;
    char *buffer = remove_trivial_chars (buffer_input, &len);

    u64 start_index = 0;
    bool isQuoted = false;
    for (u64 i = 0; i < len; i++)
    {
        if (buffer[ i ] == '"')
        {
            isQuoted = !isQuoted;
        }
        for (u32 key = 0; key < keys_count; key++)
        {
            if (strncmp (buffer + i, keys[ key ].key, strlen (keys[ key ].key))
                    == 0
                && !isQuoted)
            {
                i32 local_len = i - start_index;
                if (local_len > 0)
                {
                    char *tmp = xcalloc (local_len + 1, sizeof (char));
                    strncpy (tmp, buffer + start_index, local_len);

                    if (tmp[ 0 ] == '"')
                        lexer_add (result, tmp, lexer_string);
                    else if (tmp[ 0 ] >= '0' && tmp[ 0 ] <= '9')
                        lexer_add (result, tmp, lexer_number);
                    else
                        lexer_add (result, tmp, lexer_symbol);
                }

                // Add Key
                char *key_buffer
                    = xcalloc (strlen (keys[ key ].key) + 1, sizeof (char));
                strncpy (key_buffer, keys[ key ].key, strlen (keys[ key ].key));
                lexer_add (result, key_buffer, lexer_key);

                u32 key_len = strlen (keys[ key ].key);
                if (key_len > 1)
                {
                    i += strlen (keys[ key ].key) - 1;
                    start_index = i + 1;
                }
                else
                    start_index = i + 1;
				break;
            }
        }
    }
    free (buffer);
    return result;
}

bool
lexer_check (lexer_result_t *lexer_result)
{
    i32 brackets_count_normal = 0;
    i32 brackets_count_square = 0;
    i32 brackets_count_curly = 0;

    for (u32 i = 0; i < lexer_result->count; i++)
    {
    }

    if (brackets_count_normal != 0 || brackets_count_square != 0
        || brackets_count_curly)
        return false;
    return true;
}

void
lexer_free (lexer_result_t *result)
{
    for (u32 i = 0; i < result->count; i++)
    {
        free (result->entries[ i ].content);
    }
    free (result->entries);
    free (result);
}
