#pragma once
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ERROR(msg)                         \
    fprintf (stderr, "[Error] %s\n", msg); \
    exit (1)

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
    type_list,
    type_symbol,
    type_internal
} node_type;

typedef struct node_t
{
    union
    {
        char *string;
        f64 number;
    } value;
    node_type type;

    struct node_t *parent;
    struct node_t **children;
    u32 children_count;
} node_t;

node_t *node_insert (node_t *parent, node_t *node);
node_t *node_new (node_t *parent, char *value);
node_t *node_new_type (node_t *parent, char *value, node_type type);
node_t *node_new_number (node_t *parent, double number);
node_t *node_new_string (node_t *parent, char *string);
node_t *node_new_list (node_t *parent, node_t **children, u32 children_count);
node_t *node_new_symbol (node_t *parent, char *symbol);
node_t *node_new_internal (node_t *parent, void (*func) ()); // Todo

void node_remove(node_t *node);
