#include "std.h"

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
