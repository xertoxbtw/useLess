#pragma once
#include "../core/core.h"
#include "lexer.h"

node_t *parser (lexer_result_t *lexer);
node_t *parser_parse (lexer_result_t *lexer);
void parser_transform (node_t *root);
void parser_visualize (FILE *file, node_t *root);
