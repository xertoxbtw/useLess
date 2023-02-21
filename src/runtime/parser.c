#include "parser.h"
#include "lexer.h"
#include "runtime.h"
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <strings.h>

node_t *
parser (lexer_result_t *lexer)
{
    node_t *result = parser_parse (lexer);
    parser_transform (result);
    return result;
}

node_t *
parser_parse (lexer_result_t *lexer)
{
    node_t *root = node_new_list_symbol (NULL);
    node_t *current = root;

    for (u32 i = 0; i < lexer->count; i++)
    {
        if (lexer->entries[ i ].type == lexer_key) // Key
        {
            if (lexer->entries[ i ].content[ 0 ] == '(')
            {
                current = node_new_list_argument (current);
            }
            else if (lexer->entries[ i ].content[ 0 ] == ')')
            {
                if (i + 1 < lexer->count - 1
                    && lexer->entries[ i + 1 ].type == lexer_key
                    && lexer->entries[ i + 1 ].content[ 0 ] == '{')
                    current = current->parent;
                else
                    current = current->parent->parent;
            }
            else if (lexer->entries[ i ].content[ 0 ] == '{')
            {
                current = node_new_list_symbol (current);
            }
            else if (lexer->entries[ i ].content[ 0 ] == '}')
            {
                current = current->parent->parent;
            }
            else if (lexer->entries[ i ].content[ 0 ] == ';'
                     || lexer->entries[ i ].content[ 0 ] == ',')
            {
            }
            else
            {
                node_new_internal (current,
                                   (void *)lexer->entries[ i ].content);
            }
        }
        else
        {
            if (i + 1 < lexer->count - 1
                && lexer->entries[ i + 1 ].type == lexer_key)
            {
                if (lexer->entries[ i ].type == lexer_symbol
                    && lexer->entries[ i + 1 ].content[ 0 ]
                        == '(') // Function call
                {
                    current = node_new_list_symbol (current);
                }
            }

            if (lexer->entries[ i ].type == lexer_symbol) // Symbol
            {
                node_new_symbol (current, lexer->entries[ i ].content);
            }
            else if (lexer->entries[ i ].type == lexer_string) // String
            {
                node_new_string (current, lexer->entries[ i ].content);
            }
            else if (lexer->entries[ i ].type == lexer_number) // Number
            {
                double num = atof (lexer->entries[ i ].content);
                node_new_number (current, num);
            }
        }
    }
    return root;
}

void
parser_transform (node_t *root)
{
    if (!root)
        return;
    for (i32 i = root->children_count - 1; i >= 0; i--)
    {
        if (root->children[ i ]->type == type_internal)
        {
            node_t *key = root->children[ i ];
            root->children[ i ] = node_new_list_symbol (NULL);
            root->children[ i ]->parent = root;
            node_t *parent = root->children[ i ];

            node_t *left_side = node_extract (root->children[ i - 1 ]);
            node_t *right_side = node_extract (root->children[ i ]);

            for (u32 index = 0; index < keys_count; index++)
            {
                if (keys[ index ].function_name
                    && strcmp (keys[ index ].key, key->value.string) == 0)
                {
                    node_new_symbol (parent,
                                     (char *)keys[ index ].function_name);
                    break;
                }
            }

            node_t *args = node_new_list_argument (parent);
            node_insert (args, left_side);
            node_insert (args, right_side);
            i--;
        }
        if (root->children[ i ]->type == type_list_symbol
            || root->children[ i ]->type == type_list_argument
            || root->children[ i ]->type == type_list_data)
            parser_transform (root->children[ i ]);
    }
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
    case type_list_symbol:
        fprintf (f, "<value></value><type>List Symbol</type>");
        break;
    case type_list_data:
        fprintf (f, "<value></value><type>List Data</type>");
        break;
    case type_list_argument:
        fprintf (f, "<value></value><type>List Argument</type>");
        break;
    case type_internal:
        fprintf (f, "<value>%s</value><type>Internal</type>",
                 root->value.string);
        break;
    case type_list_map:
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
    fprintf (f,
             "<!doctype html><html><head><link rel='stylesheet' "
             "href='misc/visualizer.css'></head><body "
             "class='tree-diagram'><ul>");
    parser_visualize_node (f, root);
    fprintf (f, "</ul></body></html>\n");
}
