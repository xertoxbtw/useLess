#include "std.h"

symbol_definition_t symbols[] = {{"assign", std_assign},
                                 {"function", std_function},
                                 {"include", std_include},
                                 {"return", std_return},
                                 {"while", std_while},
                                 {"dotimes", std_dotimes},
                                 {"console.print", std_console_print},
                                 {"console.println", std_console_println},
                                 {"console.read", std_console_read},
                                 {"console.readln", std_console_readln},
                                 {"add", std_math_add},
                                 {"sub", std_math_sub},
                                 {"mul", std_math_mul},
                                 {"div", std_math_div},
                                 {"mod", std_math_mod},
                                 {"if", std_if},
                                 {"elif", std_elif},
                                 {"equal", std_equal},
                                 {"not", std_not},
                                 {"greater", std_greater},
                                 {"less", std_less},
                                 {"greater_equal", std_greater_equal},
                                 {"less_equal", std_less_equal},
                                 {"string.format", std_string_format},
                                 {"string.split", std_string_split},
                                 {"string.replace", std_string_replace},
                                 {"file.read", std_file_read},
                                 {"file.write", std_file_write},
                                 {"list?", std_types_list},
                                 {"string?", std_types_string},
                                 {"number?", std_types_number},
                                 {"list", std_list},
                                 {"list.get", std_list_get},
                                 {"list.set", std_list_set},
                                 {"list.append", std_list_append},
                                 {"list.do", std_list_do},		
                                 {"list.range", std_list_range},
                                 {"list.copy", std_list_copy},
                                 {"map", std_map},
                                 {"length", std_length},
                                 NULL};

symbol_definition_t *
module_init (void)
{
    return symbols;
}
