CC := gcc
RUNTIME-FILES := ./src/runtime/*.c
CORE-FILES := ./src/core/core.c ./src/core/node.c ./src/core/evaluate.c ./src/core/scope.c ./src/core/symbol.c ./src/core/module.c ./src/core/error.c
CFLAGS := -ldl -g3 # -fsanitize=address,undefined
MODULES-PATH := ./modules

all: build-runtime build-std

build-runtime:
	$(CC) $(RUNTIME-FILES) $(CORE-FILES) -o runtime $(CFLAGS)

build-std:
	mkdir modules -p
	$(CC) ./src/modules/std/*.c $(CORE-FILES) -shared -fPIC -o $(MODULES-PATH)/std.um  $(CFLAGS)

build-internal:
	mkdir modules -p
	$(CC) ./src/modules/internal/*.c $(CORE-FILES) -shared -fPIC -o $(MODULES-PATH)/internal.um $(CFLAGS)

build-tigr:
	mkdir modules -p
	wget "https://raw.githubusercontent.com/erkkah/tigr/master/tigr.h" -O "./src/modules/tigr/tigr.h"
	wget "https://raw.githubusercontent.com/erkkah/tigr/master/tigr.c" -O "./src/modules/tigr/tigr.c"
	$(CC) ./src/modules/tigr/*.c $(CORE-FILES) -shared -fPIC -o $(MODULES-PATH)/tigr.um $(CFLAGS) -lGLU -lGL -lX11
