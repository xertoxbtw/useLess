#include "core/runtime.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

i32
main (const int argc, const char **argv)
{
    runtime_t *runtime = runtime_init ();

    const char *file_path = NULL;

    for (u32 i = 1; i < argc; i++)
    {
        if (strncmp ("--", argv[ i ], 2) == 0)
        {
            const char *arg = argv[ i ] + 2;
            if (strcmp ("lexer", arg) == 0)
            {
                runtime->option_output_lexer = true;
            }
            else if (strcmp ("parser", arg) == 0)
            {
                runtime->option_output_parser = true;
            }
        }
        else if (!file_path)
        {
            file_path = argv[ i ];
        }
        else
        {
            error_custom ("No valid argument was passed");
        }
    }

    if (file_path)
        runtime_execute_file (runtime, file_path);
    else
		error_custom("No file was passed");

    return 0;
}
