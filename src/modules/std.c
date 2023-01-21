#include "../core/core.h"
#include <stdio.h>

node_t *
std_assign (scope_t **scope, node_t *node)
{
    node_t *children = node->children[ 1 ];
    if (children->children_count == 2)
    {
        if (children->children[ 0 ]->type == type_symbol)
        {

            symbol_t *sym
                = scope_lookup (*scope, children->children[ 0 ]->value.string);
            if (sym)
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
                sym->node = node_evaluate (scope, children->children[ 1 ]);
            }
            else
            {
                sym = symbol_create (
                    children->children[ 0 ]->value.string,
                    node_evaluate (scope, children->children[ 1 ]));

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
    return NULL;
}

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
    return NULL;
}

node_t *
std_console_println (scope_t **scope, node_t *node)
{
    std_console_print (scope, node);
    putc ('\n', stdout);
    return NULL;
}

node_t *
std_string_format (scope_t **scope, node_t *node)
{
    node_t *arguments = node->children[ 1 ];
    char *buffer = xcalloc (1, sizeof (char));
    u32 buffer_len = 0;

    for (u32 i = 0; i < arguments->children_count; i++)
    {
        node_t *value = node_evaluate (scope, arguments->children[ i ]);
        buffer_len += strlen (value->value.string);
        buffer = xreallocarray (buffer, buffer_len + 1, sizeof (char));
        strcat (buffer, value->value.string);
    }

    return node_new_string_raw (NULL, buffer);
}

node_t *
std_add (scope_t **scope, node_t *node)
{
    double result = 0;

    node_t *args = node->children[ 1 ];

    for (u64 i = 0; i < args->children_count; i++)
    {
        double value = 0;

        if (args->children[ i ]->type == type_number)
        {
            value = args->children[ i ]->value.number;
        }

        if (i == 0)
            result = value;
        else
            result += value;
    }

    return node_new_number (NULL, result);
}

i32
module_init (scope_t *scope)
{
    scope_add (scope,
               symbol_create ("assign", node_new_internal (NULL, std_assign)));
    scope_add (scope,
               symbol_create ("console.print",
                              node_new_internal (NULL, std_console_print)));
    scope_add (scope,
               symbol_create ("console.println",
                              node_new_internal (NULL, std_console_println)));
    scope_add (scope,
               symbol_create ("string.format",
                              node_new_internal (NULL, std_string_format)));

    return 0;
}
