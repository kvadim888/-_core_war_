/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkryvono <vkryvono@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/11 01:42:00 by vkryvono          #+#    #+#             */
/*   Updated: 2019/06/11 01:42:00 by vkryvono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FUNCTIONS_H
# define FUNCTIONS_H

# include "../includes/vm.h"


extern const t_operation						g_op[16];

void	func_live(t_carriage *carriage);
void	func_zjmp(t_carriage *carriage);
void	func_aff(t_carriage *carriage);

void	func_ld(t_carriage *carriage);
void	func_lld(t_carriage *carriage);
void	func_ldi(t_carriage *carriage);
void	func_lldi(t_carriage *carriage);

void	func_st(t_carriage *carriage);
void	func_sti(t_carriage *carriage);

void	func_add(t_carriage *carriage);
void	func_sub(t_carriage *carriage);
void	func_and(t_carriage *carriage);
void	func_or(t_carriage *carriage);
void	func_xor(t_carriage *carriage);

void	func_fork(t_carriage *carriage);
void	func_lfork(t_carriage *carriage);

void	initialize_op();

#endif
