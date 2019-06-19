#ifndef COREWAR_FUNCTIONS_H
#define COREWAR_FUNCTIONS_H

#include "vm.h"

void	func_live();
void	func_ld();
void	func_st();
void	func_add();
void	func_sub();
void	func_and();
void	func_or();
void	func_xor();
void	func_zjmp();
void	func_ldi();
void	func_sti();
void	func_fork();
void	func_lld();
void	func_lldi();
void	func_lfork();
void	func_aff();

// todo set function period

t_operation	g_op[16] =
{
	{
		.name = "live",
		.code = 0x01,
		.argc = 1,
		.arg_types = {T_DIR, 0, 0},
		.function = func_live,
		.period = 10
	},
	{
		.name = "ld",
		.code = 0x02,
		.argc = 2,
		.arg_types = {T_DIR | T_IND, T_REG, 0},
		.function = func_ld,
		.period = 5
	},
	{
		.name = "st",
		.code = 0x03,
		.argc = 2,
		.arg_types = {T_REG, T_REG | T_IND, 0},
		.function = func_st,
		.period = 5
	},
	{
		.name = "add",
		.code = 0x04,
		.argc = 3,
		.arg_types = {T_REG, T_REG, T_REG},
		.function = func_add,
		.period = 10
	},
	{
		.name = "sub",
		.code = 0x05,
		.argc = 3,
		.arg_types = {T_REG, T_REG, T_REG},
		.function = func_sub,
		.period = 10
	},
	{
		.name = "and",
		.code = 0x06,
		.argc = 3,
		.arg_types = {T_REG | T_DIR | T_IND, T_REG | T_DIR | T_IND, T_REG},
		.function = func_and,
		.period = 6
	},
	{
		.name = "or",
		.code = 0x07,
		.argc = 3,
		.arg_types = {T_REG | T_DIR | T_IND, T_REG | T_DIR | T_IND, T_REG},
		.function = func_or,
		.period = 6
	},
	{
		.name = "xor",
		.code = 0x08,
		.argc = 3,
		.arg_types = {T_REG | T_DIR | T_IND, T_REG | T_DIR | T_IND, T_REG},
		.function = func_xor,
		.period = 6
	},
	{
		.name = "zjmp",
		.code = 0x09,
		.argc = 1,
		.arg_types = {T_DIR, 0, 0},
		.function = func_zjmp,
		.period = 20
	},
	{
		.name = "ldi",
		.code = 0x0A,
		.argc = 3,
		.arg_types = {T_REG | T_DIR | T_IND, T_REG | T_DIR, T_REG},
		.function = func_ldi,
		.period = 25
	},
	{
		.name = "sti",
		.code = 0x0B,
		.argc = 3,
		.arg_types = {T_REG, T_REG | T_DIR | T_IND, T_REG | T_DIR},
		.function = func_sti,
		.period = 25
	},
	{
		.name = "fork",
		.code = 0x0C,
		.argc = 1,
		.arg_types = {T_DIR, 0, 0},
		.function = func_fork,
		.period = 800
	},
	{
		.name = "lld",
		.code = 0x0D,
		.argc = 2,
		.arg_types = {T_DIR | T_IND, T_REG, 0},
		.function = func_lld,
		.period = 10
	},
	{
		.name = "lldi",
		.code = 0x0E,
		.argc = 3,
		.arg_types = {T_REG | T_DIR | T_IND, T_REG | T_DIR, T_REG},
		.function = func_lldi,
		.period = 50
	},
	{
		.name = "lfork",
		.code = 0x0F,
		.argc = 1,
		.arg_types = {T_DIR, 0, 0},
		.function = func_lfork,
		.period = 1000
	},
	{
		.name = "aff",
		.code = 0x10,
		.argc = 1,
		.arg_types = {T_REG, 0, 0},
		.function = func_aff,
		.period = 2
	}
};


#endif //COREWAR_FUNCTIONS_H
