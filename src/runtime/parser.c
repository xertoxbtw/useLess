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
    node_t *root = node_new_list_symbol (NULL);
    node_t *current = root;

    u32 close_counter = 0;
    u32 translation_counter = 0, translation_amount = 0;

    for (u32 i = 0; i < lexer->count; i++)
    {
        if (translation_counter)
        {
            translation_counter--;
            if (translation_counter == 0)
            {
                for (u32 b = 0; b < translation_amount; b++)
                    current = current->parent;
                translation_amount = 0;
            }
        }
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
                {
                    current = current->parent;
                }
                else
                {
                    if (close_counter-- > 0)
                        current = current->parent;
                    current = current->parent;
                }
            }
            else if (lexer->entries[ i ].content[ 0 ] == '{')
            {
                current = node_new_list_symbol (current);
            }
            else if (lexer->entries[ i ].content[ 0 ] == '}')
            {
                if (close_counter-- > 0)
                    current = current->parent;
                current = current->parent;
            }
            else if (lexer->entries[ i ].content[ 0 ] == ';')
            {
                if ((i32)i - 1 >= 0 && lexer->entries[ i - 1 ].type == lexer_key
                    && lexer->entries[ i - 1 ].content[ 0 ] == ')')
                {
                    // Todo: If close_counter == 0 also check if
                    // *lexer->entries[ i - 1 ].content[ 0 ] == '}'*
                }
                else
                {
                    if (close_counter-- > 0)
                        current = current->parent->parent;
                }
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
                    close_counter++;
                }
                else if (lexer->entries[ i ].type == lexer_symbol
                         && lexer->entries[ i + 1 ].content[ 0 ]
                             == '[') // array call
                {
                    exit (1); // TODO
                }
                else
                {
                    for (u32 key = 0; key < keys_count; key++)
                    {
                        if (keys[ key ].function_name
                            && strcmp (keys[ key ].key,
                                       lexer->entries[ i + 1 ].content)
                                == 0)
                        {
                            current = node_new_list_symbol (current);
                            node_new_symbol (current,
                                             keys[ key ].function_name);
                            current = node_new_list_argument (current);
                            close_counter++;
                            break;
                        }
                    }
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
        // Todo
        fprintf (f, "Todo");
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
