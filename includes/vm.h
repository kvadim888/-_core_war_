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

#include "../libft/includes/libft.h"
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
uint32_t	g_id;

struct	s_game
{
	t_champion	*survivor;
	t_list		*players; // t_champion
	size_t		players_amount;
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
	uint32_t 	param_values[3];
	uint32_t 	param_types[3];
	uint32_t	reg[REG_NUMBER];
	t_operation *operation;
	// todo complete structure
};


struct	s_operation
{
	char 		*name;
	uint8_t		code;
	uint16_t	argc;
	uint16_t	argv[3];
	uint16_t	arg_types[3];
	uint32_t	period;
	void		(*function)();
	uint16_t	length;
};


# pragma pack(push, 1)

typedef union	u_agrtype
{
	uint8_t		cell;
	struct
	{
		uint8_t	arg1:2;
		uint8_t	arg2:2;
		uint8_t	arg3:2;
		uint8_t	dump:2;
	};
}				t_argtype;

typedef union	u_value
{
	uint32_t	word;
	uint8_t		byte[REG_SIZE];
}				t_value;

# pragma pack(pop)

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

void			error(int trigger, char *msg);
int				is_number(char *str);

void			set_value(int32_t addr, uint32_t value);
uint32_t		get_value(uint32_t addr);
void	        exec_function(t_list *lst);

void			log_field(int width);
void			log_champion(t_list *lst);

int				new_champion(char *path, t_champion *champion);

t_list		    *carriage_filter(t_list *lst);
void	        field_init();
t_champion	    *game_loop();

#endif //VM_H
