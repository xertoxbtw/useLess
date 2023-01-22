#pragma once
#include "../../core/core.h"

node_t *std_assign (scope_t **scope, node_t *node);
node_t *std_function (scope_t **scope, node_t *node);
node_t *std_include (scope_t **scope, node_t *node);
node_t *std_while (scope_t **scope, node_t *node);
node_t *std_if (scope_t **scope, node_t *node);
node_t *std_return (scope_t **scope, node_t *node);
node_t *std_typeof (scope_t **scope, node_t *node);

node_t *std_console_print (scope_t **scope, node_t *node);
node_t *std_console_println (scope_t **scope, node_t *node);

node_t *std_string_format (scope_t **scope, node_t *node);

node_t *std_add (scope_t **scope, node_t *node);
node_t *std_sub (scope_t **scope, node_t *node);
node_t *std_mul (scope_t **scope, node_t *node);
node_t *std_div (scope_t **scope, node_t *node);

i32 module_init (scope_t *scope);