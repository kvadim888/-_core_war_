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

#include <vm.h>
#include <op.h>

#include <functions.h>
#include <libft.h>

#include <stdio.h>

int 	get_flag(char *str)
{
	if (ft_strequ(str, "-v") || ft_strequ(str, "--verbose"))
		return (VERBOSE);
	if (ft_strequ(str, "-d") || ft_strequ(str, "--dump"))
		return (DUMP);
	if (ft_strequ(str, "-n"))
		return (CHAMPION_NUMBER);
	return (UNKNOWN);
}

void	read_params(int ac, char **av)
{
	t_champion *champion;
	int i;
	int amount;
	int flag;
	int champion_number;

	champion_number = 0;
	i = 0;
	while (++i < ac)
	{
		if (*av[i] == '-') // if arg is flag
		{
			flag = get_flag(av[i]);
			if (flag == UNKNOWN)
			{
				ft_printf("%s\n", USAGE);
				exit(0);
			}
			if (flag == VERBOSE)
				g_flag |= 1 << VERBOSE;
			if (flag == DUMP)
			{
				error(!is_number(av[++i]),
					  "The argument after -d (--dump) must be a digit");
				g_game->dump_period = ft_atoi(av[i]);
				error(g_game->dump_period < 0, "Invalid dump value");
			}
			if (flag == CHAMPION_NUMBER)
			{
				error(!is_number(av[++i]),
					  "The argument after -n must be a digit");
				champion_number = ft_atoi(av[i]);
				error(champion_number < 1 || champion_number > 4,
					  "Invalid champion_number value");
			}
		}
		else
		{
			champion = new_champion(av[i], champion_number);
			if (champion->number != 0)
				g_game->players[champion->number] = champion;
			else
			{
				int j = 0;
				while (j < MAX_PLAYERS && g_game->players[j] != NULL)
					j++;
				error(j == MAX_PLAYERS, ERR_PLAYERS_AMOUNT);
				g_game->players[j] = champion;
				champion->number = j;
			}
			champion_number = 0;
		}
	}
}

void	field_init()
{
	int			len;
	t_list		*tmp;
	t_champion	*champ;
	t_carriage	carriage;

	ft_bzero(g_game->field, MEM_SIZE);
	len = ft_lstlen(g_game->players);
	carriage = (t_carriage){.carry = 0, .live = 0, .rest = 0};
	ft_bzero(&carriage.operation, sizeof(t_operation));
	tmp = g_game->players;
	while (tmp)
	{
		champ = tmp->content;
		carriage.id = champ->number;
		carriage.reg[0] = -champ->number;
		carriage.pos = (carriage.id - 1) * (MEM_SIZE / len);
		ft_memcpy(g_game->field + carriage.pos,
				champ->code, champ->header->prog_size);
		ft_lstadd(&g_game->carriages, ft_lstnew(&carriage, sizeof(t_carriage)));
		tmp = tmp->next;
	}
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
		op = g_game->field[carriage->pos++];
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
			arg_types.cell = g_game->field[carriage->pos];
			tmp.argt[0] = arg_types.arg1;
			tmp.argt[1] = arg_types.arg2;
			tmp.argt[2] = arg_types.arg3;
		}
		read_values(&g_game, carriage, carriage->pos);
		operation->function(&g_game, carriage);
		carriage->pos += 7; // todo length estimation
	}
	else
		carriage->pos++;
}

t_list		*carriage_filter(t_list *lst)
{
	t_list		head;
	t_list		*prev;
	t_carriage	*carriage;

	head.next = lst;
	prev = &head;
	while (lst)
	{
		carriage = lst->content;
		if (carriage->live <= 0)
		{
			prev->next = lst->next;
			ft_lstdelone(&lst, ft_lstrm);
			lst = prev->next;
		}
		else
		{
			prev = lst;
			lst = lst->next;
		}
	}
	return (head.next);
}

t_game		*game_init()
{
	if (g_game)
		return (g_game);
	g_game = ft_memalloc(sizeof(t_game));
	ft_bzero(g_game, sizeof(t_game));
	return (g_game);
}

t_champion	*game_loop()
{
	while (g_game->carriages && ft_lstlen(g_game->carriages))
	{
		g_game->cycle_counter++;
		g_game->check_counter++;
		ft_lstiter(g_game->carriages, exec_function);
		if (g_game->check_counter >= g_game->check_period)
		{
			g_game->check_counter = 0;
			g_game->check_amount++;
			g_game->carriages = carriage_filter(g_game->carriages);
			if (g_game->check_amount == MAX_CHECKS ||
				g_game->live_counter >= NBR_LIVE)
				g_game->check_period -= (g_game->check_period > 0)
						? CYCLE_DELTA : 0;
		}
		if (g_game->dump_counter >= g_game->dump_period)
		{
			log_field(32); //todo log_mode
			exit(0);
		}
		if (g_game->show_counter >= g_game->show_period)
			log_field(32); //todo log_mode
	}
	return (g_game->survivor);
}

int		main(int ac, char **av)
{
	t_champion	*winer;

	if (ac < 2)
	{
		ft_printf("%s\n", USAGE);
		return (1);
	}
	g_game = game_init();

	read_params(ac, av);

	ft_printf("Introducing players\n");
	ft_lstiter(g_game->players, log_champion);

	ft_printf("Map creating\n");
	field_init();
	log_field(32); //fixme delete

	ft_printf("Game start\n");
	winer = game_loop();

	error(g_game->survivor == NULL, "Winner is disappear"); //fixme delete
	ft_printf("[%s<%d> has won!]\n",
			winer->header->prog_name, winer->number);
	return (0);
}
