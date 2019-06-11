/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkryvono <vkryvono@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/11 04:21:00 by vkryvono          #+#    #+#             */
/*   Updated: 2019/06/11 04:21:00 by vkryvono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int			is_number(char *str) //todo move to libft
{
	while (ft_iswhspace(*str))
		str++;
	while (ft_isdigit(*str))
		str++;
	while (ft_iswhspace(*str))
		str++;
	return (*str == '\0');
}
