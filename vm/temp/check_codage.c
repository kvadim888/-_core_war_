#include "functions.h"

int     c_di_r(char *c1, char *c2)
{
    if ((ft_strcmp(c1, "1001\0") || ft_strcmp(c1, "1101\0"))
    && ft_strcmp(c2, "0000\0"))
    {
        return (1);
    }
    return (0);
}

int     c_r_ri(char *c1, char *c2)
{
    if ((ft_strcmp(c1, "0101\0") || ft_strcmp(c1, "0111\0"))
    && ft_strcmp(c2, "0000\0"))
    {
        return (1);
    }
    return (0);
}

int     c_r_r_r(char *c1, char *c2)
{
    if (ft_strcmp(c1, "0101\0") && ft_strcmp(c2, "0100\0"))
    {
        return (1);
    }
    return (0);
}

int     c_rdi_rdi_r(char *c1, char *c2)
{
    if ((ft_strcmp(c1, "0101\0") || ft_strcmp(c1, "0110\0")
     || ft_strcmp(c1, "0111\0") || ft_strcmp(c1, "1001\0")
     || ft_strcmp(c1, "1010\0") || ft_strcmp(c1, "1011\0") 
     || ft_strcmp(c1, "1101\0") || ft_strcmp(c1, "1110\0")
     || ft_strcmp(c1, "1111\0")) && ft_strcmp(c2, "0100\0"))
    {
        return (1);
    }
    return (0);
}

int     c_rdi_rd_r(char *c1, char *c2)
{
    if ((ft_strcmp(c1, "0101\0") || ft_strcmp(c1, "0110\0")
     || ft_strcmp(c1, "1001\0") || ft_strcmp(c1, "1010\0")
     || ft_strcmp(c1, "1101\0") || ft_strcmp(c1, "1110\0")) 
     && ft_strcmp(c2, "0100\0"))
    {
        return (1);
    }
    return (0);
}

int     c_r_rdi_rd(char *c1, char *c2)
{
    if ((ft_strcmp(c1, "0101\0") || ft_strcmp(c1, "0110\0")
     || ft_strcmp(c1, "0111\0"))
     && (ft_strcmp(c2, "0100\0") || ft_strcmp(c2, "1000\0")))
    {
        return (1);
    }
    return (0);
}

int     c_r(char *c1, char *c2)
{
    if (ft_strcmp(c1, "0100\0") && ft_strcmp(c2, "0000\0"))
    {
        return (1);
    }
    return (0);
}