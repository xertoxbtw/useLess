#include "std.h"
#include <stdio.h>

node_t *
std_file_read (scope_t **scope, node_t *arguments, node_t *statements)
{
    char *buffer = NULL;
    FILE *file = NULL;
    u32 file_len = 0;
    if (arguments->children_count == 1)
    {
        node_t *f_path = node_evaluate (scope, arguments->children[ 0 ]);
        if (f_path->type == type_string)
        {
            file = fopen (f_path->value.string, "r");
            if (!file)
                error_custom ("file.read", "File was not found");
            fseek (file, 0, SEEK_END);
            file_len = ftell (file);
            fseek (file, 0, SEEK_SET);

            buffer = xcalloc (file_len + 1, sizeof (char));
            fread (buffer, sizeof (char), file_len, file);
            fclose (file);
        }
        else
        {
            error_argument_type ("file.read", f_path->type, type_string);
        }
    }
    else
    {
        error_argument_count ("file.read", arguments->children_count, 1);
    }
    return node_new_string_raw (NULL, buffer);
}

node_t *
std_file_write (scope_t **scope, node_t *arguments, node_t *statements)
{
	return NULL;
}
