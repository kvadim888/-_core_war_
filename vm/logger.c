/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logger.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkryvono <vkryvono@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/11 01:42:00 by vkryvono          #+#    #+#             */
/*   Updated: 2019/06/11 01:42:00 by vkryvono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vm.h>

void	log_msg(char *msg)
{
	ft_printf("%s\n", msg);
}

void	log_champ(t_list *lst)
{
	t_champion	*champion;

	champion = lst->content;
	if (champion)
		ft_printf("* Player %d, weighing %d bytes, \"%s\" (\"%s\") !\n",
				  champion->number, champion->header->prog_size,
				  champion->header->prog_name, champion->header->comment);
}

