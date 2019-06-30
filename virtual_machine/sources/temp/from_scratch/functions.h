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
#include "../libft/libft.h"

# define IND_SIZE			2
# define REG_SIZE			4
# define DIR_SIZE			REG_SIZE

# define REG_CODE			1
# define DIR_CODE			2
# define IND_CODE			3

# define MAX_ARGS_NUMBER	4
# define MAX_PLAYERS		4
# define MEM_SIZE			(4*1024)
# define IDX_MOD			(MEM_SIZE / 8)
# define CHAMP_MAX_SIZE		(MEM_SIZE / 6)

# define COMMENT_CHAR		'#'
# define LABEL_CHAR			':'
# define DIRECT_CHAR		'%'
# define SEPARATOR_CHAR		','

# define LABEL_CHARS		"abcdefghijklmnopqrstuvwxyz_0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ!'()-+*&<>=/"
# define COMMENT_CHARS		"abcdefghijklmnopqrstuvwxyz_0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ!'()-+*&<>=/ {}[]"
# define CMD_CHARS			"abcdefghijklmnopqrstuvwxyz_0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ!'()-+*&<>=/ ,"

# define NAME_CMD_STRING	".name"
# define COMMENT_CMD_STRING	".comment"

# define REG_NUMBER			16

# define CYCLE_TO_DIE		1536
# define CYCLE_DELTA		50
# define NBR_LIVE			21
# define MAX_CHECKS			10

typedef char				t_arg_type;

# define T_REG				1
# define T_DIR				2
# define T_IND				4
# define T_LAB				8

# define PROG_NAME_LENGTH	(128)
# define COMMENT_LENGTH		(2048)
# define COREWAR_EXEC_MAGIC	0xea83f3



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
	struct s_vm_proc	*next;
	struct s_vm_proc	*prev;
}						t_vm_proc;

typedef struct			s_champion
{
	uint32_t			lives_num;
	uint32_t			true_lives_num;
	uint32_t			lust_live;
	int					number;
	int					size; 
	int32_t				fd;
	char				name[PROG_NAME_LENGTH + 1];
	char				file_name[PROG_NAME_LENGTH + 1];
	char				comment[COMMENT_LENGTH + 1];
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
	t_operation			oper[16];
	t_champion			chmps[4];
	int					ch_number;
	unsigned char		map[MEM_SIZE];
	uint32_t			cycle;
	int32_t				cycle_to_die;
	uint32_t			proces_count;
	int32_t				rep_alive;
	int8_t				game_over; 
}						t_core;



char	*remove_spaces(char *s, int len);
char	*hex_to_bin(unsigned char c);
int		hex_to_dec(unsigned char *buf, int i);
int    	check_magic_header(int fd);
int     read_ch_name(t_champion *ch);
int     read_ch_comment(t_champion *ch);
int     check_ch_null(int fd);
int		check_ch_size(t_champion *ch);
int     read_params(int ac, char **av, t_core *core);
int		create_map(t_core *core);
int		read_op_code(t_champion ch, t_core *core, int p);
void 	cycle(t_core *core);

#endif
