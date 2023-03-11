#include "std.h"
#include <stdio.h>

node_t *
std_console_print (scope_t **scope, node_t *arguments, node_t *statements)
{
    for (u32 i = 0; i < arguments->children_count; i++)
    {
        node_t *value = node_evaluate (scope, arguments->children[ i ]);
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
            printf ("%.2f", value->value.number);
        }
    }
    return NULL;
}

node_t *
std_console_println (scope_t **scope, node_t *arguments, node_t *statements)
{
    std_console_print (scope, arguments, statements);
    putc ('\n', stdout);
    return NULL;
}

node_t *
std_console_readln (scope_t **scope, node_t *arguments, node_t *statements)
{
	std_console_print (scope, arguments, statements);
    char *target = NULL;
    scanf (" %m[^\n]", &target);
    if (target)
        return node_new_string_raw (NULL, target);
    return NULL;
}
