CC := gcc
RUNTIME-FILES := ./src/runtime/*.c
CORE-FILES := ./src/core/core.c ./src/core/node.c ./src/core/evaluate.c ./src/core/scope.c ./src/core/symbol.c ./src/core/module.c
CFLAGS := -g -ldl
SANITIZERS :=-fsanitize=address -fanalyzer

all: build-runtime build-std

build-runtime:
	$(CC) $(RUNTIME-FILES) $(CORE-FILES) -o runtime $(CFLAGS) # $(SANITIZERS)

build-std:
	mkdir modules
	$(CC) ./src/modules/std/*.c $(CORE-FILES) -shared -fPIC -o ./modules/std.so $(CFLAGS) # $(SANITIZERS)

