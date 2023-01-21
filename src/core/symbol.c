#include "core.h"
#include <stdbool.h>
#include <string.h>

symbol_t *
symbol_create (char *label, node_t *node)
{
    symbol_t *sym = xcalloc (1, sizeof (symbol_t));
    u32 label_len = strlen (label);

    sym->label = xcalloc (label_len + 1, sizeof (char));
    strncpy (sym->label, label, label_len);

    sym->node = node;
    return sym;
}

void
symbol_delete (symbol_t *sym)
{
}
