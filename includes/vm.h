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

# include <libft.h>
# include <op.h>

# define		CODE_EXTENSION		".s"
# define		BINARY_EXTENSION	".cor"

# define USAGE				"Usage : "
# define ERR_PLAYERS_AMOUNT	"Invalid players' amount"
# define ERR_INIT_PLAYER	"Unable to initialise player"
# define ERR_INIT_CARRIAGE	"Unable to initialise carriage"
# define ERR_INIT_VM		"Unable to initialise virtual machine"
# define ERR_OPEN_BINARY	"Binary file cannot be opened"
# define ERR_READ_BINARY	"Binary file cannot be read"
# define ERR_INVALID_BINARY	"Invalid binary file"
# define ERR_INVALID_HEADER	"Invalid magic header"

typedef struct s_game		t_game;
typedef struct s_champion	t_champion;
typedef struct s_carriage	t_carriage;
typedef struct s_operation	t_operation;

t_game						g_game;
uint8_t						g_flag;
uint32_t					g_id;

struct						s_game
{
	t_champion				*survivor;
	t_list					*players; // t_champion
	size_t					players_amount;
	t_list					*carriages; // t_champion
	uint8_t					field[MEM_SIZE];
	int32_t					check_counter;
	int32_t					check_period;
	int32_t					check_amount;
	int32_t					cycle_counter;
	int32_t					live_counter;
	int32_t					dump_period;
	int32_t					dump_counter;
	int32_t					show_period;
	int32_t					show_counter;
};

struct						s_champion
{
	int32_t					fd;
	t_header				*header;
	int						number;
	int						size;
	uint8_t					*code;
};

struct						s_operation
{
	char 					*name;
	uint8_t					code;
	uint8_t					codage;
	uint16_t				argc;
	uint16_t				argv[3];
	uint16_t				argt[3];
	uint32_t				period;
	void					(*function)();
};

struct						s_carriage
{
	uint16_t				id;
	uint8_t					pos;
	uint16_t				live;
	uint32_t				rest;
	uint8_t					carry;
	uint32_t 				param_values[3];
	uint32_t 				param_types[3];
	uint32_t				reg[REG_NUMBER];
	t_operation 			operation;
};

typedef union				u_agrtype
{
	uint8_t					cell;
	struct
	{
		uint8_t				arg1;
		uint8_t				arg2;
		uint8_t				arg3;
		uint8_t				dump;
	};
}							t_argtype;

typedef union				u_value
{
	uint32_t				word;
	uint8_t					byte[REG_SIZE];
}							t_value;

typedef enum				e_flag
{
	UNKNOWN,
	VERBOSE,
	DUMP,
	CHAMPION_NUMBER
}							t_flag;

void						error(int trigger, char *msg);
int							is_number(char *str);

void						set_value(int32_t addr, uint32_t value);
uint32_t					get_value(uint32_t addr);
void	        			exec_function(t_list *lst);

void						log_field(int width);
void						log_champion(t_list *lst);

int							check_arg(uint32_t type, uint32_t arg);
uint32_t					get_arg(t_carriage *cr, uint32_t type, uint32_t arg);

t_champion					*new_champion(char *path, int number);

t_list		    			*carriage_filter(t_list *lst);
void	        			field_init();
t_champion	    			*game_loop();

#endif
