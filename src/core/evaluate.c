#include "core.h"

#include <stdbool.h>
#include <stdio.h>

#define HANDLE_NOT_FOUND exit (1);

node_t *
node_evaluate_symbol (scope_t **scope, node_t *node)
{
    symbol_t *sym = scope_lookup (scope[ 0 ], node->value.string);
    if (sym)
        return sym->node;
    error_custom ("Symbol \"%s\" was not found",
                  node->value.string);

    return NULL;
}

node_t *
node_evaluate_list_symbol (scope_t **scope, node_t *node)
{
    if (node->children_count == 0)
        return NULL;
    if (node->children[ 0 ]->type == type_list_symbol)
    {
        node_t *last = NULL;
        for (u32 i = 0; i < node->children_count && !scope[ 0 ]->flag_return;
             i++)
            last = node_evaluate (scope, node->children[ i ]);

        return last;
    }

    symbol_t *sym
        = scope_lookup (scope[ 0 ], node->children[ 0 ]->value.string);

    if (!sym || !sym->node)
    {
        error_custom ("Symbol \"%s\" was not found",
                      node->children[ 0 ]->value.string);
        return NULL;
    }

    node_t *arguments = node->children[ 1 ];
    node_t *statements = NULL;

    if (node->children_count == 3)
        statements = node->children[ 2 ];
    else
        statements = node_new_list_symbol (NULL);

    if (sym->node->type == type_internal) // Internal Function
    {
        node_t *(*func) (scope_t **, node_t *, node_t *) = sym->node->value.raw;
        return func (scope, arguments, statements);
    }
    else if (sym->node->type == type_list_symbol) // User Defined Function
    {
        node_t *function = sym->node;
        if (function->children[ 0 ]->children_count
            == arguments->children_count)
        {
            scope[ 0 ] = scope_push (scope[ 0 ]);
            for (u32 i = 0; i < arguments->children_count; i++)
            {
                scope_add (
                    scope[ 0 ],
                    symbol_create (
                        function->children[ 0 ]->children[ i ]->value.string,
                        node_evaluate (scope, arguments->children[ i ])));
            }
            node_t *result = node_evaluate (scope, function->children[ 1 ]);
            scope[ 0 ]->flag_return = false;
            scope[ 0 ] = scope_pop (scope[ 0 ]);
            return result;
        }
        else
        {
            error_argument_count (node->children[ 0 ]->value.string,
                                  arguments->children_count,
                                  function->children[ 0 ]->children_count);
        }
    }

    return NULL;
}

node_t *
node_evaluate_string (scope_t **scope, node_t *node)
{
    u32 len = strlen (node->value.string);
    char *buffer = xcalloc (len + 1, sizeof (char));
    u32 buffer_index = 0;
    for (u32 i = 0; i < len; i++)
    {
        if (node->value.string[ i ] == '\\' && i + 1 < len - 1)
        {
            switch (node->value.string[ i + 1 ])
            {
            case 'n':
                buffer[ buffer_index++ ] = '\n';
                break;
            case 't':
                buffer[ buffer_index++ ] = '\t';
                break;
            }
            i++;
        }
        else
        {
            buffer[ buffer_index++ ] = node->value.string[ i ];
        }
    }

    free (node->value.string);
    node->value.string = buffer;

    return node;
}

node_t *
node_evaluate (scope_t **scope, node_t *node)
{
    switch (node->type)
    {
    case type_number:
        return node;
        break;
    case type_string:
        return node_evaluate_string (scope, node);
        break;
    case type_symbol:
        return node_evaluate_symbol (scope, node);
        break;
    case type_internal:
        return node; // Todo
        break;
    case type_list_symbol:
        return node_evaluate_list_symbol (scope, node);
        break;
    case type_list_argument:
    case type_list_data:
    case type_list_map:
        return node;
        break;
    }

    return NULL;
}
