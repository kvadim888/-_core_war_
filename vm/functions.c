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

int		check_arg(uint32_t type, uint32_t arg)
{
	if (type == T_REG)
		return (arg > 0 || arg < REG_NUMBER) ? T_REG : 0;
	if (type == T_IND || type == T_DIR)
		return (type);
	return (0);
}

int32_t get_arg(t_carriage *cr, uint32_t type, uint32_t arg)
{
	if (type == T_REG)
		return (cr->reg[arg - 1]);
	if (type == T_IND)
		return (get_value(((cr->pos + (arg) % IDX_MOD) + MEM_SIZE) % MEM_SIZE, REG_SIZE));
	if (type == T_DIR)
		return (arg);
}

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
	size_t		size;
	int 		i;

	if (operation->codage == 0)
		return (operation->dir_size);
	size = operation->codage;
	i = -1;
	while (++i < operation->argc)
	{
		size += (operation->argt[i] == T_DIR) ? operation->dir_size : 0;
		size += (operation->argt[i] == T_REG) ? 1 : 0;
		size += (operation->argt[i] == T_IND) ? IND_SIZE : 0;
	}
	return (size);
}

void	get_argval(t_carriage *carriage)
{
	t_operation *operation;
	size_t		size;
	int 		i;

	operation = &carriage->operation;
	size = 0;
	i = -1;
	while (++i < operation->argc)
	{
		operation->argv[i] = (operation->argt[i] == T_DIR)
			? get_value(carriage->pos + size, operation->dir_size) : 0;
		operation->argv[i] = (operation->argt[i] == T_REG)
			? get_value(carriage->pos + size, 1) : 0;
		operation->argv[i] = (operation->argt[i] == T_IND)
			? get_value(carriage->pos + size, IND_SIZE) : 0;
		size += (operation->argt[i] == T_DIR) ? operation->dir_size : 0;
		size += (operation->argt[i] == T_REG) ? 1 : 0;
		size += (operation->argt[i] == T_IND) ? IND_SIZE : 0;
	}
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
		}
		else
			ft_bzero(operation, sizeof(t_operation));
		carriage->pos++;
	}
	if (operation->period > 0 || (operation->code - 1 > 15))
		return ;
	if (get_argtype(carriage))
		operation->function(carriage);
	carriage->pos += get_arglen(operation);
}
