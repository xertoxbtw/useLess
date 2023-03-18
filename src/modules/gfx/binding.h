#pragma once
#include "../../core/core.h"

node_t *gfx_window (scope_t **scope, node_t *arguments, node_t *statements);
node_t *gfx_bitmap (scope_t **scope, node_t *arguments, node_t *statements);
node_t *gfx_close (scope_t **scope, node_t *arguments, node_t *statements);
node_t *gfx_closed (scope_t **scope, node_t *arguments, node_t *statements);
node_t *gfx_update (scope_t **scope, node_t *arguments, node_t *statements);
node_t *gfx_clear (scope_t **scope, node_t *arguments, node_t *statements);
node_t *gfx_line (scope_t **scope, node_t *arguments, node_t *statements);
node_t *gfx_rect (scope_t **scope, node_t *arguments, node_t *statements);
node_t *gfx_circle (scope_t **scope, node_t *arguments, node_t *statements);
node_t *gfx_blitalpha (scope_t **scope, node_t *arguments, node_t *statements);
node_t *gfx_color (scope_t **scope, node_t *arguments, node_t *statements);
node_t *gfx_print (scope_t **scope, node_t *arguments, node_t *statements);
node_t *gfx_mouse (scope_t **scope, node_t *arguments, node_t *statements);
node_t *gfx_keydown (scope_t **scope, node_t *arguments, node_t *statements);
node_t *gfx_keyheld (scope_t **scope, node_t *arguments, node_t *statements);
node_t *gfx_sleep (scope_t **scope, node_t *arguments, node_t *statements);

