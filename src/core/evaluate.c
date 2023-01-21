#include "core.h"
#include <stdio.h>

#define HANDLE_NOT_FOUND exit (1);

node_t *
node_evaluate_symbol (scope_t **scope, node_t *node)
{
    /* Todo: If first child is also type_list_symbol then evaluate every
     * child */

    if (node->type == type_symbol)
    {
        symbol_t *sym = scope_lookup (*scope, node->value.string);

        if (sym)
            return sym->node;
        else
            HANDLE_NOT_FOUND
    }
    else if (node->children_count == 1
             && node->children[ 0 ]->type == type_symbol)
    {
        symbol_t *sym
            = scope_lookup (*scope, node->children[ 0 ]->value.string);

        if (sym)
            return sym->node;
        else
            HANDLE_NOT_FOUND
    }
    else if (node->children_count == 2
             && node->children[ 0 ]->type == type_symbol)
    {
        symbol_t *sym
            = scope_lookup (*scope, node->children[ 0 ]->value.string);
        if (!sym)
        {
            exit (1);
        }

        if (node->children[ 1 ]->type == type_list_argument) // Function
        {
            // Todo: Check if value in symbol is actually a symbol
            // Check if argument count is equal
            if (sym->node->type == type_list_argument
                && sym->node->children[ 1 ]->children_count
                    == node->children[ 1 ]->children_count)
            {
                u64 arg_count = node->children[ 1 ]->children_count;
                *scope = scope_push (*scope);
                for (u64 i = 0; i < arg_count; i++)
                {
                    node_t *arg = sym->node->children[ 1 ]->children[ i ];
                    if (arg->type != type_symbol)
                        ERROR ("not symbol"); // Todo: Improve
                    scope_add (
                        *scope,
                        symbol_create (arg->value.string,
                                       node->children[ 1 ]->children[ 1 ]));
                }
                node_evaluate (scope, sym->node->children[ 2 ]);
            }
            else if (sym->node->type == type_internal) // Internal
            {
                node_t *(*func) (scope_t **, node_t *) = sym->node->value.func;
                return func (scope, node);
            }
        }

        else if (node->children[ 1 ]->type == type_list_data) // Array
        {
        }
    }
    else if (node->children_count == 3
             && node->children[ 0 ]->type == type_symbol)
    {
    }
    return NULL;
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
        return node;
        break;
    case type_symbol:
        return node_evaluate_symbol (scope, node);
        break;
    case type_internal:
        return node_evaluate_symbol (scope, node->parent);
        break;
    case type_list_argument:
        // TODO
        break;
    case type_list_data:
        // TODO
        break;
    case type_list_symbol:
        return node_evaluate_symbol (scope, node);
        break;
    }

    return NULL;
}
