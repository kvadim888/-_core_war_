#include "functions.h"

int     make_step(t_champion ch, t_core *core, int p)
{
    printf("make_step\n");
    //ft_putnbr(ch.processes->next_operation_code);

    if (read_op_code(ch, core, p)){
       /*  write(1, "make_step 1\n", 13);
       ft_putnbr(ch->processes->next_operation_code);
        ft_putnbr(ch->processes->param_type_1);
        ft_putnbr(ch->processes->param_type_2);
        ft_putnbr(ch->processes->param_type_3);
        write(1, "\n", 1);*/
    }
    return (0);
}

void check_ch_process(t_core *core, t_champion ch){
    t_vm_proc *temp;

    temp = ch.processes;
    printf("ch.processes->carry %i\n", ch.processes->carry);
    while (temp != NULL){
        temp->cycles_for_operation -= 1;
        printf("cycles_for_operation %i\n", temp->cycles_for_operation);
        if (temp->cycles_for_operation == 0){
            core->oper[temp->next_operation_code].function(temp);
        } else if (temp->cycles_for_operation < 0){

            make_step(ch, core, temp->carry);
        }
        temp = temp->next;
    }
}

void cycle(t_core *core){
    int i;

    i = -1;
    while (++i < core->ch_number){
       check_ch_process(core, core->chmps[i]);
    }
    
}