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
    t_operation *operation;

    operation = &carriage->operation;
	carriage->live = g_game.cycle_counter;
	g_game.live_counter++;
	if (-operation->argv[0] > 0 && -operation->argv[0] <= g_game.players_amount)
		g_game.survivor->number = -operation->argv[0];
	if (g_flag & FLAG_VERBOSE_1)
		ft_printf("Player %d (stayin' alive) is said to be alive\n",
				operation->argv[0]);
    if (g_flag & 4)
        ft_printf("P%5i | live %i\n", carriage->id, operation->argv[0]);
}

void func_zjmp(t_carriage *carriage)
{
    t_operation *operation;

    operation = &carriage->operation;
	if (carriage->carry)
	{
        carriage->pos = ((operation->argv[0] % IDX_MOD) + MEM_SIZE) % MEM_SIZE;
        if (g_flag & FLAG_VERBOSE_4)
            ft_printf("P%5i | zjmp %i OK\n", carriage->id, operation->argv[0]);
    }
    if (g_flag & FLAG_VERBOSE_4)
        ft_printf("P%5i | zjmp %i FAILED\n", carriage->id, operation->argv[0]);
}

void func_aff(t_carriage *carriage)
{
	t_operation *operation;
	uint16_t	*argv;

	operation = &carriage->operation;
	if (check_arg(operation->argt[0], operation->argv[0]) != T_REG)
		return;
	argv = operation->argv;
	ft_printf("%c\n", (char)carriage->reg[argv[0] - 1]);
	if (g_flag & FLAG_VERBOSE_4)
	    ft_printf("P%5d | aff r%d\n", carriage->id, carriage->reg[argv[0] - 1]);
}
