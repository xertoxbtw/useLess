#include "std.h"
#include <stdbool.h>
#include <stdio.h>

node_t *
std_assign (scope_t **scope, node_t *node)
{
    node_t *arguments = node->children[ 1 ];
    if (arguments->children_count == 2)
    {
        if (arguments->children[ 0 ]->type == type_symbol)
        {
            symbol_t *sym
                = scope_lookup (*scope, arguments->children[ 0 ]->value.string);
            if (sym) // If already exists, override
            {
                if (sym->reference)
                {
                    fprintf (stderr, "TODO: %s -> %i\n", __FILE__, __LINE__);
                    exit (1);
                }
                else
                {
                    node_remove (sym->node);
                }
                sym->node = node_evaluate (scope, arguments->children[ 1 ]);
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
            exit (1); // Type error
    }
    else
        exit (1); // Argument Count Error

    return NULL;
}

node_t *
std_function (scope_t **scope, node_t *node)
{
    return node;
}

node_t *
std_include (scope_t **scope, node_t *node)
{
    node_t *arguments = node->children[ 1 ];
    for (u32 i = 0; i < arguments->children_count; i++)
    {
        node_t *current = node_evaluate (scope, arguments->children[ i ]);
        if (current->type == type_string)
        {
            module_load (*scope, current->value.string);
        }
        else
        {
            exit (1); // Throw type error
        }
    }
    return NULL;
}

node_t *
std_while (scope_t **scope, node_t *node)
{
    while (1)
    {
        bool isTrue = true;
        for (u32 i = 0; i < node->children[ 1 ]->children_count && isTrue; i++)
        {
            node_t *result
                = node_evaluate (scope, node->children[ 1 ]->children[ i ]);
            if (result->type == type_number && result->value.number != 0)
            {
            }
            else
                isTrue = false;
        }
        if (!isTrue)
            break;

        node_evaluate (scope, node->children[ 2 ]);
    }
    return NULL;
}

node_t *
std_dotimes (scope_t **scope, node_t *node)
{
    if (node->children_count != 3)
        return NULL;

    node_t *arguments = node->children[ 1 ];
    if (arguments->children_count == 2)
    {
        node_t *var = arguments->children[ 0 ];
        node_t *times = node_evaluate (scope, arguments->children[ 1 ]);
        if (var->type == type_symbol && times->type == type_number)
        {
            *scope = scope_push (*scope);
            symbol_t *sym
                = symbol_create (var->value.string, node_new_number (NULL, 0));
            scope_add (*scope, sym);
            for (u32 i = 0; i < (u32)times->value.number; i++)
            {
                if (sym->node->type == type_number)
                    sym->node->value.number = i;

                for (u32 b = 0; b < node->children[ 2 ]->children_count; b++)
                    node_evaluate (scope, node->children[ 2 ]->children[ b ]);
            }
            *scope = scope_pop (*scope);
        }
    }
    return NULL;
}

node_t *
std_length (scope_t **scope, node_t *node)
{
    if (node->children_count == 2 && node->children[ 1 ]->children_count == 1)
    {
        u32 result = 0;
        node_t *value
            = node_evaluate (scope, node->children[ 1 ]->children[ 0 ]);

        if (value->type == type_list_data || value->type == type_list_symbol
            || value->type == type_list_argument)
            result = value->children_count;
        else
            result = 1;

        return node_new_number (NULL, result);
    }
    else
        exit (1); // argument count error

    return NULL;
}

node_t *
std_if (scope_t **scope, node_t *node)
{
    bool isTrue = true;
    for (u32 i = 0; i < node->children[ 1 ]->children_count && isTrue; i++)
    {
        node_t *result
            = node_evaluate (scope, node->children[ 1 ]->children[ i ]);
        if (result->type == type_number && result->value.number != 0)
        {
        }
        else
            isTrue = false;
    }
    if (isTrue)
        node_evaluate (scope, node->children[ 2 ]);

    return NULL;
}

node_t *
std_return (scope_t **scope, node_t *node)
{
    node_t *arguments = node->children[ 1 ];
    if (arguments->children_count == 1)
    {
        scope[ 0 ]->flag_return = true;
        node_t *value = node_evaluate (scope, arguments->children[ 0 ]);
        return value;
    }
    else
    {
        exit (1); // Argument count error
    }
    return NULL;
}

node_t *
std_typeof (scope_t **scope, node_t *node)
{
    node_t *arguments = node->children[ 1 ];
    if (arguments->children_count == 1)
    {
        printf ("%i\n", node_evaluate (scope, arguments->children[ 0 ])->type);
    }
    else
    {
        exit (1); // Argument count error
    }
    return NULL;
}

node_t *
std_map (scope_t **scope, node_t *node)
{
    return NULL;
}

i32
module_init (scope_t *scope)
{
    scope_add (scope,
               symbol_create ("assign", node_new_internal (NULL, std_assign)));

    scope_add (
        scope,
        symbol_create ("function", node_new_internal (NULL, std_function)));

    scope_add (scope,
               symbol_create ("console.print",
                              node_new_internal (NULL, std_console_print)));

    scope_add (scope,
               symbol_create ("console.println",
                              node_new_internal (NULL, std_console_println)));

    scope_add (scope,
               symbol_create ("string.format",
                              node_new_internal (NULL, std_string_format)));

    scope_add (
        scope,
        symbol_create ("include", node_new_internal (NULL, std_include)));

    scope_add (scope,
               symbol_create ("while", node_new_internal (NULL, std_while)));

    scope_add (
        scope,
        symbol_create ("dotimes", node_new_internal (NULL, std_dotimes)));

    scope_add (scope,
               symbol_create ("length", node_new_internal (NULL, std_length)));

    scope_add (scope, symbol_create ("if", node_new_internal (NULL, std_if)));

    scope_add (scope,
               symbol_create ("return", node_new_internal (NULL, std_return)));
    scope_add (scope,
               symbol_create ("typeof", node_new_internal (NULL, std_typeof)));

    scope_add (scope, symbol_create ("map", node_new_internal (NULL, std_map)));

    scope_add (scope, symbol_create ("add", node_new_internal (NULL, std_add)));
    scope_add (scope, symbol_create ("sub", node_new_internal (NULL, std_sub)));
    scope_add (scope, symbol_create ("mul", node_new_internal (NULL, std_mul)));
    scope_add (scope, symbol_create ("div", node_new_internal (NULL, std_div)));
    return 0;
}
