#pragma once
#include "../core/core.h"
#include "lexer.h"
#include "parser.h"

typedef struct runtime_t
{
	scope_t *scope;
	
	u32 flag_return;
} runtime_t;

runtime_t *runtime_init(void);
