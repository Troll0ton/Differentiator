//! @file frontend.h

#ifndef MIDDLE_END
#define MIDDLE_END

//-----------------------------------------------------------------------------

#include "../include/tree.h"
#include <math.h>

//-----------------------------------------------------------------------------

Node *calc_derivative  (Node *curr_node, Tree_info *info);

bool  simplify_tree    (Node *curr_node, Tree_info *info);

bool  simplify_const   (Node *curr_node, Tree_info *info);

void  print_expression (Tree_info *info);

void  print_derivative (Tree_info *info);

void  print_simplified (Tree_info *info);

//-----------------------------------------------------------------------------

#endif //MIDDLE_END
