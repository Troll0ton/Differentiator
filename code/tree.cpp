#include "../include/tree.h"

//-----------------------------------------------------------------------------

Tree_info *tree_info_ctor_ (const char* log_file, int line)
{
    Tree_info *Info = (Tree_info*) calloc (1, sizeof (Tree_info));

    Info->line        = line;
    Info->log_file    = log_file;
    Info->Root        = NULL;
    Info->Curr_parent = NULL;

    Info->file_tree = fopen ("../files/tree.txt",      "r");
    Info->file_dump = fopen ("../dump/tree_dump.html", "w+");

    Info->File_input = file_reader (Info->file_tree);
    Info->Text = lines_separator (Info->File_input);

    Info->curr_line = 0;
    Info->curr_cell = 0;
    Info->graph_num = 0;

    return Info;
}

//-----------------------------------------------------------------------------

void tree_info_dtor (Tree_info *Info)
{
    Info->Root = NULL;
    Info->Curr_parent = NULL;

    fclose (Info->file_tree);
    fclose (Info->file_dump);

    clear_mem (Info->Text, Info->File_input);

    Info->curr_line = DELETED_PAR;
    Info->curr_cell = DELETED_PAR;

    free (Info);
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
        New_node->Parent = NULL;
        New_node->Left   = NULL;
        New_node->Right  = NULL;

        New_node->name = NULL;
    }

    return New_node;
}

//-----------------------------------------------------------------------------

Node *create_root (char *name, Tree_info *Info)
{
    Node *Root = create_node ();
    Info->Root = Root;

    Root->name = name;

    return Root;
}

//-----------------------------------------------------------------------------

Node *insert_node (char *name, Node *Parent, int side)
{
    Node *New_node = create_node ();

    New_node->name = name;

    New_node->Parent = Parent;

    if(side == LEFT)
    {
        Parent->Left = New_node;
    }

    else if(side == RIGHT)
    {
        Parent->Right = New_node;
    }

    else
    {
        printf ("ERROR - insert unknown side!\n");
    }

    return New_node;
}

//-----------------------------------------------------------------------------

Node *search_node (Node *Curr_node, char *name, Stack *Stk)
{
    if(!Curr_node)
    {
        return NULL;
    }

    if(stricmp (Curr_node->name, name) == 0)
    {
        stack_push (Stk, Curr_node);

        return Curr_node;
    }

    Node* Find_left  = search_node (Curr_node->Left,  name, Stk);
    Node* Find_right = search_node (Curr_node->Right, name, Stk);

    if(Find_left)
    {
        stack_push (Stk, Curr_node);

        return Find_left;
    }

    if(Find_right)
    {
        stack_push (Stk, Curr_node);

        return Find_right;
    }

    return NULL;
}

//-----------------------------------------------------------------------------

void save_tree (Node *Curr_node, Tree_info *Info)
{
    trprint("{%s", Curr_node->name);

    if(Curr_node->Left || Curr_node->Right)
    {
        trprint("\n");

        if(Curr_node->Left)
        {
            save_tree (Curr_node->Left, Info);
        }

        else trprint("{NULL}\n");

        if(Curr_node->Right)
        {
            save_tree (Curr_node->Right, Info);
        }

        else trprint("{NULL}\n");
    }

    trprint("}\n");
}

//-----------------------------------------------------------------------------

#define CURR_LINE Info->Text[Info->curr_line].begin_line

Node *read_tree (Tree_info *Info)
{
    char sym = 0;

    sscanf (CURR_LINE, "%c", &sym);

    if(sym == '{')
    {
        char *parenth_pos = strchr (CURR_LINE, '}');

        if(parenth_pos == NULL)
        {
            return handle_branch_node (Info);
        }

        else
        {
            *parenth_pos = '\0';

            return handle_end_node (Info);
        }
    }

    else
    {
        printf ("unidentified symbol;\n");

        return POISON_PTR;
    }

    printf ("\n");
}

//-----------------------------------------------------------------------------

Node *handle_branch_node (Tree_info *Info)
{
    Node *New_node = NULL;

    if(!Info->Root)
    {
        New_node = create_root (CURR_LINE + OFFSET_PARENTHESES, Info);
    }

    else
    {
        New_node = create_node ();

        New_node->name = CURR_LINE + OFFSET_PARENTHESES;

        New_node->Parent = Info->Curr_parent;
    }

    Info->Curr_parent = New_node;

    Info->curr_line++;

    New_node->Left  = read_tree (Info);
    New_node->Right = read_tree (Info);

    Info->curr_line++;

    return New_node;
}

//-----------------------------------------------------------------------------

Node *handle_end_node (Tree_info *Info)
{
    Node *New_node   = create_node ();
    New_node->Parent = Info->Curr_parent;

    New_node->name = CURR_LINE + OFFSET_PARENTHESES;

    Info->curr_line++;

    return New_node;
}

#undef CURR_LINE

//-----------------------------------------------------------------------------

void print_tree_preorder (Node *Root)
{
    printf ("(%s", Root->name);

    if(Root->Left)  print_tree_preorder (Root->Left);
    if(Root->Right) print_tree_preorder (Root->Right);

    printf (")");
}

//-----------------------------------------------------------------------------

void print_tree_inorder (Node *Root)
{
    Node *Curr_node = Root;

    printf ("(");

    if(Curr_node->Left)  print_tree_inorder (Curr_node->Left);

    printf ("%s", Curr_node->name);

    if(Curr_node->Right) print_tree_inorder (Curr_node->Right);

    printf (")");
}

//-----------------------------------------------------------------------------

void print_tree_postorder (Node *Root)
{
    Node *Curr_node = Root;

    printf ("(");

    if(Curr_node->Left)  print_tree_postorder (Curr_node->Left);

    if(Curr_node->Right) print_tree_postorder (Curr_node->Right);

    printf ("%s)", Curr_node->name);
}

//-----------------------------------------------------------------------------

#define ROOT Info->Root

void tree_dump (Tree_info *Info)
{
    fprintf (Info->file_dump,
             "<pre>\n"
             "_________________________TREE__________________________________\n\n"
             "TREE - [Root - %p] at %s, LINE - %d \n\n",
             ROOT, Info->log_file, Info->line);

    create_tree_graph (Info);

    fprintf (Info->file_dump,
             "_______________________________________________________________ \n</pre>\n\n");
}

//-----------------------------------------------------------------------------

#define CURR_CELL Info->curr_cell

void create_tree_graph (Tree_info *Info)
{
    Info->file_dot = fopen ("../dump/list_graph.dot", "w+");

    dot_print ("digraph structs {    \n"
               "rankdir = TB;        \n"
               "graph [dpi = 200];   \n"
               "ranksep = 1.5;       \n"
               "edge[penwidth = 10]; \n");

    CURR_CELL = 0;

    create_cell (ROOT, Info);

    CURR_CELL = 1;

    dot_print("cell0 ");

    build_connections (ROOT->Left, Info);

    dot_print("cell0 ");

    CURR_CELL++;

    build_connections (ROOT->Right, Info);

    dot_print ("}\n");

    fclose (Info->file_dot);

    char img_name[MAX_LEN] = "";
    char dot_name[MAX_LEN] = "";

    sprintf (img_name, "<img width=\"1400px\" src=\"../dump/graph%d.png\">   \n", Info->graph_num);
    sprintf (dot_name, "dot -Tpng ../dump/list_graph.dot -o ../dump/graph%d.png", Info->graph_num);

    Info->graph_num++;

    system (dot_name);

    fprintf (Info->file_dump, "%s", img_name);
}

#undef ROOT

//-----------------------------------------------------------------------------

void create_cell (Node *Root, Tree_info *Info)
{
    dot_print ("cell%d [style = filled, color = black, fillcolor = paleturquoise1,\n"
               "shape=record,label = \" { <ptr> %s} \" ];                         \n",
               CURR_CELL, Root->name);

    CURR_CELL++;

    if(Root->Left)
    {
        create_cell (Root->Left, Info);
    }

    if(Root->Right)
    {
        create_cell (Root->Right, Info);
    }
}

//-----------------------------------------------------------------------------

void build_connections (Node *Root, Tree_info *Info)
{
    dot_print("-> cell%d;\n", CURR_CELL);

    int prev_cell = CURR_CELL;

    if(Root->Left)
    {
        dot_print("cell%d ", prev_cell);

        CURR_CELL++;

        build_connections (Root->Left, Info);
    }

    if(Root->Right)
    {
        dot_print("cell%d ", prev_cell);

        CURR_CELL++;

        build_connections (Root->Right, Info);
    }
}

#undef CURR_CELL

//-----------------------------------------------------------------------------

void tree_dtor (Node *Curr_node)
{
    if(Curr_node->Left)
    {
        tree_dtor (Curr_node->Left);
    }

    if(Curr_node->Right)
    {
        tree_dtor (Curr_node->Right);
    }

    free (Curr_node);
}

//-----------------------------------------------------------------------------


