#include "std.h"
#include <stdbool.h>
#include <stdio.h>
#include <time.h>

node_t *
std_assign (scope_t **scope, node_t *arguments, node_t *statements)
{
    if (arguments->children_count == 2)
    {
        if (arguments->children[ 0 ]->type == type_symbol)
        {
            symbol_t *sym
                = scope_lookup (*scope, arguments->children[ 0 ]->value.string);
            if (sym) // If already exists, override
            {
                node_t *node_new
                    = node_evaluate (scope, arguments->children[ 1 ]);
                sym->node = node_new;
            }
            else
            {
                sym = symbol_create (
                    arguments->children[ 0 ]->value.string,
                    node_evaluate (scope, arguments->children[ 1 ]));

                scope_add (*scope, sym);
            }
        }
        else
            error_argument_type ("assign", arguments->children[ 0 ]->type,
                                 type_symbol);
    }
    else
        error_argument_count ("assign", arguments->children_count, 2);

    return NULL;
}

node_t *
std_function (scope_t **scope, node_t *arguments, node_t *statements)
{
    node_t *node = node_new_list_symbol (NULL);
    node_insert (node, arguments);
    node_insert (node, statements);
    return node;
}

node_t *
std_include (scope_t **scope, node_t *arguments, node_t *statements)
{
    for (u32 i = 0; i < arguments->children_count; i++)
    {
        node_t *path = node_evaluate (scope, arguments->children[ i ]);

        if (path->type == type_string)
        {
            if (module_load (*scope, path->value.string))
            {
                error_custom ("Failed loading module \"%s\"",
                              path->value.string);
            }
        }
        else
            error_argument_type ("include", path->type, type_string);
    }
    return NULL;
}

node_t *
std_return (scope_t **scope, node_t *arguments, node_t *statements)
{
    if (arguments->children_count == 1)
    {
        node_t *value = node_evaluate (scope, arguments->children[ 0 ]);
        scope[ 0 ]->node_return = value;
        return value;
    }
    else
    {
        error_argument_count ("return", arguments->children_count, 1);
    }
    return NULL;
}

node_t *
std_random (scope_t **scope, node_t *arguments, node_t *statements)
{
    static bool std_random_seed_set = false;
    if (!std_random_seed_set)
    {
        srand (time (NULL));
        std_random_seed_set = true;
    }

    if (arguments->children_count == 0)
    {
        return node_new_number (NULL, rand ());
    }
    else if (arguments->children_count == 1)
    {
        node_t *max = node_evaluate (scope, arguments->children[ 0 ]);
        if (max->type == type_number)
        {
            return node_new_number (NULL,
                                    rand () % (i32)(max->value.number + 1));
        }
        else
            error_argument_type ("random", max->type, type_number);
    }
    else if (arguments->children_count == 2)
    {
        node_t *min = node_evaluate (scope, arguments->children[ 0 ]);
        node_t *max = node_evaluate (scope, arguments->children[ 1 ]);
        if (min->type == type_number && max->type == type_number)
        {
            return node_new_number (
                NULL,
                (i32)min->value.number
                    + rand ()
                        % (i32)(max->value.number + 1 - min->value.number));
        }
        else if (min->type != type_number)
            error_argument_type ("random", min->type, type_number);
        else if (max->type != type_number)
            error_argument_type ("random", max->type, type_number);
    }
    else
    {
        error_argument_count ("random", arguments->children_count, 2);
    }
    return NULL;
}

node_t *
std_exit (scope_t **scope, node_t *arguments, node_t *statements)
{
    if (arguments->children_count == 0)
    {
        exit (0);
    }
    else if (arguments->children_count == 1)
    {
        node_t *code = node_evaluate (scope, arguments->children[ 0 ]);
        if (code->type == type_number)
            exit ((i32)code->value.number);
        else
            error_argument_type ("exit", code->type, type_number);
    }
    else
        error_argument_count ("exit", arguments->children_count, 1);
    return NULL;
}

node_t *
std_system (scope_t **scope, node_t *arguments, node_t *statements)
{
    if (arguments->children_count == 1)
    {
        node_t *command = node_evaluate (scope, arguments->children[ 0 ]);
        if (command->type == type_string)
            return node_new_number (NULL, system (command->value.string));
        else
            error_argument_type ("system", command->type, type_string);
    }
    else
        error_argument_count ("system", arguments->children_count, 1);
    return NULL;
}
