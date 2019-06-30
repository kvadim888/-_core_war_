/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkotytsk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/21 17:24:38 by mkotytsk          #+#    #+#             */
/*   Updated: 2019/06/30 13:49:37 by vkryvono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/asm.h"

int		main(int argc, char **argv)
{
	t_all	*champ;
	int		fd;

	if (argc != 2)
		p_error("\n\tInvalid input arguments.\n"
			"Please use the following structure:\n\t./asm champion_file.s\n");
	if ((fd = open(argv[1], O_RDONLY)) < 0)
		p_error("\nERROR! Not valid file.\n");
	champ = ft_memalloc(sizeof(t_all));
	champ->base = ft_memalloc(sizeof(t_header));
	save_name(argv[1], fd, champ);
	save_inctructions(fd, champ);
	tokens_validation(champ->head, champ);
	write_in_file(champ, champ->code);
	return (0);
}
