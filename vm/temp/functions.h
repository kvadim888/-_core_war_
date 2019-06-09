/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akotilie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/06 14:06:54 by akotilie          #+#    #+#             */
/*   Updated: 2019/04/06 14:06:57 by akotilie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FUNCTIONS_H
# define FUNCTIONS_H

# include <stdint.h>
#include "stdlib.h"
#include <stdio.h>
#include "libft/libft.h"

# define COREWAR_EXEC_MAGIC		0xea83f3

#define IND_SIZE				2
#define REG_SIZE				4
#define DIR_SIZE				REG_SIZE
     
# define REG_CODE				1
# define DIR_CODE				2
# define IND_CODE				3

#define CYCLE_TO_DIE			1536
#define CYCLE_DELTA				50
#define NBR_LIVE				21
#define MAX_CHECKS				10

typedef char	t_arg_type;

#define T_REG					1
#define T_DIR					2
#define T_IND					4
#define T_LAB					8
#define REG_NUMBER				16



enum {LIVE, LD, ST, ADD, SUB, AND, OR, XOR, ZJMOP, LDI, STI, FORK, LLD, LLDI, \
LFORK, AFF};

typedef struct			s_vm_proc
{
	int8_t				carry;
   	int8_t				next_operation_code; // next operation code
    int8_t				cycles_for_operation; // cycles for op
	int8_t				is_alive;
    int8_t				param_value1; // param 1
    int8_t				param_value2; // param 2
	int8_t				param_value3; // param 3
	int32_t				pc;
	char				param_type_1; // param type 1
	char				param_type_2; // param type 2
	char				param_type_3; // param type 3
	int32_t				reg[REG_NUMBER];
	int32_t				chemp_num;
	int16_t				cycle_exec;
	uint8_t				cmd;
	uint8_t				color;
	struct s_vm_proc	*next;
	struct s_vm_proc	*prev;
}						t_vm_proc;

typedef struct			s_champion
{
	uint32_t			lives_num;
	uint32_t			true_lives_num;
	uint32_t			lust_live;
	int32_t				champs;
	int32_t				fd;
	char[PROG_NAME_LENGTH]			file_name;
    t_vm_proc*          processes;//processes
	struct s_champion	*next;
}						t_champion;

typedef struct			s_operation
{
	void				(*function)(t_vm_proc *proc);
	int					(*check)(char *c1, char *c2); // check
	short				cycle_value;
	char*				label;
	int8_t				dir_number; // label size	
}						t_operation;

typedef struct			s_core
{
	t_vm_proc			*vp;
	t_operation			oper[16];
	t_champion			chems[4];
	uint32_t			cycle;
	int32_t				cycle_to_die;
	uint32_t			proces_count;
	int32_t				rep_alive;
	int8_t				game_over; 
	int					**op_dscr;
}						t_core;

void		init_live(t_core *core);
void		init_ld(t_core *core);
void		init_st(t_core *core);
int			read_op_code(t_champion *ch, t_core **core);
int     	c_di_r(char *c1, char *c2);
int    		c_r_ri(char *c1, char *c2);
int     	c_r_r_r(char *c1, char *c2);
int     	c_rdi_rdi_r(char *c1, char *c2);
int     	c_rdi_rd_r(char *c1, char *c2);
int     	c_r_rdi_rd(char *c1, char *c2);
int     	c_r(char *c1, char *c2);
void    	create_pr(t_champion **ch, int *prm);
int     	hex_to_dec(char num[]);
int     	read_reg(int fd);
int     	read_dir(int fd, int dn);
int     	read_ind(int fd);
void		live(t_vm_proc *pr);
void		ld(t_vm_proc *pr);
void		st(t_vm_proc *pr);
void		init_add(t_core *core);
void		init_sub(t_core *core);
void		init_and(t_core *core);
void		init_or(t_core *core);
void		init_xor(t_core *core);
void		init_zjump(t_core *core);
void		check_ch_process(t_core *core, t_champion *ch);
int     	make_step(t_champion *ch, t_core **core);
int        read_params(t_vm_proc *pr, int fd);

#endif
