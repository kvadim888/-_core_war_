#ifndef COREWAR_FUNCTIONS_H
#define COREWAR_FUNCTIONS_H

#include <vm.h>


// todo set function period

t_operation	g_op[16] =
{
	{
		.name = "live",
		.code = 0x01,
		.argc = 1,
		.arg_types = {T_DIR, 0, 0},
		.function = func_live
	},
	{
		.name = "ld",
		.code = 0x02,
		.argc = 2,
		.arg_types = {T_DIR | T_IND, T_REG, 0},
		.function = func_ld
	},
	{
		.name = "st",
		.code = 0x03,
		.argc = 2,
		.arg_types = {T_REG, T_REG | T_IND, 0},
		.function = func_st
	},
	{
		.name = "add",
		.code = 0x04,
		.argc = 3,
		.arg_types = {T_REG, T_REG, T_REG},
		.function = func_add
	},
	{
		.name = "sub",
		.code = 0x05,
		.argc = 3,
		.arg_types = {T_REG, T_REG, T_REG},
		.function = func_sub
	},
	{
		.name = "and",
		.code = 0x06,
		.argc = 3,
		.arg_types = {T_REG | T_DIR | T_IND, T_REG | T_DIR | T_IND, T_REG},
		.function = func_and
	},
	{
		.name = "or",
		.code = 0x07,
		.argc = 3,
		.arg_types = {T_REG | T_DIR | T_IND, T_REG | T_DIR | T_IND, T_REG},
		.function = func_or
	},
	{
		.name = "xor",
		.code = 0x08,
		.argc = 3,
		.arg_types = {T_REG | T_DIR | T_IND, T_REG | T_DIR | T_IND, T_REG},
		.function = func_xor
	},
	{
		.name = "zjmp",
		.code = 0x09,
		.argc = 1,
		.arg_types = {T_DIR, 0, 0},
		.function = func_zjmp
	},
	{
		.name = "ldi",
		.code = 0x0A,
		.argc = 3,
		.arg_types = {T_REG | T_DIR | T_IND, T_REG | T_DIR, T_REG},
		.function = func_ldi
	},
	{
		.name = "sti",
		.code = 0x0B,
		.argc = 3,
		.arg_types = {T_REG, T_REG | T_DIR | T_IND, T_REG | T_DIR},
		.function = func_sti
	},
	{
		.name = "fork",
		.code = 0x0C,
		.argc = 1,
		.arg_types = {T_DIR, 0, 0},
		.function = func_fork
	},
	{
		.name = "lld",
		.code = 0x0D,
		.argc = 2,
		.arg_types = {T_DIR | T_IND, T_REG, 0},
		.function = func_lld
	},
	{
		.name = "lldi",
		.code = 0x0E,
		.argc = 3,
		.arg_types = {T_REG | T_DIR | T_IND, T_REG | T_DIR, T_REG},
		.function = func_lldi
	},
	{
		.name = "lfork",
		.code = 0x0F,
		.argc = 1,
		.arg_types = {T_DIR, 0, 0},
		.function = func_lfork
	},
	{
		.name = "aff",
		.code = 0x10,
		.argc = 1,
		.arg_types = {T_REG, 0, 0},
		.function = func_aff
	}
};


#endif //COREWAR_FUNCTIONS_H
