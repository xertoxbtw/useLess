#include "core.h"

#include <stdio.h>
#include <string.h>

node_t *
node_insert (node_t *parent, node_t *node)
{
    if (parent)
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
    return node;
}

node_t *
node_copy (node_t *node)
{
    node_t *copy = xcalloc (1, sizeof (node_t));
    copy->type = node->type;
    if (node->type == type_string)
    {
        u32 len = strlen (node->value.string);
        char *tmp = xcalloc (len + 1, sizeof (char));
        strcpy (tmp, node->value.string);
        copy->value.string = tmp;
    }
    else if (node->type == type_number)
    {
        copy->value.number = node->value.number;
    }
    else if (node->type == type_list_data)
    {
        for (u32 i = 0; i < node->children_count; i++)
        {
            node_insert (copy, node_copy (node->children[ i ]));
        }
    }

    return copy;
}

node_t *
node_new (node_t *parent, char *value)
{
    return node_insert (parent, xcalloc (1, sizeof (node_t)));
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
    node->value.string = xcalloc (len, sizeof (char));
    strncpy (node->value.string, string + 1, len - 2);

    return node_insert (parent, node);
}

node_t *
node_new_string_raw (node_t *parent, char *string)
{
    node_t *node = xcalloc (1, sizeof (node_t));
    node->type = type_string;

    u32 len = strlen (string);
    node->value.string = xcalloc (len + 1, sizeof (char));
    strncpy (node->value.string, string, len);

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

node_t *
node_new_internal (node_t *parent,
                   node_t *(*func) (scope_t **, node_t *, node_t *))
{
    node_t *node = xcalloc (1, sizeof (node_t));
    node->type = type_internal;
    node->value.raw = func;

    return node_insert (parent, node);
}

node_t *
node_new_internal_custom (node_t *parent, void *ptr)
{

    node_t *node = xcalloc (1, sizeof (node_t));
    node->type = type_internal;
    node->value.raw = ptr;

    return node_insert (parent, node);
}

node_t *
node_new_list_argument (node_t *parent)
{
    node_t *node = xcalloc (1, sizeof (node_t));
    node->type = type_list_argument;
    return node_insert (parent, node);
}

node_t *
node_new_list_data (node_t *parent)
{
    node_t *node = xcalloc (1, sizeof (node_t));
    node->type = type_list_data;
    return node_insert (parent, node);
}

node_t *
node_new_list_symbol (node_t *parent)
{
    node_t *node = xcalloc (1, sizeof (node_t));
    node->type = type_list_symbol;
    return node_insert (parent, node);
}

node_t *
node_extract (node_t *node)
{
    u32 index = 0;
    node_t *parent = node->parent;
    for (u32 i = 0; i < parent->children_count; i++)
    {
        if (node == parent->children[ i ])
        {
            index = i;
            break;
        }
    }

    u32 len = parent->children_count - index - 1;
    memmove (parent->children + index, parent->children + index + 1,
             len * sizeof (node_t *));
    parent->children_count--;
    node->parent = NULL;
    return node;
}
