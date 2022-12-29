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
} lexer_entry;

typedef struct
{
    lexer_entry *entries;
    u32 count;
} lexer_result;

lexer_result *lexer (const char *buffer);
lexer_result *lexer_process(lexer_result *in);
void lexer_free (lexer_result *result);
