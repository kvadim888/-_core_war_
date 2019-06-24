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
	t_operation *operation;
	int32_t		*argv;

	operation = &carriage->operation;
	if (check_arg(operation->argt[0], operation->argv[0]) != T_REG
		|| check_arg(operation->argt[1], operation->argv[1]) != T_REG
		|| check_arg(operation->argt[2], operation->argv[2]) != T_REG)
		return ;
	argv = operation->argv;
	carriage->reg[argv[2] - 1] =
			carriage->reg[argv[0] - 1] + carriage->reg[argv[1] - 1];
	carriage->carry = (carriage->reg[argv[2] - 1]) ? 0 : 1;

	if (g_flag & 4)
	    ft_printf("P%5d | add r%i r%i r%i\n", carriage->id,
	    	operation->argv[0], operation->argv[1], operation->argv[2]);
}

void func_sub(t_carriage *carriage)
{
	t_operation *operation;
	int32_t		arg_1;
	int32_t		arg_2;
	int32_t		arg_3;

	operation = &carriage->operation;
	if (check_arg(operation->argt[0], operation->argv[0]) != T_REG
		|| check_arg(operation->argt[1], operation->argv[1]) != T_REG
		|| check_arg(operation->argt[2], operation->argv[2]) != T_REG)
		return ;
	arg_1 = operation->argv[0] - 1;
	arg_2 = operation->argv[1] - 1;
	arg_3 = operation->argv[2] - 1;
	carriage->reg[arg_3] = carriage->reg[arg_1] - carriage->reg[arg_2];
	carriage->carry = (carriage->reg[arg_3]) ? 0 : 1;

    if (g_flag & 4)
        ft_printf("P%5d | add r%i r%i r%i\n", carriage->id, operation->argv[0],
                  operation->argv[1], operation->argv[2]);

	ft_printf("func_sub\n");
}

void func_and(t_carriage *carriage)
{
	t_operation *operation;
	int a1;
	int a2;
	int a3;

	operation = &carriage->operation;
	a3 = carriage->param_values[2] - 1;
	if (check_arg(operation->argt[0], operation->argv[0]) != T_REG
		&& check_param(carriage, 0, &a1)
		&& check_param(carriage, 1, &a2))
	{
		carriage->reg[a3] = a1 & a2;
		carriage->carry = (carriage->reg[a3 - 1]) ? 0 : 1;
	}
    if (g_flag & 4)
        ft_printf("P%5d | and %i %i r%i\n", carriage->id, a1, a2, operation->argv[1]);
	ft_printf("func_and\n");
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
    if (g_flag & 4)
        ft_printf("P%5d | or %i %i r%i\n", carriage->id, a1, a2, operation->argv[1]);
	ft_printf("complete\n");
}

void func_xor(t_carriage *carriage)
{
	ft_printf("func_xor...");
	t_operation *operation;
	int a1;
	int a2;
	int a3;

    operation = carriage->operation;
	a3 = carriage->param_values[2];
	if (check_reg(a3, a3, a3) && check_param(carriage, 1, &a1)
		&& check_param(carriage, 2, &a2))
	{
		carriage->reg[a3 - 1] = a1 ^ a2;
		carriage->carry = (carriage->reg[a3 - 1]) ? 0 : 1;
	}
	if (g_flag & 4)
        ft_printf("P%5d | xor %i %i r%i\n", carriage->id, a1, a2, operation->argv[1]);
	ft_printf("complete\n");
}
