//! @file frontend.h

#ifndef FRONTEND_H
#define FRONTEND_H

//-----------------------------------------------------------------------------

#include "../include/tree.h"

//-----------------------------------------------------------------------------

Node *get_g (char **grammar);

Node *get_e (char **grammar);

Node *get_t (char **grammar);

Node *get_p (char **grammar);

Node *get_n (char **grammar);

//-----------------------------------------------------------------------------

#endif //FRONTEND_H
