#pragma once
#include "../../core/core.h"

node_t *std_assign (scope_t **scope, node_t *arguments, node_t *statements);
node_t *std_function (scope_t **scope, node_t *arguments, node_t *statements);
node_t *std_include (scope_t **scope, node_t *arguments, node_t *statements);
node_t *std_return (scope_t **scope, node_t *arguments, node_t *statements);
node_t *std_random(scope_t **scope, node_t *arguments, node_t *statements);

/* loop.c */
node_t *std_while (scope_t **scope, node_t *arguments, node_t *statements);
node_t *std_dotimes (scope_t **scope, node_t *arguments, node_t *statements);

/* console.c */
node_t *std_console_print (scope_t **scope, node_t *arguments,
                           node_t *statements);
node_t *std_console_println (scope_t **scope, node_t *arguments,
                             node_t *statements);
node_t *std_console_readln (scope_t **scope, node_t *arguments,
                            node_t *statements);

/* math.c */
node_t *std_math_add (scope_t **scope, node_t *arguments, node_t *statements);
node_t *std_math_sub (scope_t **scope, node_t *arguments, node_t *statements);
node_t *std_math_mul (scope_t **scope, node_t *arguments, node_t *statements);
node_t *std_math_div (scope_t **scope, node_t *arguments, node_t *statements);
node_t *std_math_mod (scope_t **scope, node_t *arguments, node_t *statements);

node_t *std_if (scope_t **scope, node_t *arguments, node_t *statements);
node_t *std_elif (scope_t **scope, node_t *arguments, node_t *statements);
node_t *std_equal (scope_t **scope, node_t *arguments, node_t *statements);
node_t *std_not (scope_t **scope, node_t *arguments, node_t *statements);
node_t *std_greater (scope_t **scope, node_t *arguments, node_t *statements);
node_t *std_less (scope_t **scope, node_t *arguments, node_t *statements);
node_t *std_greater_equal (scope_t **scope, node_t *arguments,
                           node_t *statements);
node_t *std_less_equal (scope_t **scope, node_t *arguments, node_t *statements);

/* string.c */
node_t *std_string_format (scope_t **scope, node_t *arguments,
                           node_t *statements);
node_t *std_string_split (scope_t **scope, node_t *arguments,
                          node_t *statements);
node_t *std_string_replace (scope_t **scope, node_t *arguments,
                            node_t *statements);

/* file.c */
node_t *std_file_read (scope_t **scope, node_t *arguments, node_t *statements);
node_t *std_file_write (scope_t **scope, node_t *arguments, node_t *statements);

/* types.c */
node_t *std_types_string_check (scope_t **scope, node_t *arguments,
                                node_t *statements);
node_t *std_types_number_check (scope_t **scope, node_t *arguments,
                                node_t *statements);
node_t *std_types_list_check (scope_t **scope, node_t *arguments,
                              node_t *statements);
node_t *std_types_function_check (scope_t **scope, node_t *arguments,
                                  node_t *statements);
node_t *std_types_string (scope_t **scope, node_t *arguments,
                          node_t *statements);
node_t *std_types_number (scope_t **scope, node_t *arguments,
                          node_t *statements);

/* list.c */
node_t *std_list (scope_t **scope, node_t *arguments, node_t *statements);
node_t *std_list_new (scope_t **scope, node_t *arguments, node_t *statements);
node_t *std_list_get (scope_t **scope, node_t *arguments, node_t *statements);
node_t *std_list_set (scope_t **scope, node_t *arguments, node_t *statements);
node_t *std_list_append (scope_t **scope, node_t *arguments,
                         node_t *statements);
node_t *std_list_remove (scope_t **scope, node_t *arguments,
                         node_t *statements);
node_t *std_list_do (scope_t **scope, node_t *arguments, node_t *statements);
node_t *std_list_range (scope_t **scope, node_t *arguments, node_t *statements);
node_t *std_list_copy (scope_t **scope, node_t *arguments, node_t *statements);
node_t *std_length (scope_t **scope, node_t *arguments, node_t *statements);

symbol_definition_t *module_init (void);
