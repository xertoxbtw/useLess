#include "std.h"
#include <math.h>
#include <stdio.h>

node_t *
std_math_add (scope_t **scope, node_t *arguments, node_t *statements)
{
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
            error_argument_type ("add", current->type, type_number);
    }
    return node_new_number (NULL, result);
}

node_t *
std_math_sub (scope_t **scope, node_t *arguments, node_t *statements)
{
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
            error_argument_type ("add", current->type, type_number);
    }
    return node_new_number (NULL, result);
}

node_t *
std_math_mul (scope_t **scope, node_t *arguments, node_t *statements)
{
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
            error_argument_type ("sub", current->type, type_number);
    }
    return node_new_number (NULL, result);
}

node_t *
std_math_div (scope_t **scope, node_t *arguments, node_t *statements)
{
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
            error_argument_type ("div", current->type, type_number);
    }
    return node_new_number (NULL, result);
}

node_t *
std_math_mod (scope_t **scope, node_t *arguments, node_t *statements)
{
    if (arguments->children_count == 2)
    {
        node_t *a = node_evaluate (scope, arguments->children[ 0 ]);
        node_t *b = node_evaluate (scope, arguments->children[ 1 ]);

        if (a->type == type_number && b->type == type_number)
        {
            return node_new_number (
                NULL, (i32)a->value.number % (i32)b->value.number);
        }
        else
            error_argument_type (
                "mod", a->type == type_number ? b->type : a->type, type_number);
    }
    else
        error_argument_count ("mod", arguments->children_count, 2);
    return NULL;
}

node_t *
std_math_pow (scope_t **scope, node_t *arguments, node_t *statements)
{
    if (arguments->children_count == 2)
    {
        node_t *a = node_evaluate (scope, arguments->children[ 0 ]);
        node_t *b = node_evaluate (scope, arguments->children[ 1 ]);

        if (a->type == type_number && b->type == type_number)
        {
            return node_new_number (NULL,
                                    powf (a->value.number, b->value.number));
        }
        else
            error_argument_type (
                "pow", a->type == type_number ? b->type : a->type, type_number);
    }
    else
        error_argument_count ("pow", arguments->children_count, 2);
    return NULL;
}
