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

#include <libft.h>

#include <vm.h>
#include <op.h>
#include <functions.h>

uint8_t		get_flag(char *str)
{
	ft_printf("flag = %s\n", str);
	if (ft_strequ(str, "-v") || ft_strequ(str, "--verbose"))
		return (VERBOSE);
	if (ft_strequ(str, "-d") || ft_strequ(str, "--dump"))
		return (DUMP);
	if (ft_strequ(str, "-n"))
		return (CHAMPION_NUMBER);
	return (UNKNOWN);
}

int		handle_flag(int flag, char *av)
{
	int	champion_number;

	champion_number = 0;
	if (flag == UNKNOWN)
		usage();
	if (flag == VERBOSE)
	{
		error(!is_number(av), "The argument after -v (-verbose) must be a positive digit");
		g_flag |= (uint8_t)ft_atoi(av);
	}
	if (flag == DUMP)
	{
		error(!is_number(av), "The argument after -d (-dump) must be a positive digit");
		g_game.dump_period = ft_atoi(av);
		g_flag |= FLAG_DUMP;
		error(g_game.dump_period < 0, "Invalid dump value");
	}
	if (flag == CHAMPION_NUMBER)
	{
		error(!is_number(av), "The argument after -n must be a positive digit");
		champion_number = ft_atoi(av);
		error(champion_number < 1 || champion_number > 4,
			  "Invalid champion_number value");
	}
	return (champion_number);
}

void	read_params(int ac, char **av)
{
	t_champion champion;
	int i;
	int amount;

	i = 0;
	ft_bzero(&champion, sizeof(t_champion));
	while (++i < ac)
	{
		if (*av[i] == '-') // if arg is flag
		{
			champion.number = handle_flag(get_flag(av[i]), av[i + 1]);
			i++;
		}
		else
		{
			error(new_champion(av[i], &champion), ERR_INIT_PLAYER);
			ft_lstappend(&g_game.players, ft_lstnew(&champion, sizeof(t_champion)));
			ft_bzero(&champion, sizeof(t_champion));
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
	ft_bzero(&carriage, sizeof(t_carriage));
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


int		main(int ac, char **av)
{
	t_champion	*winer;

	if (ac < 2)
	{
		ft_printf("%s\n", USAGE);
		return (1);
	}
	read_params(ac, av);
	ft_lstiter(g_game.players, choose_num);
	ft_printf("Introducing players\n");
	ft_lstiter(g_game.players, log_champion);

	ft_printf("Map creating\n");
	field_init();
	log_field(32); //fixme delete
	 ft_printf("Game start\n");
	winer = game_loop();
	log_winner(winer);
	return (0);
}
