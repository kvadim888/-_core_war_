/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   func_fork.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkryvono <vkryvono@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/22 18:27:00 by vkryvono          #+#    #+#             */
/*   Updated: 2019/06/22 18:27:00 by vkryvono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <functions.h>

void func_fork(t_carriage	*carriage)
{
	t_carriage *new;

	ft_lstadd(&g_game.carriages, ft_lstnew(carriage, sizeof(carriage)));
	new = g_game.carriages->content;
	new->pos = ((carriage->param_values[0] % IDX_MOD) + MEM_SIZE) % MEM_SIZE;
	new->id = ++g_id;
	new->op = 0;
	ft_printf("func_fork\n");
}

void func_lfork(t_carriage *carriage)
{
	t_carriage *new;

	ft_lstadd(&g_game.carriages, ft_lstnew(carriage, sizeof(carriage)));
	new = g_game.carriages->content;
	new->pos = (carriage->pos + carriage->param_values[0]) % MEM_SIZE;
	new->id = ++g_id;
	new->op = 0;
	ft_printf("func_lfork\n");
}

