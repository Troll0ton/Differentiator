//! @file frontend.h

#ifndef FRONTEND_H
#define FRONTEND_H

//-----------------------------------------------------------------------------

#include "../include/tree.h"

//-----------------------------------------------------------------------------

Node *get_grammar     (char **grammar);

Node *get_expression  (char **grammar);

Node *get_mul_div     (char **grammar);

Node *get_parentheses (char **grammar);

Node *get_str         (char **grammar);

Node *get_bottom      (char **grammar);

Node *get_pow         (char **grammar);

Node *get_funct       (char **grammar, char *name);

//-----------------------------------------------------------------------------

#define CHECK_EXPRESSION(EXPR, TEXT)           \
    if(!(EXPR))                                \
    {                                          \
        printf ("DETECTED MISTAKE: %s", TEXT); \
                                               \
        return NULL;                           \
    }

//-----------------------------------------------------------------------------

#endif //FRONTEND_H
