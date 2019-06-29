/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkryvono <vkryvono@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/22 19:03:00 by vkryvono          #+#    #+#             */
/*   Updated: 2019/06/22 19:03:00 by vkryvono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vm.h>

t_list		*carriage_filter(t_list *lst)
{
	t_list		head;
    t_list		*prev;
    t_carriage	*carriage;

    head.next = lst;
    prev = &head;
    while (lst)
    {
        carriage = lst->content;
        if (g_game.cycle_counter - carriage->live > g_game.check_period)
        {
            if (g_flag & FLAG_VERBOSE_8)
            	ft_printf("Process %d hasn't lived for %d cycles (CTD %d)\n",
            		carriage->id, g_game.cycle_counter - carriage->live,
            		g_game.check_period);
            if (head.next == lst)
				ft_lstcut(&head.next, prev, ft_lstrm);
            else
				ft_lstcut(&lst, prev, ft_lstrm);
        }
        else
        {
            prev = lst;
            lst = lst->next;
        }
    }
    return (head.next);
}

t_champion	*game_loop()
{
    while (g_game.carriages && ft_lstlen(g_game.carriages))
	{
        g_game.cycle_counter++;
        if (g_flag & FLAG_VERBOSE_2)
        	ft_printf("It is now cycle %d\n", g_game.cycle_counter);
        g_game.check_counter++;
		g_game.dump_counter++;
        ft_lstiter(g_game.carriages, exec_function);
        if (g_game.check_counter >= g_game.check_period)
        {
            g_game.check_counter = 0;
            g_game.check_amount++;
            g_game.carriages = carriage_filter(g_game.carriages);
            if (g_game.check_amount == MAX_CHECKS ||
                g_game.live_counter >= NBR_LIVE)
                g_game.check_period -= (g_game.check_period > 0)
                                        ? CYCLE_DELTA : 0;
        }
        if ((g_flag & FLAG_DUMP) && g_game.dump_counter >= g_game.dump_period)
        {
            log_field(32);
            exit(0);
        }
    }
    return (g_game.survivor);
}
