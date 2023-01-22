#include "std.h"

node_t *
std_console_print (scope_t **scope, node_t *node)
{
    node_t *arguments = node->children[ 1 ];
    if (arguments->children_count != 1)
    {
        exit (1); // Argument Count Error
    }

    node_t *value = node_evaluate (scope, arguments->children[ 0 ]);
    if (!value)
    {
        printf ("(null)");
    }
    else if (value->type == type_string)
    {
        printf ("%s", value->value.string);
    }
    else if (value->type == type_number)
    {
        printf ("%f", value->value.number);
    }
    return NULL;
}

node_t *
std_console_println (scope_t **scope, node_t *node)
{
    std_console_print (scope, node);
    putc ('\n', stdout);
    return NULL;
}
