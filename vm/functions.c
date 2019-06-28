/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkryvono <vkryvono@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/11 02:46:00 by vkryvono          #+#    #+#             */
/*   Updated: 2019/06/11 02:46:00 by vkryvono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vm.h>
#include <functions.h>

int 	get_argtype(t_carriage *carriage)
{
	t_argtype		argtype;
	t_operation		*operation;

	operation = &carriage->operation;
	if (operation->codage == 0)
		return (1);
	argtype.cell = g_game.field[carriage->pos % MEM_SIZE];
	operation->argt[0] = (argtype.arg1 & 3U) ? 1U << (argtype.arg1 - 1U) : 0;
	operation->argt[1] = (argtype.arg2 & 3U) ? 1U << (argtype.arg2 - 1U) : 0;
	operation->argt[2] = (argtype.arg3 & 3U) ? 1U << (argtype.arg3 - 1U) : 0;
	return ((operation->argt[0] & g_op[operation->code - 1].argt[0]) &&
			(operation->argt[1] & g_op[operation->code - 1].argt[1]) &&
			(operation->argt[2] & g_op[operation->code - 1].argt[2]));
}

size_t	get_arglen(t_operation *operation)
{
	size_t size;
	int i;

	if (operation->codage == 0)
		return (operation->dir_size);
	size = operation->codage;
	i = -1;
	while (++i < operation->argc)
	{
		if (operation->argt[i] == T_DIR)
			size += operation->dir_size;
		else if (operation->argt[i] == T_REG)
			size += 1;
		else if (operation->argt[i] == T_IND)
			size += IND_SIZE;
	}
	return (size);
}

uint32_t get_argval(t_carriage *carriage)
{
}

void	exec_function(t_list *lst)
{
	t_carriage *carriage;
	t_operation *operation;

	carriage = lst->content;
	operation = &carriage->operation;
	if (operation->period > 0)
		operation->period--;
	else
	{
		if (g_game.field[carriage->pos] > 0 &&
			g_game.field[carriage->pos] <= 16)
		{
			memcpy(operation, &g_op[g_game.field[carriage->pos] - 1],
				   sizeof(t_operation));
			operation->period--;
		} else
			ft_bzero(operation, sizeof(t_operation));
		carriage->pos++;
	}
	if (operation->period > 0 || (operation->code - 1 > 15))
		return;
	if (get_argtype(carriage))
	{
		get_argval(carriage);
		operation->function(carriage);
	}
	carriage->pos += get_arglen(operation);
}
