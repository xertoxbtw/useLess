#include "core.h"
#include <stdio.h>
#ifdef linux
#include <dlfcn.h>

i32
module_load (scope_t *scope, char *path)
{
    void *dl = dlopen (path, RTLD_LAZY);
    if (!dl)
        return 1;
    symbol_definition_t *(*func) ()
        = (symbol_definition_t * (*)()) dlsym (dl, "module_init");
    if (!func)
        return 1;

    symbol_definition_t *result = func ();
    while (result->label != NULL)
    {
        scope_add (scope,
                   symbol_create (result->label,
                                  node_new_internal (NULL, result->fun)));
        result++;
    }

    return 0;
}

#endif
#ifdef _WIN32
i32
module_load (char *path)
{
    fprintf (stderr,
             "'module_load' does currently not work on Windows based systems");
    exit (1);
    return 0;
}
#endif
