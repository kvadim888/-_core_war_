/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_champs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akotilie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/28 20:37:11 by akotilie          #+#    #+#             */
/*   Updated: 2019/06/28 20:37:14 by akotilie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <functions.h>

void swap(t_list *a, t_list *b)
{
    t_champion	*champ;
    champ = a->content;
    a->content = b->content;
    b->content = champ;
}

void sort_chmps()
{
    int	swapped;
    t_champion *cht;
    t_champion *ncht;
    t_list	*tmp;
    t_list	*ltmp;

    ltmp = NULL;
    swapped = 1;
    while (swapped)
    {
        swapped = 0;
        tmp = g_game.players;
        while (tmp->next != ltmp)
        {
            cht = tmp->content;
            ncht = tmp->next->content;
            if (cht->number > ncht->number)
            {
                swap(tmp, tmp->next);
                swapped = 1;
            }
            tmp = tmp->next;
        }
        ltmp = tmp;
    }
}
