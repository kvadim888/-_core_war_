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
#include <libft.h>
#include <op.h>

#define USAGE	"Usage:<need fill>"

#define FLAG_VERBOSE	1

char g_flags = 0; // -v = verbose output

int		new_champion(t_champion *champion)
{
	//todo fill champion structure

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
	error(read(fd, &header, sizeof(header)) < 0, ERR_READ_BINARY);
	error(header != COREWAR_EXEC_MAGIC, ERR_INVALID_HEADER);
	return (fd);
}

void	read_params(int ac, char **av, t_game *core)
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
	core->players = players;
}

void	map_create(t_game *game)
{

}

int		main(int ac, char **av)
{
	t_game game;

	game = (t_game){.players = NULL};
	if (ac < 2)
	{
		ft_printf("%s\n", USAGE);
		return (1);
	}
	read_params(ac, av, &game);
	ft_printf("map creating\n");
	create_map(&game);

	ft_printf("game start\n");
//	cycle(&core);
	return (0);
}
