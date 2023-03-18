#include "std.h"
#include <stdio.h>
#include <string.h>

node_t *
std_types_string_check (scope_t **scope, node_t *arguments, node_t *statements)
{
    if (arguments->children_count != 1)
        error_argument_count ("string?", arguments->children_count, 1);
    node_t *node = node_evaluate (scope, arguments->children[ 0 ]);
    return node_new_number (NULL, node->type == type_string);
}

node_t *
std_types_number_check (scope_t **scope, node_t *arguments, node_t *statements)
{
    if (arguments->children_count != 1)
        error_argument_count ("number?", arguments->children_count, 1);
    node_t *node = node_evaluate (scope, arguments->children[ 0 ]);
    return node_new_number (NULL, node->type == type_number);
}

node_t *
std_types_list_check (scope_t **scope, node_t *arguments, node_t *statements)
{
    if (arguments->children_count != 1)
        error_argument_count ("list?", arguments->children_count, 1);
    node_t *node = node_evaluate (scope, arguments->children[ 0 ]);
    return node_new_number (NULL, node->type == type_list_data);
}

node_t *
std_types_string (scope_t **scope, node_t *arguments, node_t *statements)
{
    if (arguments->children_count == 1)
    {
        node_t *value = node_evaluate (scope, arguments->children[ 0 ]);
        if (value->type == type_string)
        {
            return node_new_string_raw (NULL, value->value.string);
        }
        else if (value->type == type_number)
        {
            char *buffer = xcalloc (64, sizeof (char));
            sprintf (buffer, "%f", value->value.number);
            return node_new_string_raw (NULL, buffer);
        }
        else
            error_argument_type ("string", value->type, type_string);
    }
    else
        error_argument_count ("string", arguments->children_count, 1);
    return NULL;
}

node_t *
std_types_number (scope_t **scope, node_t *arguments, node_t *statements)
{
    if (arguments->children_count == 1)
    {
        node_t *value = node_evaluate (scope, arguments->children[ 0 ]);
        if (value->type == type_string)
        {
            return node_new_number (NULL, atof (value->value.string));
        }
        else if (value->type == type_number)
        {
            return node_new_number (NULL, value->value.number);
        }
        else
            error_argument_type ("number", value->type, type_number);
    }
    else
        error_argument_count ("number", arguments->children_count, 1);
    return NULL;
}
