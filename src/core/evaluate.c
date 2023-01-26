#include "core.h"
#include <stdbool.h>
#include <stdio.h>

#define HANDLE_NOT_FOUND exit (1);

node_t *
node_evaluate_symbol (scope_t **scope, node_t *node)
{
    node_t *result = NULL;
    // Eval all nodes
    if (node->type == type_list_symbol
        && node->children[ 0 ]->type == type_list_symbol)
    {
        for (u32 i = 0; i < node->children_count; i++)
        {
            result = node_evaluate (scope, node->children[ i ]);
            if (scope[ 0 ]->flag_return)
            {
                scope[ 0 ]->flag_return = false;
                return result;
            }
        }
    }
    else
    {
        if (node->type == type_symbol) // Variable
        {
            symbol_t *sym = scope_lookup (*scope, node->value.string);

            if (sym)
                return sym->node;
            else
                HANDLE_NOT_FOUND
        }
        else if (node->children_count == 1
                 && node->children[ 0 ]->type == type_symbol) // Variable
        {
            symbol_t *sym
                = scope_lookup (*scope, node->children[ 0 ]->value.string);

            if (sym)
                return sym->node;
            else
                HANDLE_NOT_FOUND
        }
        else if (node->children_count == 2
                 && node->children[ 0 ]->type == type_symbol) // Function/Array
        {
            symbol_t *sym
                = scope_lookup (*scope, node->children[ 0 ]->value.string);
            if (!sym)
            {
                printf ("Symbol: %s was not found\n",
                        node->children[ 0 ]->value.string);
                exit (1);
            }

            if (sym->node->type == type_list_symbol
                && node->children[ 1 ]->type == type_list_argument) // Function
            {
                // Compare argument count
                if (sym->node->children[ 1 ]->children_count
                    == node->children[ 1 ]->children_count)
                {
                    *scope = scope_push (*scope);

                    for (u32 i = 0; i < node->children[ 1 ]->children_count;
                         i++)
                    {
                        scope_add (
                            *scope,
                            symbol_create (
                                sym->node->children[ 1 ]
                                    ->children[ i ]
                                    ->value.string,
                                node_copy (node_evaluate (
                                    scope,
                                    node->children[ 1 ]->children[ i ]))));
                    }

                    result = node_evaluate (scope, sym->node->children[ 2 ]);
                    *scope = scope_pop (*scope);
                }
                else
                {
                    exit (1); // argument count error
                }
            }
            else if (sym->node->type == type_internal) // Internal
            {
                node_t *(*func) (scope_t **, node_t *) = sym->node->value.func;
                return func (scope, node);
            }
            else if (sym->node->type == type_list_data
                     && node->children[ 1 ]->type
                         == type_list_argument) // Array
            {
                if (node->children[ 1 ]->children_count == 1)
                {
                    node_t *index = node_evaluate (
                        scope, node->children[ 1 ]->children[ 0 ]);
                    if (index->type == type_number)
                    {
                        if ((u32)index->value.number
                            <= sym->node->children_count - 1)
                            return sym->node
                                ->children[ (u32)index->value.number ];
                        else
                            return NULL;
                    }
                }
                else
                {
                    return sym->node;
                }
            }
        }
        else if (node->children_count == 3
                 && node->children[ 0 ]->type
                     == type_symbol) // Complex Function
        {
            symbol_t *sym
                = scope_lookup (*scope, node->children[ 0 ]->value.string);
            if (!sym)
            {
                exit (1);
            }

            if (sym->node->type == type_internal) // Internal
            {
                node_t *(*func) (scope_t **, node_t *) = sym->node->value.func;
                return func (scope, node);
            }
        }
    }

    return result;
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

    case type_list_symbol:
        return node_evaluate_symbol (scope, node);
        break;
    case type_list_argument:
    case type_list_data:
    case type_list_map:
        return node;
        break;
    }

    return NULL;
}
