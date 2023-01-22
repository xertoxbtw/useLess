#include "std.h"

node_t *
std_string_format (scope_t **scope, node_t *node)
{
    node_t *arguments = node->children[ 1 ];
    char *buffer = xcalloc (1, sizeof (char));
    u32 buffer_len = 0;

    for (u32 i = 0; i < arguments->children_count; i++)
    {
        node_t *value = node_evaluate (scope, arguments->children[ i ]);
        buffer_len += strlen (value->value.string);
        buffer = xreallocarray (buffer, buffer_len + 1, sizeof (char));
        strcat (buffer, value->value.string);
    }

    return node_new_string_raw (NULL, buffer);
}
