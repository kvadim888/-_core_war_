/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   func_misc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkryvono <vkryvono@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/22 19:03:00 by vkryvono          #+#    #+#             */
/*   Updated: 2019/06/22 19:03:00 by vkryvono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <functions.h>

void func_live(t_carriage *carriage)
{
	carriage->live = g_game.cycle_counter;
	g_game.nbr_live++;
	if (-carriage->param_values[0] > 0 && -carriage->param_values[0] <= g_game.players_amount)
		g_game.survivor->number = -carriage->param_values[0];
	ft_printf("func_live\n");
}

void func_zjmp(t_carriage *carriage)
{
	if (carriage->carry)
		carriage->pos = ((carriage->param_values[0] % IDX_MOD) + MEM_SIZE) % MEM_SIZE;
	ft_printf("func_zjmp\n");
}

void func_aff(t_carriage *carriage)
{
	int a1;

	a1 = carriage->param_values[0];
	if (check_reg(a1, 10, 10))
		printf("%c\n", (char)carriage->reg[a1 - 1]);
	ft_printf("func_aff\n");
}
