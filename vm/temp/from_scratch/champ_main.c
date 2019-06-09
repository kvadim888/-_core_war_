#include "functions.h"

// read size __________________________________________________

int     check_ch_size(t_champion *ch)
{
    unsigned char	buf[REG_SIZE + 1];

    ft_bzero(buf, REG_SIZE + 1);
    if (read(ch->fd, buf, REG_SIZE) < 0)
		return 0;
    if ((ch->size = hex_to_dec(buf, REG_SIZE)) > CHAMP_MAX_SIZE)
        return (0);
   // printf("size is : %i b\n", ch->size);
    return (1);
}  


// read null __________________________________________________

int     check_ch_null(int fd)
{
    unsigned char	buf[REG_SIZE + 1];

    ft_bzero(buf, REG_SIZE + 1);
    if (read(fd, buf, REG_SIZE) < 0)
		return 0;
    if (hex_to_dec(buf, REG_SIZE) != 0)
        return (0);
    return (1);
}


// read comments __________________________________________________

int     read_ch_comment(t_champion *ch)
{

    ft_bzero(ch->comment, COMMENT_LENGTH + 1);
    if ((read(ch->fd, ch->comment, COMMENT_LENGTH)) <= 0)
		return -1;
  //  printf("comment : %s\n", ch->comment);
    return (1);
}


// read name _______________________________________________________

int     read_ch_name(t_champion *ch)
{
    ft_bzero(ch->name, PROG_NAME_LENGTH + 1);
    if ((read(ch->fd, ch->name, PROG_NAME_LENGTH)) <= 0)
		return -1;
  //  printf("Name : %s\n", ch->name);
    return (1);
}


// check header _______________________________________________________________

int    check_magic_header(int fd)
{
    unsigned char	buf[REG_SIZE];

    if ((read(fd, buf, REG_SIZE)) < 0)
		return -1;
  //  printf("COREWAR_EXEC_MAGIC = %i\n", COREWAR_EXEC_MAGIC);
    if (hex_to_dec(buf, REG_SIZE) != COREWAR_EXEC_MAGIC)
        return (0);    
    return (1);
} 