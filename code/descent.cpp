#include "../include/descent.h"

//-----------------------------------------------------------------------------

int main ()
{
    FILE *file_in = fopen ("../files/problem.txt", "rb");

    File *File_input = file_reader (file_in);
    Line *Text = lines_separator (File_input);

    printf ("|result - %d\n|", get_g (Text[0].begin_line));

    fclose (file_in);

    return 0;
}

//-----------------------------------------------------------------------------

int get_t ()
{
    int val1 = get_p ();

    while(*str == '*' || *str == '/')
    {
        char *op = str;
        str++;

        int val2 = get_p ();

        if(*op == '*')
        {
            val1 *= val2;
        }

        else
        {
            val1 /= val2;
        }
    }

    return val1;
}

//-----------------------------------------------------------------------------

int get_p ()
{
    int val = 0;

    if(*str == '(')
    {
        str++;
        val = get_e ();

        assert (*str == ')');

        str++;
    }

    else
    {
        val = get_n ();
    }

    return val;
}

//-----------------------------------------------------------------------------

int get_e ()
{
    int val1 = get_t ();

    while(*str == '+' || *str == '-')
    {
        char *op = str;
        str++;

        int val2 = get_t ();

        if(*op == '+')
        {
            val1 += val2;
        }

        else
        {
            val1 -= val2;
        }
    }

    return val1;
}

//-----------------------------------------------------------------------------

int get_g (char *s)
{
    str = s;

    int val = get_e ();

    assert (*str == '\0');

    return val;
}

//-----------------------------------------------------------------------------

int get_n ()
{
    int val = 0;

    const char *str_old = str;

    if(*str == '\n' || *str == '\r')
    {
        *str = '\0';
    }

    while(*str >= '0' && *str <= '9')
    {
        val = val * 10 + *str - '0';
        str++;
    }

    assert (str != str_old);

    return val;
}

//-----------------------------------------------------------------------------


