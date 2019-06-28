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
		return (arg < 1 || arg > REG_NUMBER) ? 0 : T_REG;
	if (type == T_IND || type == T_DIR)
		return (type);
	return (0);
}

uint32_t get_arg(t_carriage *cr, uint32_t type, uint32_t arg)
{
	if (type == T_REG)
		return (cr->reg[arg - 1]);
	if (type == T_IND)
		return (get_value(((cr->pos + (arg) % IDX_MOD) + MEM_SIZE) % MEM_SIZE, REG_SIZE));
	if (type == T_DIR)
		return (arg);
}

void		set_params(t_operation *operation, uint16_t pos)
{
    int i;
    int tl;
    int op_code = operation->code;

    operation->length = 1;
    if (op_code != 1 && op_code != 9 && op_code != 12 && op_code != 15) {
        operation->length += 1;
    }
    i = -1;
    while (++i < operation->argc)
    {
        tl = 0;
        if (operation->argt[i] == 2)
        {
            if (op_code < 9 || op_code == 13 || op_code == 16)
            {
                tl = 4;
            } else {
                tl = 2;
            }
            operation->argt[i] = T_DIR;
        } else if (operation->argt[i] == 3)
        {
            tl = 2;
            operation->argt[i] = T_IND;
        } else if (operation->argt[i] == T_REG) {
            tl = 1;
        }
        if (tl != 0)
            operation->argv[i] = get_value((pos + operation->length) % MEM_SIZE, tl);
        operation->length += tl;
    }
}

void	exec_function(t_list *lst)
{
    t_carriage	*carriage;
    t_operation	*operation;
    t_argtype	argtype;

    carriage = lst->content;

    if (carriage->rest > 0)
        carriage->rest--;
    else
    {
        if (g_game.field[carriage->pos] > 0 && g_game.field[carriage->pos] < 16)
        {
            ft_memcpy(&carriage->operation,
                   &g_op[g_game.field[carriage->pos] - 1], sizeof(t_operation));
            carriage->rest = carriage->operation.period - 1;
        }
        else
        {
            carriage->operation.code = -1;
            carriage->rest = 0;
        }
    }
    if (carriage->rest > 0)
        return ;
    operation = &carriage->operation;
    //ft_printf("code = %i\n", carriage->pos);
    if (operation->code > 0 && operation->code < 16)
    {
        if (operation->codage != 0) {
            operation->argt[0] = (((uint8_t) g_game.field[carriage->pos + 1] >> 6) & 0b11);
            operation->argt[1] = (((uint8_t) g_game.field[carriage->pos + 1] >> 4) & 0b11);
            operation->argt[2] = (((uint8_t) g_game.field[carriage->pos + 1] >> 2) & 0b11);
            set_params(operation, carriage->pos);
        }
        else {
            operation->argv[0] = get_value((carriage->pos + 1) % MEM_SIZE, (operation->code == 1) ? 4 : 2);
            operation->length = (operation->code == 1) ? 5 : 3;
        }
        operation->function(carriage);
        carriage->pos = (carriage->pos + operation->length) % MEM_SIZE; // todo length estimation
    }
}