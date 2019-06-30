#include "functions.h"

void check_ch_process(t_core *core, t_champion *ch){
    t_vm_proc *temp;

    temp = ch->processes;
        while (temp != NULL){
        temp->cycles_for_operation -= 1;
        if (temp->cycles_for_operation == 0){
            core->oper[temp->next_operation_code].function(temp);
        } else if (temp->cycles_for_operation < 0){
            make_step(ch, &core);
        }
        temp = temp->next;
    }
}


