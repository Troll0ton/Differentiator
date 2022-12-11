#include "../include/frontend.h"
#include "../include/middleend.h"

//-----------------------------------------------------------------------------

#define CURR_LINE    &(info.Text[line].begin_line)
#define NUM_OF_LINES info.File_input->num_of_lines

int main ()
{
    Tree_info info = { 0 };

    tree_info_ctor (&info);

    create_latex_file (&info);

    for(int line = 0; line < NUM_OF_LINES; line++)
    {
        nullify_tree_pars (&info);

        info.root = get_grammar (CURR_LINE);

        fprintf (info.file_tex, "---------------------------------------------------------------------------------------------------------------------------\\\\\n");

        fprintf (info.file_tex, "Current expression:\\\\\n");

        print_tree_inorder (info.root, &info);

        tree_dump (&info);

        fprintf (info.file_tex, "\\\\\n");

        fprintf (info.file_tex, "Devirative:\\\\\n");

        calc_derivative (info.root, &info);

        print_tree_inorder (info.root, &info);

        tree_dump (&info);

        fprintf (info.file_tex, "\\\\\n");

        fprintf (info.file_tex, "Simplify something:\\\\\n");

        simplify_tree (info.root, &info);

        print_tree_inorder (info.root, &info);

        tree_dump (&info);

        fprintf (info.file_tex, "\\\\\n");

        fprintf (info.file_tex, "---------------------------------------------------------------------------------------------------------------------------\\\\\n");

        tree_dtor (info.root);

        fprintf (info.file_tex, "\\\\\n");
    }

    convert_to_pdf (&info);

    tree_info_dtor (&info);

    return 0;
}

#undef CURR_LINE
#undef NUM_OF_LINES

//-----------------------------------------------------------------------------
