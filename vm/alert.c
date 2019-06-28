/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alert.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkryvono <vkryvono@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/11 04:19:00 by vkryvono          #+#    #+#             */
/*   Updated: 2019/06/11 04:19:00 by vkryvono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	error(int trigger, char *msg)
{
	if (trigger)
	{
		ft_dprintf(2, "ERROR: %s\n", msg);
		exit(1);
	}
}

void	err_msg(int trigger, char *msg, char *var)
{
    if (trigger)
    {
        if (var != NULL)
            ft_dprintf(2, msg, var);
        else
            ft_dprintf(2, msg);
        exit(1);
    }
}

void	err_too_big_code(int trigger, char *msg, char *n, int s)
{
    if (trigger)
    {
        ft_dprintf(2, msg, n, s);
        exit(1);
    }
}

void	usage()
{
	ft_printf("%s\n", USAGE);
	exit(0);
}
