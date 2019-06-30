/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkryvono <vkryvono@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/11 01:42:00 by vkryvono          #+#    #+#             */
/*   Updated: 2019/06/30 13:43:15 by vkryvono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VM_H
#define VM_H

<<<<<<< Updated upstream:includes/vm.h
#include "libft.h"
#include "op.h"
=======
# include "../libft/includes/libft.h"
# include "op.h"
>>>>>>> Stashed changes:virtual_machine/includes/vm.h

#define		CODE_EXTENSION		".s"
#define		BINARY_EXTENSION	".cor"

/*
** Basic structures
*/

typedef struct	s_game
{
	t_list		*players; // t_champion
	uint8_t		field[];
}				t_game;

typedef struct	s_champion
{
	int32_t		fd;
	t_list		*proc; // t_vm_proc
	t_header	*header;
	int			number;
	int			size;
}				t_champion;

typedef struct	s_carriage
{
	uint8_t		carry;
	uint32_t	pc;
	uint32_t	reg[REG_NUMBER];
	// todo complete structure
}				t_carriage;

/*
** Error messages
*/

# define ERR_PLAYERS_AMOUNT		"Invalid players' amount"
# define ERR_INIT_PLAYER		"Unable to initialise player"
# define ERR_INIT_CURSOR		"Unable to initialise cursor"
# define ERR_INIT_VM			"Unable to initialise virtual machine"
# define ERR_OPEN_BINARY		"Binary file cannot be opened"
# define ERR_READ_BINARY		"Binary file cannot be read"
# define ERR_INVALID_BINARY		"Invalid binary file"
# define ERR_INVALID_HEADER		"Invalid magic header"

/*
**	functions
*/

enum	e_operation
{
	LIVE,
	LD,
	ST,
	ADD,
	SUB,
	AND,
	OR,
	XOR,
	ZJMOP,
	LDI,
	STI,
	FORK,
	LLD,
	LLDI,
	LFORK,
	AFF
};

typedef struct	s_operation
{
	void		(*function)(void);
	int			(*check)(char *c1, char *c2); // check
	short		cycle_value;
	char*		label;
	int8_t		dir_number; // label size
}				t_operation;


void			error(int trigger, char *msg);
int				is_number(char *str);

#endif //VM_H
