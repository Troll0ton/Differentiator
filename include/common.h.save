//! @file common.h

#ifndef COMMON_H
#define COMMON_H

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
    ADD,
    SUB,
    MUL,
    DIV,
    POW,
    SIN,
    COS,
    LN,
    TG,
    CTG,
    ARCSIN,
    ARCCOS,
    ARCTG,
    ARCCTG,
};

//-----------------------------------------------------------------------------

#define IS_(SYM)    \
   **grammar == SYM

//-----------------------------------------------------------------------------

#define IS_FUNCT(curr_node)        \
    curr_node->type == OP    &&    \
    curr_node->priority == 4 &&    \
    curr_node->right->type == NUM  \

#define IS_NUM(curr_node)          \
    curr_node->type == NUM

#define IS_NULL(curr_node)                                       \
    (curr_node->type == NUM && is_equal (curr_node->val.num, 0))

#define IS_ONE(curr_node)                                        \
    (curr_node->type == NUM && is_equal (curr_node->val.num, 1))

//-----------------------------------------------------------------------------

#define IS_ADD(curr_node)                                       \
    (curr_node->type == OP && curr_node->val.op == ADD)

#define IS_SUB(curr_node)                                       \
    (curr_node->type == OP && curr_node->val.op == SUB)

#define IS_MUL(curr_node)                                       \
    (curr_node->type == OP && curr_node->val.op == MUL)

#define IS_DIV(curr_node)                                       \
    (curr_node->type == OP && curr_node->val.op == DIV)

#define IS_OP(curr_node)           \
    curr_node->type == OP

//-----------------------------------------------------------------------------

#define CASE(SYM, VAL)  \
    case SYM:           \
    {                   \
        val.op = VAL;   \
                        \
        break;          \
    }

//-----------------------------------------------------------------------------

#define INIT(OPERATION, PRIORITY)  \
    value val = { 0 };             \
    val.op = OPERATION;            \
    INIT_OP(val, PRIORITY);

//-----------------------------------------------------------------------------

#define INIT_OP(val, hight) INIT_NODE (new_node, left_node, right_node, NULL, OP, val, hight)

//-----------------------------------------------------------------------------

#define INIT_VAR(val) INIT_NODE (new_node, NULL, NULL, NULL, VAR, val, 4)

#define INIT_NUM(val) INIT_NODE (new_node, NULL, NULL, NULL, NUM, val, 4)

//-----------------------------------------------------------------------------

#define ASSIGN_NODE(new_node, new_left, new_right, new_parent, new_type, new_value, new_priority) \
    new_node->left = new_left;                                                                    \
    new_node->right = new_right;                                                                  \
    new_node->parent = new_parent;                                                                \
    new_node->type = new_type;                                                                    \
    new_node->priority = new_priority;                                                            \
                                                                                                  \
    new_node->val = new_value;                                                                    \
                                                                                                  \
    if(new_node->left)                                                                            \
    {                                                                                             \
        new_node->left->parent = new_node;                                                        \
    }                                                                                             \
                                                                                                  \
    if(new_node->right)                                                                           \
    {                                                                                             \
        new_node->right->parent = new_node;                                                       \
    }

//-----------------------------------------------------------------------------

#define LINES fprintf (info->file_tex, "---------------------------------------------------------------------------------------------------------------------------\\\\\n");

#define ENTER fprintf (info->file_tex, "\\\\\n");

//-----------------------------------------------------------------------------

#define INIT_NODE(new_node, new_left, new_right, new_parent, new_type, new_value, new_priority)                                                                                       \
    Node *new_node = create_node ();                                                              \
    ASSIGN_NODE(new_node, new_left, new_right, new_parent, new_type, new_value, new_priority)

//-----------------------------------------------------------------------------

#endif //COMMON_H
