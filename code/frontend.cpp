#include "../include/frontend.h"

//-----------------------------------------------------------------------------

//{----------------------------------------------------------------------------
//!                                (and with union value)
//! INIT_OP_1 - initialize operator-node with 1-priority and left and right son;
//! INIT_OP_2 - initialize operator-node with 2-priority and left and right son;
//! INIT_OP_3 - initialize operator-node with 3-priority and left and right son;
//! INIT_OP_4 - initialize operator-node with 4-priority;
//!
//! 1 = +, -
//! 2 = *, /
//! 3 = ^
//! 4 = sin, cos, tg, ctg, ln, arcsin, arccos, arctg, arcctg
//!
//}----------------------------------------------------------------------------

Node *get_mul_div (char **grammar)
{
    Node *left_node = get_pow (grammar);

    value val = { 0 };

    while(IS_('*') || IS_('/'))
    {
        char curr_op = **grammar;
        (*grammar)++;

        Node *right_node = get_pow (grammar);

        switch(curr_op)
        {
            CASE ('*', MUL);

            CASE ('/', DIV);

            default:
            {
                printf ("WTF?\n");

                break;
            }
        }

        INIT_OP_2;

        left_node = new_node;
    }

    return left_node;
}

//-----------------------------------------------------------------------------

Node *get_pow (char **grammar)
{
    Node *left_node = get_parentheses (grammar);

    while(IS_('^'))
    {
        (*grammar)++;

        Node *right_node = get_parentheses (grammar);

        INIT (POW, 3);

        left_node = new_node;
    }

    return left_node;
}

//-----------------------------------------------------------------------------

Node *get_parentheses (char **grammar)
{
    Node *new_node = NULL;

    if(IS_('('))
    {
        (*grammar)++;

        new_node = get_expression (grammar);

        CHECK_EXPRESSION (**grammar == ')', "CLOSING BRACKET\n");

        (*grammar)++;
    }

    else
    {
        new_node = get_bottom (grammar);
    }

    return new_node;
}

//-----------------------------------------------------------------------------

Node *get_expression (char **grammar)
{
    Node *left_node = get_mul_div (grammar);

    while(IS_('+') || IS_('-'))
    {
        char curr_op = **grammar;
        (*grammar)++;

        Node *right_node = get_mul_div (grammar);

        value val = { 0 };

        switch(curr_op)
        {
            CASE ('+', ADD);

            CASE ('-', SUB);

            default:
            {
                printf ("WTF?\n");

                break;
            }
        }

        INIT_OP_1;

        left_node = new_node;
    }

    return left_node;
}

//-----------------------------------------------------------------------------

Node *get_grammar (char **grammar)
{
    Node *root = get_expression (grammar);

    CHECK_EXPRESSION (**grammar == '\0', "END OF EXPRESSION\n");

    return root;
}

//-----------------------------------------------------------------------------

Node *get_str (char **grammar)
{
    char name[MAX_LEN] = "";

    value val = { 0 };

    int i = 0;

    while(isalpha (**grammar) && i < MAX_LEN)
    {
        name[i] = **grammar;
        i++;

        (*grammar)++;
    }

    if(IS_('('))
    {
        return get_funct (grammar, name);
    }

    val.var = *name;

    INIT_VAR;

    return new_node;
}

//-----------------------------------------------------------------------------

Node *get_funct (char **grammar, char *name)
{
    Node *right_node = get_parentheses (grammar);

    if(stricmp (name, "sin") == 0)
    {
        INIT (SIN, 4);

        return new_node;
    }

    else if(stricmp (name, "cos") == 0)
    {
        INIT (COS, 4);

        return new_node;
    }

    else if(stricmp (name, "tg") == 0)
    {
        INIT (TG, 4);

        return new_node;
    }

    else if(stricmp (name, "ctg") == 0)
    {
        INIT (CTG, 4);

        return new_node;
    }

    else if(stricmp (name, "ln") == 0)
    {
        INIT (LN, 4);

        return new_node;
    }

    else if(stricmp (name, "arcsin") == 0)
    {
        INIT (ARCSIN, 4);

        return new_node;
    }

    else if(stricmp (name, "arccos") == 0)
    {
        INIT (ARCCOS, 4);

        return new_node;
    }

    else if(stricmp (name, "arctg") == 0)
    {
        INIT (ARCTG, 4);

        return new_node;
    }

    else if(stricmp (name, "arcctg") == 0)
    {
        INIT (ARCCTG, 4);

        return new_node;
    }

    else
    {
        printf ("UNKNOWN COMMAND!\n");

        return NULL;
    }
}

//-----------------------------------------------------------------------------

#define VALUE_NUM val.num

Node *get_bottom (char **grammar)
{
    value val = { 0 };

    const char *str_old = *grammar;

    if(isalpha (**grammar))
    {
        return get_str (grammar);
    }

    while(is_num (**grammar))
    {
        VALUE_NUM = VALUE_NUM * 10 + **grammar - '0';
        (*grammar)++;
    }

    INIT_NUM;

    CHECK_EXPRESSION (*grammar != str_old, "ERROR WHILE GET NUM\n");

    return new_node;
}

#undef VALUE_NUM

//-----------------------------------------------------------------------------
