#include "../include/frontend.h"
#include "../include/middleend.h"

//-----------------------------------------------------------------------------

int main ()
{
    greetings ();

    Tree_info *info = tree_info_ctor();

    info->root = get_g (&(info->Text[0].begin_line));

    fclose (info->file_in);

    print_tree_inorder (info->root);

    tree_dump (info);

    printf ("\n");

    info->root = copy_tree (info->root->left, info);

    tree_dump (info);

    //-----------------------------------------------------------------------------

    /*
    calc_derivative (info->root);

    print_tree_inorder (info->root);

    tree_dump (info); */

    Node *root = info->root;

    tree_dtor (root);

    tree_info_dtor (info);

    return 0;
}

//-----------------------------------------------------------------------------
