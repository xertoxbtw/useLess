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

    lexer_result *result = lexer (buffer);
    free (buffer);

	node_t * root = parser(result);
	
	file = fopen("tree.html", "w");
    parser_visualize (file, root);
	fclose(file);
   

    lexer_free (result);
    return 0;
}
