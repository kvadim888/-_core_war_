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
	int32_t		*argv;

	get_argval(carriage);
    operation = &carriage->operation;
	argv = operation->argv;
	if (check_arg(operation->argt[0], operation->argv[0]) == T_IND)
		carriage->reg[argv[1] - 1] = get_value((carriage->pos +
			(operation->argv[0] % IDX_MOD) + MEM_SIZE) % MEM_SIZE, REG_SIZE);
	else if (check_arg(operation->argt[0], operation->argv[0]) == T_DIR)
		carriage->reg[argv[1] - 1] = operation->argv[0];
	carriage->carry = (carriage->reg[argv[1] - 1]) ? 0 : 1;
	if (g_flag & FLAG_VERBOSE_4)
	    ft_printf("P%5d | ld %i r%i\n", carriage->id, argv[1], argv[1]);
}

void func_ldi(t_carriage *carriage)
{
    t_operation *operation;
	int32_t		*argv;

	get_argval(carriage);
    operation = &carriage->operation;
	argv = operation->argv;
	argv[0] = get_value(carriage);
	argv[1] = get_value(carriage);
	carriage->reg[argv[2] - 1] = get_value((((argv[0] + argv[1]) % IDX_MOD)
											+ MEM_SIZE) % MEM_SIZE, REG_SIZE);
	if (g_flag & FLAG_VERBOSE_4)
		ft_printf("P%5i | ldi r%i %i %i\n"
			"     | -> load from %i + %i = %i (with pc and mod %i\n",
			carriage->id, argv[0], argv[1], argv[2], argv[1], argv[2],
			argv[1] + argv[2], carriage->pos + ((argv[1] + argv[2]) % IDX_MOD));
}

void func_lld(t_carriage *carriage)
{
    t_operation *operation;
	int32_t		*argv;

	get_argval(carriage);
    operation = &carriage->operation;
	argv = operation->argv;
	if (check_arg(operation->argt[0], operation->argv[0]) == T_IND)
		argv[0] = get_value(((carriage->pos + argv[0])
											+ MEM_SIZE) % MEM_SIZE, REG_SIZE);
	carriage->reg[argv[1] - 1] = argv[0];
	carriage->carry = (carriage->reg[argv[1] - 1]) ? 0 : 1;
	if (g_flag & FLAG_VERBOSE_4)
	    ft_printf("P%5i | lld %i r%i", carriage->pos, argv[0], argv[1]);
}

void func_lldi(t_carriage *carriage)
{
    t_operation *operation;
	int32_t		*argv;

	get_argval(carriage);
    operation = &carriage->operation;
	argv = operation->argv;
	if (check_arg(operation->argt[0], operation->argv[0]) == T_IND)
		argv[0] = get_value(carriage->pos, );
	argv[1] = get_value();
	carriage->reg[argv[2] - 1] =
			get_value((((argv[0] + argv[1])) + MEM_SIZE) % MEM_SIZE, REG_SIZE);
	if (g_flag & FLAG_VERBOSE_4)
	    ft_printf("P%5i | lldi %i %i r%i\n",
	    		carriage->id, argv[0], argv[1], operation->argv[2]);
}
