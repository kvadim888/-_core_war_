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

int			is_number(char *str)
{
	while (ft_iswhspace(*str))
		str++;
	while (ft_isdigit(*str))
		str++;
	while (ft_iswhspace(*str))
		str++;
	return (*str == '\0');
}

void		set_value(int32_t addr, uint32_t value)
{
	int		i;
	t_value	val;

	val.word = value;
	i = 0;
	while (i < REG_SIZE)
	{
		g_game.field[(addr + i + MEM_SIZE) % MEM_SIZE] = val.byte[i];
		i++;
	}
}

uint32_t	get_value(uint32_t addr)
{
	int 	i;
	t_value	value;

	value.word = 0;
	i = 0;
	while (i < REG_SIZE)
	{
		value.byte[i] = g_game.field[(addr + i + MEM_SIZE) % MEM_SIZE];
		i++;
	}
	return (value.word);
}
