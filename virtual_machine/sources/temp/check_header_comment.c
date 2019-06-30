#include "functions.h"

void		cw_check_magic(t_champ *champ)
{
	unsigned char	buf[REG_SIZE];

	ft_bzero(buf, REG_SIZE);
	if ((read(champ->fd, buf, REG_SIZE)) < 0)
		cw_perror_exit(champ->file_name, READ_FILE);
	champ->head.magic = cw_hex_to_dec(buf, 4);
	if (champ->head.magic != COREWAR_EXEC_MAGIC)
		cw_exit(champ->file_name, HEADER);
}
