#include "std.h"
#include <string.h>
#define STEP_SIZE 32

char *
str_copy (const char *base)
{
    u32 len = strlen (base);
    char *str = xcalloc (len + 1, sizeof (char));
    strncpy (str, base, len);
    return str;
}

node_t *
std_string_split (scope_t **scope, node_t *arguments, node_t *statements)
{
    node_t *root = node_new_list_data (NULL);
    if (arguments->children_count == 2)
    {
        node_t *str_node = node_evaluate (scope, arguments->children[ 0 ]);
        node_t *delim_node = node_evaluate (scope, arguments->children[ 1 ]);
        if (str_node->type == type_string && delim_node->type == type_string)
        {
            char *str = str_copy (str_node->value.string);
            char *token = strtok (str, delim_node->value.string);
            while (token != NULL)
            {
                node_new_string_raw (root, token);
                token = strtok (NULL, delim_node->value.string);
            }

            return root;
        }
        else
            error_argument_type ("string.split",
                                 str_node->type == type_string
                                     ? delim_node->type
                                     : str_node->type,
                                 type_string);
    }
    else
        error_argument_count ("string.split", arguments->children_count, 2);
    return NULL;
}

node_t *
std_string_replace (scope_t **scope, node_t *arguments, node_t *statements)
{
    char *buffer = NULL;
    return node_new_string_raw (NULL, buffer);
}

node_t *
std_string_append (scope_t **scope, node_t *arguments, node_t *statements)
{
    char *buffer = xcalloc (1, sizeof (char));
    u32 buffer_len = 0;
    for (u32 i = 0; i < arguments->children_count; i++)
    {
        node_t *current = node_evaluate (scope, arguments->children[ i ]);
        if (current->type == type_string)
        {
            u32 start_index = buffer_len;
            buffer_len += strlen (current->value.string);
            buffer = xreallocarray (buffer, buffer_len + 1, sizeof (char));
            strncpy (buffer + start_index, current->value.string,
                     strlen (current->value.string));
        }
        else
            error_argument_type ("string.append", current->type, type_string);
    }
    return node_new_string_raw (NULL, buffer);
}
