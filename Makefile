CC := gcc
RUNTIME-FILES := ./src/runtime/*.c
CORE-FILES := ./src/core/core.c ./src/core/node.c ./src/core/evaluate.c ./src/core/scope.c ./src/core/symbol.c ./src/core/module.c
CFLAGS := -g
SANITIZERS :=-fsanitize=address -fanalyzer

all: build-runtime build-std

build-runtime:
	$(CC) $(RUNTIME-FILES) $(CORE-FILES) -o runtime $(CFLAGS) # $(SANITIZERS)

build-std:
	$(CC) ./src/modules/std.c $(CORE-FILES) -shared -fPIC -o ./modules/std.so $(CFLAGS) # $(SANITIZERS)


test: build-runtime
	./runtime examples/greet.ul --parser > tree.html
	google-chrome tree.html
