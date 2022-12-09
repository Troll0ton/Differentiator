#include "../include/frontend.h"
#include "../include/middleend.h"

//-----------------------------------------------------------------------------

int main ()
{
    FILE *file_in = fopen ("../files/task1.txt", "rb");

    File *File_input = file_reader (info->file_in);
    Line *Text = lines_separator (info->File_input);

    fclose (file_in);

    //-----------------------------------------------------------------------------

    for(int line = 0; line < File_input->num_of_lines; line++)
    {
        Tree_info *info = tree_info_ctor (File_input, Text);

        info->root = get_g (&(info->Text[0].begin_line));

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
    }

    tree_info_dtor (info);

    return 0;
}

//-----------------------------------------------------------------------------
