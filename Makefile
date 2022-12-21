CC := gcc
RUNTIME-FILES := ./src/runtime/*.c
CORE-FILES := ./src/core/core.c ./src/core/node.c
CFLAGS := -g
SANITIZERS :=-fsanitize=address -fanalyzer

build-runtime:
	$(CC) $(RUNTIME-FILES) $(CORE-FILES) -o runtime $(CFLAGS) # $(SANITIZERS)

test: build-runtime
	./runtime examples/greet.ul
	google-chrome tree.html
