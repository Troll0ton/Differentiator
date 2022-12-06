#include "../include/tree.h"

//-----------------------------------------------------------------------------

void greetings ()
{
    txCreateWindow (1000, 600);

    txSetFillColor (TX_BLACK);
    txSetColor     (TX_WHITE);

    txSelectFont   ("Comic Sans MS", 120);
    txTextOut (50,  200, "DIFFERENTIATOR.");
    txSleep   (4000);
    txClear   ();

    txSelectFont   ("Comic Sans MS", 60);

    txTextOut (300, 200, "BY WALTER WHITE.");

    HDC image1 = txLoadImage ("C:/Users/ASUS_TUF_GAMING/Desktop/Git_Hub/Differentiator/images/walter.bmp", 300, 400);

    if (!image1)
    {
        txMessageBox ("�� ���� ��������� ��� �� Background.bmp", "��, � ���������� ��� �� �������");
    }

    txBitBlt (txDC(), 0, 0, 800, 600, image1, 0, 0);

    txDeleteDC (image1);

    txSleep   (4000);
    txClear   ();
}

//-----------------------------------------------------------------------------

Tree_info *tree_info_ctor_ (const char* log_file, int line)
{
    Tree_info *info = (Tree_info*) calloc (1, sizeof (Tree_info));

    info->line      = line;
    info->log_file  = log_file;
    info->root      = NULL;

    info->file_dump = fopen ("../dump/tree_dump.html",  "w+");
    info->file_in   = fopen ("../files/task1.txt", "rb");

    info->File_input = file_reader (info->file_in);
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
    info->curr_parent = NULL;

    fclose (info->file_dump);

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

Node *copy_tree (Node *orig_root, Tree_info *info)
{
    Node *new_root = create_node ();

    new_root->type = orig_root->type;
    new_root->val  = orig_root->val;

    info->curr_parent = orig_root;

    if(orig_root->left)
    {
        new_root->left = copy_node (orig_root->left, info);
    }

    if(orig_root->right)
    {
        new_root->right = copy_node (orig_root->right, info);
    }

    return new_root;
}

//-----------------------------------------------------------------------------

Node *copy_node (Node *curr_node, Tree_info *info)
{
    Node *new_node = create_node ();

    new_node->type = curr_node->type;
    new_node->val  = curr_node->val;

    new_node->parent  = info->curr_parent;
    info->curr_parent = new_node;

    if(curr_node->left)
    {
        new_node->left = copy_node (curr_node->left, info);
    }

    if(curr_node->right)
    {
        new_node->right = copy_node (curr_node->right, info);
    }

    return new_node;
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



