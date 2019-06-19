#include "vm.h"

int     c_di_r(char *c, t_carriage  *pr)
{
    if (ft_strcmp(c, "10010000\0") || ft_strcmp(c, "11010000\0"))
    { 
        pr->param_types[0] = (ft_strcmp(c, "10010000\0")) ? 'd' : 'i';
        pr->param_types[1] = 'r';
        return (1);
    }
    return (0);
}

int     c_r_ri(char *c, t_carriage  *pr)
{
    if (ft_strcmp(c, "01010000\0") || ft_strcmp(c, "01110000\0"))
    { 
        pr->param_types[0] = 'r';
        pr->param_types[1] = (ft_strcmp(c, "01010000\0")) ?'r': 'i';
        return (1);
    }
    return (0);
}

int     c_r_r_r(char *c, t_carriage  *pr)
{
    if (ft_strcmp(c, "01010100\0"))
    { 
        pr->param_types[0] = 'r';
        pr->param_types[1] = 'r';
        pr->param_types[2] = 'r';
        return (1);
    }
    return (0);
}

int     c_rdi_rdi_r(char *c, t_carriage  *pr)
{
    if (ft_strcmp(c, "01010100\0") || ft_strcmp(c, "01100100\0")
     || ft_strcmp(c, "01110100\0") || ft_strcmp(c, "10010100\0")
     || ft_strcmp(c, "10100100\0") || ft_strcmp(c, "10110100\0") 
     || ft_strcmp(c, "11010100\0") || ft_strcmp(c, "11100100\0")
     || ft_strcmp(c, "11110100\0"))
    {
        pr->param_types[0] = (c[0] == '0' && c[1] == '1') ?'r': 'i';
        pr->param_types[0] = (c[0] == '1' && c[1] == '0') ?'d': pr->param_types[0];
        pr->param_types[1] = (c[2] == '0' && c[3] == '1') ?'r': 'i';
        pr->param_types[1] = (c[2] == '1' && c[3] == '0') ?'d': pr->param_types[1];
        pr->param_types[2] = 'r';
        return (1);
    }
    return (0);
}

int     c_rdi_rd_r(char *c, t_carriage  *pr)
{
    if (ft_strcmp(c, "01010100\0") || ft_strcmp(c, "01100100\0")
     || ft_strcmp(c, "10010100\0") || ft_strcmp(c, "10100100\0")
     || ft_strcmp(c, "11010100\0") || ft_strcmp(c, "11100100\0"))
    {
        pr->param_types[0] = (c[0] == '0' && c[1] == '1') ?'r': 2;
        pr->param_types[1] = (c[2] == '0' && c[3] == '1') ?'r': 2;
        pr->param_types[2] = 'r';
        return (1);
    }
    return (0);
}

int     c_r_rdi_rd(char *c, t_carriage  *pr)
{
    if (ft_strcmp(c, "01010100\0") || ft_strcmp(c, "01100100\0")
     || ft_strcmp(c, "01110100\0") || ft_strcmp(c, "01011000\0") 
     || ft_strcmp(c, "01101000\0") || ft_strcmp(c, "01111000\0"))
    {
        pr->param_types[0] = 'r';
        pr->param_types[1] = (c[2] == '0' && c[3] == '1') ? 'r': 'i';
        pr->param_types[1] = (c[2] == '1' && c[3] == '0') ? 'd': pr->param_types[1];
        pr->param_types[2] = (c[4] == '0' && c[5] == '1') ? 'r': 'd';
        return (1);
    }
    return (0);
}

int     c_r(char *c, t_carriage  *pr)
{
    if (ft_strcmp(c, "01000000\0"))
    {
        pr->param_types[0] = 'r';
        return (1);
    }
    return (0);
}
