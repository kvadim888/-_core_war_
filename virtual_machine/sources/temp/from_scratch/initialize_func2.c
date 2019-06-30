
#include "functions.h"

void		init_and(t_core *core)
{
    (*core).oper[5].label = "and"; 
    //(*core).oper[5].function = &and;
    (*core).oper[5].cycle_value = 5;
    (*core).oper[5].dir_number = 4;
    (*core).oper[5].check = &c_r_ri;
}

void		init_or(t_core *core)
{
    (*core).oper[6].label = "or"; 
   // (*core).oper[6].function = &or;
    (*core).oper[6].cycle_value = 5;
    (*core).oper[6].dir_number = 4;
    (*core).oper[6].check = &c_r_ri;
}

void		init_xor(t_core *core)
{
    (*core).oper[7].label = "xor"; 
    //(*core).oper[7].function = &xor;
    (*core).oper[7].cycle_value = 5;
    (*core).oper[7].dir_number = 4;
    (*core).oper[7].check = &c_r_ri;
}

void		init_zjump(t_core *core)
{
    (*core).oper[8].label = "zjump"; 
    //(*core).oper[8].function = &zjump;
    (*core).oper[8].cycle_value = 5;
    (*core).oper[8].dir_number = 4;
    (*core).oper[8].check = &c_r_ri;
}

