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
#include "../includes/functions.h"

int		check_arg(uint32_t type, uint32_t arg)
{
	if (type == T_REG)
		return (arg < 1 || arg > REG_NUMBER) ? T_REG : 0;
	if (type == T_IND || type == T_DIR)
		return (type);
	return (0);
}

uint32_t get_arg(t_carriage *cr, uint32_t type, uint32_t arg)
{
	if (type == T_REG)
		return (cr->reg[arg - 1]);
	if (type == T_IND)
		return (get_value(((cr->pos + (arg) % IDX_MOD) + MEM_SIZE) % MEM_SIZE));
	if (type == T_DIR)
		return (arg);
    return (0);
}

int		steps_estimation(t_operation	operation, int op_code)
{
	int s;
	int i;
	int tl;

	s = 1;
	if (op_code != 1 && op_code != 9 && op_code != 12 & op_code != 15)
		s += 1;
	i = -1;
//	printf("operation.code = %i\n", op_code);
	while (++i < 3)
	{
		tl = 1;
	//	printf("type %i = %i\n", i, operation.arg_types[i]);
		if (operation.argt[i] == T_DIR)
		{	
			if (op_code < 8 || op_code == 13 || op_code == 16)
			{
				tl = 4;
			} else
				tl = 2;
		} else if (operation.argt[i] == T_IND)
		{
			tl = 2;
		} else if (operation.argt[i] == T_REG){
			tl = 1;
		}
		s += tl;
	}
	printf("steps = %i\n", s);
	return (s);
}

void	exec_function(t_list *lst)
{
    printf("exec function\n");
    uint32_t	op;
    t_carriage	*carriage;
    t_operation	*operation;
    t_operation	tmp;
    t_argtype	arg_types;

    carriage = lst->content;
    if (carriage->operation.period > 0)
        carriage->operation.period--;
    else
    {
        op = g_game.field[carriage->pos++];
        if (op > 0 && op <= 16)
            ft_memcpy(&carriage->operation, &g_op[op - 1], sizeof(t_operation));
        else
            ft_bzero(&carriage->operation, sizeof(t_operation));
    }
     printf("exec function 2\n");
     printf("carriage->operation.period %i\n", carriage->operation.period);
    if (carriage->operation.period > 0)
        return ;
    printf("exec function 3\n");
    if (carriage->operation.code > 0)
    {
        if (carriage->operation.codage)
        {
            arg_types.cell = g_game.field[carriage->pos];
            tmp.argt[0] = arg_types.arg1;
            tmp.argt[1] = arg_types.arg2;
            tmp.argt[2] = arg_types.arg3;
        }
       // read_values(&g_game, carriage);
        operation->function(&g_game, carriage);
        carriage->pos = (carriage->pos + steps_estimation(tmp, carriage->op)) % MEM_SIZE; // todo length estimation
    }
    else
        carriage->pos++;
}