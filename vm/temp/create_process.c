/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_process.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akotilie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/06 14:05:14 by akotilie          #+#    #+#             */
/*   Updated: 2019/04/06 14:05:16 by akotilie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "functions.h"

void    create_pr(t_champion **ch, int *prm){ //prm : 0 - op code, 1 - cycles to execute , 2 - 1 param , 3 - sec param, 4 - 3 param 
    t_vm_proc *temp;

    temp = (t_vm_proc*)ft_memalloc(sizeof(t_vm_proc));
    temp->next_operation_code = prm[0];
    temp->cycles_for_operation = prm[1];
    temp->param_value1 = prm[2];
    temp->param_value2 = prm[3];
    temp->param_value3 = prm[4];
    temp->next = (*ch)->processes;
    (*ch)->processes = temp;
}
