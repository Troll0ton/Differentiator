//! @file tree.h

#ifndef   TREE_H
#define   TREE_H

//-----------------------------------------------------------------------------

#include "../include/lines_handle.h"
#include "../include/input_output.h"
#include "../include/stack.h"

//-----------------------------------------------------------------------------

#define trprint(...) fprintf (Info->file_tree, __VA_ARGS__)

#define dot_print(...) fprintf (Info->file_dot, __VA_ARGS__)

//-----------------------------------------------------------------------------

#define tree_info_ctor() tree_info_ctor_ (__FILE__, __LINE__)

//-----------------------------------------------------------------------------

#define N(suffix)  NUM_OF_##suffix

//-----------------------------------------------------------------------------

#define DELETED_PAR -1
#define POISON_PTR  NULL

//-----------------------------------------------------------------------------

enum TREE_INFO
{
    MAX_LEN = 100,
};

//-----------------------------------------------------------------------------

enum TREE_OFFSETS
{
    OFFSET_PARENTHESES = 1,
};

//-----------------------------------------------------------------------------

typedef struct Tree_info
{
    FILE *file_tree;
    FILE *file_dump;
    FILE *file_dot;
    Line *Text;
    File *File_input;
    Node *Root;
    Node *Curr_parent;
    int   curr_line;
    int   curr_cell;
    int   graph_num;

    const char *name;
    const char *log_file;
    int         line;
} Tree_info;

//-----------------------------------------------------------------------------

enum SIDES
{
    LEFT,
    RIGHT,
};

//-----------------------------------------------------------------------------

Node      *create_node          ();

Node      *create_root          (char *name, Tree_info *Info);

Node      *insert_node          (char *name, Node *Parent, int side);

void       save_tree            (Node *Curr_node, Tree_info *Info);

Node      *read_tree            (Tree_info *Info);

void       get_node             (Node *Root);

void       print_tree_preorder  (Node *Root);

Tree_info *tree_info_ctor_      (const char* log_file, int line);

void       tree_info_dtor       (Tree_info *Info);

Node      *search_node          (Node *Curr_node, char *name, Stack *Stk);

void       print_tree_inorder   (Node *Root);

void       tree_dump            (Tree_info *Info);

void       create_tree_graph    (Tree_info *Info);

void       print_tree_postorder (Node *Root);

Node      *handle_end_node      (Tree_info *Info);

Node      *handle_branch_node   (Tree_info *Info);

void       create_cell          (Node *Root, Tree_info *Info);

void       build_connections    (Node *Root, Tree_info *Info);

void       tree_dtor            (Node *Curr_node);

//-----------------------------------------------------------------------------

#endif //TREE_H
