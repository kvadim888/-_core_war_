#include "functions.h"


// read null __________________________________________________

int     check_ch_null(int fd){
    unsigned char	buf[REG_SIZE + 1];
    unsigned char   temp[2];

    int i;
    ft_bzero(buf, REG_SIZE + 1);
    ft_bzero(temp, 2);
    if ((fd, buf, REG_SIZE)) < 0)
		return 0;
    i = -1;
    printf("buf 2: %s\n", buf);
    while (buf[++i]){
        temp[0] = buf[i];
        (*ch)->comment[i] = hex_to_dec(temp, 1);
         printf("comment : %c\n", (*ch)->comment[i]);
        if ((*ch)->comment[i] == 0)
            i += COMMENT_LENGTH;
    }
    printf("comment : %s\n", (*ch)->comment);
    return (1);
}


// read comments __________________________________________________

int     read_ch_comment(t_champion **ch){
    unsigned char	buf[COMMENT_LENGTH + 1];
    unsigned char   temp[2];

    int i;
    ft_bzero(buf, COMMENT_LENGTH + 1);
    ft_bzero((*ch)->comment, COMMENT_LENGTH + 1);
    ft_bzero(temp, 2);
    if ((read((*ch)->fd, buf, COMMENT_LENGTH)) < 0)
		return 0;
    i = -1;
    printf("buf 3: %s\n", buf);
    while (buf[++i]){
        temp[0] = buf[i];
        (*ch)->comment[i] = hex_to_dec(temp, 1);
         printf("comment : %c\n", (*ch)->comment[i]);
        if ((*ch)->comment[i] == 0)
            i += COMMENT_LENGTH;
    }
    printf("comment : %s\n", (*ch)->comment);
    return (1);
}


// read name _______________________________________________________

int     read_ch_name(t_champion **ch)
{
    unsigned char	buf[PROG_NAME_LENGTH + 1];
    unsigned char   temp[2];
    int i;

    ft_bzero(buf, PROG_NAME_LENGTH + 1);
    ft_bzero((*ch)->name, PROG_NAME_LENGTH + 1);
    ft_bzero(temp, 2);
    if ((read((*ch)->fd, buf, PROG_NAME_LENGTH)) < 0)
		return -1;

      printf("buf1 : %s\n", buf);
    i = -1;
    while (buf[++i]){
        temp[0] = buf[i];
        (*ch)->name[i] = hex_to_dec(temp, 1);
        if ((*ch)->name[i] == 0)
            i += PROG_NAME_LENGTH;
    }
    printf("Name : %s\n", (*ch)->name);
    return (1);
}


// check header _______________________________________________________________

int    check_magic_header(int fd){
    unsigned char	buf[REG_SIZE];

    if ((read(fd, buf, REG_SIZE)) < 0)
		return -1;
        printf("COREWAR_EXEC_MAGIC = %i\n", COREWAR_EXEC_MAGIC);
    	if (hex_to_dec(buf,4) != COREWAR_EXEC_MAGIC){
        printf("Error with magic header");
        return (0);
    } 
    return (1);
} 

//read params___________________________________________________________________

int     check_file_format(char *s, t_champion **ch)
{
    int i;

    ft_bzero((*ch)->file_name, PROG_NAME_LENGTH + 1);
    i = ft_strlen(s);
    ft_strcpy((*ch)->file_name, s);
    while (s[--i]){
        if (s[i] == 'r' && s[--i] && s[i] == 'o' &&
        s[--i] && s[i] == 'c' && s[--i] && s[i] == '.' && s[--i]){
            return (1); 
        }
    }
    return (0);
}

int     open_read_file(t_core **core, int c, t_champion **ch){
    printf("file_name : %s\n ", (*ch)->file_name);

    (*ch)->fd = open((*ch)->file_name, O_RDONLY);
    (*core)->chems[c] = (**ch);
    printf("ch->fd: %i\n" , (*ch)->fd);
    if (check_magic_header((*ch)->fd) &&
    read_ch_name(ch) && read_ch_comment(ch)){

       printf("msgic header and name and comment are true\n");
    }
    return (0);
}

int     process_file(char **av, int i, t_core **core, int c)
{ 
    int f;
    t_champion *ch;
    f = 0;

    ch = (t_champion*)ft_memalloc(sizeof(t_champion));
    if (ft_strequ("-n", av[i])){
        if (av[++i] && ft_atoi(av[i]) > 0)
        {
            f = ft_atoi(av[i]);
            i++;
            ch->number = f; 
            printf("n = %i\n", ch->number);     
        } else 
        {
           printf("Error: after -n must be digit");
        }

    } 
    if (check_file_format(av[i], &ch)){
        open_read_file(core, c, &ch);
    }   else {
         printf("Wrong file format");
    }
    return i;
}

int     read_params(int ac, char **av, t_core **core)
{
    int i;
    int c;

    c = 0;
    i = 1;
    if (ac == 1)
    {
        printf("Please specify cor files");
    } /*else if (ac > 4)
    {
        printf("Too much parameters");
    }*/
     else {
        while(i < ac && av[i])
        {
            i += process_file(av, i,core,  c);
            c++;
        }
    }
    return (1);
}


//main__________________________________________________________________________
int     main(int ac, char**av)
{   
    t_core *core; 
    core  = (t_core*)ft_memalloc(sizeof(t_core));

    read_params(ac, av, &core);

    return (0);
}