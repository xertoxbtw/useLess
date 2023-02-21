#include "binding.h"
#include "tigr.h"
#include <stdio.h>

TPixel
getColor (scope_t **scope, node_t *list)
{
    TPixel color = tigrRGBA (0, 0, 0, 0);
    if (list->children_count < 3)
        return color;
    if (list->children_count == 4)
    {
        color.a = (u8)node_evaluate (scope, list->children[ 3 ])->value.number;
    }
    color.r = (u8)node_evaluate (scope, list->children[ 0 ])->value.number;
    color.g = (u8)node_evaluate (scope, list->children[ 1 ])->value.number;
    color.b = (u8)node_evaluate (scope, list->children[ 2 ])->value.number;
    return color;
}

node_t *
tigr_window (scope_t **scope, node_t *arguments, node_t *statements)
{
    Tigr *window = NULL;
    if (arguments->children_count == 4)
    {
        node_t *node_width = node_evaluate (scope, arguments->children[ 0 ]);
        node_t *node_height = node_evaluate (scope, arguments->children[ 1 ]);
        node_t *node_title = node_evaluate (scope, arguments->children[ 2 ]);
        node_t *node_flags = node_evaluate (scope, arguments->children[ 3 ]);

        if (node_width->type == type_number && node_height->type == type_number
            && node_title->type == type_string
            && node_flags->type == type_number)
        {
            window = tigrWindow (
                (i32)node_width->value.number, (i32)node_height->value.number,
                node_title->value.string, (i32)node_flags->value.number);
            return node_new_internal_custom (NULL, window);
        }
        else
        {
            TODO ("Implement argument type error");
        }
    }

    error_argument_count ("tigr.window", arguments->children_count, 4);
    return NULL;
}

node_t *
tigr_bitmap (scope_t **scope, node_t *arguments, node_t *statements)
{
    return NULL;
}

node_t *
tigr_free (scope_t **scope, node_t *arguments, node_t *statements)
{
    if (arguments->children_count == 1)
    {
        node_t *bmp = node_evaluate (scope, arguments->children[ 0 ]);
        if (bmp->type == type_internal)
        {
            tigrFree (bmp->value.raw);
        }
        else
        {
            TODO ("Implement argument type error");
        }
    }
    else
        error_argument_count ("tigr.free", arguments->children_count, 1);
    return NULL;
}

node_t *
tigr_closed (scope_t **scope, node_t *arguments, node_t *statements)
{
    if (arguments->children_count == 1)
    {
        node_t *bmp = node_evaluate (scope, arguments->children[ 0 ]);
        if (bmp->type == type_internal)
        {
            return node_new_number (NULL, tigrClosed (bmp->value.raw));
        }
        else
        {
            TODO ("Implement argument type error");
        }
    }
    else
        error_argument_count ("tigr.free", arguments->children_count, 1);
    return NULL;
}

node_t *
tigr_update (scope_t **scope, node_t *arguments, node_t *statements)
{
    if (arguments->children_count == 1)
    {
        node_t *bmp = node_evaluate (scope, arguments->children[ 0 ]);
        if (bmp->type == type_internal)
        {
            tigrUpdate (bmp->value.raw);
        }
        else
        {
            TODO ("Add 'error_argument_type_custom' where the expected type is "
                  "a string");
        }
    }
    else
    {
        error_argument_count ("tigr.update", arguments->children_count, 1);
    }
    return NULL;
}

node_t *
tigr_clear (scope_t **scope, node_t *arguments, node_t *statements)
{
    if (arguments->children_count == 2)
    {
        node_t *bmp = node_evaluate (scope, arguments->children[ 0 ]);
        if (bmp->type == type_internal)
        {
            tigrClear (
                bmp->value.raw,
                getColor (scope,
                          node_evaluate (scope, arguments->children[ 1 ])));
        }
        else
        {
            TODO ("Add 'error_argument_type_custom' where the expected type is "
                  "a string");
        }
    }
    else
    {
        error_argument_count ("tigr.clear", arguments->children_count, 2);
    }
    return NULL;
}

node_t *
tigr_fill (scope_t **scope, node_t *arguments, node_t *statements)
{
    return NULL;
}

node_t *
tigr_line (scope_t **scope, node_t *arguments, node_t *statements)
{
    return NULL;
}

node_t *
tigr_rect (scope_t **scope, node_t *arguments, node_t *statements)
{
    return NULL;
}

node_t *
tigr_fillrect (scope_t **scope, node_t *arguments, node_t *statements)
{
    if (arguments->children_count == 6)
    {
        node_t *bmp = node_evaluate (scope, arguments->children[ 0 ]);
        node_t *x = node_evaluate (scope, arguments->children[ 1 ]);
        node_t *y = node_evaluate (scope, arguments->children[ 2 ]);
        node_t *w = node_evaluate (scope, arguments->children[ 3 ]);
        node_t *h = node_evaluate (scope, arguments->children[ 4 ]);
        node_t *color = node_evaluate (scope, arguments->children[ 5 ]);
        if (bmp->type == type_internal && x->type == type_number
            && y->type == type_number && w->type == type_number
            && h->type == type_number && color->type == type_list_data)
        {
            tigrRect (bmp->value.raw, (i32)x->value.number,
                      (i32)y->value.number, (i32)w->value.number,
                      (i32)h->value.number, getColor (scope, color));
            tigrFillRect (bmp->value.raw, (i32)x->value.number,
                          (i32)y->value.number, (i32)w->value.number,
                          (i32)h->value.number, getColor (scope, color));
        }
        else
        {
            TODO ("Add 'error_argument_type_custom' where the expected type is "
                  "a string");
        }
    }
    else
    {
        error_argument_count ("tigr.fillRect", arguments->children_count, 6);
    }
    return NULL;
}

node_t *
tigr_circle (scope_t **scope, node_t *arguments, node_t *statements)
{
    return NULL;
}

node_t *
tigr_fillcircle (scope_t **scope, node_t *arguments, node_t *statements)
{
    return NULL;
}

node_t *
tigr_clip (scope_t **scope, node_t *arguments, node_t *statements)
{
    return NULL;
}

node_t *
tigr_blit (scope_t **scope, node_t *arguments, node_t *statements)
{
    return NULL;
}

node_t *
tigr_blitalpha (scope_t **scope, node_t *arguments, node_t *statements)
{
    return NULL;
}

node_t *
tigr_color (scope_t **scope, node_t *arguments, node_t *statements)
{
    return NULL;
}

node_t *
tigr_print (scope_t **scope, node_t *arguments, node_t *statements)
{
    return NULL;
}

node_t *
tigr_mouse (scope_t **scope, node_t *arguments, node_t *statements)
{
    return NULL;
}

node_t *
tigr_keydown (scope_t **scope, node_t *arguments, node_t *statements)
{
    return NULL;
}

node_t *
tigr_keyheld (scope_t **scope, node_t *arguments, node_t *statements)
{
    return NULL;
}
