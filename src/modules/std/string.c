#include "std.h"
#define STEP_SIZE 32

node_t *
std_string_format (scope_t **scope, node_t *arguments, node_t *statements)
{
    /*
    if (arguments->children_count == 0)
        error_argument_count ("string.format", arguments->children_count, 1);

    node_t *format = node_evaluate (scope, arguments->children[ 0 ]);
    if (format->type != type_string)
        error_argument_type ("string.format", format->type, type_string);

    char *format_string = format->value.string;
    u32 format_length = strlen (format_string);
    u32 buffer_size = STEP_SIZE, buffer_index = 0;
    char *buffer = xcalloc (buffer_size, sizeof (char));
    u32 node_index = 1;

    for (u32 i = 0; i < format_length; i++)
    {
        if (format_string[ i ] == '~' && i + 1 < format_length - 1
            && (format_string[ i + 1 ] == 'A' || format_string[ i + 1 ] == 'a'))
        {
            if (node_index < arguments->children_count - 1)
            {
                node_t *current = node_evaluate (
                    scope, arguments->children[ node_index++ ]);
                char *value = NULL;
                if (current->type == type_string)
                {
                    value = current->value.string;
                }
                else if (current->type == type_number)
                {
                }
                else
                {
                }
            }
            else
                error_argument_count ("string.format",
                                      arguments->children_count, node_index);

            i++;
        }
        else
        {
        }
        }*/

    return NULL;
}

node_t *
std_string_split (scope_t **scope, node_t *arguments, node_t *statements)
{
    return NULL;
}

node_t *
std_string_replace (scope_t **scope, node_t *arguments, node_t *statements)
{
    char *buffer = NULL;
    return node_new_string_raw (NULL, buffer);
}
