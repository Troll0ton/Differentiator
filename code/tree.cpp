#include "../include/tree.h"

//-----------------------------------------------------------------------------

Tree_info *tree_info_ctor_ (const char* log_file, int line)
{
    Tree_info *info = (Tree_info*) calloc (1, sizeof (Tree_info));

    info->line      = line;
    info->log_file  = log_file;
    info->root      = NULL;

    info->file_tree = fopen ("../files/tree.txt",       "a+");
    info->file_expr = fopen ("../files/expression.txt", "w+");
    info->file_dump = fopen ("../dump/tree_dump.html",  "w+");

    info->File_input = file_reader (info->file_tree);
    info->Text = lines_separator (info->File_input);

    info->curr_line = 0;
    info->curr_cell = 0;
    info->graph_num = 0;

    return info;
}

//-----------------------------------------------------------------------------

void tree_info_dtor (Tree_info *info)
{
    info->root = NULL;
    info->Curr_parent = NULL;

    fclose (info->file_tree);
    fclose (info->file_expr);
    fclose (info->file_dump);

    clear_mem (info->Text, info->File_input);

    info->curr_line = DELETED_PAR;
    info->curr_cell = DELETED_PAR;

    free (info);
}

//-----------------------------------------------------------------------------

Node *create_node ()
{
    Node *New_node = (Node*) calloc (1, sizeof (Node));

    if(!New_node)
    {
        printf ("ERROR - memory allocation for new node!\n");
    }

    else
    {
        New_node->parent = NULL;
        New_node->left   = NULL;
        New_node->right  = NULL;
    }

    return New_node;
}

//-----------------------------------------------------------------------------

Node *create_root (int type, value val, Tree_info *info)
{
    Node *root = create_node ();
    info->root = root;

    root->type = type;

    root->val = val;

    return root;
}

//-----------------------------------------------------------------------------

void print_tree_inorder (Node *curr_node)
{
    printf ("(");

    if(curr_node->left)
    {
        print_tree_inorder (curr_node->left);
    }

    if(curr_node->type == OP)
    {
        printf ("%c", curr_node->val.op);
    }

    else if(curr_node->type == NUM)
    {
        printf ("%lg", curr_node->val.num);
    }

    else if(curr_node->type == VAR)
    {
        printf ("%c", curr_node->val.var);
    }

    else
    {
        printf ("UNKNOWN VALUE!\n");
    }

    if(curr_node->right)
    {
        print_tree_inorder (curr_node->right);
    }

    printf (")");
}

//-----------------------------------------------------------------------------

#define root info->root

void tree_dump (Tree_info *info)
{
    fprintf (info->file_dump,
             "<pre>\n"
             "_________________________TREE__________________________________\n\n"
             "TREE - [root - %p] at %s, LINE - %d \n\n",
             root, info->log_file, info->line);

    create_tree_graph (info);

    fprintf (info->file_dump,
             "_______________________________________________________________ \n</pre>\n\n");
}

//-----------------------------------------------------------------------------

#define CURR_CELL info->curr_cell

void create_tree_graph (Tree_info *info)
{
    info->file_dot = fopen ("../dump/list_graph.dot", "w+");

    dot_print ("digraph structs {    \n"
               "rankdir = TB;        \n"
               "graph [dpi = 200];   \n"
               "ranksep = 1.5;       \n"
               "edge[penwidth = 10]; \n");

    CURR_CELL = 0;

    create_cell (root, info);

    CURR_CELL = 1;

    dot_print("cell0 ");

    build_connections (root->left, info);

    dot_print("cell0 ");

    CURR_CELL++;

    build_connections (root->right, info);

    dot_print ("}\n");

    fclose (info->file_dot);

    char img_name[MAX_LEN] = "";
    char dot_name[MAX_LEN] = "";

    sprintf (img_name, "<img width=\"1400px\" src=\"../dump/graph%d.png\">   \n", info->graph_num);
    sprintf (dot_name, "dot -Tpng ../dump/list_graph.dot -o ../dump/graph%d.png", info->graph_num);

    info->graph_num++;

    system (dot_name);

    fprintf (info->file_dump, "%s", img_name);
}

#undef root

//-----------------------------------------------------------------------------

void create_cell (Node *root, Tree_info *info)
{
    dot_print ("cell%d [style = filled, color = black, shape=record, \n",
               CURR_CELL);

    if(root->type == OP)
    {
        dot_print ("fillcolor = paleturquoise1, label = \" { <ptr> TYPE: OPERATION | %c",
                   root->val.op);
    }

    else if(root->type == NUM)
    {
        dot_print ("fillcolor = coral2, label = \" { <ptr> TYPE: NUMERIC | %lg",
                   root->val.num);
    }

    else if(root->type == VAR)
    {
        dot_print ("fillcolor = darkolivegreen2, label = \" { <ptr> TYPE: VARIABLE | %c",
                   root->val.var);
    }

    else
    {
        printf ("|UNKNOWN VALUE - %d!\n", root->type);
    }

    dot_print ("} \" ];                         \n"),

    CURR_CELL++;

    if(root->left)
    {
        create_cell (root->left, info);
    }

    if(root->right)
    {
        create_cell (root->right, info);
    }
}

//-----------------------------------------------------------------------------

void build_connections (Node *root, Tree_info *info)

{
    dot_print("-> cell%d;\n", CURR_CELL);

    int prev_cell = CURR_CELL;

    if(root->left)
    {
        dot_print("cell%d ", prev_cell);

        CURR_CELL++;

        build_connections (root->left, info);
    }

    if(root->right)
    {
        dot_print("cell%d ", prev_cell);

        CURR_CELL++;

        build_connections (root->right, info);
    }
}

#undef CURR_CELL

//-----------------------------------------------------------------------------

void tree_dtor (Node *curr_node)
{
    if(curr_node->left)
    {
        tree_dtor (curr_node->left);
    }

    if(curr_node->right)
    {
        tree_dtor (curr_node->right);
    }

    free (curr_node);
}

//-----------------------------------------------------------------------------



