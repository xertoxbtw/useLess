#include "std.h"
#include <stdio.h>
#include <string.h>

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
                error_custom ("File %s was not found", f_path->value.string);
            fseek (file, 0, SEEK_END);
            file_len = ftell (file);
            fseek (file, 0, SEEK_SET);

            buffer = xcalloc (file_len + 1, sizeof (char));
            fread (buffer, sizeof (char), file_len, file);
            fclose (file);
        }
        else
            error_argument_type ("file.read", f_path->type, type_string);
    }
    else
        error_argument_count ("file.read", arguments->children_count, 1);
    return node_new_string_raw (NULL, buffer);
}

node_t *
std_file_write (scope_t **scope, node_t *arguments, node_t *statements)
{
    if (arguments->children_count == 2)
    {
        node_t *file_path = node_evaluate (scope, arguments->children[ 0 ]);
        node_t *file_content = node_evaluate (scope, arguments->children[ 1 ]);
        if (file_path->type == type_string && file_content->type == type_string)
        {
            FILE *file = fopen (file_path->value.string, "w");
            if (!file)
                error_custom ("Failed to open file %s for writing",
                              file_path->value.string);
            fwrite (file_content->value.string,
                    strlen (file_content->value.string), sizeof (char), file);
            fclose (file);
        }
        else
            error_argument_type ("file.write",
                                 file_path->type == type_string
                                     ? file_content->type
                                     : file_path->type,
                                 type_string);
    }
    else
        error_argument_count ("file.write", arguments->children_count, 2);
    return NULL;
}
