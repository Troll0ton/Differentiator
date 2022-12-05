#include "../include/middleend.h"

//-----------------------------------------------------------------------------

Node *calc_derivative (Node *curr_node)
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
                    curr_node->left  = calc_derivative (curr_node->left);
                    curr_node->right = calc_derivative (curr_node->right);

                    return curr_node;
                }

                case '-':
                {
                    curr_node->left  = calc_derivative (curr_node->left);
                    curr_node->right = calc_derivative (curr_node->right);

                    return curr_node;
                }

                case '*':
                {
                    Node *left_node_c = create_node ();
                    *left_node_c = *(curr_node->left);
                    Node *right_node_c = create_node ();
                    *right_node_c = *(curr_node->right);

                    Node *new_node_1   = create_node ();
                    new_node_1->type   = OP;
                    new_node_1->val.op = '*';
                    new_node_1->parent = curr_node;
                    new_node_1->left   = calc_derivative (left_node_c);
                    new_node_1->right  = curr_node->right;
                    new_node_1->left->parent  = new_node_1;
                    new_node_1->right->parent = new_node_1;

                    Node *new_node_2   = create_node ();
                    new_node_2->type   = OP;
                    new_node_2->val.op = '*';
                    new_node_2->parent = curr_node;
                    new_node_2->left   = curr_node->left;
                    new_node_2->right  = calc_derivative (right_node_c);
                    new_node_2->left->parent  = new_node_2;
                    new_node_2->right->parent = new_node_2;

                    curr_node->val.op = '+';
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
                    new_node_1->left   = calc_derivative (curr_node->left);
                    new_node_1->right  = curr_node->right;
                    new_node_1->left->parent  = new_node_1;
                    new_node_1->right->parent = new_node_1;

                    Node *new_node_2   = create_node ();
                    new_node_2->type   = OP;
                    new_node_2->val.op = '*';
                    new_node_2->parent = new_node_sub;
                    new_node_2->left   = curr_node->left;
                    new_node_2->right  = calc_derivative (curr_node->right);
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


