/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkryvono <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/08 15:40:58 by vkryvono          #+#    #+#             */
/*   Updated: 2019/06/08 15:42:45 by vkryvono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "functions.h"
#include "../libft/includes/libft.h"
#include "op.h"
#include <stdio.h>

#define USAGE	"Usage:<need fill>"

#define FLAG_VERBOSE	1

char	g_flags = 0; // -v = verbose output
t_game	g_game;


int		new_champion(t_champion *ch)
{
	//todo fill champion structure
	unsigned char	buf[REG_SIZE];

	ch->header = (t_header*)ft_memalloc(sizeof(t_header));
    error(read(ch->fd, buf, REG_SIZE) < 0, ERR_READ_BINARY); 
    error((ch->header->magic = hex_to_dec(buf, REG_SIZE)) != COREWAR_EXEC_MAGIC, ERR_INVALID_HEADER);
	//printf("header = %i\n", hex_to_dec(buf, REG_SIZE));
	ft_bzero(ch->header->prog_name, PROG_NAME_LENGTH + 1);
    error(read(ch->fd, ch->header->prog_name, PROG_NAME_LENGTH) < 0, ERR_READ_BINARY);
//	printf("ch->header->prog_name = %s\n", ch->header->prog_name);
	ft_bzero(buf, REG_SIZE);
    error(read(ch->fd, buf, REG_SIZE) < 0, ERR_READ_BINARY); 
    error((hex_to_dec(buf, REG_SIZE) != 0), "Champion file must contain null\n");
	ft_bzero(buf, REG_SIZE);
    error(read(ch->fd, buf, REG_SIZE) < 0, ERR_READ_BINARY); 
    error((ch->header->prog_size = hex_to_dec(buf, REG_SIZE)) > CHAMP_MAX_SIZE, "Champion size too big\n");
//	printf("ch->header->prog_size = %i\n", ch->header->prog_size);
	ft_bzero(ch->header->comment, COMMENT_LENGTH + 1);
    error(read(ch->fd, ch->header->comment, COMMENT_LENGTH) < 0, ERR_READ_BINARY);
//	printf("ch->header->comment = %s\n", ch->header->comment);
	ft_bzero(buf, REG_SIZE);
    error((read(ch->fd, buf, REG_SIZE) < 0), ERR_READ_BINARY);
    error((hex_to_dec(buf, REG_SIZE) != 0), "Champion file must contain null\n");
	ch->code = ft_memalloc(sizeof(uint8_t) * ch->header->prog_size);
	ft_bzero(ch->code, ch->header->prog_size);
    error((read(ch->fd, ch->code, ch->header->prog_size) < 0), ERR_READ_BINARY);
	return (0);
}

int		get_file(char *path)
{
	char		*localname;
	char		*extension;
	int			fd;
	uint32_t	header;

	localname = ft_strrchr(path, '/');
	localname == NULL ? path : localname++;
	extension = ft_strrchr(path, '.');
	error(!(*extension), "File extension is not specified");
	error((extension <= localname), "Invalid filename");
	extension = ft_strdup(extension);
	error(ft_strcmp(extension, BINARY_EXTENSION), "Invalid file extension");
	error((fd = open(path, O_RDONLY)) == -1, ERR_OPEN_BINARY);

	//error(read(fd, &header, sizeof(header)) < 0, ERR_READ_BINARY);
	//printf("header = %u\n", header);
	//printf("header = %u\n", COREWAR_EXEC_MAGIC);
//	error(header != COREWAR_EXEC_MAGIC, ERR_INVALID_HEADER);
	return (fd);
}

void	read_params(int ac, char **av, t_game *game)
{
	int			i;
	t_list		*players;
	t_champion	champion;
	int		amount;

	players = NULL;
	i = 0;
	while (++i < ac)
	{
		if (ft_strequ(av[i], "-v") || ft_strequ(av[i], "--verbose"))
		{
			g_flags |= FLAG_VERBOSE;
			ft_printf("verbose enabled\n");
			//todo: verbose output
		}
		else if (ft_strequ(av[i], "-n"))
		{
			ft_bzero(&champion, sizeof(t_champion)); // clear fields
			error(!is_number(av[++i]), "Error: after -n must be digit");
			champion.number = ft_atoi(av[i]);
			error(champion.number > 4 || champion.number < 1, "Invalid champion number");
			champion.fd = get_file(av[++i]);
			error(new_champion(&champion), ERR_INVALID_BINARY);
			ft_lstadd(&players, ft_lstnew(&champion, sizeof(t_champion)));
		}
		else
			error(1, "Invalid parameters\n");
	}
	amount = ft_lstlen(players);
	error(amount < 1 || amount > MAX_PLAYERS, ERR_PLAYERS_AMOUNT);
	game->players = players;
}

void	map_create(t_game *game)
{
	int			len;
	t_list		*tmp;
	t_champion	*champ;
	t_carriage	carriage;

	ft_bzero(game->field, MEM_SIZE);
	len = ft_lstlen(game->players);
	carriage = (t_carriage){.carry = 0, .op = 0, .live = 0, .rest = 0, .param_types = {0, 0, 0}};
	tmp = game->players;
	while (tmp)
	{
		champ = tmp->content;
		carriage.id = champ->number;
		carriage.reg[0] = -champ->number;
		carriage.pos = (carriage.id - 1) * (MEM_SIZE / len);
		ft_memcpy(game->field + carriage.pos, champ->code, champ->header->prog_size);
		ft_lstadd(&game->carriages, ft_lstnew(&carriage, sizeof(t_carriage)));
		tmp = tmp->next;
	}
}

void	exec_function(t_list *lst)
{
	t_carriage	*carriage;
	t_operation	*operation;

	carriage = lst->content;
	if (carriage->rest > 0)
		carriage->rest--;
	else
	{
		carriage->op = g_game.field[carriage->pos];
		if (carriage->op > 0 && carriage->op <= 16)
			carriage->rest = g_op[carriage->op - 1].period - 1;
		else
		{
			carriage->op = 0;
			carriage->rest = 0;
		}
	}
	if (carriage->rest > 0)
		return ;
	operation = (carriage->op > 0) ? &g_op[carriage->op - 1] : NULL;
	if (operation)
	{	
		if (operation->check(hex_to_bin(g_game.field[++carriage->pos], 1), carriage)){
			printf("Codage checked\n");
			carriage->pos = read_values(&g_game, carriage, carriage->pos);
		}
		operation->function(&g_game, carriage);
		carriage->pos += operation->length; // todo length estimation
	}
	else
		carriage->pos++;
}

t_list	*carriage_filter(t_list *lst)
{
	t_list		*tmp;
	t_carriage	*carriage;

	carriage = lst->content;
	while (carriage->live == 0)
	{
		tmp = lst;
		lst = lst->next;
		ft_lstdelone(&tmp, ft_lstrm);
	}
	return (lst);
}

int		main(int ac, char **av)
{

	g_game = (t_game){.players = NULL, .survivor = NULL, .check_counter = 0,
				   .check_period = 0, .check_amount = 0, .carriages = NULL,
				   .cycle_counter = 0, .nbr_live = 0};
	if (ac < 2)
	{
		ft_printf("%s\n", USAGE);
		return (1);
	}
	ft_printf("Introducing\n");
	ft_lstiter(g_game.players, log_champ);
	read_params(ac, av, &g_game);
	ft_printf("map creating\n");
	map_create(&g_game);

	ft_printf("game start\n");

	// game loop
	while (ft_lstlen(g_game.carriages))
	{
		g_game.cycle_counter++;
		g_game.check_counter++;
		ft_lstiter(g_game.carriages, exec_function);
		if (g_game.check_counter == g_game.check_period)
		{
			g_game.check_amount++;
			ft_lstmap(g_game.carriages, carriage_filter);
			if (g_game.check_amount == MAX_CHECKS
				|| g_game.nbr_live >= NBR_LIVE)
			{
				g_game.check_period -= CYCLE_DELTA;
			}
			g_game.check_counter = 0;
		}
	}
	error(g_game.survivor==NULL, "Winner is disappear");
	ft_printf("[%s<%d> has won!]\n",
			g_game.survivor->header->prog_name, g_game.survivor->number);
	return (0);
}
