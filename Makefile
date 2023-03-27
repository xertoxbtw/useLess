CC := gcc
CORE-FILES := ./src/core/core.c ./src/core/node.c ./src/core/evaluate.c ./src/core/scope.c ./src/core/symbol.c ./src/core/module.c ./src/core/error.c ./src/core/lexer.c ./src/core/parser.c ./src/core/runtime.c
CFLAGS := -lgc -ldl -g3 # -fsanitize=address,undefined
MODULES-PATH := ./modules

all: build-runtime build-std build-internal build-gfx

clear:
	rm ./src/modules/gfx/tigr.*
	rm runtime

build-runtime:
	$(CC) ./src/main.c $(CORE-FILES) -o runtime $(CFLAGS)

build-std:
	mkdir modules -p
	$(CC) ./src/modules/std/*.c $(CORE-FILES) -shared -fPIC -o $(MODULES-PATH)/std.um  $(CFLAGS) -lm

build-internal:
	mkdir modules -p
	$(CC) ./src/modules/internal/*.c $(CORE-FILES) -shared -fPIC -o $(MODULES-PATH)/internal.um $(CFLAGS)

build-gfx:
	mkdir modules -p
	wget "https://raw.githubusercontent.com/erkkah/tigr/master/tigr.h" -O "./src/modules/gfx/tigr.h"
	wget "https://raw.githubusercontent.com/erkkah/tigr/master/tigr.c" -O "./src/modules/gfx/tigr.c"
	$(CC) ./src/modules/gfx/*.c $(CORE-FILES) -shared -fPIC -o $(MODULES-PATH)/gfx.um $(CFLAGS) -lGLU -lGL -lX11
