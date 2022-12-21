#pragma once
#include "../core/core.h"
#include "lexer.h"

node_t *parser (lexer_result *lexer);
void parser_visualize(FILE *file, node_t *root);
