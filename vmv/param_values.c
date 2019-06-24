#include "../includes/vm.h"

int get_val_size(int op_code, char t)
{
    if (t == 'r')
        return 1;
    else if (t == 'd' && ((op_code > 8 && op_code < 13) || (op_code > 13 && op_code < 16)))
        return 2;
    else if (t == 'd')
        return 4;
    else if (t == 'i')
        return 2;
    return -1;
}

int   read_values(t_game *game, t_carriage  *pr, int p)
{   
    int i;
    int s;
    unsigned char buf[5];

    ft_bzero(buf, 5);
    i = -1;
    while (pr->param_types[++i] != 0)
    {
        s = get_val_size(pr->op, pr->param_types[i]);
        buf[0] = game->field[p++];
        if (s == 2 || s == 4)
            buf[1] = game->field[p++];
        if (s == 4)
        {
            buf[2] = game->field[p++];
            buf[3] = game->field[p++];
        }
     //   printf("read d = %c\n", pr->param_types[i]);
     //   printf("read v = %i\n", hex_to_dec(buf, s));
        pr->param_values[i] = hex_to_dec(buf, s);
    }
    return p;
}
