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
#include "functions.h"
//#include <libft.h>
#include "op.h"
#include <stdio.h>

int 	get_flag(char *str)
{
	if (ft_strequ(str, "-v") || ft_strequ(str, "--verbose"))
		return (VERBOSE);
	if (ft_strequ(str, "-d") || ft_strequ(str, "--dump"))
		return (DUMP);
	if (ft_strequ(str, "-n"))
		return (CHAMPION_NUMBER);
	return (UNKNOWN);
}













int     process_file(char **av, int i)
{ 
    int f;
    t_champion ch;
    f = 0;

    ch.number = ++g_game->ch_count;
    if (ft_strequ("-n", av[i])){
        if (av[++i] && ft_atoi(av[i]) > 0)
        {
			flag = get_flag(av[i]);
			if (flag == UNKNOWN)
			{
				ft_printf("%s\n", USAGE);
				exit(1);
			}
			if (flag == VERBOSE)
				g_flag |= 1 << VERBOSE;
			if (flag == DUMP)
			{
				error(!is_number(av[++i]), ERR_D_NOT_DIGIT);
				g_game.dump_period = ft_atoi(av[i++]);
				error(g_game.dump_period < 0, ERR_INVALID_DUMP);
			}
			if (flag == CHAMPION_NUMBER)
			{
				error(!is_number(av[++i]), ERR_N_NOT_DIGIT);
				champion_number = ft_atoi(av[i++]);
				error(champion_number < 1 || champion_number > 4, ERR_INVALID_CH_NUMBER);
				ch.number = champion_number;
			} 
         //   printf("n = %i\n", ch.number);     
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

int     read_params(int ac, char **av)
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












void	read_params(int ac, char **av)
{
	int			i;
	t_champion	champion;
	int			amount;
	int			flag;
	int			champion_number;

	champion_number = 0;
	i = 0;
	while (++i < ac)
	{
		ft_bzero(&champion, sizeof(t_champion)); // clear fields
		if (*av[i] == '-') // if arg is flag
		{
			
		}
		else
		{
			champion.number = champion_number;
			printf("new champion \n");
			error(new_champion(av[i], &champion), ERR_INIT_PLAYER);
			ft_lstappend(&g_game.players, ft_lstnew(&champion, sizeof(t_champion)));
			champion_number = 0;
		}
	}
	amount = ft_lstlen(g_game.players);
	g_id = amount;
	error(amount < 1 || amount > MAX_PLAYERS, ERR_PLAYERS_AMOUNT);
}

void	map_create(t_game *game)
{
	int			len;
	t_list		*tmp;
	t_champion	*champ;
	t_carriage	carriage;

	ft_bzero(game->field, MEM_SIZE);
	len = ft_lstlen(game->players);
	carriage = (t_carriage){.carry = 0, .op = 0, .live = 0, .rest = 0};
	tmp = game->players;
	while (tmp)
	{
		champ = tmp->content;
		carriage.id = champ->number;
		carriage.reg[0] = -champ->number;
		carriage.pos = (carriage.id - 1) * (MEM_SIZE / len);
		ft_memcpy(game->field + carriage.pos, champ->code, champ->header->prog_size);
		ft_lstadd(&game->carriages, ft_lstnew(&carriage, sizeof(t_carriage)));
		tmp = tmp->next;
	}
}

void	exec_function(t_list *lst)
{
	t_carriage	*carriage;
	t_operation	*operation;
	t_operation	tmp;

	carriage = lst->content;

	if (carriage->rest > 0)
		carriage->rest--;
	else
	{
		carriage->op = g_game.field[carriage->pos];
		if (carriage->op > 0 && carriage->op <= 16)
		{
			carriage->rest = g_op[carriage->op - 1].period - 1;
		}
		else
		{
			carriage->op = 0;
			carriage->rest = 0;
		}
	}
	if (carriage->rest > 0)
		return ;
	operation = (carriage->op > 0) ? &g_op[carriage->op - 1] : NULL;
	if (operation)
	{
		//printf("pos = %i\n", carriage->id);
		tmp.arg_types[0] = (((uint8_t)g_game.field[carriage->pos] >> 6) & 0b11);
		tmp.arg_types[1] = (((uint8_t)g_game.field[carriage->pos] >> 4) & 0b11);
		tmp.arg_types[2] = (((uint8_t)g_game.field[carriage->pos] >> 2) & 0b11);
		printf("type = %i\n", tmp.arg_types[0]);

		// todo function arg_types parsing & validation
		// todo function args parsing & validation
		carriage->pos = read_values(&g_game, carriage, carriage->pos);
		operation->function(&g_game, carriage);
		carriage->pos += 7; // todo length estimation
	}
	else
		carriage->pos++;
}

t_list	*carriage_filter(t_list *lst)
{
	t_list		head;
	t_list		*prev;
	t_carriage	*carriage;

	head.next = lst;
	prev = &head;
	while (lst)
	{
		carriage = lst->content;
		if (carriage->live == 0)
		{
			prev->next = lst->next;
			ft_lstdelone(&lst, ft_lstrm);
			lst = prev->next;
		}
		else
		{
			prev = lst;
			lst = lst->next;
		}
	}
	return (head.next);
}

int		main(int ac, char **av)
{
	if (ac < 2)
	{
		ft_printf("%s\n", USAGE);
		return (1);
	}
	g_game = (t_game){.players = NULL, .survivor = NULL, .check_counter = 0,
			.check_period = CYCLE_TO_DIE, .check_amount = 0, .carriages = NULL,
			.cycle_counter = 0, .nbr_live = 0, .ch_count = 0};

	read_params(ac, av);

	ft_printf("Introducing\n");
	ft_lstiter(g_game.players, log_champion);

	ft_printf("Map creating\n");
	map_create(&g_game);
	//log_field(32);

	ft_printf("Game start\n");
/*
	// game loop
	while (g_game.carriages && ft_lstlen(g_game.carriages))
	{
		g_game.cycle_counter++;
		g_game.check_counter++;
		ft_lstiter(g_game.carriages, exec_function);
		if (g_game.check_counter >= g_game.check_period)
		{
			g_game.check_counter = 0;
			g_game.check_amount++;
			g_game.carriages = carriage_filter(g_game.carriages);
			if (g_game.check_amount == MAX_CHECKS || g_game.nbr_live >= NBR_LIVE)
				g_game.check_period -= (g_game.check_period > 0) ? CYCLE_DELTA : 0;
		}
	}

	//winner output
	error(g_game.survivor == NULL, ERR_WINNER_DISAPPEAR);
	ft_printf("[%s<%d> has won!]\n",
			g_game.survivor->header->prog_name, g_game.survivor->number);*/
	return (0);
}
