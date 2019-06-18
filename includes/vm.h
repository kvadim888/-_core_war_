/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkryvono <vkryvono@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/11 01:42:00 by vkryvono          #+#    #+#             */
/*   Updated: 2019/06/11 01:42:00 by vkryvono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VM_H
#define VM_H

#include "libft.h"
#include "op.h"

#define		CODE_EXTENSION		".s"
#define		BINARY_EXTENSION	".cor"

/*
** Basic structures
*/

typedef struct s_game		t_game;
typedef struct s_champion	t_champion;
typedef struct s_operation	t_operation;
typedef struct s_carriage	t_carriage;

// Globals

uint8_t		g_flag;
t_game		g_game;

struct	s_game
{
	t_champion	*survivor;
	t_list		*players; // t_champion
	t_list		*carriages; // t_champion
	uint8_t		field[MEM_SIZE];
	int			check_counter;
	int			cycle_counter;
	int			check_period;
	int			check_amount;
	int			nbr_live;
	int			dump_period;
};

struct	s_champion
{
	int32_t		fd;
	t_header	*header;
	int			number;
	int			size;
	uint8_t		*code;
};

struct	s_carriage
{
	uint16_t	id;
	uint8_t		pos;
	uint16_t	op;
	uint16_t	live;
	uint32_t	rest;
	uint8_t		carry;
	uint32_t	reg[REG_NUMBER];
	// todo complete structure
};


struct	s_operation
{
	char 		*name;
	uint8_t		code;
	uint16_t	argc;
	uint16_t	arg_types[3];
	uint32_t	period;
	void		(*function)();
	uint16_t	length;
};

/*
** Error messages
*/

# define USAGE					"Usage : "

# define ERR_PLAYERS_AMOUNT		"Invalid players' amount"
# define ERR_INIT_PLAYER		"Unable to initialise player"
# define ERR_INIT_CARRIAGE		"Unable to initialise carriage"
# define ERR_INIT_VM			"Unable to initialise virtual machine"
# define ERR_OPEN_BINARY		"Binary file cannot be opened"
# define ERR_READ_BINARY		"Binary file cannot be read"
# define ERR_INVALID_BINARY		"Invalid binary file"
# define ERR_INVALID_HEADER		"Invalid magic header"


/*
** flags
*/

typedef enum	e_flag
{
	UNKNOWN,
	VERBOSE,
	DUMP,
	CHAMPION_NUMBER
}				t_flag;

/*
**	functions
*/

enum	e_function
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
}		t_function;

//typedef struct	s_operation
//{
//	void		(*function)(void);
//	int			(*check)(char *c1, char *c2); // check
//	short		cycle_value;
//	char*		label;
//	int8_t		dir_number; // label size
//}				t_operation;

void			error(int trigger, char *msg);
int				is_number(char *str);

void			log_field(int width);
void			log_champion(t_list *lst);

int				new_champion(char *path, t_champion *champion);


#endif //VM_H
