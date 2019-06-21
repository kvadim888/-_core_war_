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

#include "vm.h"


//todo write functions

void	setvalue(int addr, int val)
{
	int i;

	i = REG_SIZE;
	while (i--)
	{
		g_game.field[(addr + i + MEM_SIZE) % MEM_SIZE] = val & 255;
		val >>= 8;
	}
}

int		getvalue(int addr)
{
	int 	i;
	int32_t result;
	int32_t num;
	int 	minus;

	i = 0;
	result = 0;
	minus = (g_game.field[addr] & 0b10000000) ? 1 : 0;
	while (i < REG_SIZE)
	{
		num = g_game.field[(addr + i + MEM_SIZE) % MEM_SIZE];
		result <<= 8;
		(minus) ? num ^= 255 : 0;
		result |= num;
		i++;
	}
	result = (minus) ? ~(result) : result;
	return (result);
}

int 	check_reg(int i, int j, int k)
{
	if (i < 1 || i > 16 ||
		j < 1 || j > 16 ||
		k < 1 || k > 16)
		return (0);
	return (1);
}

int		check_param(t_carriage	*carriage, int i, int *a)
{
	if (carriage->param_types[i] == T_REG && check_reg(carriage->param_values[i], 10, 10))
	{
		*a = carriage->reg[carriage->param_values[i] - 1];
		return (0);
	}
	else if (carriage->param_types[i] == T_IND)
	{
		*a = getvalue(((carriage->pos + (carriage->param_values[i]) % IDX_MOD) + MEM_SIZE) % MEM_SIZE);
		return (0);
	}
	else if (carriage->param_types[i] == T_DIR)
	{
		*a = carriage->param_values[i];
		return (0);
	}
	else
		return (-1);		
}

void	clone_reg(uint32_t *arr1, uint32_t *arr2)
{
	int i;

	i = 0;
	while (i < REG_NUMBER)
	{
		arr1[i] = arr2[i];
		i++;
	}
}

void func_live(t_game *game, t_carriage	*carriage)
{
	ft_printf("func_live\n");
	carriage->live = g_game.cycle_counter;
	g_game.nbr_live++;
	if (-carriage->param_values[0] > 0 && -carriage->param_values[0] < g_game.pamount + 1)
		g_game.survivor->number = -carriage->param_values[0];
	else
		return ;
}

void func_ld(t_game *game, t_carriage	*carriage)
{
	ft_printf("func_ld\n");
	int	a1;
	int a2;

	a1 = carriage->param_values[0];
	a2 = carriage->param_values[1];
	if (!check_reg(a1, a2, a2))
		return ;
	if (carriage->param_types[0] == T_IND)
	{
		a1 = getvalue((carriage->pos + (a1 % IDX_MOD) + MEM_SIZE) % MEM_SIZE);
		carriage->reg[a2 - 1] = a1;
	}
	else
		carriage->reg[a2 - 1] = a1;
	carriage->carry = (carriage->reg[a2 - 1]) ? 0 : 1;
}

void func_st(t_game *game, t_carriage	*carriage)
{
	ft_printf("func_st\n");
	int a1;
	int a2;

	a1 = carriage->param_values[0];
	a2 = carriage->param_values[1];
	if (check_reg(a1, a1, a1))
	{
		if (carriage->param_types[1] == T_REG && check_reg(a2, a2, a2))
			carriage->reg[a2 - 1] = carriage->reg[a1 - 1];
		if (carriage->param_types[1] == T_IND)
			setvalue((((carriage->pos + (a2 % IDX_MOD)) + MEM_SIZE) % MEM_SIZE), carriage->reg[a1 - 1]);
	}
}

void func_add(t_game *game, t_carriage	*carriage)
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
	else
	{
		return ;
	}
}

void func_sub(t_game *game, t_carriage	*carriage)
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
	else
	{
		return ;
	}
}

void func_and(t_game *game, t_carriage	*carriage)
{
	ft_printf("func_and\n");
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
}

void func_or(t_game *game, t_carriage	*carriage)
{
	ft_printf("func_or\n");
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
}

void func_xor(t_game *game, t_carriage	*carriage)
{
	ft_printf("func_xor\n");
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
}

void func_zjmp(t_game *game, t_carriage	*carriage)
{
	ft_printf("func_zjmp\n");
	if (carriage->carry == 1)
	{
		carriage->pos = ((carriage->param_values[0] % IDX_MOD) + MEM_SIZE) % MEM_SIZE;
	}
	else
		return ;
}

void func_ldi(t_game *game, t_carriage	*carriage)
{
	ft_printf("func_ldi\n");
	int	a1;
	int a2;
	int a3;

	a3 = carriage->param_values[2];
	if (check_reg(a3, a3, a3) && check_param(carriage, 0, &a1) && check_param(carriage, 0, &a2))
	{
		carriage->reg[a3 - 1] = getvalue((((a1 + a2) % IDX_MOD) + MEM_SIZE) % MEM_SIZE);
	}
}

void func_sti(t_game *game, t_carriage	*carriage)
{
	ft_printf("func_sti\n");
	int a1;
	int a2;
	int a3;

	a1 = carriage->param_values[0];
	if (check_reg(a1, a1, a1) && check_param(carriage, 1, &a2) && check_param(carriage, 2, &a3))
	{
			setvalue((((a2 + a3) + MEM_SIZE) % MEM_SIZE), carriage->reg[a1 - 1]);
	}
}

void func_fork(t_game *game, t_carriage	*carriage)
{
	ft_printf("func_fork\n");
	t_carriage *new;

	new = (t_carriage *)malloc(sizeof(t_carriage));
	ft_memcpy(new, carriage, sizeof(t_carriage));
	new->pos = ((carriage->param_values[0] % IDX_MOD) + MEM_SIZE) % MEM_SIZE;
	new->carry = carriage->carry;
	new->id = ++g_id;
	new->live = carriage->live;
	new->op = 0;
	clone_reg(new->reg, carriage->reg);
}

void func_lld(t_game *game, t_carriage	*carriage)
{
	ft_printf("func_lld\n");
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
}

void func_lldi(t_game *game, t_carriage	*carriage)
{
	ft_printf("func_lldi\n");
int	a1;
	int a2;
	int a3;

	a3 = carriage->param_values[2];
	if (check_reg(a3, a3, a3) && check_param(carriage, 0, &a1) && check_param(carriage, 0, &a2))
	{
		carriage->reg[a3 - 1] = getvalue((((a1 + a2)) + MEM_SIZE) % MEM_SIZE);
	}
}

void func_lfork(t_game *game, t_carriage *carriage)
{
	ft_printf("func_lfork\n");
		t_carriage *new;

	new = (t_carriage *)malloc(sizeof(t_carriage));
	ft_memcpy(new, carriage, sizeof(t_carriage));
	new->pos = (carriage->pos + carriage->param_values[0]) % MEM_SIZE;
	new->carry = carriage->carry;
	new->id = ++g_id;
	new->live = carriage->live;
	new->op = 0;
	clone_reg(new->reg, carriage->reg);
}

void func_aff(t_game *game, t_carriage	*carriage)
{
	ft_printf("func_aff\n");
	int a1;

	a1 = carriage->param_values[0];
	if (check_reg(a1, 10, 10))
		printf("%c\n", (char)carriage->reg[a1 - 1]);
	else
		return ;
}