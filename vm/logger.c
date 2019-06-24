/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logger.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkryvono <vkryvono@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/11 01:42:00 by vkryvono          #+#    #+#             */
/*   Updated: 2019/06/11 01:42:00 by vkryvono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	log_champion(t_list *lst)
{
	t_champion	*champion;

	champion = lst->content;
	if (champion)
		ft_printf("* Player %d, weighing %d bytes, \"%s\" (\"%s\") !\n",
				  champion->number, champion->header->prog_size,
				  champion->header->prog_name, champion->header->comment);
}

void	log_field(int width)
{
	int	pos;

	pos = 0;
	while (pos < MEM_SIZE)
	{
		if (pos % width == 0)
			ft_printf("%.3p : ", pos);
		ft_printf("%.2x ", g_game.field[pos]);
		if (++pos % width == 0)
			ft_printf("\n");
	}
}
