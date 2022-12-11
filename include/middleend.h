//! @file frontend.h

#ifndef MIDDLE_END
#define MIDDLE_END

//-----------------------------------------------------------------------------

#include "../include/tree.h"
#include <math.h>

//-----------------------------------------------------------------------------

Node *calc_derivative (Node *curr_node, Tree_info *info);

Node *simplify_tree   (Node *curr_node, Tree_info *info);

//-----------------------------------------------------------------------------

#endif //MIDDLE_END
