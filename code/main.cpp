#include "../include/frontend.h"
#include "../include/middleend.h"

//-----------------------------------------------------------------------------

int main ()
{
    //greetings ();

    Tree_info *info = tree_info_ctor();

    info->root = get_g (&(info->Text[0].begin_line));

    fclose (info->file_in);

    create_latex_file (info);

    print_tree_inorder (info->root, info);

    tree_dump (info);

    txprint ("\\\\\n");

    calc_derivative (info->root, info);

    print_tree_inorder (info->root, info);

    convert_to_pdf (info);

    tree_dump (info);

    Node *root = info->root;

    tree_dtor (root);

    tree_info_dtor (info);

    return 0;
}

//-----------------------------------------------------------------------------
