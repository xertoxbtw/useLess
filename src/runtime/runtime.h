#pragma once
#include "../core/core.h"
#include "lexer.h"
#include "parser.h"
#include <stdbool.h>

typedef struct runtime_t
{
    scope_t *scope;

    bool option_output_lexer;
    bool option_output_parser;

    bool flag_return;
} runtime_t;

runtime_t *runtime_init (void);
void runtime_execute_file (runtime_t *runtime, const char *path);
