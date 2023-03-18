#include "std.h"

node_t *
std_list (scope_t **scope, node_t *arguments, node_t *statements)
{
    node_t *root = node_new_list_data (NULL);
    for (u32 i = 0; i < arguments->children_count; i++)
    {
        node_insert (root, node_evaluate (scope, arguments->children[ i ]));
    }
    return root;
}

node_t *
std_list_get (scope_t **scope, node_t *arguments, node_t *statements)
{
    if (arguments->children_count == 2)
    {
        node_t *var = node_evaluate (scope, arguments->children[ 0 ]);
        node_t *index = node_evaluate (scope, arguments->children[ 1 ]);
        if (var->type != type_list_data)
            error_argument_type ("list.get", var->type, type_list_data);

        if (index->type == type_number)
        {
            u32 ind = (u32)index->value.number;
            if (ind < var->children_count)
            {
                return var->children[ ind ];
            }
            else
                error_custom ("Index is out of bounds");
        }
        else
            error_argument_type ("list.get", index->type, type_number);
    }
    error_argument_count ("list.get", arguments->children_count, 2);

    return NULL;
}

node_t *
std_list_set (scope_t **scope, node_t *arguments, node_t *statements)
{
    if (arguments->children_count == 3)
    {
        node_t *list = node_evaluate (scope, arguments->children[ 0 ]);
        node_t *index = node_evaluate (scope, arguments->children[ 1 ]);
        node_t *node = node_evaluate (scope, arguments->children[ 2 ]);
        if (list->type == type_list_data)
        {
            if (index->type == type_number)
            {

                list->children[ (u32)index->value.number ] = node;
            }
            else
                error_argument_type ("list.set", index->type, type_number);
        }
    }
    else
        error_argument_count ("list.set", arguments->children_count, 3);

    return NULL;
}

node_t *
std_list_append (scope_t **scope, node_t *arguments, node_t *statements)
{
    if (arguments->children_count >= 2)
    {
        node_t *list = node_evaluate (scope, arguments->children[ 0 ]);
        if (list->type == type_list_data)
        {
            for (u32 i = 1; i < arguments->children_count; i++)
            {
                node_insert (list,
                             node_evaluate (scope, arguments->children[ i ]));
            }
        }
        else
            error_argument_type ("list.append", list->type, type_list_data);
    }
    else
        error_argument_count ("list.append", arguments->children_count, 2);

    return NULL;
}

node_t *
std_list_remove (scope_t **scope, node_t *arguments, node_t *statements)
{
    if (arguments->children_count == 2)
    {
        node_t *list = node_evaluate (scope, arguments->children[ 0 ]);
        node_t *index = node_evaluate (scope, arguments->children[ 1 ]);
        if (list->type == type_list_data && index->type == type_number)
        {
            node_t *new = node_new_list_data (NULL);
            for (u32 i = 0; i < list->children_count; i++)
            {
                if (i != (u32)index->value.number)
                {
                    node_insert (new, node_copy (list->children[ i ]));
                }
            }
            return new;
        }
        else if (list->type != type_list_data)
            error_argument_type ("list.remove", list->type, type_list_data);
        else if (index->type != type_number)
            error_argument_type ("list.remove", index->type, type_number);
    }
    else
        error_argument_count ("list.remove", arguments->children_count, 2);

    return NULL;
}

node_t *
std_list_do (scope_t **scope, node_t *arguments, node_t *statements)
{
    if (arguments->children_count == 2)
    {
        node_t *a = arguments->children[ 0 ];
        node_t *b = node_evaluate (scope, arguments->children[ 1 ]);
        if (a->type != type_symbol)
            error_argument_type ("list.do", a->type, type_symbol);
        else if (b->type != type_list_data)
            error_argument_type ("list.do", b->type, type_list_data);

        *scope = scope_push (*scope);
        symbol_t *sym = symbol_create (a->value.string, NULL);
        scope_add (*scope, sym);
        for (u32 i = 0; i < b->children_count; i++)
        {
            sym->node = node_copy (b->children[ i ]);
            node_evaluate (scope, statements);
        }
        *scope = scope_pop (*scope);
    }
    else
        error_argument_count ("list.do", arguments->children_count, 2);
    return NULL;
}

node_t *
std_list_range (scope_t **scope, node_t *arguments, node_t *statements)
{
    if (arguments->children_count != 2)
        error_argument_count ("list.range", arguments->children_count, 2);

    node_t *min = node_evaluate (scope, arguments->children[ 0 ]);
    node_t *max = node_evaluate (scope, arguments->children[ 1 ]);
    if (min->type != type_number)
        error_argument_type ("list.range", min->type, type_number);
    else if (max->type != type_number)
        error_argument_type ("list.range", max->type, type_number);

    node_t *result = node_new_list_data (NULL);

    for (double i = min->value.number; i < max->value.number; i++)
        node_new_number (result, i);

    return result;
}

node_t *
std_list_copy (scope_t **scope, node_t *arguments, node_t *statements)
{
    if (arguments->children_count == 1)
    {
        node_t *list = node_evaluate (scope, arguments->children[ 0 ]);
        if (list->type == type_list_data)
            return node_copy (list);
        else
            error_argument_type ("list.copy", list->type, type_list_data);
    }
    else
        error_argument_count ("list.copy", arguments->children_count, 1);

    return NULL;
}

node_t *
std_length (scope_t **scope, node_t *arguments, node_t *statements)
{
    if (arguments->children_count == 1)
    {
        node_t *node = node_evaluate (scope, arguments->children[ 0 ]);
        if (node->type == type_list_data)
        {
            return node_new_number (NULL, node->children_count);
        }
        else if (node->type == type_string)
        {
            return node_new_number (NULL, strlen (node->value.string));
        }
        else
            error_argument_type ("length", node->type, type_list_data);
    }
    else
        error_argument_count ("length", arguments->children_count, 1);
    return NULL;
}
