/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   func_st.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkryvono <vkryvono@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/22 18:26:00 by vkryvono          #+#    #+#             */
/*   Updated: 2019/06/22 18:26:00 by vkryvono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/functions.h"

void func_st(t_carriage *carriage)
{
	int	a1;
	int a2;

	a1 = carriage->param_values[0];
	a2 = carriage->param_values[1];
	if (check_reg(a1, a1, a1))
	{
		if (carriage->param_types[1] == T_REG && check_reg(a2, a2, a2))
			carriage->reg[a2 - 1] = carriage->reg[a1 - 1];
		if (carriage->param_types[1] == T_IND)
			set_value((((carriage->pos + (a2 % IDX_MOD)) + MEM_SIZE) % MEM_SIZE), carriage->reg[a1 - 1]);
	}
	ft_printf("func_st\n");
}

void func_sti(t_carriage *carriage)
{
	ft_printf("func_sti\n");
	int a1;
	int a2;
	int a3;

	a1 = carriage->param_values[0];
	if (check_reg(a1, a1, a1) && check_param(carriage, 1, &a2) && check_param(carriage, 2, &a3))
		set_value((((a2 + a3) + MEM_SIZE) % MEM_SIZE), carriage->reg[a1 - 1]);
}

