#include "../include/frontend.h"

//-----------------------------------------------------------------------------

Node *get_t (char **grammar) //handle operations with 2-priority
{
    Node *left_node = get_p (grammar);

    while(**grammar == '*' || **grammar == '/')
    {
        char *curr_op = *grammar;
        (*grammar)++;

        Node *right_node = get_p (grammar);

        Node *new_node = create_node ();

        new_node->left   = left_node;
        new_node->right  = right_node;
        new_node->type   = OP;
        new_node->val.op = *curr_op;

        left_node->parent = new_node;
        right_node->parent = new_node;

        left_node = new_node;
    }

    return left_node;
}

//-----------------------------------------------------------------------------

Node *get_p (char **grammar)
{
    Node *new_node = NULL;

    if(**grammar == '(')
    {
        (*grammar)++;

        new_node = get_e (grammar);

        assert (**grammar == ')');

        (*grammar)++;
    }

    else
    {
        new_node = get_n (grammar);
    }

    return new_node;
}

//-----------------------------------------------------------------------------

Node *get_e (char **grammar)  //handle operations with 3-priority
{
    Node *left_node = get_t (grammar);

    while(**grammar == '+' || **grammar == '-')
    {
        char *curr_op = *grammar;
        (*grammar)++;

        Node *right_node = get_t (grammar);

        Node *new_node = create_node ();

        new_node->left   = left_node;
        new_node->right  = right_node;
        new_node->type   = OP;
        new_node->val.op = *curr_op;

        left_node->parent = new_node;
        right_node->parent = new_node;

        left_node = new_node;
    }

    return left_node;
}

//-----------------------------------------------------------------------------

Node *get_g (char **grammar)
{
    Node *root = get_e (grammar);

    assert (**grammar == '\0');

    return root;
}

//-----------------------------------------------------------------------------

#define VALUE new_node->val.num

Node *get_n (char **grammar)  //handle numeric
{
    Node *new_node = create_node ();

    new_node->type = NUM;

    VALUE = 0;

    const char *str_old = *grammar;

    if(**grammar == '\n' || **grammar == '\r')
    {
        **grammar = '\0';
    }

    while(**grammar >= '0' && **grammar <= '9')
    {
        VALUE = VALUE * 10 + **grammar - '0';
        (*grammar)++;
    }

    assert (*grammar != str_old);

    return new_node;
}

#undef VALUE

//-----------------------------------------------------------------------------
