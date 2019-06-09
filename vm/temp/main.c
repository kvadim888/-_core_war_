/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akotilie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/06 14:05:14 by akotilie          #+#    #+#             */
/*   Updated: 2019/04/06 14:05:16 by akotilie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "functions.h"

void		operation_initialize(t_core *core)
{
	init_live(core);
	init_ld(core);
	init_st(core);
    init_add(core);
    init_sub(core);
    init_and(core);
    init_or(core);
    init_xor(core);
    init_zjump(core);
}

int     make_step(t_champion *ch, t_core **core)
{
    write(1, "make_step 0\n", 13);
    ft_putnbr(ch->processes->next_operation_code);

    if (read_op_code(ch, core)){
        write(1, "make_step 1\n", 13);
        ft_putnbr(ch->processes->next_operation_code);
        ft_putnbr(ch->processes->param_type_1);
        ft_putnbr(ch->processes->param_type_2);
        ft_putnbr(ch->processes->param_type_3);
        write(1, "\n", 1);
    }
    return (0);
}


void    start_working_on_functions(t_core **core){
    t_champion *ch;
    t_vm_proc *temp;
    int i;

    write(1, "main 1\n", 7);
    operation_initialize(core); 
    write(1, "main 2\n", 7);
    ch = (t_champion*)ft_memalloc(sizeof(t_champion));
    ch->fd = open("test.cor", O_RDONLY);
    temp = (t_vm_proc*)ft_memalloc(sizeof(t_vm_proc));
    temp->cycles_for_operation = 0;
    ch->processes = temp;
    i = 0;
    write(1, "main 3\n", 7);
    while (i < 100)
    {
        write(1, "main 4\n", 7);

        check_ch_process(core, ch);  
        i++;
    }
}




int     main()
{   
    t_core *core; 
    core  = (t_core*)ft_memalloc(sizeof(t_core));
    
}
