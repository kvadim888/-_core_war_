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

#include "../includes/vm.h"

//todo write functions

int		check_arg(uint32_t type, uint32_t arg)
{
	if (type == T_REG)
		return (arg < 1 || arg > REG_NUMBER);
	return (type == T_IND || type == T_DIR);
}

uint32_t get_arg(uint32_t type, uint32_t arg)
{
	if (type == T_REG)

		return (arg < 1 || arg > REG_NUMBER);
	return (type == T_IND || type == T_DIR);
}

//		return (0);
////		*a = carriage->reg[carriage->param_values[i] - 1];
//		return (0);
////		*a = getvalue(((carriage->pos + (carriage->param_values[i]) % IDX_MOD) + MEM_SIZE) % MEM_SIZE);
//	if (carriage->param_types[i] == T_DIR)
//		return (0);
////		*a = carriage->param_values[i];
//	return (1);
//}

