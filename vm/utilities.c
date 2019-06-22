/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkryvono <vkryvono@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/11 04:21:00 by vkryvono          #+#    #+#             */
/*   Updated: 2019/06/11 04:21:00 by vkryvono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int			is_number(char *str) //todo move to libft
{
	while (ft_iswhspace(*str))
		str++;
	while (ft_isdigit(*str))
		str++;
	while (ft_iswhspace(*str))
		str++;
	return (*str == '\0');
}

char    *hex_to_bin(unsigned char b, unsigned char m)
{
	char *bits;
	int i;

	i = -1;
	bits = ft_memalloc(sizeof(char) * 9);
	ft_bzero(bits, 9);
	while (++i < 8)
		bits[8 - i - 1] = ((b & (m << i)) != 0) ? '1' : '0';
	return bits;
}

int				hex_to_dec(unsigned char *buf, int i)
{
	int res;

	res = 0;
	if (!i)
		return (0);
    if (i == 4)
	{
		res += buf[0] * 16777216;
		res += buf[1] * 65536;
		res += buf[2] * 256;
		res += buf[3];
	} else 
    {
	    if (i == 2)
	    {
		    res += buf[0] * 256;
		    res += buf[1];
        } else 
           res += buf[0];
		res = (short)res;
	}
	return (res);
}
