#include "std.h"

node_t *
std_add (scope_t **scope, node_t *node)
{
    node_t *arguments = node->children[ 1 ];
    double result = 0;
    for (u32 i = 0; i < arguments->children_count; i++)
    {
        node_t *current = node_evaluate (scope, arguments->children[ i ]);
        if (current->type == type_number)
        {
            if (i == 0)
                result = current->value.number;
            else
                result += current->value.number;
        }
        else
            exit (1); // Type Error
    }
    return node_new_number (NULL, result);
}

node_t *
std_sub (scope_t **scope, node_t *node)
{
    node_t *arguments = node->children[ 1 ];
    double result = 0;
    for (u32 i = 0; i < arguments->children_count; i++)
    {
        node_t *current = node_evaluate (scope, arguments->children[ i ]);
        if (current->type == type_number)
        {
            if (i == 0)
                result = current->value.number;
            else
                result -= current->value.number;
        }
        else
            exit (1); // Type Error
    }
    return node_new_number (NULL, result);
}

node_t *
std_mul (scope_t **scope, node_t *node)
{
    node_t *arguments = node->children[ 1 ];
    double result = 0;
    for (u32 i = 0; i < arguments->children_count; i++)
    {
        node_t *current = node_evaluate (scope, arguments->children[ i ]);
        if (current->type == type_number)
        {
            if (i == 0)
                result = current->value.number;
            else
                result *= current->value.number;
        }
        else
            exit (1); // Type Error
    }
    return node_new_number (NULL, result);
}

node_t *
std_div (scope_t **scope, node_t *node)
{
    node_t *arguments = node->children[ 1 ];
    double result = 0;
    for (u32 i = 0; i < arguments->children_count; i++)
    {
        node_t *current = node_evaluate (scope, arguments->children[ i ]);
        if (current->type == type_number)
        {
            if (i == 0)
                result = current->value.number;
            else
                result /= current->value.number;
        }
        else
            exit (1); // Type Error
    }
    return node_new_number (NULL, result);
}

