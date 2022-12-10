//! @file tree.h

#ifndef TREE_H
#define TREE_H

//-----------------------------------------------------------------------------

#include "../include/lines_handle.h"
#include "../include/input_output.h"
#include "../include/common.h"

//-----------------------------------------------------------------------------

#define trprint(...) fprintf (info->file_tree, __VA_ARGS__)

#define txprint(...) fprintf (info->file_tex, __VA_ARGS__)

#define dot_print(...) fprintf (info->file_dot, __VA_ARGS__)

//-----------------------------------------------------------------------------

#define tree_info_ctor(info, File_input, Text) tree_info_ctor_ (info, File_input, Text, __FILE__, __LINE__)

//-----------------------------------------------------------------------------

#define N(suffix) num_of_##suffix

//-----------------------------------------------------------------------------

#define DELETED_PAR -1
#define POISON_PTR  NULL

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
    char  priority;
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
    FILE *file_in;
    FILE *file_dump;
    FILE *file_tex;
    FILE *file_dot;
    FILE *file_expr;
    Line *Text;
    File *File_input;
    Node *root;
    Node *curr_parent;
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

void       tree_info_ctor_    (Tree_info *info, File *File_input, Line *Text, const char* log_file, int line);

void       tree_info_dtor     (Tree_info *info);

Node      *create_node        ();

Node      *create_root        (int type, value val, Tree_info *info);

void       print_tree_inorder (Node *curr_node, Tree_info *info);

void       tree_dump          (Tree_info *info);

void       create_tree_graph  (Tree_info *info);

void       create_latex_file  (Tree_info *info);

void       convert_to_pdf     (Tree_info *info);

//void     greetings          ();

Node      *copy_tree          (Node *orig_root, Tree_info *info);

Node      *copy_node          (Node *curr_node, Tree_info *info);

void       create_cell        (Node *root, Tree_info *info);

void       build_connections  (Node *root, Tree_info *info);

void       tree_dtor          (Node *curr_node);

//-----------------------------------------------------------------------------

#endif //TREE_H
