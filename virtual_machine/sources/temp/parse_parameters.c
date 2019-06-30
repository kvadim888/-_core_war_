#include "functions.h"

int     check_file_format(char *s, t_champion *ch)
{
    int i;

    ft_bzero(ch->file_name, PROG_NAME_LENGTH + 1)
    i = -1;
    while (s[++i]){
        ch->file_name[i] = s[i];
        if (s[i] == '.' && s[++i] && s[i] == 'c' &&
        s[++i] && s[i] == 'o' && s[++i] && s[i] == 'r' && !s[++i]){
            return (1);
        }
    }
    return (0);
}

char      *remove_spaces(char s[], int len){
    char *ns;
    int sp;
    int i;

    i = -1;
    sp = 0;
    ns = (char*)ft_memalloc(sizeof(char) * len);
    ns = ft_memalloc(sizeof(char) * ft_strlen(s));
    while (s[++i])
    {
        if (s[i] == ' ')
        {
            sp++;
        }
        ns[i] = s[i + sp];
    }
    return ns;  
}


int    check_magic_header(int fd){
    char			buf[10];

    ft_bzero(buf, 10);
    if ((read(fd, buf, 9)) < 0)
		return -1;
    buf = remove_spaces(buf, ft_strlen(buf));
	if (hex_to_dec(buf) != hex_to_dec(COREWAR_EXEC_MAGIC)){
        //error
        return (0);
    } 
    return (1);
} 

char     *check_ch_name(int fd, t_champion *ch){
    char			buf[PROG_NAME_LENGTH * 2 + 1];
    char            temp[3];
    char            name[128]
    int i;
    int k;
    ft_bzero(buf, ROG_NAME_LENGTH * 2 + 1);
    ft_bzero(temp, 3);
    if ((read(fd, buf, 256)) < 0)
		return -1;
    buf = remove_spaces(buf, ft_strlen(buf));
    i = -1;
    k = -1;
    while (buf[++i]){
        temp[0] = buf[i];
        temp[1] = buf[++i];
        name[++k] = hex_to_dec(temp);
        if (name[k] == 0)
            i += 256;
    }
	if (!ft_strcmp(ch->file_name, name)){
        //error
        return (0);
    } 
    return (1);
}


char     *check_ch_comment(int fd, t_champion *ch){
    char			buf[PROG_NAME_LENGTH * 2 + 1];
    char            temp[3];
    char            name[128]
    int i;
    int k;
    ft_bzero(buf, ROG_NAME_LENGTH * 2 + 1);
    ft_bzero(temp, 3);
    if ((read(fd, buf, 256)) < 0)
		return -1;
    buf = remove_spaces(buf, ft_strlen(buf));
    i = -1;
    k = -1;
    while (buf[++i]){
        temp[0] = buf[i];
        temp[1] = buf[++i];
        name[++k] = hex_to_dec(temp);
        if (name[k] == 0)
            i += 256;
    }
	if (!ft_strcmp(ch->file_name, name)){
        //error
        return (0);
    } 
    return (1);
}


int     open_read_file(char *f_name, t_core **core, int c){
    t_champion *ch;

    ch = (t_champion*)ft_memalloc(sizeof(t_champion));
    ch->fd = open(f_name, O_RDONLY);
    (*core)->chems[c] = ch;
    if (check_magic_header(ch->fd)){
        if (){

        }
    }
}

int     process_file(char **av, int i, t_core **core)
{
    int f;
    int c;

    f = 0;
    c = 0; 
    if (ft_strequ("-n")){
        if (av[++i] && ft_isdigit(av[i]) == 1)
        {
            f = ft_atoi(av[i]);
        } else 
        {
           // error
        }

    } 
    if (check_file_format[av[i]]){

        c++;
    }

    if ()

    return f;
}


int     read_params(int ac, char **av, t_core **core)
{
    int i;

    i = 1;
    if (ac == 1)
    {
        //menu
    } else if (ac > 4)
    {
        //error
    } else 
    {
        while(i < ac && av[i])
        {
            i += process_file(av, i);
        }
    }

}