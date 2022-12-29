#include "core.h"
#include <stdio.h>

node_t *
node_evaluate (scope_t *scope, node_t *node)
{
    if (node->type == type_list)
    {
        if (node->children_count > 0
            && node->children[ 0 ]->type == type_symbol)
        {
            printf ("%s\n", node->children[ 0 ]->value.string);
        }
        else
        {
            for (u32 i = 0; i < node->children_count; i++)
            {
                node_evaluate (scope, node->children[ i ]);
            }
        }
    }
    return NULL;
}
