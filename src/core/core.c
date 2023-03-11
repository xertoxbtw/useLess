#include "core.h"
#include <gc.h>

void *
xcalloc (size_t nmemb, size_t size)
{
	
    return GC_malloc(nmemb * size);
}

void *
xrealloc (void *ptr, size_t size)
{
    return GC_realloc(ptr, size);
}

void *
xreallocarray (void *ptr, size_t nmemb, size_t size)
{
    return GC_realloc(ptr, nmemb * size);
}

void xfree(void *ptr)
{
	GC_free(ptr);
}
