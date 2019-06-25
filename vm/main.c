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
	t_champion champion;
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
			{
				error(!is_number(av[++i]),
					  "The argument after -v (-verbose) must be a digit");
				g_flag |= ft_atoi(av[i]);
			}
			if (flag == DUMP)
			{
				error(!is_number(av[++i]),
					  "The argument after -d (-dump) must be a digit");
				g_game.dump_period = ft_atoi(av[i]);
				error(g_game.dump_period < 0, "Invalid dump value");
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
			champion.number = champion_number;
			error(new_champion(av[i], &champion), ERR_INIT_PLAYER);
			ft_lstappend(&g_game.players, ft_lstnew(&champion, sizeof(t_champion)));
			champion_number = 0;
		}
	}
	amount = ft_lstlen(g_game.players);
	g_id = amount;
	error(amount < 1 || amount > MAX_PLAYERS, ERR_PLAYERS_AMOUNT);
}

void	map_create(t_game *game)
{
	int			len;
	t_list		*tmp;
	t_champion	*champ;
	t_carriage	carriage;

	ft_bzero(game->field, MEM_SIZE);
	len = ft_lstlen(game->players);
	carriage = (t_carriage){.carry = 0, .op = 0, .live = 0, .rest = 0};
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
	t_operation	tmp;

	carriage = lst->content;

	if (carriage->rest > 0)
		carriage->rest--;
	else
	{
		carriage->op = g_game.field[carriage->pos];
		if (carriage->op > 0 && carriage->op <= 16)
		{
			carriage->rest = g_op[carriage->op - 1].period - 1;
		}
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
		tmp.argt[0] = (uint16_t)(g_game.field[carriage->pos] >> 6 & 0b11);
		tmp.argt[1] = (uint16_t)(g_game.field[carriage->pos] >> 4 & 0b11);
		tmp.argt[2] = (uint16_t)(g_game.field[carriage->pos] >> 2 & 0b11);
		printf("type = %i\n", tmp.arg_types[0]);

		carriage->pos = read_values(&g_game, carriage, carriage->pos);
		operation->function(&g_game, carriage);
		carriage->pos += 7; // todo length estimation
	}
}

int		main(int ac, char **av)
{
	t_champion	*winer;

	if (ac < 2)
	{
		ft_printf("%s\n", USAGE);
		return (1);
	}
	read_params(ac, av);

	ft_printf("Introducing players\n");
	ft_lstiter(g_game.players, log_champion);

	ft_printf("Map c.ating\n");
	field_init();
	log_field(32); //fixme delete

	ft_printf("Game start\n");
	winer = game_loop();

	error(g_game.survivor == NULL, "Winner is disappear"); //fixme delete
	ft_printf("[%s<%d> has won!]\n",
			winer->header->prog_name, winer->number);
	return (0);
}
