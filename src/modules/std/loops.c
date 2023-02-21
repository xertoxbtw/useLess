#include "std.h"
#include <stdio.h>

node_t *
std_while (scope_t **scope, node_t *arguments, node_t *statements)
{
    bool isTrue = true;

    while (isTrue)
    {
        for (u32 i = 0; i < arguments->children_count && isTrue; i++)
        {
            node_t *result = node_evaluate (scope, arguments->children[ i ]);
            if (result->type != type_number || result->value.number == 0)
                isTrue = false;
        }
        if (isTrue)
            node_evaluate (scope, statements);
    }
    return NULL;
}

node_t *
std_dotimes (scope_t **scope, node_t *arguments, node_t *statements)
{
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
                else
                    error_custom ("dotimes", "Type of symbol got changed");

                node_evaluate (scope, statements);
            }
            *scope = scope_pop (*scope);
        }
    }
    return NULL;
}
