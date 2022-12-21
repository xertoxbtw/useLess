#include "core.h"

void *
xcalloc (size_t nmemb, size_t size)
{
    void *ptr = calloc (nmemb, size);
    if (!ptr)
    {
        ERROR ("Memory Allocation failed");
    }
    return ptr;
}

void *
xrealloc (void *ptr, size_t size)
{
    void *new_ptr = realloc (ptr, size);
    if (!new_ptr)
    {
        ERROR ("Memory Reallocation failed");
    }
    return new_ptr;
}

void *
xreallocarray (void *ptr, size_t nmemb, size_t size)
{
    return xrealloc (ptr, nmemb * size);
}
