#include "core.h"
#include <string.h>

node_t *
node_insert (node_t *parent, node_t *node)
{
    if (parent)
    {
        if (parent->type != type_list)
        {
            // Todo: Handle non list parents
        }
        else
        {
            node->parent = parent;
            if (parent->children_count == 0)
                node->parent->children = xcalloc (1, sizeof (node_t *));
            else
                node->parent->children = xreallocarray (
                    node->parent->children, node->parent->children_count + 1,
                    sizeof (node_t *));

            node->parent->children[ node->parent->children_count++ ] = node;
        }
    }
    return node;
}

node_t *
node_new (node_t *parent, char *value)
{
	return NULL;
}

node_t *
node_new_type (node_t *parent, char *value, node_type type)
{
    node_t *node = xcalloc (1, sizeof (node_t));
    return node_insert (parent, node);
}

node_t *
node_new_number (node_t *parent, double number)
{
    node_t *node = xcalloc (1, sizeof (node_t));
    node->value.number = number;
    node->type = type_number;

    return node_insert (parent, node);
}

node_t *
node_new_string (node_t *parent, char *string)
{
    node_t *node = xcalloc (1, sizeof (node_t));
    node->type = type_string;

    u32 len = strlen (string);
    node->value.string = xcalloc (len + 1, sizeof (char));
    strncpy (node->value.string, string, len);

    return node_insert (parent, node);
}

node_t *
node_new_list (node_t *parent, struct node_t **children, u32 children_count)
{
    node_t *node = xcalloc (1, sizeof (node_t));
    node->type = type_list;
    node->children_count = children_count;
    if (node->children_count)
        node->children = children;

    return node_insert (parent, node);
}

node_t *
node_new_symbol (node_t *parent, char *symbol)
{
    node_t *node = xcalloc (1, sizeof (node_t));
    node->type = type_symbol;

    u32 len = strlen (symbol);
    node->value.string = xcalloc (len + 1, sizeof (char));
    strncpy (node->value.string, symbol, len);

    return node_insert (parent, node);
}

void
node_remove (node_t *node)
{
}
