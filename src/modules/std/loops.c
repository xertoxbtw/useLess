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
        else
        {
            if (var->type != type_symbol)
                error_argument_type ("dotimes", var->type, type_symbol);
            else if (times->type != type_number)
                error_argument_type ("dotimes", times->type, type_number);
        }
    }
    else if (arguments->children_count == 3)
    {
		node_t *var = arguments->children[ 0 ];
        node_t *min = node_evaluate (scope, arguments->children[ 1 ]);
        node_t *max = node_evaluate (scope, arguments->children[ 2 ]);
        if (var->type == type_symbol && min->type == type_number && max->type == type_number)
        {
            *scope = scope_push (*scope);
            symbol_t *sym
                = symbol_create (var->value.string, node_new_number (NULL, 0));
            scope_add (*scope, sym);
            for (i32 i = (i32)min->value.number; i < (i32)max->value.number; i++)
            {
                if (sym->node->type == type_number)
                    sym->node->value.number = i;
                else
                    error_custom ("dotimes", "Type of symbol got changed");

                node_evaluate (scope, statements);
            }
            *scope = scope_pop (*scope);
        }
        else
        {
            if (var->type != type_symbol)
                error_argument_type ("dotimes", var->type, type_symbol);
            else if (min->type != type_number)
                error_argument_type ("dotimes", min->type, type_number);
            else if (max->type != type_number)
                error_argument_type ("dotimes", max->type, type_number);
        }
    }
    else
        error_argument_count ("dotimes", arguments->children_count, 3);

    return NULL;
}
