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

#define ASSIGN_NODE(new_node, new_left, new_right, new_parent, new_type, new_value, new_priority) \
    new_node->left = new_left;                                                                    \
    new_node->right = new_right;                                                                  \
    new_node->parent = new_parent;                                                                \
    new_node->type = new_type;                                                                    \
    new_node->priority = new_priority;                                                            \
                                                                                                  \
    switch(new_type)                                                                              \
    {                                                                                             \
        case 2:                                                                                   \
        {                                                                                         \
            new_node->val.op = new_value;                                                         \
            break;                                                                                \
        }                                                                                         \
        case 1:                                                                                   \
        {                                                                                         \
            new_node->val.num = new_value;                                                        \
            break;                                                                                \
        }                                                                                         \
        case 0:                                                                                   \
        {                                                                                         \
            new_node->val.var = new_value;                                                        \
            break;                                                                                \
        }                                                                                         \
        default:                                                                                  \
        {                                                                                         \
            printf ("UNKNOWN TYPE: %d!\n", new_type);                                             \
            break;                                                                                \
        }                                                                                         \
    }                                                                                             \
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
    Node *new_node = create_node ();                                                            \
    ASSIGN_NODE(new_node, new_left, new_right, new_parent, new_type, new_value, new_priority)

//-----------------------------------------------------------------------------

#endif //COMMON_H
