#pragma once
#include "../core/core.h"

typedef enum
{
    lexer_string,
    lexer_number,
    lexer_key,
    lexer_symbol
} lexer_type;

typedef struct
{
    char *content;
    lexer_type type;
} lexer_entry_t;

typedef struct
{
    lexer_entry_t *entries;
    u64 count;
} lexer_result_t;

lexer_result_t *lexer (const char *buffer);
lexer_result_t *lexer_tokenize (const char *buffer);
bool lexer_check (lexer_result_t *lexer_result);
void lexer_free (lexer_result_t *result);

