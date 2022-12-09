#include "../include/frontend.h"

//-----------------------------------------------------------------------------

Node *get_t (char **grammar) //handle operations with 2-priority
{
    Node *left_node = get_d (grammar);

    while(**grammar == '*' ||
          **grammar == '/'   )
    {
        char *curr_op = *grammar;
        (*grammar)++;

        Node *right_node = get_d (grammar);

        INIT_NODE (new_node, left_node, right_node, NULL, OP, *curr_op, 2);

        left_node = new_node;
    }

    return left_node;
}

//-----------------------------------------------------------------------------

Node *get_d (char **grammar)
{
    Node *left_node = get_p (grammar);

    while(**grammar == '^')
    {
        char *curr_op = *grammar;
        (*grammar)++;

        Node *right_node = get_p (grammar);

        INIT_NODE (new_node, left_node, right_node, NULL, OP, *curr_op, 3);

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

        INIT_NODE (new_node, left_node, right_node, NULL, OP, *curr_op, 1);

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

#define VALUE_num new_node->val.num
#define VALUE_VAR new_node->val.var

Node *get_n (char **grammar)  //handle numeric
{
    INIT_NODE (new_node, NULL, NULL, NULL, NUM, 0, 4);

    const char *str_old = *grammar;

    if(**grammar == '\n' || **grammar == '\r')
    {
        **grammar = '\0';
    }

    if(isalpha (**grammar))
    {
        new_node->type = VAR;

        VALUE_VAR = **grammar;

        (*grammar)++;

        return new_node;
    }

    while(**grammar >= '0' && **grammar <= '9')
    {
        VALUE_num = VALUE_num * 10 + **grammar - '0';
        (*grammar)++;
    }

    assert (*grammar != str_old);

    return new_node;
}

#undef VALUE_num
#undef VALUE_VAR

//-----------------------------------------------------------------------------
