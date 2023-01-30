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

typedef struct
{
    char *key;
    char *function_name;
} key_entry_t;

#define keys_count 16
extern key_entry_t keys[keys_count];

runtime_t *runtime_init (void);
void runtime_execute_file (runtime_t *runtime, const char *path);
