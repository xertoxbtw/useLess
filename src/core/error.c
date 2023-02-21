#include "core.h"
#include <stdarg.h>
#include <stdio.h>

#define ERROR_HEADER "\x1b[31m[Error] "
#define ERROR_FOOTER "\x1b[0m\n"

void
error_argument_count (char *symbol, u32 got, u32 expected)
{
    fprintf (stderr,
             ERROR_HEADER
             "%s exprected %i arguments but recieved %i" ERROR_FOOTER,
             symbol, expected, got);
    exit (1);
}

void
error_argument_type (char *symbol, node_type got, node_type expected)
{
    char *got_string = NULL;
    char *expected_string = NULL;
    switch (got)
    {
    case type_number:
        got_string = "number";
        break;
    case type_string:
        got_string = "string";
        break;
    case type_symbol:
        got_string = "symbol";
        break;
    case type_list_data:
        got_string = "list";
        break;
    default:
        break;
    }
    switch (expected)
    {
    case type_number:
        expected_string = "number";
        break;
    case type_string:
        expected_string = "string";
        break;
    case type_symbol:
        expected_string = "symbol";
        break;
    case type_list_data:
        expected_string = "list";
        break;
    default:
        break;
    }

    fprintf (stderr,
             ERROR_HEADER "\"%s\" expected argument of type \"%s\" but "
                          "recieved type \"%s\"" ERROR_FOOTER,
             symbol, expected_string, got_string);
    exit (1);
}

void
error_argument_type_custom (char *symbol, node_type got, char *expected)
{
    char *got_string = NULL;
    switch (got)
    {
    case type_number:
        got_string = "number";
        break;
    case type_string:
        got_string = "string";
        break;
    case type_symbol:
        got_string = "symbol";
        break;
    case type_list_data:
        got_string = "list";
        break;
    default:
        break;
    }

    fprintf (stderr,
             ERROR_HEADER "\"%s\" expected argument of type \"%s\" but "
                          "recieved type \"%s\"" ERROR_FOOTER,
             symbol, expected, got_string);
    exit (1);
}

void
error_custom (char *format, ...)
{
    va_list argList;
    va_start (argList, format);

    fprintf (stderr, ERROR_HEADER);
    vfprintf (stderr, format, argList);
    fprintf (stderr, ERROR_FOOTER);

    va_end (argList);
    exit (1);
}
