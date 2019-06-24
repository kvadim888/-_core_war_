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

#include "../includes/vm.h"

static t_header	*get_header(int fd)
{
	t_header	*header;
	uint32_t	buff;

	header = ft_memalloc(sizeof(t_header));
	header->magic = COREWAR_EXEC_MAGIC;
	error(read(fd, &header->prog_name, PROG_NAME_LENGTH) < PROG_NAME_LENGTH,
		  ERR_INVALID_BINARY);
	error(read(fd, &buff, REG_SIZE) < REG_SIZE, ERR_INVALID_BINARY);
	error(buff, "No null 4 bytes");
	error(read(fd, &buff, REG_SIZE) < REG_SIZE, ERR_INVALID_BINARY);
	header->prog_size = ft_swap32(buff);
	error(header->prog_size > CHAMP_MAX_SIZE, "Invalid prog_size");
	error(read(fd, &header->comment, COMMENT_LENGTH) < COMMENT_LENGTH,
		  ERR_INVALID_BINARY);
	error(read(fd, &buff, REG_SIZE) < REG_SIZE, ERR_INVALID_BINARY);
	error(buff, "No null 4 bytes");
	return (header);
}

static int		get_file(char *path)
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
	error(read(fd, &header, sizeof(uint32_t)) < 0, ERR_READ_BINARY);
	error(header != ft_swap32(COREWAR_EXEC_MAGIC), ERR_INVALID_HEADER);
	ft_strdel(&extension);
	return (fd);
}

int				new_champion(char *path, t_champion *champion)
{
	int		size;
	int		fd;

	if (champion == NULL)
		return (1);
	fd = get_file(path);
	champion->header = get_header(fd);
	champion->code = ft_memalloc(champion->header->prog_size * sizeof(uint8_t));
	ft_bzero(champion->code, champion->header->prog_size);
	size = read(fd, champion->code, champion->header->prog_size);
	error(size < champion->header->prog_size, ERR_INVALID_BINARY);
	error(read(fd, NULL, 1) != 0, ERR_INVALID_BINARY);
	close(fd);
	return (0); // return 0 if reading is complete
}

