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
        else if (node_width->type != type_number)
            error_argument_type ("gfx.window", node_width->type, type_number);
        else if (node_height->type != type_number)
            error_argument_type ("gfx.window", node_height->type, type_number);
        else if (node_title->type != type_string)
            error_argument_type ("gfx.window", node_title->type, type_string);
        else if (node_flags->type != type_number)
            error_argument_type ("gfx.window", node_flags->type, type_number);
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
            error_argument_type_custom ("gfx.close", bmp->type, "gfx.window");
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
            error_argument_type_custom ("gfx.closed", bmp->type, "gfx.window");
        }
    }
    else
        error_argument_count ("gfx.closed", arguments->children_count, 1);
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
            error_argument_type_custom ("gfx.update", bmp->type, "gfx.window");
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
            error_argument_type_custom ("gfx.clear", bmp->type, "gfx.window");
        }
    }
    else
    {
        error_argument_count ("gfx.clear", arguments->children_count, 2);
    }
    return NULL;
}

node_t *
gfx_line (scope_t **scope, node_t *arguments, node_t *statements)
{
    if (arguments->children_count == 6)
    {
        node_t *bmp = node_evaluate (scope, arguments->children[ 0 ]);
        node_t *x0 = node_evaluate (scope, arguments->children[ 1 ]);
        node_t *y0 = node_evaluate (scope, arguments->children[ 2 ]);
        node_t *x1 = node_evaluate (scope, arguments->children[ 3 ]);
        node_t *y1 = node_evaluate (scope, arguments->children[ 4 ]);
        node_t *color = node_evaluate (scope, arguments->children[ 5 ]);
        if (bmp->type == type_internal && x0->type == type_number
            && y0->type == type_number && x1->type == type_number
            && y1->type == type_number && color->type == type_list_data)
        {
            tigrLine (bmp->value.raw, (i32)x0->value.number,
                      (i32)y0->value.number, (i32)x1->value.number,
                      (i32)y1->value.number, getColor (scope, color));
        }
        else
        {
            error_argument_type_custom ("gfx.line", bmp->type, "gfx.window");
        }
    }
    else
    {
        error_argument_count ("gfx.line", arguments->children_count, 6);
    }
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
            tigrFill (bmp->value.raw, (i32)x->value.number,
                      (i32)y->value.number, (i32)w->value.number,
                      (i32)h->value.number, getColor (scope, color));
        }
        else
        {
            error_argument_type_custom ("gfx.rect", bmp->type, "gfx.window");
        }
    }
    else
    {
        error_argument_count ("gfx.rect", arguments->children_count, 6);
    }
    return NULL;
}

node_t *
gfx_circle (scope_t **scope, node_t *arguments, node_t *statements)
{
    if (arguments->children_count == 5)
    {
        node_t *bmp = node_evaluate (scope, arguments->children[ 0 ]);
        node_t *x = node_evaluate (scope, arguments->children[ 1 ]);
        node_t *y = node_evaluate (scope, arguments->children[ 2 ]);
        node_t *r = node_evaluate (scope, arguments->children[ 3 ]);
        node_t *color = node_evaluate (scope, arguments->children[ 4 ]);
        if (bmp->type == type_internal && x->type == type_number
            && y->type == type_number && r->type == type_number
            && color->type == type_list_data)
        {
            tigrFillCircle (bmp->value.raw, (i32)x->value.number,
                            (i32)y->value.number, (i32)r->value.number,
                            getColor (scope, color));
            tigrCircle (bmp->value.raw, (i32)x->value.number,
                            (i32)y->value.number, (i32)r->value.number,
                            getColor (scope, color));
        }
        else
        {
            error_argument_type_custom ("gfx.circle", bmp->type, "gfx.window");
        }
    }
    else
    {
        error_argument_count ("gfx.circle", arguments->children_count, 6);
    }
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
    u8 r = 0, g = 0, b = 0, a = 255;
    if (arguments->children_count == 1)
    {
        node_t *value = node_evaluate (scope, arguments->children[ 0 ]);
        if (value->type == type_number)
        {
            r = value->value.number;
            g = value->value.number;
            b = value->value.number;
        }
        else
            error_argument_type ("gfx.color", value->type, type_number);
    }
    else if (arguments->children_count == 2)
    {
        node_t *value_color = node_evaluate (scope, arguments->children[ 0 ]);
        node_t *value_alpha = node_evaluate (scope, arguments->children[ 1 ]);
        if (value_color->type == type_number
            && value_alpha->type == type_number)
        {
            r = value_color->value.number;
            g = value_color->value.number;
            b = value_color->value.number;
            a = value_alpha->value.number;
        }
        else
            error_argument_type ("gfx.color",
                                 value_color->type == type_number
                                     ? value_alpha->type
                                     : value_color->type,
                                 type_number);
    }
    else if (arguments->children_count == 3)
    {
        node_t *value_r = node_evaluate (scope, arguments->children[ 0 ]);
        node_t *value_g = node_evaluate (scope, arguments->children[ 1 ]);
        node_t *value_b = node_evaluate (scope, arguments->children[ 2 ]);

        if (value_r->type == type_number && value_g->type == type_number
            && value_b->type == type_number)
        {
            r = value_r->value.number;
            g = value_g->value.number;
            b = value_b->value.number;
        }
        else if (value_r != type_number)
            error_argument_type ("gfx.color", value_r->type, type_number);
        else if (value_g != type_number)
            error_argument_type ("gfx.color", value_g->type, type_number);
        else if (value_b != type_number)
            error_argument_type ("gfx.color", value_b->type, type_number);
    }
    else if (arguments->children_count == 4)
    {
        node_t *value_r = node_evaluate (scope, arguments->children[ 0 ]);
        node_t *value_g = node_evaluate (scope, arguments->children[ 1 ]);
        node_t *value_b = node_evaluate (scope, arguments->children[ 2 ]);
        node_t *value_a = node_evaluate (scope, arguments->children[ 3 ]);

        if (value_r->type == type_number && value_g->type == type_number
            && value_b->type == type_number && value_a->type == type_number)
        {
            r = value_r->value.number;
            g = value_g->value.number;
            b = value_b->value.number;
            a = value_a->value.number;
        }
        else if (value_r != type_number)
            error_argument_type ("gfx.color", value_r->type, type_number);
        else if (value_g != type_number)
            error_argument_type ("gfx.color", value_g->type, type_number);
        else if (value_b != type_number)
            error_argument_type ("gfx.color", value_b->type, type_number);
        else if (value_a != type_number)
            error_argument_type ("gfx.color", value_a->type, type_number);
    }
    else
        error_argument_count ("gfx.color", arguments->children_count, 4);
    node_t *result = node_new_list_data (NULL);
    node_new_number (result, r);
    node_new_number (result, g);
    node_new_number (result, b);
    node_new_number (result, a);
    return result;
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
            error_argument_type_custom ("gfx.keyDown", bmp->type, "gfx.window");
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
            error_argument_type_custom ("gfx.keyHeld", bmp->type, "gfx.window");
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
