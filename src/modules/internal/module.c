#include "../../core/core.h"
#include <stdio.h>

void
print_symbols (scope_t *scope)
{
    for (u32 i = 0; i < scope->symbols_count; i++)
        printf ("%s\n", scope->symbols[ i ]->label);
    if (scope->previous)
        print_symbols (scope->previous);
}

node_t *
internal_symbols (scope_t **scope, node_t *arguments, node_t *statements)
{
	print_symbols(*scope);
    return NULL;
}

symbol_definition_t symbols[] = {{"internal.symbols", internal_symbols}, NULL};

symbol_definition_t *
module_init (void)
{
    return symbols;
}
