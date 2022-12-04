//! @file tree.h

#ifndef TREE_H
#define TREE_H

//-----------------------------------------------------------------------------

#include "../include/lines_handle.h"
#include "../include/input_output.h"

//-----------------------------------------------------------------------------

#define trprint(...) fprintf (info->file_tree, __VA_ARGS__)

#define dot_print(...) fprintf (info->file_dot, __VA_ARGS__)

//-----------------------------------------------------------------------------

#define tree_info_ctor() tree_info_ctor_ (__FILE__, __LINE__)

//-----------------------------------------------------------------------------

#define N(suffix)  NUM_OF_##suffix

//-----------------------------------------------------------------------------

#define DELETED_PAR -1
#define POISON_PTR  NULL

//-----------------------------------------------------------------------------

enum TYPES
{
    VAR,
    NUM,
    OP,
};

//-----------------------------------------------------------------------------

enum OPERATIONS
{
    //11000000 - first two bits are priority

    ADD = 0x40,
    SUB = 0x41,
    MUL = 0x80,
    DIV = 0x81,
};

//-----------------------------------------------------------------------------

typedef union value
{
    double num;
    char op;
    char var;
} value;

//-----------------------------------------------------------------------------

typedef struct Node
{
    Node *parent;
    Node *left;
    Node *right;
    int   type;
    union value val;
} Node;

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
    FILE *file_expr;
    Line *Text;
    File *File_input;
    Node *root;
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
    left,
    right,
};

//-----------------------------------------------------------------------------

Tree_info *tree_info_ctor_    (const char* log_file, int line);

void       tree_info_dtor     (Tree_info *info);

Node      *create_node        ();

Node      *create_root        (int type, value val, Tree_info *info);

void       print_tree_inorder (Node *curr_node);

void       tree_dump          (Tree_info *info);

void       create_tree_graph  (Tree_info *info);

void       create_cell        (Node *root, Tree_info *info);

void       build_connections  (Node *root, Tree_info *info);

void       tree_dtor          (Node *curr_node);

//-----------------------------------------------------------------------------

#endif //TREE_H
