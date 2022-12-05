#include "../include/frontend.h"
#include "../include/middleend.h"

//-----------------------------------------------------------------------------

int main ()
{
    Tree_info *info = tree_info_ctor();

    FILE *file_in = fopen ("../files/task1.txt", "rb");

    File *File_input = file_reader (file_in);
    Line *Text = lines_separator (File_input);

    info->root = get_g (&(Text[0].begin_line));

    fclose (file_in);

    print_tree_inorder (info->root);

    tree_dump (info);

    printf ("\n");

    calc_derivative (info->root);

    print_tree_inorder (info->root);

    tree_dump (info);

    Node *root = info->root;

    tree_dtor (root);

    tree_info_dtor (info);

    return 0;
}

//-----------------------------------------------------------------------------
