#include "functions.h"

//read params___________________________________________________________________

int     check_file_format(char *s, t_champion *ch)
{
    int i;

    ft_bzero(ch->file_name, PROG_NAME_LENGTH + 1);
    i = ft_strlen(s);
    ft_strcpy(ch->file_name, s);
    while (s[--i]){
        if (s[i] == 'r' && s[--i] && s[i] == 'o' &&
        s[--i] && s[i] == 'c' && s[--i] && s[i] == '.' && s[--i]){
            return (1); 
        }
    }
    return (0);
}

int     open_read_file(t_core *core, t_champion *ch){
  //  printf("file_name : %s\n ", ch->file_name);

    ch->fd = open(ch->file_name, O_RDONLY);
    //printf("ch->fd: %i\n" , ch->fd);
    if (check_magic_header(ch->fd) &&
    read_ch_name(ch) && check_ch_null(ch->fd) 
    && check_ch_size(ch) && read_ch_comment(ch) && check_ch_null(ch->fd) ){
     //  printf("magic header and name and comment are true\n");
    }
    return (0);
}

int     process_file(char **av, int i, t_core *core)
{ 
    int f;
    t_champion ch;
    f = 0;

    ch.number = core->ch_number + 1;
    if (ft_strequ("-n", av[i])){
        if (av[++i] && ft_atoi(av[i]) > 0)
        {
            f = ft_atoi(av[i]);
            i++;
            ch.number = f; 
         //   printf("n = %i\n", ch.number);     
        } else 
        {
           printf("Error: after -n must be digit");
        }

    } 
    if (check_file_format(av[i], &ch)){
        open_read_file(core, &ch);
        core->chmps[core->ch_number] = ch;
        i++;
    }   else {
         printf("Wrong file format");
    }
    return i;
}

int    sort_chmps(t_core *core)
{
    t_champion  tch;
    int i;
    int j;

  //  printf("core->ch_number %i\n",core->ch_number);
    i = -1;
    while (++i < core->ch_number)
    {
        //printf("ch name %s\n",core->chmps[i].name);
      //  printf("ch number %i\n",core->chmps[i].number);
            j = -1;
        while (++j < core->ch_number)
        {
            if (core->chmps[i].number < 1 || core->chmps[i].number > core->ch_number)
            {
                printf("wrong champion number\n");
                return (0);
            }
            if (core->chmps[j].number > core->chmps[i].number)               
			{
				tch = core->chmps[i];
				core->chmps[i] = core->chmps[j];
				core->chmps[j] = tch;
			}  
        }
    }
   // printf("-------------------------------\n");
    return (1);
}

int     read_params(int ac, char **av, t_core *core)
{
    int i;

    i = 1;
    core->ch_number = 0;
    if (ac == 1)
    {
        printf("Please specify cor files");
    }
    else {
        while(i < ac && av[i] && core->ch_number < MAX_PLAYERS)
        {
           // printf("I before: %i\n", i);
           // printf("ch_number before: %i\n", core->ch_number);
            i = process_file(av, i, core);
            core->ch_number++;
           // printf("I after: %i\n", i);
           // printf("ch_number after: %i\n", core->ch_number);
        }
    }
    if (core->ch_number == MAX_PLAYERS && i < ac)
    {
        printf("Too much parameters\n");
    }
    sort_chmps(core);


    for (int i = 0; i < 4; i++){
        printf("ch name %s\n",core->chmps[i].name);
    }
    return (1);
}
