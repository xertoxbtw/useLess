#include "std.h"
#include <stdio.h>

node_t *
std_if (scope_t **scope, node_t *arguments, node_t *statements)
{

    bool isTrue = true;
    for (u32 i = 0; i < arguments->children_count && isTrue; i++)
    {
        node_t *result = node_evaluate (scope, arguments->children[ i ]);
        if (result->type == type_number && result->value.number != 0)
        {
        }
        else
            isTrue = false;
    }

    scope[ 0 ]->flag_if_failed = !isTrue;
    if (isTrue)
    {
        scope[ 0 ] = scope_push (scope[ 0 ]);
        node_t *result_a = node_evaluate (scope, statements);
        node_t *result_b = scope[ 0 ]->node_return;
        scope[ 0 ] = scope_pop (scope[ 0 ]);
        scope[ 0 ]->node_return = result_b;
        return result_a;
    }

    return NULL;
}

node_t *
std_elif (scope_t **scope, node_t *arguments, node_t *statements)
{
    if (!scope[ 0 ]->flag_if_failed)
        return NULL;

    bool isTrue = true;
    for (u32 i = 0; i < arguments->children_count && isTrue; i++)
    {
        node_t *result = node_evaluate (scope, arguments->children[ i ]);
        if (result->type == type_number && result->value.number != 0)
        {
        }
        else
            isTrue = false;
    }

    scope[ 0 ]->flag_if_failed = !isTrue;
    if (isTrue)
    {
        scope[ 0 ] = scope_push (scope[ 0 ]);
        node_t *result_a = node_evaluate (scope, statements);
        node_t *result_b = scope[ 0 ]->node_return;
        scope[ 0 ] = scope_pop (scope[ 0 ]);
        scope[ 0 ]->node_return = result_b;
        return result_a;
    }

    return NULL;
}

node_t *
std_equal (scope_t **scope, node_t *arguments, node_t *statements)
{
    if (arguments->children_count == 2)
    {
        node_t *a = node_evaluate (scope, arguments->children[ 0 ]);
        node_t *b = node_evaluate (scope, arguments->children[ 1 ]);
        if (a->type == b->type)
        {
            if (a->type == type_number)
            {
                return node_new_number (NULL,
                                        a->value.number == b->value.number);
            }
            else if (a->type == type_string)
            {
                return node_new_number (
                    NULL, strcmp (a->value.string, b->value.string) == 0);
            }
            else
            {
                error_argument_type ("equal", a->type, type_number);
            }
        }
        else
            error_custom ("equal", "Both arguments should have the same type");
    }
    else
        error_argument_count ("equal", arguments->children_count, 2);
    return NULL;
}

node_t *
std_not (scope_t **scope, node_t *arguments, node_t *statements)
{
    node_t *result = std_equal (scope, arguments, statements);
    return node_new_number (NULL, !((u32)result->value.number));
}

node_t *
std_greater (scope_t **scope, node_t *arguments, node_t *statements)
{
    if (arguments->children_count == 2)
    {
        node_t *a = node_evaluate (scope, arguments->children[ 0 ]);
        node_t *b = node_evaluate (scope, arguments->children[ 1 ]);
        if (a->type == type_number && a->type == b->type)
        {
            return node_new_number (NULL, a->value.number > b->value.number);
        }
        else
            error_argument_type ("greater",
                                 a->type == type_number ? b->type : a->type,
                                 type_number);
    }
    else
        error_argument_count ("greater", arguments->children_count, 2);
    return NULL;
}
node_t *
std_less (scope_t **scope, node_t *arguments, node_t *statements)
{
    if (arguments->children_count == 2)
    {
        node_t *a = node_evaluate (scope, arguments->children[ 0 ]);
        node_t *b = node_evaluate (scope, arguments->children[ 1 ]);
        if (a->type == type_number && a->type == b->type)
        {
            return node_new_number (NULL, a->value.number < b->value.number);
        }
        else
            error_argument_type ("less",
                                 a->type == type_number ? b->type : a->type,
                                 type_number);
    }
    else
        error_argument_count ("less", arguments->children_count, 2);
    return NULL;
}
node_t *
std_greater_equal (scope_t **scope, node_t *arguments, node_t *statements)
{
    if (arguments->children_count == 2)
    {
        node_t *a = node_evaluate (scope, arguments->children[ 0 ]);
        node_t *b = node_evaluate (scope, arguments->children[ 1 ]);
        if (a->type == type_number && a->type == b->type)
        {
            return node_new_number (NULL, a->value.number >= b->value.number);
        }
        else
            error_argument_type ("greater_equal",
                                 a->type == type_number ? b->type : a->type,
                                 type_number);
    }
    else
        error_argument_count ("greater_equal", arguments->children_count, 2);
    return NULL;
}
node_t *
std_less_equal (scope_t **scope, node_t *arguments, node_t *statements)
{
    if (arguments->children_count == 2)
    {
        node_t *a = node_evaluate (scope, arguments->children[ 0 ]);
        node_t *b = node_evaluate (scope, arguments->children[ 1 ]);
        if (a->type == type_number && a->type == b->type)
        {
            return node_new_number (NULL, a->value.number <= b->value.number);
        }
        else
            error_argument_type ("less_equal",
                                 a->type == type_number ? b->type : a->type,
                                 type_number);
    }
    else
        error_argument_count ("less_equal", arguments->children_count, 2);
    return NULL;
}
