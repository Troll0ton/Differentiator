#include "../include/backend.h"

//-----------------------------------------------------------------------------

int main ()
{
    Tree_info *info = tree_info_ctor();

    read_tree (info);

    print_tree_inorder (info->root);

    tree_dump (info);

    Node *root = info->root;

    tree_dtor (root);

    tree_info_dtor (info);

    return 0;
}

//-----------------------------------------------------------------------------
