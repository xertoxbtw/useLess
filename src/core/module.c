#include "core.h"
#ifdef linux
#include <dlfcn.h>

i32
module_load (scope_t *scope, char *path)
{
    void *dl = dlopen (path, RTLD_LAZY);
	if(!dl)
		return 1;
    i32 (*func) (scope_t *) = (i32 (*) (scope_t *))dlsym (dl, "module_init");
	if(!func)
		return 1;

	return func(scope);
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
