#pragma once
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void *xcalloc (size_t nmemb, size_t size);
void *xrealloc (void *ptr, size_t size);
void *xreallocarray (void *ptr, size_t nmemb, size_t size);

typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

typedef int8_t i8;
typedef int16_t i16;
typedef int32_t i32;
typedef int64_t i64;

typedef float f32;
typedef double f64;

typedef enum
{
    type_number,
    type_string,
    type_symbol,
    type_internal,
    type_key,
    type_list_argument,
    type_list_data,
    type_list_symbol
} node_type;

typedef struct
{
    const char *key;
    const char *function_name;
} key_entry_t;

typedef struct
{
    char *content;
    node_type type;
} lexer_entry_t;

typedef struct
{
    lexer_entry_t *entries;
    u64 count;
} lexer_result_t;

typedef struct node_t
{
    union
    {
        char *string;
        f64 number;
        void *raw;
    } value;
    node_type type;

    struct node_t *parent;
    struct node_t **children;
    u32 children_count;
} node_t;

typedef struct symbol_t
{
    char *label;
    node_t *node;
} symbol_t;

typedef struct scope_t
{
    symbol_t **symbols;
    u32 symbols_count;
    node_t *node_return;
    bool flag_if_failed;

    struct scope_t *previous;
    struct scope_t *next;
} scope_t;

typedef struct symbol_definition_t
{
    char *label;
    node_t *(*fun) (scope_t **, node_t *, node_t *);
} symbol_definition_t;

node_t *node_insert (node_t *parent, node_t *node);
node_t *node_copy (node_t *node);
node_t *node_new_number (node_t *parent, double number);
node_t *node_new_string (node_t *parent, char *string);
node_t *node_new_string_raw (node_t *parent, char *string);
node_t *node_new_symbol (node_t *parent, char *symbol);
node_t *node_new_key (node_t *parent, char *symbol);
node_t *node_new_internal (node_t *parent,
                           node_t *(*func) (scope_t **, node_t *, node_t *));
node_t *node_new_internal_custom (node_t *parent, void *ptr);

node_t *node_new_list_argument (node_t *parent);
node_t *node_new_list_data (node_t *parent);
node_t *node_new_list_symbol (node_t *parent);

node_t *node_evaluate (scope_t **scope, node_t *node);
node_t *node_extract (node_t *node);

symbol_t *symbol_create (char *label, node_t *node);
void symbol_delete (symbol_t *sym);

scope_t *scope_push (scope_t *scope);
scope_t *scope_pop (scope_t *scope);
void scope_add (scope_t *scope, symbol_t *symbol);
scope_t *scope_get_global (scope_t *scope);
symbol_t *scope_lookup (scope_t *scope, char *label);

void error_argument_count (char *symbol, u32 got, u32 expected);
void error_argument_type (char *symbol, node_type got, node_type expected);
void error_argument_type_custom (char *symbol, node_type got, char *expected);
void error_custom (char *format, ...);

i32 module_load (scope_t *scope, char *path);

lexer_result_t *lexer (const char *buffer);
lexer_result_t *lexer_tokenize (const char *buffer);
bool lexer_check (lexer_result_t *lexer_result);

node_t *parser (lexer_result_t *lexer);
node_t *parser_parse (lexer_result_t *lexer);
void parser_transform (node_t *root);
void parser_visualize (FILE *file, node_t *root);
