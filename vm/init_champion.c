/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_champion.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkryvono <vkryvono@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/18 04:08:00 by vkryvono          #+#    #+#             */
/*   Updated: 2019/06/18 04:08:00 by vkryvono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static t_header	*get_header(int fd, char *path)
{
	t_header	*header;
	uint32_t	buff;

	header = ft_memalloc(sizeof(t_header));
	header->magic = COREWAR_EXEC_MAGIC;
    err_msg(read(fd, &header->prog_name, PROG_NAME_LENGTH) < PROG_NAME_LENGTH,
            ERR_CH_TOO_SMALL, path);
    err_msg(read(fd, &buff, REG_SIZE) < REG_SIZE, ERR_CH_TOO_SMALL, path);
    err_msg(read(fd, &buff, REG_SIZE) < REG_SIZE, ERR_CH_TOO_SMALL, path);
	header->prog_size = ft_swap32(buff);
   // err_msg(header->prog_size > CHAMP_MAX_SIZE, "Invalid prog_size");
    err_msg(read(fd, &header->comment, COMMENT_LENGTH) < COMMENT_LENGTH, ERR_CH_TOO_SMALL, path);
    err_msg(read(fd, &buff, REG_SIZE) < REG_SIZE, ERR_CH_TOO_SMALL, path);
	return (header);
}

static int		get_file(char *path)
{
	int			fd;
	uint32_t	header;

    err_msg((fd = open(path, O_RDONLY)) == -1, ERR_CANT_READ_FILE, path);
    err_msg(read(fd, &header, sizeof(uint32_t)) < 0, ERR_CH_TOO_SMALL, path);
    err_msg(header != ft_swap32(COREWAR_EXEC_MAGIC), ERR_INVALID_HEADER, path);
	return (fd);
}

int				new_champion(char *path, t_champion *champion)
{
	int		size;
	int		fd;

	if (champion == NULL)
		return (1);
	fd = get_file(path);
	champion->header = get_header(fd, path);
	champion->code = ft_memalloc(champion->header->prog_size * sizeof(uint8_t));
	ft_bzero(champion->code, champion->header->prog_size);
	size = read(fd, champion->code, champion->header->prog_size);
    err_msg(size < champion->header->prog_size, ERR_INVALID_SIZE, path);
    err_msg(read(fd, NULL, 1) != 0, ERR_INVALID_SIZE, path);
	close(fd);
	return (0);
}

