/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recognize_op.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akotilie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/24 14:58:19 by akotilie          #+#    #+#             */
/*   Updated: 2019/03/24 14:58:21 by akotilie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "functions.h"

char    **get_quads(){
    char **quads;

    quads = (char **)ft_memalloc(sizeof(char*) * 16);
    quads[0] = "0000\0";
	quads[1] = "0001\0";
	quads[2] = "0010\0";
	quads[3] = "0011\0";
	quads[4] = "0100\0";
	quads[5] = "0101\0";
	quads[6] = "0110\0";
	quads[7] = "0111\0";
	quads[8] = "1000\0";
	quads[9] = "1001\0";
	quads[10] = "1010\0";
	quads[11] = "1011\0";
	quads[12] = "1100\0";
	quads[13] = "1101\0";
	quads[14] = "1110\0";
	quads[15] = "1111\0";
	return (quads);
}


char    *hex_to_bin(unsigned char c)
{
    char    **quads;

    quads = get_quads();
  if (c >= '0' && c <= '9') {
  	return quads[(int)c - (int)'0'];
  }
  if (c >= 'A' && c <= 'F') {
  	return quads[10 + (int)c - (int)'A'];
  }
  if (c >= 'a' && c <= 'f') {
  	return quads[10 + (int)c - (int)'a'];
  }
  return NULL;
}

int     hex_to_dec(char num[]) 
{    
    ft_putstr("\nhex to dec 1\n");
    ft_putstr(num);
    ft_putstr("\n");
    int len = ft_strlen(num); 
    int base = 1; 
    int dec_val = 0;     
      
    int i = len;
    while (--i >= 0) 
    {    
        ft_putstr("num[i]\n");
        ft_putchar(num[i]);
        ft_putchar('\n');
        ft_putnbr(num[i]);
        ft_putchar("\n");
        if (num[i]>='0' && num[i]<='9') 
        { 
            dec_val += (num[i] - 48)*base; 
        } 
        else if (num[i]>='a' && num[i]<='f') 
        { 
            dec_val += (num[i] - 55)*base; 
        } 
                ft_putstr("dec val\n");
        ft_putchar(dec_val);
        ft_putchar('\n');
        base = base * 16;   
    } 
    ft_putnbr(dec_val);
    ft_putstr("\n\n");   
    return dec_val; 
}

int    check_codage(t_vm_proc *pr, t_core *core, char *buf)
{
    char *c1 = hex_to_bin(buf[0]);
    char *c2 = hex_to_bin(buf[1]);
    if ((core->oper[(pr)->next_operation_code]).check(c1, c2) == 1)
    {
        if (c1[0] == '0' && c1[1] == '1')
            (pr)->param_type_1 = 'r';
        if (c1[0] == '1' && c1[1] == '0')
            (pr)->param_type_1 = 'd';
        if (c1[0] == '1' && c1[1] == '1')
            (pr)->param_type_1 = 'i';
        if (c1[2] == '0' && c1[3] == '1')
            (pr)->param_type_2 = 'r';
        if (c1[2] == '1' && c1[3] == '0')
            (pr)->param_type_2 = 'd';
        if (c1[2] == '1' && c1[3] == '1')
            (pr)->param_type_2 = 'i';
        if (c2[0] == '0' && c2[1] == '1')
            (pr)->param_type_3 = 'r';
        if (c2[0] == '1' && c2[1] == '0')
            (pr)->param_type_3 = 'd';
        return (1);
    }
    return (0);
}

int			read_op_code(t_champion *ch, t_core **core)
{
	char			buf[3];
    t_vm_proc       *pr;
    int             code;

	ft_bzero(buf, 2);
    buf[2] = '\0';
 	if ((read(ch->fd, buf, 2)) < 0)
		return -1;    
	code = hex_to_dec((char*)buf);
    ft_putstr("\n");
    ft_putstr(buf);
    ft_putstr("read_op_code\n");
    ft_putnbr(code);
    ft_putstr("\n");
    if (code > -1 && code < 17)
    {
        pr = (t_vm_proc*)ft_memalloc(sizeof(t_vm_proc));
        pr->next_operation_code = code;
        if (code != 1 && code != 9 && code != 12 & code != 15){
            if ((read(ch->fd, buf, 2)) < 0)
		        return -2;
            if (check_codage(pr, *core, (char*)buf) != 1){
                return -2;// exit_perror("invalid codage", 4);
            }
            read_params(pr, ch->fd);
        } else {
            return 0;
        }
    }
    return (1);
}


