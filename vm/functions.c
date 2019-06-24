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
#include <functions.h>

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
}

int32_t		get_op_arg(t_vm *vm, t_cursor *cursor, uint8_t index, t_bool mod)
{
	t_op		*op;
	int32_t		value;
	int32_t		addr;

	op = &g_op[INDEX(cursor->op_code)];
	value = 0;
	if (cursor->args_types[INDEX(index)] & T_REG)
		value = cursor->reg[INDEX(get_byte(vm, cursor->pc, cursor->step))];
	else if (cursor->args_types[INDEX(index)] & T_DIR)
		value = bytecode_to_int32(vm->arena, cursor->pc + cursor->step, op->t_dir_size);
	else if (cursor->args_types[INDEX(index)] & T_IND)
	{
		addr = bytecode_to_int32(vm->arena, cursor->pc + cursor->step, IND_SIZE);
		value = bytecode_to_int32(vm->arena, cursor->pc + (mod ? (addr % IDX_MOD) : addr), DIR_SIZE);
	}
	cursor->step += step_size(cursor->args_types[INDEX(index)], op);
	return (value);
}

void	exec_function(t_list *lst)
{
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
    if (carriage->operation.period > 0)
        return ;
    if (carriage->operation.code > 0)
    {
        if (carriage->operation.codage)
        {
            arg_types.cell = g_game.field[carriage->pos];
            tmp.argt[0] = arg_types.arg1;
            tmp.argt[1] = arg_types.arg2;
            tmp.argt[2] = arg_types.arg3;
        }
        read_values(&g_game, carriage);
        operation->function(&g_game, carriage);
        carriage->pos += 7; // todo length estimation
    }
    else
        carriage->pos++;
}
