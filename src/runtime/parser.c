#include "parser.h"
#include "lexer.h"
#include <stdio.h>
#include <string.h>

node_t *
parser (lexer_result *lexer)
{
    node_t *root = node_new_list (NULL, NULL, 0);
    node_t *current = node_new_list (root, NULL, 0);
    for (u32 i = 0; i < lexer->count; i++)
    {
        // fprintf (stderr, "%s\n", lexer->entries[ i ].content);
        if (lexer->entries[ i ].type == lexer_key)
        {
            if (lexer->entries[ i ].content[ 0 ] == ';')
            {
                if (i + 1 < lexer->count - 1
                    && lexer->entries[ i + 1 ].type != lexer_key)
                    current = node_new_list (current->parent, NULL, 0);
            }
            else if (lexer->entries[ i ].content[ 0 ] == '(')
            {
                current = node_new_list (current, NULL, 0);
            }
            else if (lexer->entries[ i ].content[ 0 ] == ')')
            {

                current = current->parent;
            }
        }
        else if (lexer->entries[ i ].type == lexer_string)
        {
            node_new_string (current, lexer->entries[ i ].content);
        }
        else
            node_new_symbol (current, lexer->entries[ i ].content);
    }
    return root;
}

void
parser_visualize_node (FILE *f, node_t *root)
{
    fprintf (f, "<li>");
    switch (root->type)
    {
    case type_number:
        fprintf (f, "<value>%f</value><type>Number</type>", root->value.number);
        break;
    case type_string:
        fprintf (f, "<value>%s</value><type>String</type>", root->value.string);
        break;
    case type_symbol:
        fprintf (f, "<value>%s</value><type>Symbol</type>", root->value.string);
        break;
    case type_list:
        fprintf (f, "<value></value><type>List</type>");
        break;
    case type_internal:
        // Todo
        fprintf (f, "Todo");
        break;
    }
    fprintf (f, "<ul>");
    for (u32 i = 0; i < root->children_count; i++)
    {
        parser_visualize_node (f, root->children[ i ]);
    }
    fprintf (f, "</ul></li>");
}

void
parser_visualize (FILE *f, node_t *root)
{
    fprintf (
        f,
        "<!doctype html><html><head><link rel='stylesheet' "
        "href='misc/visualizer.css'></head><body class='tree-diagram'><ul>");
    parser_visualize_node (f, root);
    fprintf (f, "</ul></body></html>");
}
