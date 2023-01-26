#include "core.h"

scope_t *
scope_push (scope_t *scope)
{
    scope_t *new = xcalloc (1, sizeof (scope_t));
    if (scope)
    {
        new->previous = scope;
        scope->next = new;
    }
    return new;
}

scope_t *
scope_pop (scope_t *scope)
{
    for (u32 i = 0; i < scope->symbols_count; i++)
    {
        free (scope->symbols[ i ]->label);
        node_remove (scope->symbols[ i ]->node);
        free (scope->symbols[ i ]);
    }
    scope_t *new = scope->previous;
    new->next = NULL;
    free (scope);
    return new;
}

void
scope_add (scope_t *scope, symbol_t *symbol)
{
    if (scope->symbols_count == 0)
        scope->symbols = xcalloc (1, sizeof (symbol_t *));
    else
        scope->symbols = xreallocarray (
            scope->symbols, scope->symbols_count + 1, sizeof (symbol_t *));

    scope->symbols[ scope->symbols_count++ ] = symbol;
}

symbol_t *
scope_lookup (scope_t *scope, char *label)
{
    for (u32 i = 0; i < scope->symbols_count; i++)
    {
        if (strcmp (scope->symbols[ i ]->label, label) == 0)
            return scope->symbols[ i ];
    }
    if (scope->previous)
        return scope_lookup (scope->previous, label);

    return NULL;
}
