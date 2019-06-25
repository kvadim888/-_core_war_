/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   func_ld.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkryvono <vkryvono@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/22 18:25:00 by vkryvono          #+#    #+#             */
/*   Updated: 2019/06/22 18:25:00 by vkryvono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <functions.h>

void func_ld(t_carriage *carriage)
{
    t_operation *operation;
	uint16_t	*argv;

    operation = &carriage->operation;
	if (!check_arg(operation->argt[1], operation->argv[1]))
		return ;
	argv = operation->argv;
	if (check_arg(operation->argt[0], operation->argv[0]) == T_IND)
		carriage->reg[argv[1] - 1] = get_value((carriage->pos +
				(operation->argv[0] % IDX_MOD) + MEM_SIZE) % MEM_SIZE);
	else if (check_arg(operation->argt[0], operation->argv[0]) == T_DIR)
		carriage->reg[argv[1] - 1] = operation->argv[0];
	carriage->carry = (carriage->reg[argv[1] - 1]) ? 0 : 1;
	if (g_flag & 4)
	    ft_printf("P%5d | ld %i r%i\n", carriage->id, argv[1], argv[1]);
}

void func_ldi(t_carriage *carriage)
{
    t_operation *operation;
	uint16_t	*argv;

    operation = &carriage->operation;
	if (check_arg(operation->argt[2], operation->argv[2]) != T_REG)
		return ;
	argv = operation->argv;
	if (check_param(carriage, 0, &a1) && check_param(carriage, 0, &a2))
		carriage->reg[argv[2] - 1] =
				get_value((((a1 + a2) % IDX_MOD) + MEM_SIZE) % MEM_SIZE);
    if (g_flag & 4)
        ft_printf("P%5i | ldi r%i %i %i\n"
				  "     | -> load from %i + %i = %i (with pc and mod %i\n",
                  carriage->id, operation->argv[0], a2, a3, a2, a3, a2 + a3, carriage->pos + ((a2 + a3) % IDX_MOD));
	ft_printf("func_ldi\n");
}

void func_lld(t_carriage *carriage)
{
    t_operation *operation;
	uint16_t	*argv;

    operation = &carriage->operation;
	if (check_arg(operation->argt[1], operation->argv[1]) != T_REG)
		return ;
	argv = operation->argv;
	if (check_arg(operation->argt[0], operation->argv[0]) == T_IND)
		argv[0] = get_value(((carriage->pos + argv[0]) + MEM_SIZE) % MEM_SIZE);
	carriage->reg[argv[1] - 1] = argv[0];
	carriage->carry = (carriage->reg[argv[1] - 1]) ? 0 : 1;
	if (g_flag & 4)
	    ft_printf("P%5i | lld %i r%i", carriage->pos, argv[0], argv[1]);
}

void func_lldi(t_carriage *carriage)
{
    t_operation *operation;
	uint16_t	*argv;

    operation = &carriage->operation;
	if (check_arg(operation->argt[2], operation->argv[2]) != T_REG)
		return ;
	if (check_arg(operation->argt[0], operation->argv[0]) != (T_REG | T_DIR | T_IND) ||
		check_arg(operation->argt[1], operation->argv[1]) != (T_REG | T_DIR))
		return ;
	argv = operation->argv;
	if (check_param(carriage, 0, &a1) && check_param(carriage, 0, &a2))
		carriage->reg[argv[2] - 1] = get_value((((a1 + a2)) + MEM_SIZE) % MEM_SIZE);
	if (g_flag & 4)
	    ft_printf("P%5i | lldi %i %i r%i\n", carriage->id, a1, a2, operation->argv[2]);
}
