#include "../include/middleend.h"

//-----------------------------------------------------------------------------

#define COPY_LEFT copy_tree (curr_node->left, info)
#define COPY_RIGHT copy_tree (curr_node->right, info)
#define LEFT_NODE curr_node->left
#define RIGHT_NODE curr_node->right
#define CALC_DRV(node) calc_derivative (node, info)

Node *calc_derivative (Node *curr_node, Tree_info *info)
{
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
            switch(curr_node->val.op)
            {
                case '+':
                {
                    LEFT_NODE  = CALC_DRV (LEFT_NODE);
                    RIGHT_NODE = CALC_DRV (RIGHT_NODE);

                    return curr_node;
                }

                case '-':
                {
                    LEFT_NODE  = CALC_DRV (LEFT_NODE);
                    RIGHT_NODE = CALC_DRV (RIGHT_NODE);

                    return curr_node;
                }

                case '*':
                {
                    Node *left_node_c  = COPY_LEFT;
                    Node *right_node_c = COPY_RIGHT;

                    INIT_NODE (new_node_1, CALC_DRV (LEFT_NODE), right_node_c, curr_node, OP, '*', 2);

                    INIT_NODE (new_node_2, left_node_c, CALC_DRV (RIGHT_NODE), curr_node, OP, '*', 2);

                    ASSIGN_NODE (curr_node, new_node_1, new_node_2, curr_node->parent, OP, '+', 1);

                    return curr_node;
                }

                case '/':
                {
                    Node *left_node_c   = COPY_LEFT;
                    Node *right_node_c  = COPY_RIGHT;
                    Node *right_node_c1 = COPY_RIGHT;
                    Node *right_node_c2 = COPY_RIGHT;

                    INIT_NODE (new_node_1, CALC_DRV (LEFT_NODE), right_node_c, NULL, OP, '*', 2);

                    INIT_NODE (new_node_2, left_node_c, CALC_DRV (RIGHT_NODE), NULL, OP, '*', 2);

                    INIT_NODE (new_node_sub, new_node_1, new_node_2, curr_node, OP, '-', 1);

                    INIT_NODE (new_node_deg, right_node_c1, right_node_c2, curr_node, OP, '*', 2);

                    ASSIGN_NODE (curr_node, new_node_sub, new_node_deg, curr_node->parent, OP, '/', 2);

                    return curr_node;
                }
                /*
                case '^':
                {
                    Node *left_node_c  = copy_tree (curr_node->left, info);
                    Node *right_node_c = copy_tree (curr_node->right, info);

                    Node *new_node_1   = create_node ();
                    new_node_1->type   = OP;
                    new_node_1->val.op = '-';
                    new_node_1->priority = 1;
                    new_node_1->parent = curr_node;
                    new_node_1->left   = right_node_c;

                    Node *one_node     = create_node ();
                    one_node->type     = NUM;
                    one_node->val.num  = 1;
                    one_node->priority = 4;
                    one_node->parent   = new_node_1;

                    new_node_1->left   = right_node_c;
                    new_node_1->right  = one_node;
                    new_node_1->left->parent  = new_node_1;
                    new_node_1->right->parent = new_node_1;

                    Node *new_node_2   = create_node ();
                    new_node_2->type   = OP;
                    new_node_2->val.op = '*';
                    new_node_2->priority = 2;
                    new_node_2->parent = curr_node;
                    new_node_2->left   = left_node_c;
                    new_node_2->right  = calc_derivative (curr_node->right, info);
                    new_node_2->left->parent = new_node_2;
                    new_node_2->right->parent = new_node_2;

                    curr_node->val.op = '*';
                    curr_node->priority = 2;
                    curr_node->left  = new_node_1;
                    curr_node->right = new_node_2;

                    return curr_node;
                    break;
                } */

                default:
                {
                    printf ("E");

                    break;
                }
            }

            break;
        }

        default:
        {
            printf ("MIDDLEEND - UNKNOWN TYPE!: %d\n",
                    curr_node->type);
            break;
        }
    }
}

#undef LEFT_NODE
#undef RIGHT_NODE
#undef COPY_LEFT
#undef COPY_RIGHT

//-----------------------------------------------------------------------------


