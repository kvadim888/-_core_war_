#include "vm.h"

void    f
int     check_ch_size(t_champion *ch)
{
    unsigned char	buf[REG_SIZE];

    ft_bzero(buf, REG_SIZE);
	error((read(ch->fd, buf, REG_SIZE) < 0), ERR_READ_BINARY);
    ch->size = hex_to_dec(buf, REG_SIZE);
    error(ch->size > CHAMP_MAX_SIZE)), "Champion size too big\n");
    return (1);
}

int     check_ch_null(int fd)
{
    unsigned char	buf[REG_SIZE + 1];

    ft_bzero(buf, REG_SIZE + 1);
    error((read(fd, buf, REG_SIZE) < 0), ERR_READ_BINARY);
    error((hex_to_dec(buf, REG_SIZE) != 0), "Champion file must contain null\n");
}


// read comments __________________________________________________

int     read_ch_comment(t_champion *ch)
{
    ft_bzero(ch->comment, COMMENT_LENGTH + 1);
    error(read(ch->fd, ch->comment, COMMENT_LENGTH), ERR_READ_BINARY);
    return (1);
}


// read name _______________________________________________________

void     read_ch_name(t_champion *ch)
{
    ft_bzero(ch->name, PROG_NAME_LENGTH + 1);
    error(read(ch->fd, ch->name, PROG_NAME_LENGTH) < 0), ERR_READ_BINARY);
}


// check header _______________________________________________________________

void       check_magic_header(int fd)
{
    unsigned char	buf[REG_SIZE];

    error(read(ch->fd, ch->comment, REG_SIZE), ERR_READ_BINARY); 
    error(hex_to_dec(buf, REG_SIZE) != COREWAR_EXEC_MAGIC, ERR_INVALID_HEADER);   
} 