#include "functions.h"

void    start_working_on_functions(t_core **core){
    t_champion *ch;
    t_vm_proc *temp;
    int i;

    operation_initialize(core); 
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

