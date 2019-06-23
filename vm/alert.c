/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alert.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkryvono <vkryvono@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/11 04:19:00 by vkryvono          #+#    #+#             */
/*   Updated: 2019/06/11 04:19:00 by vkryvono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	free_carriages(){
	t_list	*tmp;
	t_carriage *carr;
	t_operation *op;

	tmp = g_game.carriages;
	while (tmp)
	{
		carr = tmp->content;
		op = carr->operation;
		free(op);
		tmp = tmp->next;
		free(carr);
	}
}

void	error(int trigger, char *msg)
{
	if (trigger)
	{
		//free_carriages();
		ft_dprintf(2, "ERROR: %s\n", msg);
		exit(1);
	}
}
