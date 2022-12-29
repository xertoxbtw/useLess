#include "lexer.h"
#include "runtime.h"
#include <stdio.h>
#include <stdlib.h>

i32
main (const int argc, const char **argv)
{
    FILE *file = fopen (argv[ 1 ], "r");
    fseek (file, 0, SEEK_END);
    u32 size = ftell (file);
    fseek (file, 0, SEEK_SET);

    char *buffer = calloc (size + 1, sizeof (char));
    fread (buffer, size, size, file);
    fclose (file);

    lexer_result *result_1 = lexer (buffer);
	lexer_result *result_2 = lexer_process(result_1);
    free (buffer);

	node_t * root = parser(result_2);

	//node_evaluate(NULL, root);
	
	file = fopen("tree.html", "w");
    parser_visualize (file, root);
	fclose(file); 

	/*
    lexer_free (result_1);
    lexer_free (result_2);
	*/
    return 0;
}
