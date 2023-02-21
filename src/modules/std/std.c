#include "std.h"
#include <stdbool.h>
#include <stdio.h>

node_t *
std_assign (scope_t **scope, node_t *arguments, node_t *statements)
{
    if (arguments->children_count == 2)
    {
        if (arguments->children[ 0 ]->type == type_symbol)
        {
            symbol_t *sym = scope_lookup (
                *scope, arguments->children[ 0 ]->value.string);
            if (sym) // If already exists, override
            {
                node_t *node_new
                    = node_evaluate (scope, arguments->children[ 1 ]);
                if (node_new->type == sym->node->type)
                {
                    if (node_new->type == type_string)
                    {
                        free (sym->node->value.string);
                        sym->node->value.string = node_new->value.string;
                    }
                    else if (node_new->type == type_number)
                    {
                        sym->node->value.number = node_new->value.number;
                    }
                }
                else
                {
                    if (node_new->type == type_string)
                    {
                        if (sym->node->type == type_number)
                        {
                            sym->node->type = type_string;
                            sym->node->value.string = node_new->value.string;
                        }
                        else
                            exit (1); // Todo
                    }
                    else if (node_new->type == type_number)
                    {
                        if (sym->node->type == type_string)
                        {
                            sym->node->type = type_number;
                            free (sym->node->value.string);
                            sym->node->value.number = node_new->value.number;
                        }
                        else
                            exit (1); // Todo
                    }
                }
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
        node_t *current = node_evaluate (scope, arguments->children[ i ]);
        if (current->type == type_string)
        {
            module_load (*scope, current->value.string);
        }
        else
        {
            error_argument_type ("include", current->type, type_string);
        }
    }
    return NULL;
}

node_t *
std_return (scope_t **scope, node_t *arguments, node_t *statements)
{
    if (arguments->children_count == 1)
    {
        scope[ 0 ]->flag_return = true;
        node_t *value = node_evaluate (scope, arguments->children[ 0 ]);
        return value;
    }
    else
    {
        error_argument_count ("return", arguments->children_count, 1);
    }
    return NULL;
}
