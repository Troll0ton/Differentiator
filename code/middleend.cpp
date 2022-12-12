#include "../include/middleend.h"

//-----------------------------------------------------------------------------

#define COPY_LEFT copy_tree (curr_node->left, info)
#define COPY_RIGHT copy_tree (curr_node->right, info)
#define LEFT_NODE curr_node->left
#define RIGHT_NODE curr_node->right
#define CALC_DRV(node) calc_derivative (node, info)

Node *calc_derivative (Node *curr_node, Tree_info *info)
{
    value val = { 0 };

    switch(curr_node->type)
    {
        case NUM:
        {
            curr_node->val.num = 0;

            return curr_node;
        }

        case VAR:
        {
            curr_node->type = NUM;
            curr_node->val.num = 1;

            return curr_node;
        }

        case OP:
        {
            #define CMD_DEF(cmd, cmd_name, ...) \
            case cmd:                           \
            {                                   \
                __VA_ARGS__                     \
            }

            switch(curr_node->val.op)
            {
                //-----------------------------------------------------------------------------

                #include "../include/codegen/op_1.h"
                #include "../include/codegen/op_2.h"
                #include "../include/codegen/op_3.h"
                #include "../include/codegen/op_4.h"

                //-----------------------------------------------------------------------------

                default:
                {
                    printf ("UNKNOWN FUNCTION!\n");
                }
            }

            #undef CMD_DEF

            return NULL;
        }

        default:
        {
            printf ("MIDDLEEND - UNKNOWN TYPE!: %d\n", curr_node->type);

            return NULL;
        }
    }
}

//-----------------------------------------------------------------------------

#define LEFT_NUM  curr_node->left->val.num
#define RIGHT_NUM curr_node->right->val.num
#define DETECTED return true

bool simplify_tree (Node *curr_node, Tree_info *info)
{
    if(curr_node->left)
    {
        while(simplify_tree (curr_node->left, info))  { }
    }

    if(curr_node->right)
    {
        while(simplify_tree (curr_node->right, info)) { }
    }

    simplify_node (curr_node, info);

    return false;
}

//-----------------------------------------------------------------------------

bool simplify_node (Node *curr_node, Tree_info *info)
{
    if(simplify_const (curr_node, info))
    {
         DETECTED;
    }

    if(simplify_mul_div_null (curr_node, info))
    {
         DETECTED;
    }

    if(simplify_add_sub_null (curr_node, info))
    {
         DETECTED;
    }

    if(simplify_mul_div_one (curr_node, info))
    {
         DETECTED;
    }

    return false;
}

//-----------------------------------------------------------------------------

bool simplify_mul_div_one (Node *curr_node, Tree_info *info)
{
    if((IS_MUL (curr_node)  ||
        IS_DIV (curr_node)) &&
        IS_ONE (RIGHT_NODE)   )
    {
        Node *old_right = RIGHT_NODE;
        Node *old_left  = LEFT_NODE;

        ASSIGN_NODE (curr_node, old_left->left, old_left->right, curr_node->parent, old_left->type, old_left->val, old_left->priority);

        free (old_right);
        free (old_left);

        DETECTED;
    }

    if((IS_MUL (curr_node)  ||
        IS_DIV (curr_node)) &&
        IS_ONE (LEFT_NODE)    )
    {
        Node *old_right = RIGHT_NODE;
        Node *old_left  = LEFT_NODE;

        ASSIGN_NODE (curr_node, old_right->left, old_right->right, curr_node->parent, old_right->type, old_right->val, old_right->priority);

        free (old_right);
        free (old_left);

        DETECTED;
    }

    return false;
}

//-----------------------------------------------------------------------------

bool simplify_add_sub_null (Node *curr_node, Tree_info *info)
{
    if((IS_ADD (curr_node)  ||
        IS_SUB (curr_node)) &&
        IS_NULL (LEFT_NODE))
    {
        Node *old_right = RIGHT_NODE;
        Node *old_left  = LEFT_NODE;

        ASSIGN_NODE (curr_node, old_right->left, old_right->right, curr_node->parent, old_right->type, old_right->val, old_right->priority);

        free (old_right);
        free (old_left);

        DETECTED;
    }

    if((IS_ADD (curr_node)  ||
        IS_SUB (curr_node)) &&
        IS_NULL (RIGHT_NODE))
    {
        Node *old_right = RIGHT_NODE;
        Node *old_left  = LEFT_NODE;

        ASSIGN_NODE (curr_node, old_left->left, old_left->right, curr_node->parent, old_left->type, old_left->val, old_left->priority);

        free (old_right);
        free (old_left);

        DETECTED;
    }
    return false;
}

//-----------------------------------------------------------------------------

bool simplify_mul_div_null (Node *curr_node, Tree_info *info)
{
    if(IS_MUL (curr_node)  &&
      (IS_NULL (LEFT_NODE) ||
       IS_NULL (RIGHT_NODE)  ))
    {
        ASSIGN_NUM (curr_node, 0);

        tree_dtor (LEFT_NODE);
        tree_dtor (RIGHT_NODE);

        DETECTED;
    }

    if(IS_DIV (curr_node) &&
       IS_NULL (LEFT_NODE))
    {
        ASSIGN_NUM (curr_node, 0);

        tree_dtor (LEFT_NODE);
        tree_dtor (RIGHT_NODE);

        DETECTED;
    }

    return false;
}

//-----------------------------------------------------------------------------

bool simplify_const (Node *curr_node, Tree_info *info)
{
    if(IS_OP (curr_node) &&
       IS_NUM (RIGHT_NODE) &&
     (!LEFT_NODE || IS_NUM (LEFT_NODE)))
    {
        curr_node->type = NUM;
        curr_node->priority = 4;

        #define CMD_DEF(cmd, cmd_name, ...) \
        case cmd:                           \
        {                                   \
            __VA_ARGS__                     \
                                            \
            break;                          \
        }

        switch(curr_node->val.op)
        {
            //-----------------------------------------------------------------------------

            #include "../include/codegen/calc.h"

            //-----------------------------------------------------------------------------

            default:
            {
                printf ("UNKNOWN FUNCTION!\n");
            }
        }

        #undef CMD_DEF

        tree_dtor (LEFT_NODE);
        tree_dtor (RIGHT_NODE);

        DETECTED;
    }

    return false;
}

#undef LEFT_NUM
#undef RIGHT_NUM
#undef LEFT_NODE
#undef RIGHT_NODE
#undef COPY_LEFT
#undef COPY_RIGHT

//-----------------------------------------------------------------------------

void print_expression (Tree_info *info)
{
    LINES;

    fprintf (info->file_tex, "Current expression:\\\\\n");

    print_tree_inorder (info->root, info);

    tree_dump (info);

    ENTER;
}

//-----------------------------------------------------------------------------

void print_derivative (Tree_info *info)
{
    fprintf (info->file_tex, "Calculate Derivative:\\\\\n");

    calc_derivative (info->root, info);

    print_tree_inorder (info->root, info);

    tree_dump (info);

    ENTER;
}

//-----------------------------------------------------------------------------

void print_simplified (Tree_info *info)
{
    fprintf (info->file_tex, "Simplify something:\\\\\n");

    simplify_tree (info->root, info);

    print_tree_inorder (info->root, info);

    tree_dump (info);

    ENTER;
    LINES;
    ENTER;
}

//-----------------------------------------------------------------------------


