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
