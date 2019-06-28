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

static int	find_num(t_list *lst, int num)
{
	t_champion *champion;

	while(lst)
	{
		champion = lst->content;
		if (champion->number == num)
			return (1);
		lst = lst->next;
	}
	return (0);
}

void		choose_num(t_list *lst)
{
	static int	num = 1;
	t_champion	*champion;

	champion = lst->content;
	if (champion->number > 0)
		return ;
	while (find_num(g_game.players, num) && num <= MAX_PLAYERS)
		num++;
	if (num > MAX_PLAYERS)
	{
		ft_printf(USAGE);
		exit(0);
	}
	champion->number = num;
}

void		set_value(int32_t addr, uint32_t value, size_t size)
{
	int		i;
	t_value	val;

	val.word = value;
	i = 0;
	while (i < size)
	{
		g_game.field[(addr + i + MEM_SIZE) % MEM_SIZE] = val.byte[i];
		i++;
	}
}

uint32_t	get_value(uint32_t addr, size_t size)
{
	int 	i;
	t_value	value;

	value.word = 0;
	i = 0;
	while (i < size)
	{
		value.byte[size - i + 1] =
				g_game.field[(addr + i + MEM_SIZE) % MEM_SIZE];
		i++;
	}
	return (value.word);
}
