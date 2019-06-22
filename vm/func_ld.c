/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   func_ldst.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkryvono <vkryvono@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/22 18:25:00 by vkryvono          #+#    #+#             */
/*   Updated: 2019/06/22 18:25:00 by vkryvono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <functions.h>

void func_ld(t_game *game, t_carriage	*carriage)
{
	int	a1;
	int a2;

	a1 = carriage->param_values[0];
	a2 = carriage->param_values[1];
	if (!check_reg(a1, a2, a2))
		return ;
	if (carriage->param_types[0] == T_IND)
	{
		a1 = get_value((carriage->pos + (a1 % IDX_MOD) + MEM_SIZE) % MEM_SIZE);
		carriage->reg[a2 - 1] = a1;
	}
	else
		carriage->reg[a2 - 1] = a1;
	carriage->carry = (carriage->reg[a2 - 1]) ? 0 : 1;
	ft_printf("func_ld\n");
}

void func_ldi(t_game *game, t_carriage	*carriage)
{
	int	a1;
	int a2;
	int a3;

	a3 = carriage->param_values[2];
	if (check_reg(a3, a3, a3) && check_param(carriage, 0, &a1) && check_param(carriage, 0, &a2))
	{
		carriage->reg[a3 - 1] = getvalue((((a1 + a2) % IDX_MOD) + MEM_SIZE) % MEM_SIZE);
	}
	ft_printf("func_ldi\n");
}

void func_lld(t_game *game, t_carriage	*carriage)
{
	int	a1;
	int a2;

	a1 = carriage->param_values[0];
	a2 = carriage->param_values[1];
	if (!check_reg(a1, a2, a2))
		return ;
	if (carriage->param_types[0] == T_IND)
	{
		a1 = getvalue(((carriage->pos + a1) + MEM_SIZE) % MEM_SIZE);
		carriage->reg[a2 - 1] = a1;
	}
	else
		carriage->reg[a2 - 1] = a1;
	carriage->carry = (carriage->reg[a2 - 1]) ? 0 : 1;
	ft_printf("func_lld\n");
}

void func_lldi(t_game *game, t_carriage	*carriage)
{
	int	a1;
	int a2;
	int a3;

	a3 = carriage->param_values[2];
	if (check_reg(a3, a3, a3) && check_param(carriage, 0, &a1) && check_param(carriage, 0, &a2))
	{
		carriage->reg[a3 - 1] = getvalue((((a1 + a2)) + MEM_SIZE) % MEM_SIZE);
	}
	ft_printf("func_lldi\n");
}
