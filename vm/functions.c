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

#include <vm.h>

//todo write functions

typedef union	u_value
{
	uint32_t	word;
	uint8_t		byte[REG_SIZE];
}				t_value;

void		set_value(int32_t addr, uint32_t value)
{
	int		i;
	t_value	val;

	val.word = value;
	i = 0;
	while (i < REG_SIZE)
	{
		g_game.field[(addr + i + MEM_SIZE) % MEM_SIZE] = val.byte[i];
		i++;
	}
}

uint32_t	get_value(uint32_t addr)
{
	int 	i;
	t_value	value;

	value.word = 0;
	i = 0;
	while (i < REG_SIZE)
	{
		value.byte[i] = g_game.field[(addr + i + MEM_SIZE) % MEM_SIZE];
		i++;
	}
	return (value.word);
}

int 		check_reg(int i, int j, int k)
{
	if (i < 1 || i > 16 || j < 1 || j > 16 || k < 1 || k > 16)
		return (0);
	return (1);
}

int		check_param(t_carriage	*carriage, int i)
{
	if (carriage->param_types[i] == T_REG && carriage->param_values[i])
		return (0);
//		*a = carriage->reg[carriage->param_values[i] - 1];
	if (carriage->param_types[i] == T_IND)
		return (0);
//		*a = getvalue(((carriage->pos + (carriage->param_values[i]) % IDX_MOD) + MEM_SIZE) % MEM_SIZE);
	if (carriage->param_types[i] == T_DIR)
		return (0);
//		*a = carriage->param_values[i];
	return (1);
}

