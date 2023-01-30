#include "std.h"
#define STEPS_SIZE 32

node_t *
std_string_format (scope_t **scope, node_t *node)
{
    node_t *arguments = node->children[ 1 ];
    if (arguments->children_count == 0)
        exit (1); // argument count error

    char *buffer = xcalloc (STEPS_SIZE + 1, sizeof (char));
    u32 buffer_index = 0, buffer_size = STEPS_SIZE;

    char *format = arguments->children[ 0 ]->value.string;
    u32 current_argument = 0;
    for (u32 i = 0; i < strlen (format); i++)
    {
        if (format[ i ] == '\\'
            && i + 1 < strlen (format) - 1) // Escape Character
        {
            switch (format[ i + 1 ])
            {
            case 'n':
                buffer[ buffer_index++ ] = '\n';
                break;
            case 't':
                buffer[ buffer_index++ ] = '\t';
                break;
            }
            i++;
        }
        else if (format[ i ] == '%' && i + 1 < strlen (format) - 1
                 && (format[ i + 1 ] == 'A'
                     || format[ i + 1 ] == 'a')) // Argument
        {
            if (current_argument + 1 < arguments->children_count)
            {
                node_t *current = node_evaluate (
                    scope, arguments->children[ current_argument + 1 ]);
                if (current->type == type_string)
                {
                }
                else if (current->type == type_number)
                {
                }
                else
                {
                    exit (1); // Error
                }
            }
            else
            {
                exit (1); // Error
            }
        }
        else
        {
            buffer[ buffer_index++ ] = format[ i ];
        }

        if (buffer_index > buffer_size - 1)
        {
            buffer_size += STEPS_SIZE;
            buffer = xreallocarray (buffer, buffer_size + 1, sizeof (char));
        }
    }

    return node_new_string_raw (NULL, buffer);
}
