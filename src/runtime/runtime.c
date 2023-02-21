#include "runtime.h"
#include "lexer.h"
#include "parser.h"
#include <stdio.h>

key_entry_t _internal_keys[]
    = {{"==", "equal"}, {"!=", "not"}, {"=", "assign"}, {";", NULL},
       {",", NULL},     {"(", NULL},   {")", NULL},     {"{", NULL},
       {"}", NULL},     {"+", "add"},  {"-", "sub"},    {"*", "mul"},
       {"/", "div"},    {"%", "mod"},  {":", "map"}};

key_entry_t *keys;
u32 keys_count;

runtime_t *
runtime_init (void)
{
    runtime_t *runtime = xcalloc (1, sizeof (runtime_t));
    runtime->scope = xcalloc (1, sizeof (scope_t));

    keys_count = sizeof (_internal_keys) / sizeof (_internal_keys[ 0 ]);
    keys = _internal_keys;

    return runtime;
}

void
runtime_execute_file (runtime_t *runtime, const char *path)
{
    FILE *file_ptr = NULL;
    u64 file_len = 0;
    char *buffer = NULL;

    file_ptr = fopen (path, "r");
    if (!file_ptr)
    {
        ERROR ("Passed file was not found");
    }

    fseek (file_ptr, 0, SEEK_END);
    file_len = ftell (file_ptr);
    fseek (file_ptr, 0, SEEK_SET);

    buffer = xcalloc (file_len + 1, sizeof (char));
    fread (buffer, file_len, file_len, file_ptr);
    fclose (file_ptr);

    lexer_result_t *lexer_result = lexer (buffer);
    if (runtime->option_output_lexer)
    {
        for (u64 i = 0; i < lexer_result->count; i++)
        {
            printf ("%s\n", lexer_result->entries[ i ].content);
        }
    }
    else
    {
        node_t *root_node = parser (lexer_result);
        if (runtime->option_output_parser)
        {
            parser_visualize (stdout, root_node);
        }
        else
        {
            module_load (runtime->scope, "modules/std.um");

            for (u32 i = 0; i < root_node->children_count; i++)
                node_evaluate (&runtime->scope, root_node->children[ i ]);
        }
    }

    free (buffer);
    lexer_free (lexer_result);
}
