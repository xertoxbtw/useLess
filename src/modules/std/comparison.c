#include "std.h"

node_t *
std_equal (scope_t **scope, node_t *node)
{
    u8 result = 0;

    if (node->children[ 1 ]->children_count != 2)
        exit (1); // argument count error
    node_t *a = node_evaluate (scope, node->children[ 1 ]->children[ 0 ]);

    node_t *b = node_evaluate (scope, node->children[ 1 ]->children[ 1 ]);

    if (a->type == b->type)
    {
        if (a->type == type_number)
        {
            result = (a->value.number == b->value.number);
        }
        else if (a->type == type_string)
        {
            if (strcmp (a->value.string, b->value.string) == 0)
                result = 1;

            else
                result = 0;
        }
        else
            result = 0;
    }
    else
        result = 0;

    return node_new_number (NULL, result);
}

node_t *
std_not (scope_t **scope, node_t *node)
{
    node_t *result = std_equal (scope, node);
    return node_new_number (NULL, !((u32)result->value.number));
}

node_t *
std_greater (scope_t **scope, node_t *node)
{
}

node_t *
std_less (scope_t **scope, node_t *node)
{
}

node_t *
std_greater_equal (scope_t **scope, node_t *node)
{
}

node_t *
std_less_equal (scope_t **scope, node_t *node)
{
}
