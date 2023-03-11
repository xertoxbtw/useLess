#include "binding.h"
#include "tigr.h"
#include <stdio.h>
#include <unistd.h>

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
gfx_window (scope_t **scope, node_t *arguments, node_t *statements)
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

    error_argument_count ("gfx.window", arguments->children_count, 4);
    return NULL;
}

node_t *
gfx_bitmap (scope_t **scope, node_t *arguments, node_t *statements)
{
    return NULL;
}

node_t *
gfx_close (scope_t **scope, node_t *arguments, node_t *statements)
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
        error_argument_count ("gfx.close", arguments->children_count, 1);
    return NULL;
}

node_t *
gfx_closed (scope_t **scope, node_t *arguments, node_t *statements)
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
        error_argument_count ("gfx.free", arguments->children_count, 1);
    return NULL;
}

node_t *
gfx_update (scope_t **scope, node_t *arguments, node_t *statements)
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
        error_argument_count ("gfx.update", arguments->children_count, 1);
    }
    return NULL;
}

node_t *
gfx_clear (scope_t **scope, node_t *arguments, node_t *statements)
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
        error_argument_count ("gfx.clear", arguments->children_count, 2);
    }
    return NULL;
}

node_t *
gfx_fill (scope_t **scope, node_t *arguments, node_t *statements)
{
    return NULL;
}

node_t *
gfx_line (scope_t **scope, node_t *arguments, node_t *statements)
{
    return NULL;
}

node_t *
gfx_rect (scope_t **scope, node_t *arguments, node_t *statements)
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
        error_argument_count ("gfx.fillRect", arguments->children_count, 6);
    }
    return NULL;
}

node_t *
gfx_circle (scope_t **scope, node_t *arguments, node_t *statements)
{
    return NULL;
}

node_t *
gfx_blitalpha (scope_t **scope, node_t *arguments, node_t *statements)
{
    return NULL;
}

node_t *
gfx_color (scope_t **scope, node_t *arguments, node_t *statements)
{
    return NULL;
}

node_t *
gfx_print (scope_t **scope, node_t *arguments, node_t *statements)
{
    return NULL;
}

node_t *
gfx_mouse (scope_t **scope, node_t *arguments, node_t *statements)
{
    return NULL;
}

node_t *
gfx_keydown (scope_t **scope, node_t *arguments, node_t *statements)
{
    if (arguments->children_count == 2)
    {
        node_t *bmp = node_evaluate (scope, arguments->children[ 0 ]);
        node_t *key = node_evaluate (scope, arguments->children[ 1 ]);
        if (bmp->type == type_internal)
        {
            if (key->type == type_number)
            {
                return node_new_number (
                    NULL, tigrKeyDown (bmp->value.raw, key->value.number));
            }
            else if (key->type == type_string)
            {
                return node_new_number (
                    NULL, tigrKeyDown (bmp->value.raw, key->value.string[ 0 ]));
            }
            else
                error_argument_type ("gfx.keyDown", key->type, type_number);
        }
        else
            error_argument_type_custom ("gfx.keyDown", bmp->type,
                                        "gfx.window");
    }
    else
        error_argument_count ("gfx.keyDown", arguments->children_count, 2);
    return NULL;
}

node_t *
gfx_keyheld (scope_t **scope, node_t *arguments, node_t *statements)
{
    if (arguments->children_count == 2)
    {
        node_t *bmp = node_evaluate (scope, arguments->children[ 0 ]);
        node_t *key = node_evaluate (scope, arguments->children[ 1 ]);
        if (bmp->type == type_internal)
        {
            if (key->type == type_number)
            {
                return node_new_number (
                    NULL, tigrKeyHeld (bmp->value.raw, key->value.number));
            }
            else if (key->type == type_string)
            {
                return node_new_number (
                    NULL, tigrKeyHeld (bmp->value.raw, key->value.string[ 0 ]));
            }
            else
                error_argument_type ("gfx.keyHeld", key->type, type_number);
        }
        else
            error_argument_type_custom ("gfx.keyHeld", bmp->type,
                                        "gfx.window");
    }
    else
        error_argument_count ("gfx.keyHeld", arguments->children_count, 2);
    return NULL;
}

node_t *
gfx_sleep (scope_t **scope, node_t *arguments, node_t *statements)
{
    if (arguments->children_count == 1)
    {
        node_t *time = node_evaluate (scope, arguments->children[ 0 ]);
        if (time->type == type_number)
        {
            usleep (time->value.number * 1000000);
        }
        else
            error_argument_type ("gfx.sleep", time->type, type_number);
    }
    else
        error_argument_count ("gfx.sleep", arguments->children_count, 1);
    return NULL;
}
