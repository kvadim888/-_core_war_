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
		return (arg < 1 || arg > REG_NUMBER) ? T_REG : 0;
	if (type == T_IND || type == T_DIR)
		return (type);
	return (0);
}

uint32_t get_arg(t_carriage *cr, uint32_t type, uint32_t arg)
{
	if (type == T_REG)
		return (cr->reg[arg - 1]);
	if (type == T_IND)
		return (get_value(((cr->pos + (arg) % IDX_MOD) + MEM_SIZE) % MEM_SIZE));
	if (type == T_DIR)
		return (arg);
}

void	exec_function(t_list *lst)
{
	t_carriage	*carriage;
	t_operation	*operation;
	t_argtype	argtype;

	carriage = lst->content;

	if (carriage->rest > 0)
		carriage->rest--;
	else
	{
		if (g_game.field[carriage->pos] > 0 && g_game.field[carriage->pos] < 16)
		{
			memcpy(&carriage->operation,
				&g_op[g_game.field[carriage->pos]], sizeof(t_operation));
			carriage->rest = carriage->operation.period - 1;
		}
		else
		{
			carriage->operation.code = -1;
			carriage->rest = 0;
		}
	}
	if (carriage->rest > 0)
		return ;
	operation = &carriage->operation;
	if (operation->code > 0 && operation->code < 16)
	{
		argtype.cell = g_game.field[carriage->pos];
		operation->argt[0] = (uint16_t)(argtype.arg1);
		operation->argt[1] = (uint16_t)(argtype.arg2);
		operation->argt[2] = (uint16_t)(argtype.arg3);
		operation->function(&g_game, carriage);
		carriage->pos += 7; // todo length estimation
	}
}

