#include "../include/middleend.h"

//-----------------------------------------------------------------------------

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
                    curr_node->left  = calc_derivative (curr_node->left,  info);
                    curr_node->right = calc_derivative (curr_node->right, info);

                    return curr_node;
                }

                case '-':
                {
                    curr_node->left  = calc_derivative (curr_node->left,  info);
                    curr_node->right = calc_derivative (curr_node->right, info);

                    return curr_node;
                }

                case '*':
                {
                    Node *left_node_c  = copy_tree (curr_node->left, info);
                    Node *right_node_c = copy_tree (curr_node->right, info);

                    Node *new_node_1   = create_node ();
                    new_node_1->type   = OP;
                    new_node_1->val.op = '*';
                    new_node_1->priority = 2;
                    new_node_1->parent = curr_node;
                    new_node_1->left   = calc_derivative (curr_node->left, info);
                    new_node_1->right  = right_node_c;
                    new_node_1->left->parent = new_node_1;
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

                    left_node_c->parent = new_node_1;
                    right_node_c->parent = new_node_2;

                    curr_node->val.op = '+';
                    curr_node->priority = 1;
                    curr_node->left  = new_node_1;
                    curr_node->right = new_node_2;

                    return curr_node;
                }

                case '/':
                {
                    Node *new_node_sub   = create_node ();
                    new_node_sub->type   = OP;
                    new_node_sub->val.op = '-';

                    Node *new_node_1   = create_node ();
                    new_node_1->type   = OP;
                    new_node_1->val.op = '*';
                    new_node_1->parent = new_node_sub;
                    new_node_1->left   = calc_derivative (curr_node->left, info);
                    new_node_1->right  = curr_node->right;
                    new_node_1->left->parent  = new_node_1;
                    new_node_1->right->parent = new_node_1;

                    Node *new_node_2   = create_node ();
                    new_node_2->type   = OP;
                    new_node_2->val.op = '*';
                    new_node_2->parent = new_node_sub;
                    new_node_2->left   = curr_node->left;
                    new_node_2->right  = calc_derivative (curr_node->right, info);
                    new_node_2->left->parent  = new_node_2;
                    new_node_2->right->parent = new_node_2;

                    new_node_sub->left  = new_node_1;
                    new_node_sub->right = new_node_2;

                    //-----------------------------------------------------------------------------

                    Node *new_node_deg = create_node ();
                    new_node_deg->type   = OP;
                    new_node_deg->val.op = '*';
                    new_node_deg->parent = new_node_sub;
                    new_node_deg->left   = curr_node->right;
                    new_node_deg->right  = curr_node->right;
                    curr_node->left->parent  = new_node_deg;
                    curr_node->right->parent = new_node_deg;

                    //-----------------------------------------------------------------------------

                    curr_node->left  = new_node_sub;
                    curr_node->right = new_node_deg;

                    return curr_node;
                }

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

//-----------------------------------------------------------------------------


