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
    t_operation *operation;
	uint16_t	*argv;

    operation = &carriage->operation;
    argv = operation->argv;
	if (check_arg(operation->argt[0], operation->argv[0]) != T_REG)
		return;
	if (check_arg(operation->argt[1], operation->argv[1]) == T_REG)
		carriage->reg[argv[1] - 1] = carriage->reg[argv[0] - 1];
	if (check_arg(operation->argt[1], operation->argv[1]) == T_IND)
		set_value((((carriage->pos + (argv[1] % IDX_MOD)) + MEM_SIZE) % MEM_SIZE),
				carriage->reg[argv[0] - 1]);
	if (g_flag & 4)
	    ft_printf("P%5i | st r%i %i\n", carriage->id, argv[0], argv[1]);
}

void func_sti(t_carriage *carriage)
{
    t_operation *operation;
	uint16_t	*argv;

    operation = &carriage->operation;
	if (check_arg(operation->argt[0], operation->argv[0]) != T_REG)
		return ;
	if (!check_arg(operation->argt[1], operation->argv[1]) ||
		!check_arg(operation->argt[2], operation->argv[2]))
		return ;
	argv = operation->argv;
	set_value((((argv[1] + argv[2]) + MEM_SIZE) % MEM_SIZE),
			carriage->reg[argv[0] - 1]);
	if (g_flag & 4)
	    ft_printf("P%5i | sti r%i %i %i\n"
			"     | -> store to %i + %i = %i (with pc and mod %i)\n",
			carriage->id, operation->argv[0], argv[1], argv[2],
			argv[1], argv[2], argv[1] + argv[2],
			carriage->pos + ((argv[1] + argv[2]) % IDX_MOD));
}

