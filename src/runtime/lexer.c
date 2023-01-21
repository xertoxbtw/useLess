#include "lexer.h"
#include "runtime.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Todo: Complete Key List
char keys[] = {'=', ';', '(', ')', '{', '}', '[', ']', ',', '%', '&'};

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
    lexer_result_t *tmp = lexer_tokenize (buffer_input);
    lexer_result_t *result = lexer_process (tmp);

    free (tmp->entries);
    free (tmp);

    return result;
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
        for (u32 key = 0; key < sizeof (keys) / sizeof (char); key++)
        {
            if (buffer[ i ] == keys[ key ] && !isQuoted)
            {
                u64 local_len = i - start_index;
                if (local_len != 0)
                {
                    char *tmp = xcalloc (local_len + 1, sizeof (char));
                    strncpy (tmp, buffer + start_index, local_len);

                    // TODO: Simple Typecheck
                    if (tmp[ 0 ] == '"')
                        lexer_add (result, tmp, lexer_string);
                    else
                        lexer_add (result, tmp, lexer_symbol);
                }

                // Add Key
                char *key_buffer = xcalloc (2, sizeof (char));
                key_buffer[ 0 ] = keys[ key ];
                lexer_add (result, key_buffer, lexer_key);

                start_index = i + 1;
            }
        }
    }
    free (buffer);
    return result;
}

lexer_result_t *
lexer_process (lexer_result_t *in)
{
    lexer_result_t *result = xcalloc (1, sizeof (lexer_result_t));
    u32 close_counter = 0;

    for (u32 i = 0; i < in->count; i++)
    {
        /*
        if (in->entries[ i ].type == lexer_key)
        {
            if (in->entries[ i ].content[ 0 ] == ')' && close_counter != 0)
            {
                close_counter--;
                char *tmp = xcalloc (2, sizeof (char));
                tmp[ 0 ] = ')';
                lexer_add (result, tmp, lexer_key);
                lexer_add (result, in->entries[ i ].content,
                           in->entries[ i ].type);
            }
            else
                lexer_add (result, in->entries[ i ].content,
                           in->entries[ i ].type);
        }
        else if (in->entries[ i ].type == lexer_symbol)
        {
            if ((i32)i > 0 && i + 1 < in->count - 1
                && in->entries[ i - 1 ].type == lexer_key
                && (in->entries[ i - 1 ].content[ 0 ] == '('
                    || in->entries[ i - 1 ].content[ 0 ] == ',')
                && in->entries[ i + 1 ].type == lexer_key
                && in->entries[ i + 1 ].content[ 0 ] == '(')
            {
                close_counter++;
                char *tmp = xcalloc (2, sizeof (char));
                tmp[ 0 ] = '(';
                lexer_add (result, tmp, lexer_key);
            }
            lexer_add (result, in->entries[ i ].content, in->entries[ i ].type);
        }
        else*/
        lexer_add (result, in->entries[ i ].content, in->entries[ i ].type);
    }

    return result;
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
