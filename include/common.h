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

#define CASE(SYM, VAL)  \
    case SYM:           \
    {                   \
        val.op = VAL;   \
                        \
        break;          \
    }

//-----------------------------------------------------------------------------

#define INIT_ADD(new_node, left_node, right_node, parent_node)  \
    value val;                                                  \
    val.op = ADD;                                               \
    INIT_OP_1;                                                  \

//-----------------------------------------------------------------------------

#define INIT(OPERATION, PRIORITY)  \
    value val = { 0 };             \
    val.op = OPERATION;            \
    INIT_OP_##PRIORITY;

//-----------------------------------------------------------------------------

#define INIT_OP_1 INIT_NODE (new_node, left_node, right_node, NULL, OP, val, 1)

#define INIT_OP_2 INIT_NODE (new_node, left_node, right_node, NULL, OP, val, 2)

#define INIT_OP_3 INIT_NODE (new_node, left_node, right_node, NULL, OP, val, 3)

#define INIT_OP_4 INIT_NODE (new_node, NULL, right_node, NULL, OP, val, 4)

//-----------------------------------------------------------------------------

#define INIT_VAR INIT_NODE (new_node, NULL, NULL, NULL, VAR, val, 4)

#define INIT_NUM INIT_NODE (new_node, NULL, NULL, NULL, NUM, val, 4)

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

#define INIT_NODE(new_node, new_left, new_right, new_parent, new_type, new_value, new_priority)                                                                                       \
    Node *new_node = create_node ();                                                              \
    ASSIGN_NODE(new_node, new_left, new_right, new_parent, new_type, new_value, new_priority)

//-----------------------------------------------------------------------------

#endif //COMMON_H
