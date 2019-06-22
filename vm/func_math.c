/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   func_math.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkryvono <vkryvono@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/22 16:13:00 by vkryvono          #+#    #+#             */
/*   Updated: 2019/06/22 16:13:00 by vkryvono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <functions.h>

void func_add(t_carriage *carriage)
{
	ft_printf("func_add\n");
	int	a1;
	int a2;
	int a3;

	a1 = carriage->param_values[0];
	a2 = carriage->param_values[1];
	a3 = carriage->param_values[2];
	if (check_reg(a1, a2, a3))
	{
		carriage->reg[a3 - 1] = carriage->reg[a1 - 1] + carriage->reg[a2 - 1];
		carriage->carry = (carriage->reg[a3 - 1]) ? 0 : 1;
	}
}

void func_sub(t_carriage *carriage)
{
	ft_printf("func_sub\n");
	int	a1;
	int a2;
	int a3;

	a1 = carriage->param_values[0];
	a2 = carriage->param_values[1];
	a3 = carriage->param_values[2];
	if (check_reg(a1, a2, a3))
	{
		carriage->reg[a3 - 1] = carriage->reg[a1 - 1] - carriage->reg[a2 - 1];
		carriage->carry = (carriage->reg[a3 - 1]) ? 0 : 1;
	}
}

void func_and(t_carriage *carriage)
{
	ft_printf("func_and...");
	int a1;
	int a2;
	int a3;

	a3 = carriage->param_values[2];
	if (check_reg(a3, a3, a3) && check_param(carriage, 0, &a1)
		&& check_param(carriage, 1, &a2))
	{
		carriage->reg[a3 - 1] = a1 & a2;
		carriage->carry = (carriage->reg[a3 - 1]) ? 0 : 1;
	}
	ft_printf("complete\n");
}

void func_or(t_carriage *carriage)
{
	ft_printf("func_or...");
	int a1;
	int a2;
	int a3;

	a3 = carriage->param_values[2];
	if (check_reg(a3, a3, a3) && check_param(carriage, 1, &a1)
		&& check_param(carriage, 2, &a2))
	{
		carriage->reg[a3 - 1] = a1 | a2;
		carriage->carry = (carriage->reg[a3 - 1]) ? 0 : 1;
	}
	ft_printf("complete\n");
}

void func_xor(t_carriage *carriage)
{
	ft_printf("func_xor...");
	int a1;
	int a2;
	int a3;

	a3 = carriage->param_values[2];
	if (check_reg(a3, a3, a3) && check_param(carriage, 1, &a1)
		&& check_param(carriage, 2, &a2))
	{
		carriage->reg[a3 - 1] = a1 ^ a2;
		carriage->carry = (carriage->reg[a3 - 1]) ? 0 : 1;
	}
	ft_printf("complete\n");
}
