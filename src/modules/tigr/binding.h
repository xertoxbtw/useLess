#pragma once
#include "../../core/core.h"

node_t *tigr_window (scope_t **scope, node_t *arguments, node_t *statements);
node_t *tigr_bitmap (scope_t **scope, node_t *arguments, node_t *statements);
node_t *tigr_free (scope_t **scope, node_t *arguments, node_t *statements);
node_t *tigr_closed (scope_t **scope, node_t *arguments, node_t *statements);
node_t *tigr_update (scope_t **scope, node_t *arguments, node_t *statements);
node_t *tigr_clear (scope_t **scope, node_t *arguments, node_t *statements);
node_t *tigr_fill (scope_t **scope, node_t *arguments, node_t *statements);
node_t *tigr_line (scope_t **scope, node_t *arguments, node_t *statements);
node_t *tigr_rect (scope_t **scope, node_t *arguments, node_t *statements);
node_t *tigr_fillrect (scope_t **scope, node_t *arguments, node_t *statements);
node_t *tigr_circle (scope_t **scope, node_t *arguments, node_t *statements);
node_t *tigr_fillcircle (scope_t **scope, node_t *arguments, node_t *statements);
node_t *tigr_clip (scope_t **scope, node_t *arguments, node_t *statements);
node_t *tigr_blit (scope_t **scope, node_t *arguments, node_t *statements);
node_t *tigr_blitalpha (scope_t **scope, node_t *arguments, node_t *statements);
node_t *tigr_color (scope_t **scope, node_t *arguments, node_t *statements);
node_t *tigr_print (scope_t **scope, node_t *arguments, node_t *statements);
node_t *tigr_mouse (scope_t **scope, node_t *arguments, node_t *statements);
node_t *tigr_keydown (scope_t **scope, node_t *arguments, node_t *statements);
node_t *tigr_keyheld (scope_t **scope, node_t *arguments, node_t *statements);
